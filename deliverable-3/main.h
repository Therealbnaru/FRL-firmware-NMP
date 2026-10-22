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
//schedular stuff
void run_scheduler(void);
void sample_sensor(void);
void calculate_telemetry(void);
void print_telemetry(void);
void run_state(void);

//Buffer Sensor
void push(const sensor_sample_s *sensor);
int pop(sensor_sample_s *sensor);

//Buffer Tele
void pusht(const telemetry_packet_s *telemetry);
int popt(telemetry_packet_s *telemetry);

    


void update_sensor_sample(sensor_sample_s *sensor);
void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry);
void run_rocket_state(const telemetry_packet_s *telemetry);

typedef enum
{
    FLIGHT_ASCENT,
    FLIGHT_COAST,
    FLIGHT_DESCENT,
    FLIGHT_LANDED
} rocket_state;
