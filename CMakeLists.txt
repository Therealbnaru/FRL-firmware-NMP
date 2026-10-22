cmake_minimum_required(VERSION 3.16)
project(frl_firmware_nmp LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(deliverable_1 deliverable-1/main.c)
add_executable(deliverable_2 deliverable-2/main.c)
add_executable(deliverable_3
    deliverable-3/main.c
    deliverable-3/timer.c
    deliverable-3/sensor_buffer.c
    deliverable-3/tele_buffer.c
    deliverable-3/sample_sensor.c
    deliverable-3/calculate_tele.c
    deliverable-3/print_telemetry.c
    deliverable-3/run_state.c
)

# Deliverable 1 uses fmax from the math library on Unix systems.
if(UNIX)
    target_link_libraries(deliverable_1 PRIVATE m)
endif()

foreach(target deliverable_1 deliverable_2 deliverable_3)
    if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic)
    elseif(MSVC)
        target_compile_options(${target} PRIVATE /W4)
    endif()
endforeach()
