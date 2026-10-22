#include "main.h"
#include <stdio.h>
#include "timer.h"


void run_schedular(void)
{
    static task_s tasks[4];
    tasks[0].run = sample_sensor;
    tasks[0].interval_ms = 100;
    tasks[1].run = calculate_telemetry;
    tasks[1].interval_ms = 200;
    tasks[2].run = print_telemetry;
    tasks[2].interval_ms = 500;
    tasks[3].run = run_state;
    tasks[3].interval_ms = 200;

    for (int x = 0; x < 4; x++)
    {
        uint32_t curr = get_ms();
        if (curr - tasks[x].t >= tasks[x].interval_ms)
        {
            tasks[x].t = curr;
            tasks[x].run();
        }
    }

}
void update_sensor_sample(sensor_sample_s *sensor)
{
    sensor->acceleration = -G;
    if (sensor->fuel > 0)
    {
        sensor->acceleration = THRUST - G;
        sensor->fuel--;
    }
    sensor->timestamp += TIME;
}

void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry)
{
    telemetry->sensor = *sensor;
    telemetry->velocity += sensor->acceleration * TIME;
    telemetry->altitude += telemetry->velocity * TIME;
}
static rocket_state state = FLIGHT_ASCENT;
void run_rocket_state(const telemetry_packet_s *telemetry)
{
    switch (state)
    {
        case FLIGHT_LANDED:
            break;

        case FLIGHT_COAST:
            if (telemetry->velocity <= 0)
            {
                state = FLIGHT_DESCENT;
            }
            break;
        case FLIGHT_DESCENT:
            if (telemetry->altitude <= 0)
            {
                state = FLIGHT_LANDED;
            }
            break;

        case FLIGHT_ASCENT:
            if (telemetry-> altitude <= 0 && telemetry->velocity <= 0)
            {
                state = FLIGHT_LANDED;
            }
            else if (telemetry-> velocity <= 0)
            {
                state = FLIGHT_DESCENT;
            }
            else if (telemetry->sensor.fuel == 0)
            {
                state = FLIGHT_COAST;
            }
            break;


    }

}
int main(void)
{
    sensor_sample_s sensor = {0};
    sensor.fuel = FUELI;
    telemetry_packet_s telemetry = {0};
    telemetry.velocity = VI;
    telemetry.altitude = ALTI;

    while (state != FLIGHT_LANDED)
    {
        update_sensor_sample(&sensor);
        update_telemetry_state(&sensor, &telemetry);
        run_rocket_state(&telemetry);
        printf("Time: %.2f s\n", sensor.timestamp);
        printf("Altitude: %.1f m\n", telemetry.altitude);
        printf("Velocity: %.1f m/s\n", telemetry.velocity);
        printf("Fuel: %d\n\n", sensor.fuel);
        printf("State: %d\n", state);
    }

}
