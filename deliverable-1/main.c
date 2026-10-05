#include <stdio.h>

int main(void)
{
    printf("Deliverable 1: rocket telemetry logger starter.\n");
    double altituide;
    double velocity;
    int Fuelsteps;
    double thrust;
    double time;
    int maxSteps;

    printf("Enter z0 (m): ");
    scanf("%lf", &altituide);

    printf("Enter velocity (m/s): ");
    scanf("%lf", &velocity);

    printf("Enter initial fuel (steps)");
    scanf("%d", &Fuelsteps);

    printf("Enter engine accel a_thrust(m/s^2)");
    scanf("%lf", &thrust);

    printf("Enter dt (s): ");
    scanf("%lf", &time);

    printf("Enter max steps");
    scanf("%d", &maxSteps);
    double altituideArr[maxSteps];

    return 0;
}
