
#include <stdint.h>
#include "led.h"

void led_Init(void)
{
  ws2812b_Init();
}

void led_Add(void)
{

}
// show all
void led_Show_RGB(RGB_t *rgbLeds, unsigned count)
{
  ws2812b_SendRGB(rgbLeds, count);
}

void led_Show_HSV(HSV_t *hsvLeds, unsigned count)
{
  ws2812b_SendHSV(hsvLeds, count);
}

void led_Show_HEX(HEX_t *hexLeds, unsigned count)
{
  ws2812b_SendHEX(hexLeds, count);
}
// clear all
void led_Clear_RGB(RGB_t *rgbLeds, unsigned count)
{
	for (int i = 0; i < count; i++)
	{
		rgbLeds[i].r = 0;
		rgbLeds[i].g = 0;
		rgbLeds[i].b = 0;
	}
}

void led_Clear_HSV(HSV_t *hsvLeds, unsigned count)
{
	for (int i = 0; i < count; i++)
	{
		hsvLeds[i].h = 0;
		hsvLeds[i].s = 0;
		hsvLeds[i].v = 0;
	}
}

void led_Clear_HEX(HEX_t *hexLeds, unsigned count)
{
	for (int i = 0; i < count; i++)
	{
		hexLeds[i] = 0x000000;
	}
}

RGB_t RGB(uint8_t r, uint8_t g, uint8_t b)
{
  RGB_t tmp = { r, g, b };
  return tmp;
}

HSV_t HSV(uint8_t h, uint8_t s, uint8_t v)
{
  HSV_t tmp = { h, s, v };
  return tmp;
}

void led_Bright_RGB(RGB_t *led, uint8_t bright)
{
	
}


void led_Bright_HEX(HEX_t *led)
{

}
