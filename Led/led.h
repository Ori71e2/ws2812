#ifndef __LED_H
#define __LED_H

#include <stdint.h>
#include "delay.h"
#include "bitmap.h"
#include "ws2812b.h"

void led_Init(void);
int led_IsReady(void);
void led_Show_RGB(RGB_t *rgbLeds, uint32_t count);
void led_Show_HSV(HSV_t *hsvLeds, uint32_t count);
void led_Show_HEX(HEX_t *hexLeds, uint32_t count);
void led_Loop_Show_RGB(RGB_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime, uint32_t clickTimes);
void led_Loop_Show_HSV(HSV_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime, uint32_t clickTimes);
void led_Loop_Show_HEX(HEX_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime, uint32_t clickTimes);
void led_Gradual_Show_RGB(RGB_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime);
void led_Gradual_Show_HSV(HSV_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime);
void led_Gradual_Show_HEX(HEX_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime);
void led_Gradual_Cover_Show_RGB(RGB_t *source, RGB_t *end, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime);
void led_Shut_RGB(uint32_t count);
void led_Shut_HSV(uint32_t count);
void led_Shut_HEX(uint32_t count);
void led_Clear_RGB(RGB_t *rgbLeds, uint32_t count);
void led_Clear_HSV(HSV_t *hsvLeds, uint32_t count);
void led_Clear_HEX(HEX_t *hexLeds, uint32_t count);
RGB_t RGB(uint8_t r, uint8_t g, uint8_t b);
HSV_t HSV(uint8_t h, uint8_t s, uint8_t v);
#define HEX(hex) hex

void led_Bright_RGB(RGB_t *ledRgb, uint8_t bright);
void led_Bright_HSV(HSV_t *ledHsv, uint8_t bright);
void led_Bright_HEX(HEX_t *ledHex, uint8_t bright);

void led_Fill_Solid_RGB(RGB_t *start, uint32_t count, RGB_t color);
void led_Fill_Solid_HSV(HSV_t *start, uint32_t count, HSV_t color);
void led_Fill_Solid_HEX(HEX_t *start, uint32_t count, HEX_t color);

void led_Fill_Gradient_RGB(RGB_t *start, uint32_t count, RGB_t startColor, RGB_t endColor);
void led_Fill_Gradient_HSV(HSV_t *start, uint32_t count, HSV_t startColor, HSV_t endColor);
void led_Fill_Gradient_HEX(HEX_t *start, uint32_t count, HEX_t startColor, HEX_t endColor);

void led_Fill_Line_HEX(HEX_t *start, uint32_t count, HEX_t startColor, HEX_t endColor);

void led_Fill_Rainbow_HSV(HSV_t *start, uint32_t count, HSV_t startColor, HSV_t endColor);
void led_Fill_Rainbow_RGB(RGB_t *start, uint32_t count, RGB_t startColor, RGB_t endColor);
void led_Fill_Rainbow_HEX(HEX_t *start, uint32_t count, HEX_t startColor, HEX_t endColor);
// void led_Fill_Platte();
void led_SFill_RGB(RGB_t *ledRgb, RGB_t rgbColor);

#endif //__LED_H
