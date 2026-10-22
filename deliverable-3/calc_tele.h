#ifndef FRL_FIRMWARE_NMP_CALC_TELE_H
#define FRL_FIRMWARE_NMP_CALC_TELE_H

#include "main.h"

void calculate_telemetry(void);
void update_telemetry_state(const sensor_sample_s *sensor, telemetry_packet_s *telemetry);
const telemetry_packet_s *get_telemetry(void);

#endif
