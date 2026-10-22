# Deliverable 3: Cooperative Scheduler and Ring Buffers

The scheduler checks four tasks at 100 ms (sensor), 200 ms (calculation),
500 ms (printing), and 200 ms (flight state). Each task has its own source
and header file. Build and run the deliverable_3 target in CLion.

The sensor buffer discards its oldest sample when full. The calculation task
drains that buffer and pushes each result into the telemetry buffer, which
rejects new packets when full. The print task drains the telemetry buffer.
The state task reads the latest calculated telemetry separately.

The existing acceleration, fuel, velocity, altitude, and flight-state logic
is preserved. TIME remains the simulated seconds per sensor sample, so the
current TIME of 0.1 matches the 100 ms sensor interval. Timestamps still
advance by TIME; they do not yet measure actual elapsed time. The supplied
clock() timer is unchanged.

Still to do: test different task intervals and verify both buffer overflow
policies during scheduler runs. If the sensor interval changes, revisit TIME
and timestamp handling before treating the printed timestamps as elapsed time.
