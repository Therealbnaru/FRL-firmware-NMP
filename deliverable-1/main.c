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

    print("Enter z0 (m): ");
    scanf("%lf", &altituide);

    print("Enter velocity (m/s): ");
    scanf("%lf", &velocity);

    print("Enter initial fuel (steps)");
    scanf("%d", &Fuelsteps);

    print("Enter engine accel a_thrust(m/s^2)");
    scanf("%lf", &thrust);

    print("Enter dt (s): ");
    scanf("%lf", &time);

    print("Enter max steps");
    scanf("%d", &maxSteps);
    double altituideArr[maxSteps];

    return 0;
}
