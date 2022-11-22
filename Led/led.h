#ifndef __LED_H
#define __LED_H

#include <stdint.h>
#include "delay.h"
#include "bitmap.h"
#include "ws2812b.h"

void led_Init(void);
int led_IsReady(void);
void led_Show_RGB(RGB_t *rgbLeds, unsigned count);
void led_Show_HSV(HSV_t *hsvLeds, unsigned count);
void led_Show_HEX(HEX_t *hexLeds, unsigned count);
void led_Loop_Show_RGB(RGB_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime, unsigned num);
void led_Loop_Show_HSV(HSV_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime, unsigned num);
void led_Loop_Show_HEX(HEX_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime, unsigned num);
void led_Gradual_Show_RGB(RGB_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime);
void led_Gradul_Show_HSV(HSV_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime);
void led_Gradul_Show_HEX(HEX_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime);
void led_Shut_RGB(unsigned count);
void led_Shut_HSV(unsigned count);
void led_Shut_HEX(unsigned count);
void led_Clear_RGB(RGB_t *rgbLeds, unsigned count);
void led_Clear_HSV(HSV_t *hsvLeds, unsigned count);
void led_Clear_HEX(HEX_t *hexLeds, unsigned count);
RGB_t RGB(uint8_t r, uint8_t g, uint8_t b);
HSV_t HSV(uint8_t h, uint8_t s, uint8_t v);
#define HEX(hex) hex

void led_Bright_RGB(RGB_t *ledRgb, uint8_t bright);
void led_Bright_HSV(HSV_t *ledHsv, uint8_t bright);
void led_Bright_HEX(HEX_t *ledHex, uint8_t bright);

void led_Fill_Solid_RGB(RGB_t *start, unsigned count, RGB_t color);
void led_Fill_Solid_HSV(HSV_t *start, unsigned count, HSV_t color);
void led_Fill_Solid_HEX(HEX_t *start, unsigned count, HEX_t color);

void led_Fill_Gradient_RGB(RGB_t *start, unsigned count, RGB_t startColor, RGB_t endColor);
void led_Fill_Gradient_HSV(HSV_t *start, unsigned count, HSV_t startColor, HSV_t endColor);
void led_Fill_Gradient_HEX(HEX_t *start, unsigned count, HEX_t startColor, HEX_t endColor);

void led_Fill_Line_HEX(HEX_t *start, unsigned count, HEX_t startColor, HEX_t endColor);

void led_Fill_Rainbow_HSV(HSV_t *start, unsigned count, HSV_t startColor, HSV_t endColor);
void led_Fill_Rainbow_RGB(RGB_t *start, unsigned count, RGB_t startColor, RGB_t endColor);
void led_Fill_Rainbow_HEX(HEX_t *start, unsigned count, HEX_t startColor, HEX_t endColor);
// void led_Fill_Platte();

#endif //__LED_H
