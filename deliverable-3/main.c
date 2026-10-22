#include "main.h"
#include "timer.h"
#include "sample_sensor.h"
#include "calc_tele.h"
#include "print_telemetry.h"
#include "run_state.h"

void run_scheduler(void)
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

int main(void)
{
    while (get_state() != FLIGHT_LANDED)
    {
        run_scheduler(); // Tasks run only when their intervals have elapsed.
    }

    print_telemetry(); // Prints any packets still waiting after landing.
    return 0;
}
