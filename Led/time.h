#ifndef __TIME_H
#define __TIME_H
#include <stdint.h>
typedef uint32_t (Delaytime_t)(uint32_t num, uint32_t length, uint32_t clickTimes, uint32_t time);

uint32_t delaytimeC(uint32_t num, uint32_t length, uint32_t clickTimes, uint32_t time);
uint32_t delaytimeAverage(uint32_t num, uint32_t length, uint32_t clickTimes, uint32_t time);

#endif

