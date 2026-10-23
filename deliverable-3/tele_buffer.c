//
// Created by Srilatha Kamasamudram on 10/22/26.
//
#include "main.h"

static telemetry_packet_s buffer[TELEMETRY_BUFFER];
static int head = 0;//changing
static int tail = 0;//old
static int count = 0;

void pusht(const telemetry_packet_s *telemetry)
{
    if (count == TELEMETRY_BUFFER)
    {
        return;
    }
    buffer[head] = *telemetry;
    head = (head + 1) % TELEMETRY_BUFFER;
    count++;
}

int popt(telemetry_packet_s *telemetry)
{
    if (count == 0)
    {
        return 0;
    }
    *telemetry = buffer[tail];
    tail = (tail + 1) % TELEMETRY_BUFFER;
    count--;

    return 1;

}