//
// Created by Srilatha Kamasamudram on 10/22/26.
//

#include "main.h"

static sensor_sample_s buffer[SENSOR_BUFFER];
static int head = 0;//changing
static int tail = 0;//old
static int count = 0;

void push(const sensor_sample_s *sensor)
{
    if (count == SENSOR_BUFFER)
    {
        tail = (tail + 1) % SENSOR_BUFFER; // wraps incase
        count--;
    }
    buffer[head] = *sensor;
    head = (head + 1) % SENSOR_BUFFER;
    count++;
}

int pop(sensor_sample_s *sensor)
{
    if (count == 0)
    {
        return 0;
    }

    *sensor = buffer[tail];
    tail = (tail + 1) % SENSOR_BUFFER; // mod wraps incase need
    count--;

    return 1;
}
