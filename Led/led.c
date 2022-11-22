
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

void led_Loop_Show_RGB(RGB_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime, unsigned num)
{
	RGB_t rgbStart[count];
	int i = offset;
	int clickTimes = count * num;
	led_Clear_RGB(rgbStart, count);
	while(clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			(rgbStart + (i + j - 1) % count)->r = (start + (i + j - 1) % count)->r;
			(rgbStart + (i + j - 1) % count)->g = (start + (i + j - 1) % count)->g;
			(rgbStart + (i + j - 1) % count)->b = (start + (i + j - 1) % count)->b;	
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		for (int j = 0; j < length; j++)
		{
			(rgbStart + (i + j - 1) % count)->r = 0;
			(rgbStart + (i + j - 1) % count)->g = 0;
			(rgbStart + (i + j - 1) % count)->b = 0;	
		}
		i += length;
	}
}
void led_Gradual_Show_RGB(RGB_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime)
{
	RGB_t rgbStart[count];
	int i = offset;
	int clickTimes = count * 1;
	led_Clear_RGB(rgbStart, count);
	while(clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			(rgbStart + (i + j - 1) % count)->r = (start + (i + j - 1) % count)->r;
			(rgbStart + (i + j - 1) % count)->g = (start + (i + j - 1) % count)->g;
			(rgbStart + (i + j - 1) % count)->b = (start + (i + j - 1) % count)->b;	
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		i += length;
	}
}

void led_Loop_Show_HSV(HSV_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime, unsigned num)
{
	RGB_t rgbStart[count];
	int i = offset;
	HSV_t tmp = HSV(0, 0, 0);
	int clickTimes = count * num;
	led_Clear_RGB(rgbStart, count);
	while(clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			 HSV2RGB((start + (i + j - 1) % count), rgbStart + (i + j - 1) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		for (int j = 0; j < length; j++)
		{
			HSV2RGB(&tmp, rgbStart + (i + j - 1) % count);
		}
		i += length;
	}
}

void led_Gradul_Show_HSV(HSV_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime)
{
	RGB_t rgbStart[count];
	int i = offset;
	HSV_t tmp = HSV(0, 0, 0);
	int clickTimes = count * 1;
	led_Clear_RGB(rgbStart, count);
	while(clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			 HSV2RGB((start + (i + j - 1) % count), rgbStart + (i + j - 1) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		i += length;
	}
}

void led_Loop_Show_HEX(HEX_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime, unsigned num)
{
	RGB_t rgbStart[count];
	int i = offset;
	int clickTimes = count * num;
	led_Clear_RGB(rgbStart, count);
	while(clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			 HEX2RGB(*(start + (i + j - 1) % count), rgbStart + (i + j - 1) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		for (int j = 0; j < length; j++)
		{
			 HEX2RGB(HEX(0x000000), rgbStart + (i + j - 1) % count);
		}
		i += length;
	}
}

void led_Gradul_Show_HEX(HEX_t *start, unsigned count, unsigned offset, unsigned length, unsigned delayTime)
{
	RGB_t rgbStart[count];
	int i = offset;
	int clickTimes = count * 1;
	led_Clear_RGB(rgbStart, count);
	while(clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			 HEX2RGB(*(start + (i + j - 1) % count), rgbStart + (i + j - 1) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		i += length;
	}
}

// clear all
void led_Shut_RGB(unsigned count)
{
	RGB_t rgbLeds[count];
	for (int i = 0; i < count; i++)
	{
		rgbLeds[i].r = 0;
		rgbLeds[i].g = 0;
		rgbLeds[i].b = 0;
	}
	led_Show_RGB(rgbLeds, count);
}

void led_Shut_HSV(unsigned count)
{
	HSV_t hsvLeds[count];
	for (int i = 0; i < count; i++)
	{
		hsvLeds[i].h = 0;
		hsvLeds[i].s = 0;
		hsvLeds[i].v = 0;
	}
	led_Show_HSV(hsvLeds, count);
}

void led_Shut_HEX(unsigned count)
{
	HEX_t hexLeds[count];
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

void led_Fill_Gradient_HSV(HSV_t *start, unsigned count, HSV_t startColor, HSV_t endColor)
{
	RGB_t rgbStart[count];
	RGB_t rgbStartColor;
	RGB_t rgbEndColor;
	HSV2RGB(&startColor, &rgbStartColor);
	HSV2RGB(&endColor, &rgbEndColor);
	led_Fill_Gradient_RGB(rgbStart, count, rgbStartColor, rgbEndColor);
	for (int i = 1; i < count - 1; i++)
	{
		RGB2HSV((rgbStart+i), (start + i));
	}
	start->h = startColor.h;
	start->s = startColor.s;
	start->v = startColor.v;
	(start + count - 1)->h = endColor.h;
	(start + count - 1)->s = endColor.s;
	(start + count - 1)->v = endColor.v;
}

void led_Fill_Gradient_HEX(HEX_t *start, unsigned count, HEX_t startColor, HEX_t endColor)
{
	RGB_t rgbStart[count];
	RGB_t rgbStartColor;
	RGB_t rgbEndColor;
	HEX2RGB(startColor, &rgbStartColor);
	HEX2RGB(endColor, &rgbEndColor);
	led_Fill_Gradient_RGB(rgbStart, count, rgbStartColor, rgbEndColor);
	for (int i = 1; i < count - 1; i++)
	{
		RGB2HEX(&rgbStart[i], (start + i));
	}
	start[0] = startColor;
	start[count - 1] = endColor;
}

void led_Fill_Line_HEX(HEX_t *start, unsigned count, HEX_t startColor, HEX_t endColor)
{
	for (int32_t i = 1; i < count - 1; i++)
	{
		*(start + i) = (uint32_t)((int32_t)startColor + ((int32_t)endColor - (int32_t)startColor) / ((int32_t)count - 1) * i);
	}
	*start = startColor;
	*(start + count - 1) = endColor;
}

void led_Fill_Rainbow_HSV(HSV_t *start, unsigned count, HSV_t startColor, HSV_t endColor)
{
	int32_t h, s, v;
	for (int32_t i = 1; i < count - 1; i++)
	{
		h = ((int32_t)(startColor.h) + ((int32_t)endColor.h - (int32_t)startColor.h) * i / ((int32_t)count - 1));
		s = ((int32_t)(startColor.s) + ((int32_t)endColor.s - (int32_t)startColor.s) * i / ((int32_t)count - 1));
		v = ((int32_t)(startColor.v) + ((int32_t)endColor.v - (int32_t)startColor.v) * i / ((int32_t)count - 1));
		(start + i)->h = (uint8_t)(h);
		(start + i)->s = (uint8_t)(s);
		(start + i)->v = (uint8_t)(v);
	}
	start->h = startColor.h;
	start->s = startColor.s;
	start->v = startColor.v;
	(start + count - 1)->h = endColor.h;
	(start + count - 1)->s = endColor.s;
	(start + count - 1)->v = endColor.v;
}

void led_Fill_Rainbow_RGB(RGB_t *start, unsigned count, RGB_t startColor, RGB_t endColor)
{
	HSV_t hsvStart[count];
	HSV_t hsvStartColor;
	HSV_t hsvEndColor;
	RGB2HSV(&startColor, &hsvStartColor);
	RGB2HSV(&endColor, &hsvEndColor);
	led_Fill_Rainbow_HSV(hsvStart, count, hsvStartColor, hsvEndColor);
	for (int i = 1; i < count - 1; i++)
	{
		HSV2RGB((hsvStart+i), (start + i));
	}
	start->r = startColor.r;
	start->g = startColor.g;
	start->b = startColor.b;
	(start + count - 1)->r = endColor.r;
	(start + count - 1)->g = endColor.g;
	(start + count - 1)->b = endColor.b;
}

void led_Fill_Rainbow_HEX(HEX_t *start, unsigned count, HEX_t startColor, HEX_t endColor)
{
	HSV_t hsvStart[count];
	HSV_t hsvStartColor;
	HSV_t hsvEndColor;
	HEX2HSV(startColor, &hsvStartColor);
	HEX2HSV(endColor, &hsvEndColor);
	led_Fill_Rainbow_HSV(hsvStart, count, hsvStartColor, hsvEndColor);
	for (int i = 1; i < count - 1; i++)
	{
		HSV2HEX((hsvStart+i), (start + i));
	}
	start[0] = startColor;
	*(start + count - 1) = endColor;
}

