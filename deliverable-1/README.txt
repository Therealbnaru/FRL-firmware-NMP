Deliverable 1: Rocket Telemetry Logger
Status: Not implemented

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
[To complete]

Screenshot of the model working:
[Save in screenshots/ and enter its filename here]

Suggested checks (not additional assignment requirements):
- Normal launch with thrust greater than gravity.
- Thrust below gravity, starting on the ground.
- No initial fuel.
- Maximum step limit reached before touchdown.
- Invalid input, nonpositive dt, and nonpositive max_steps.

The handout's example output is a sketch; verify against the specified update order.
