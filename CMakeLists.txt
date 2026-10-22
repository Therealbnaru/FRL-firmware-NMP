cmake_minimum_required(VERSION 3.16)
project(frl_firmware_nmp LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(deliverable_1 deliverable-1/main.c
        deliverable-3/timer.h
        deliverable-3/timer.c
        deliverable-3/flight_config.h
        deliverable-3/main.h
        deliverable-3/main.c
        deliverable-3/sensor_buffer.c
        deliverable-3/tele_buffer.c
)
add_executable(deliverable_2 deliverable-2/main.c
        deliverable-3/main.h
        deliverable-3/main.c
        deliverable-3/tele_buffer.c)

if(CMAKE_C_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(deliverable_1 PRIVATE -Wall -Wextra -Wpedantic)
    target_compile_options(deliverable_2 PRIVATE -Wall -Wextra -Wpedantic)
elseif(MSVC)
    target_compile_options(deliverable_1 PRIVATE /W4)
    target_compile_options(deliverable_2 PRIVATE /W4)
endif()
