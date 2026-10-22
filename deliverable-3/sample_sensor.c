#include <stdio.h>
#include "sample_sensor.h"

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

void sample_sensor(void)
{
    static sensor_sample_s sensor = {0, FUELI, 0}; // Keeps fuel and time between runs.

    update_sensor_sample(&sensor);
    push(&sensor); // Saves a copy for the calculation task.
    printf("Sensor task ran\n");
}
