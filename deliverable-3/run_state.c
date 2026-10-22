#include <stdio.h>
#include "run_state.h"
#include "calc_tele.h"

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

void run_state(void)
{
    const telemetry_packet_s *telemetry = get_telemetry();

    if (telemetry->sensor.timestamp > 0)
    {
        run_rocket_state(telemetry);
    }

    printf("State: %d\n", state);
}

rocket_state get_state(void)
{
    return state;
}
