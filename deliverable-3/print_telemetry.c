#include <stdio.h>
#include "main.h"
#include "print_telemetry.h"
#include "timer.h"

void print_telemetry(void)
{
    telemetry_packet_s telemetry;

    printf("Print task ran\n");

    while (popt(&telemetry))
    {
        printf("Elapsed time: %.2f s\n", get_ms() / 1000.0);
        printf("Time: %.2f s\n", telemetry.sensor.timestamp);
        printf("Altitude: %.1f m\n", telemetry.altitude);
        printf("Velocity: %.1f m/s\n", telemetry.velocity);
        printf("Fuel: %d\n\n", telemetry.sensor.fuel);
    }
}
