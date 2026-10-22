#include <stdio.h>
#include "calc_tele.h"

static telemetry_packet_s telemetry = {{0}, VI, ALTI}; // Keeps the latest motion state.

void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry)
{
    telemetry->sensor = *sensor;
    telemetry->velocity += sensor->acceleration * TIME;
    telemetry->altitude += telemetry->velocity * TIME;
}

void calculate_telemetry(void)
{
    sensor_sample_s sensor;

    while (pop(&sensor)) // Processes every available sensor sample.
    {
        update_telemetry_state(&sensor, &telemetry);
        pusht(&telemetry); // Saves each result for the print task.
    }

    printf("Calculate task ran\n");
}

const telemetry_packet_s *get_telemetry(void)
{
    return &telemetry; // Lets the state task read the latest result without consuming the print buffer.
}
