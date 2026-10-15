#include <stdint.h>


#define ALTI 0.0
#define VI 0.0
#define FUELI 50
#define THRUST 15.0
#define TIME 0.1
#define G 9.81
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
