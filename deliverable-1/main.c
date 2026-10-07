#include <stdio.h>
#include <tgmath.h>

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
    printf("Enter initial fuel (steps): ");
    scanf("%d", &Fuelsteps);
    printf("Enter engine accel a_thrust(m/s^2): ");
    scanf("%lf", &thrust);
    printf("Enter dt (s): ");
    scanf("%lf", &time);
    printf("Enter max steps: ");
    scanf("%d", &maxSteps);
    double altituideArr[maxSteps];

    int currSteps = 0;
    double netAccel = 0;
    double maxAlt = altituide;
    //Loop ends when alt is < 0 or max step count is reached
    while(currSteps < maxSteps && (currSteps == 0 || altituide > 0 || velocity > 0))
    {
        netAccel = -9.81;
        if(Fuelsteps > 0)
        {
            netAccel = thrust - 9.81;
            Fuelsteps--;
        }
        velocity = velocity + netAccel*time;
        altituide = altituide + velocity*time;
        altituideArr[currSteps] = altituide;
        maxAlt = fmax(maxAlt, altituide);
        currSteps++;

    }
    if (altituide < 0)
    {
        altituide = 0;
        altituideArr[currSteps - 1] = 0;

    }

    printf("Rocket Telemetry: ");
    printf("Steps %d\n", currSteps);
    printf("Total time: %.1f s\n", currSteps* time);
    printf("Max altituide %.1f m\n", maxAlt);
    printf("Final altituide %.1f m\n", altituide);
    printf("Final velocity %.1f m/s\n", velocity);
    printf("Fuel remaining %d\n", Fuelsteps);
    printf("Altitude history: ");
    for (int x = 0; x < currSteps - 1; x++)
    {
        printf("%.2f, ", altituideArr[x]);
    }

    return 0;
}
