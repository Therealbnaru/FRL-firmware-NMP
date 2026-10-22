#ifndef FRL_FIRMWARE_NMP_RUN_STATE_H
#define FRL_FIRMWARE_NMP_RUN_STATE_H

#include "main.h"

void run_state(void);
void run_rocket_state(const telemetry_packet_s *telemetry);
rocket_state get_state(void);

#endif
