Deliverable 2: Telemetry with Pointers and Structs
Status: Not implemented

Write your own 2-3 sentences for each section:

update_sensor_sample:
Establish net accel. Check weather fuel is remaining and subtract a fuel step if it does exist and modify accleration
based on thrust. I also update the time at the end so the timestep increases, we do-so with a pointer
to change the structs attributes.

update_telemetry_state:
Copy the sensor readings into the one embeded within telemetry struct. Update velocity and altiuide in that order.

run_rocket_state:
Use a switch statement to check which state the flight currently exists in, at each step decide weather state needs to be changed
.State exists between all functions.

Main loop:
Init sensor and telemetry structs using constants temporary, then updates avaible ones with the default macros. Then
loops and calls functions in a specfic order so all attributes are updated correctly. Prints each
timestep out for validation.
