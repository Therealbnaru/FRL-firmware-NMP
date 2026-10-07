Deliverable 1: Rocket Telemetry Logger
Status: Completed

Required behavior:
- Read z0, v0, initial fuel in steps, engine acceleration, dt, and max_steps.
- Use gravity = 9.81 m/s^2.
- While fuel is available, acceleration = engine acceleration - gravity.
- Otherwise, acceleration = -gravity.
- Update velocity first: v = v + a * dt.
- Update altitude second: z = z + v * dt.
- Consume fuel if thrusting, and save each updated altitude in the history array.
- Stop on z <= 0 and v <= 0 after at least one step, or at max_steps.
- Print total time/steps, maximum altitude, final altitude/velocity, remaining fuel,
  and altitude history (all values or every Nth value).
- Size the history array to accommodate the user-selected maximum steps.

Chosen inputs and explanation (write your own 2-3 sentences):
I used the same inputs provided in the assignment’s example sketch so I could compare my outputs to the assignment's and check whether the simulation worked accurately. Specifically, I chose a starting altitude and velocity of 0, an engine acceleration of 15 m/s^2, 50 fuel steps, thrust for 5 seconds, a total max time of 30 seconds, with a .1 second time step. This let me verify the simulation worked during a full flight where the rocket ascends, runs out of fuel, and falls back down.

Screenshot of the model working:
https://github.com/Therealbnaru/FRL-firmware-NMP/blob/main/deliverable-1/screenshots/Screenshot%202026-10-07%20013704.png

Suggested checks (not additional assignment requirements):
- Normal launch with thrust greater than gravity.
- Thrust below gravity, starting on the ground.
- No initial fuel.
- Maximum step limit reached before touchdown.
- Invalid input, nonpositive dt, and nonpositive max_steps.

The handout's example output is a sketch; verify against the specified update order.
