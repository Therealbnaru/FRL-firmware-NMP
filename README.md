# FRL Firmware New Member Project

Bhuvan Naru • Florida Rocket Lab • Fall 2026

Personal coursework repository for the Firmware New Member Project. This is a starter workspace; the simulation and driver logic are not implemented yet.

## Deliverables

| Folder | Assignment | Mentor meeting |
| --- | --- | --- |
| `deliverable-1/` | Rocket telemetry logger | October 8–9 |
| `deliverable-2/` | Telemetry with pointers, structs, and functions | October 15–16 |
| `deliverable-3/` | Cooperative scheduler (instructions pending) | October 22–23 |
| `deliverable-4/` | STM32 HAL I2C sensor driver (instructions pending) | October 29–30; final November 5–6 |

Schedule each meeting by Wednesday night and submit at least 30 minutes before the meeting. Dates are from the Fall 2026 handout.

## Open in CLion

Open this repository's root folder as a project. Let CLion load `CMakeLists.txt`, select `deliverable_1` or `deliverable_2`, then run it. Both currently print a starter message.

With CMake installed, a terminal build is also available:

```sh
cmake -S . -B build
cmake --build build
```

## Workflow

1. Implement the current deliverable in its folder.
2. Run it with several inputs and review the results.
3. Save screenshots in that deliverable's `screenshots/` folder.
4. Replace the prompts in `README.txt` with your own explanations.
5. Commit your work and share the repository with your mentor.

Keep each deliverable independent so earlier submissions remain reviewable. Detailed requirements for deliverables 3 and 4 must be added when FRL supplies them.
