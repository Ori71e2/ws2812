#ifndef __LED_H
#define __LED_H

#include <stdint.h>
#include "delay.h"
#include "bitmap.h"
#include "ws2812b.h"

void led_Init(void);
void led_Show_RGB(RGB_t *rgbLeds, unsigned count);
void led_Show_HSV(HSV_t *hsvLeds, unsigned count);
void led_Show_HEX(HEX_t *hexLeds, unsigned count);
void led_Clear_RGB(RGB_t *rgbLeds, unsigned count);
void led_Clear_HSV(HSV_t *hsvLeds, unsigned count);
void led_Clear_HEX(HEX_t *hexLeds, unsigned count);
RGB_t RGB(uint8_t r, uint8_t g, uint8_t b);
HSV_t HSV(uint8_t h, uint8_t s, uint8_t v);
#define HEX(hex) hex

#endif //__LED_H
