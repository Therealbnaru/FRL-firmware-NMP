# Florida Rocket Lab Firmware New Member Project

Fall 2026 · Florida Rocket Lab

We built a one-dimensional telemetry simulator in C, split it into sampling, calculation, and flight-state functions, then scheduled those functions independently using ring buffers. The final deliverable applies the same producer–consumer pattern on an STM32, where simulated acceleration gives way to three-axis measurements from an ADXL343.

| Deliverable | What we built |
| --- | --- |
| [1. Rocket Telemetry Logger](deliverable-1/) | An interactive simulation that records altitude and summarizes a flight |
| [2. Telemetry with Pointers and Structs](deliverable-2/) | A fixed-step simulator with structured data and a flight state machine |
| [3. Cooperative Scheduler and Ring Buffers](deliverable-3/) | Independently scheduled sampling, calculation, printing, and state updates |
| [4. STM32 Flight Computer Firmware](deliverable-4/ButtonLED/) | An ADXL343 sampling, threshold, and USB logging pipeline with remaining hardware bring-up work |

## Deliverable 1 · Rocket Telemetry Logger

The program asks for initial altitude and velocity, fuel in simulation steps, engine acceleration, the time step, and a maximum step count. It models only vertical motion. Each powered step consumes one unit of fuel and uses engine acceleration minus gravity. Once the fuel is gone, acceleration is −9.81 m/s². The loop updates velocity first and uses that new velocity to update altitude.

We stored altitude after each update and tracked the peak as the simulation ran. The loop ends at ground contact or at the step limit. The program clamps a below-ground final altitude to zero, retains the final velocity, and prints elapsed time, peak altitude, remaining fuel, and altitude history. The history print loop omits the final recorded entry.

For the example case, enter **0, 0, 50, 15, 0.1, 300** in prompt order. Starting from rest with five simulated seconds of thrust makes it possible to observe powered ascent, coast, and descent in one run. This case reached **99.2 m**, ended after **121 steps (12.1 s)**, and reported a final velocity of **−43.7 m/s**. See the [original run screenshot](deliverable-1/screenshots/Screenshot%202026-10-07%20013704.png).

## Deliverable 2 · Telemetry with Pointers and Structs

We kept the same physics and moved the initial conditions into macros in [main.h](deliverable-2/main.h). A `sensor_sample_s` holds acceleration, fuel, and time. A `telemetry_packet_s` embeds that sample alongside velocity and altitude so each packet preserves the input used for its calculation.

| Function | Role and design |
| --- | --- |
| `update_sensor_sample` | Takes a writable pointer to the sample and updates it in place. It selects powered or gravity-only acceleration, decrements fuel during a powered step, and advances the timestamp. |
| `update_telemetry_state` | Reads the sample through a `const` pointer and updates the packet through a writable pointer. It copies the sample into the packet and integrates acceleration into velocity before integrating velocity into altitude. |
| `run_rocket_state` | Reads the current packet and uses a switch to update a file-local state that persists across calls. Fuel exhaustion during upward motion starts coast, nonpositive velocity marks descent, and reaching the ground marks landing. |
| `main` | Initializes the sample and packet, then runs sampling, calculation, and state evaluation in that order. Each iteration prints the new telemetry and numeric state, including the final landed iteration. |

The state enum is ordered **ascent (0) → coast (1) → descent (2) → landed (3)** for the default inputs. The ascent branch can also transition directly to descent or landed if its velocity and altitude checks take precedence over the fuel check. The final sample in the default run shows about **−0.3 m** because the integration step crosses ground level before the landing check.

## Deliverable 3 · Cooperative Scheduler and Ring Buffers

In [main.c](deliverable-3/main.c), each task has a function pointer, a period, and a stored last-run time. The scheduler polls the timer and calls each due function in order. Tasks run to completion, so any slow task can delay the next one. The desktop timer wraps C's `clock()`, which measures process CPU time. The periods below are therefore measured against that clock.

| Task | Period | Work |
| --- | ---: | --- |
| `sample_sensor` | 100 ms | Updates simulated fuel and acceleration, timestamps the sample, and queues it. |
| `calculate_telemetry` | 200 ms | Drains pending samples in order and integrates using the difference between successive timestamps. Queues a packet for each processed sample. |
| `print_telemetry` | 500 ms | Drains queued packets and prints sample time, elapsed timer value, altitude, velocity, and fuel. |
| `run_state` | 200 ms | Reads the latest computed packet directly and updates flight state after the first valid sample. |

Both FIFO queues use a fixed 10-entry array, a head for the next write, a tail for the oldest entry, and a count to distinguish full from empty. The [sensor buffer](deliverable-3/sensor_buffer.c) evicts its oldest sample when full, keeping recent inputs available to the calculator. The [telemetry buffer](deliverable-3/tele_buffer.c) drops incoming packets when full, preserving the earlier records already waiting to print. The state task can still see the latest calculation even if its packet was dropped from the print queue. When the state reaches landed, `main` drains any remaining print packets and exits.

## Deliverable 4 · STM32 and ADXL343

The target is a WeAct Black Pill V2.0 with an STM32F411CEU6 and an ADXL343 accelerometer. The [CubeMX configuration](deliverable-4/ButtonLED/FirmwareNMPFinal.ioc) and [PlatformIO settings](deliverable-4/ButtonLED/platformio.ini) accompany the [application code](deliverable-4/ButtonLED/main.c). The application initializes HAL, GPIO, USB CDC, and I²C1. It uses the HAL millisecond tick to schedule work in the main loop.

- **Button and sampling.** The loop polls the pulled-up user button and accepts a changed state after 50 ms of stability. Each accepted press toggles sampling, which starts disabled. Every 100 ms, the sampling task checks that flag and attempts an I²C read when enabled.
- **I²C data acquisition.** `read_accel` reads six consecutive bytes starting at register `0x32` using the shifted HAL address `0x53 << 1`. It combines the low and high bytes of each axis into a signed 16-bit reading. Successful reads enter the sensor queue. Failed reads skip the enqueue.
- **Processing and LED output.** Every 300 ms, the processing task drains the sensor queue and uses the newest sample for the threshold decision. It divides each axis by 256 and computes the Euclidean magnitude, √(x² + y² + z²), using the scaled axes. The source compares that value with `USERG` (10.0) and drives PC13 high above the threshold and low otherwise. The visible LED behavior depends on board polarity.
- **USB telemetry.** Every 300 ms, the print task drains its queue and prints the newest available sample as raw X, Y, and Z counts plus the calculated magnitude in g. Both firmware queues have ten entries and overwrite their oldest entry when full. The current processing loop skips the first popped sample when a batch contains multiple samples and can enqueue the newest sample twice. The print task still selects the newest available value.
- **Output timing.** The `_write` hook redirects `printf` to USB CDC. It retries until USB accepts the transmission, so stalled USB output can delay sampling and other tasks in the same loop.

### Hardware bring-up status

The button toggles the firmware's sampling flag. The ADXL343 measurement-mode write is currently commented out, so the checked-in startup sequence does not enable measurement mode. The 256 counts/g conversion also assumes a compatible sensor configuration. Verify measurement mode, scale, and LED polarity on the board before treating the threshold output as a hardware result.

The checked-in STM32 folder contains the application, `.ioc`, PlatformIO settings, and formatting script. A build requires generating the CubeMX support files and reconciling the paths in `platformio.ini` with the generated project. For example, the configuration expects the app under `Src` and the pre-build script under `scripts`, while the repository stores both files at the project root. The configuration specifies DFU upload. Build, flash, and sensor output have not been verified for this revision.

## Build and run the desktop deliverables

From the repository root, use CMake 3.16 or newer and a C11 compiler with variable-length array support, such as GCC or Clang.

```sh
cmake -S . -B build
cmake --build build
./build/deliverable_1
./build/deliverable_2
./build/deliverable_3
```

Deliverable 1 prompts for input. Deliverables 2 and 3 use their source-defined defaults and stop when the simulated flight reaches the landed state. The STM32 project has its own PlatformIO configuration.
