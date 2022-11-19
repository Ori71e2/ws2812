
#include <stdint.h>
#include "led.h"

void led_Init(void)
{
  ws2812b_Init();
}
int led_IsReady(void)
{
  return ws2812b_IsReady();
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
void led_Shut_RGB(RGB_t *rgbLeds, unsigned count)
{
	for (int i = 0; i < count; i++)
	{
		rgbLeds[i].r = 0;
		rgbLeds[i].g = 0;
		rgbLeds[i].b = 0;
	}
	led_Show_RGB(rgbLeds, count);
}

void led_Shut_HSV(HSV_t *hsvLeds, unsigned count)
{
	for (int i = 0; i < count; i++)
	{
		hsvLeds[i].h = 0;
		hsvLeds[i].s = 0;
		hsvLeds[i].v = 0;
	}
	led_Show_HSV(hsvLeds, count);
}

void led_Shut_HEX(HEX_t *hexLeds, unsigned count)
{
	for (int i = 0; i < count; i++)
	{
		hexLeds[i] = 0x000000;
	}
	 led_Show_HEX(hexLeds, count);
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

void led_Bright_RGB(RGB_t *ledRgb, uint8_t bright)
{
	HSV_t ledHsv;
	RGB2HSV(ledRgb, &ledHsv);
	ledHsv.v = bright;
	HSV2RGB(&ledHsv, ledRgb);
}

void led_Bright_HSV(HSV_t *ledHsv, uint8_t bright)
{
	ledHsv->v = bright;
}

void led_Bright_HEX(HEX_t *ledHex, uint8_t bright)
{
	HSV_t ledHsv;
	RGB_t ledRgb;
	HEX2RGB(*ledHex, &ledRgb);
	RGB2HSV(&ledRgb, &ledHsv);
	ledHsv.v = bright;
	HSV2RGB(&ledHsv, &ledRgb);
	RGB2HEX(&ledRgb, ledHex);
}

void led_Fill_Solid_RGB(RGB_t *start, unsigned count, RGB_t color)
{
	for ( ; count > 0; count--)
	{
		start->r = color.r;
		start->g = color.g;
		start->b = color.b;
		start++;
	}
}

void led_Fill_Solid_HSV(HSV_t *start, unsigned count, HSV_t color)
{
	for ( ; count > 0; count--)
	{
		start->h = color.h;
		start->s = color.s;
		start->v = color.v;
		start++;
	}
}

void led_Fill_Solid_HEX(HEX_t *start, unsigned count, HEX_t color)
{
	for ( ; count > 0; count--)
	{
		*start = color;
		start++;
	}
}

void led_Fill_Gradient_RGB(RGB_t *start, unsigned count, RGB_t startColor, RGB_t endColor)
{
	int32_t r, g, b;
	for (int32_t i = 1; i < count - 1; i++)
	{
		r = ((int32_t)(startColor.r) + ((int32_t)endColor.r - (int32_t)startColor.r) * i / ((int32_t)count - 1));
		g = ((int32_t)(startColor.g) + ((int32_t)endColor.g - (int32_t)startColor.g) * i / ((int32_t)count - 1));
		b = ((int32_t)(startColor.b) + ((int32_t)endColor.b - (int32_t)startColor.b) * i / ((int32_t)count - 1));
		(start + i)->r = (uint8_t)(r);
		(start + i)->g = (uint8_t)(g);
		(start + i)->b = (uint8_t)(b);
	}
	start->r = startColor.r;
	start->g = startColor.g;
	start->b = startColor.b;
	(start + count - 1)->r = endColor.r;
	(start + count - 1)->g = endColor.g;
	(start + count - 1)->b = endColor.b;
}

void led_Fill_Gradient_HEX(HEX_t *start, unsigned count, HEX_t startColor, HEX_t endColor)
{
	int32_t gap;
	gap = endColor - startColor;
	for (int32_t i = 1; i < count - 1; i++)
	{
		*(start + i) = (uint32_t)((int32_t)startColor + ((int32_t)endColor - (int32_t)startColor) / ((int32_t)count - 1) * i);
	}
	*start = startColor;
	*(start + count - 1) = endColor;
}
