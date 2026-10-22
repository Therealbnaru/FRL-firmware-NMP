#include <stdio.h>
#include "calc_tele.h"

static telemetry_packet_s telemetry = {{0}, VI, ALTI};

void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry)
{
    double t = sensor->timestamp - telemetry->sensor.timestamp;
    telemetry->velocity += sensor->acceleration * t;
    telemetry->altitude += telemetry->velocity * t;
    telemetry->sensor = *sensor;

}

void calculate_telemetry(void)
{
    sensor_sample_s sensor;

    while (pop(&sensor))
    {
        update_telemetry_state(&sensor, &telemetry);
        pusht(&telemetry);
    }

    printf("Calculate task ran\n");
}

const telemetry_packet_s *get_telemetry(void)
{
    return &telemetry;
}
