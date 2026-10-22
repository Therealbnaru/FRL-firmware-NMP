#include <stdio.h>
#include "sample_sensor.h"
#include "timer.h"

void update_sensor_sample(sensor_sample_s *sensor)
{
    sensor->acceleration = -G;
    if (sensor->fuel > 0)
    {
        sensor->acceleration = THRUST - G;
        sensor->fuel--;
    }
    sensor->timestamp = get_ms()/1000.0;
}

void sample_sensor(void)
{
    static sensor_sample_s sensor = {0, FUELI, 0};
    update_sensor_sample(&sensor);
    push(&sensor);
    printf("Sensor task ran\n");
}
