#ifndef FRL_FIRMWARE_NMP_MAIN_H
#define FRL_FIRMWARE_NMP_MAIN_H

#include <stdint.h>
#include "flight_config.h"

typedef struct
{
    void (*run)(void);
    uint32_t interval_ms;
    uint32_t t;
} task_s;

typedef struct
{
    double acceleration;
    uint16_t fuel;
    float timestamp;
} sensor_sample_s;

typedef struct
{
    sensor_sample_s sensor;
    double velocity;
    double altitude;
} telemetry_packet_s;

typedef enum
{
    FLIGHT_ASCENT,
    FLIGHT_COAST,
    FLIGHT_DESCENT,
    FLIGHT_LANDED
} rocket_state;

void run_scheduler(void);

// Sensor ring buffer: discards the oldest sample when full.
void push(const sensor_sample_s *sensor);
int pop(sensor_sample_s *sensor);

// Telemetry ring buffer: rejects new packets when full.
void pusht(const telemetry_packet_s *telemetry);
int popt(telemetry_packet_s *telemetry);

#endif
