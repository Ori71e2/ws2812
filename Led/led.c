
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
void led_Show_RGB(RGB_t *rgbLeds, uint32_t count)
{
  ws2812b_SendRGB(rgbLeds, count);
}

void led_Show_HSV(HSV_t *hsvLeds, uint32_t count)
{
  ws2812b_SendHSV(hsvLeds, count);
}

void led_Show_HEX(HEX_t *hexLeds, uint32_t count)
{
  ws2812b_SendHEX(hexLeds, count);
}

void led_Loop_Show_RGB(RGB_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime, uint32_t clickTimes)
{
	RGB_t rgbStart[count];
	uint32_t i = offset;
	led_Clear_RGB(rgbStart, count);
	while (clickTimes--)
	{
		for (uint32_t j = 0; j < length; j++)
		{
			(rgbStart + (i + j) % count)->r = (start + (i + j) % count)->r;
			(rgbStart + (i + j) % count)->g = (start + (i + j) % count)->g;
			(rgbStart + (i + j) % count)->b = (start + (i + j) % count)->b;	
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		for (uint32_t j = 0; j < length; j++)
		{
			(rgbStart + (i + j) % count)->r = 0;
			(rgbStart + (i + j) % count)->g = 0;
			(rgbStart + (i + j) % count)->b = 0;	
		}
		i += length;
	}
}

void led_PLoop_Show_RGB(RGB_t *start, uint32_t count, uint32_t offset, uint32_t length, Delaytime_t *delaytimeF, uint32_t clickTimes, uint32_t time)
{
	RGB_t rgbStart[count];
	uint32_t i = offset;
	Delaytime_t *delayTime = delaytimeF;
	led_Clear_RGB(rgbStart, count);
	while (clickTimes--)
	{
		for (uint32_t j = 0; j < length; j++)
		{
			(rgbStart + (i + j) % count)->r = (start + (i + j) % count)->r;
			(rgbStart + (i + j) % count)->g = (start + (i + j) % count)->g;
			(rgbStart + (i + j) % count)->b = (start + (i + j) % count)->b;	
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime(count, length, clickTimes, time));
		for (uint32_t j = 0; j < length; j++)
		{
			(rgbStart + (i + j) % count)->r = 0;
			(rgbStart + (i + j) % count)->g = 0;
			(rgbStart + (i + j) % count)->b = 0;	
		}
		i += length;
	}
}

void led_Gradual_Show_RGB(RGB_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime)
{
	RGB_t rgbStart[count];
	uint32_t i = offset;
	uint32_t clickTimes = count * 1;
	led_Clear_RGB(rgbStart, count);
	while (clickTimes--)
	{
		for (uint32_t j = 0; j < length; j++)
		{
			(rgbStart + (i + j) % count)->r = (start + (i + j) % count)->r;
			(rgbStart + (i + j) % count)->g = (start + (i + j) % count)->g;
			(rgbStart + (i + j) % count)->b = (start + (i + j) % count)->b;	
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		i += length;
	}
}

void led_Gradual_Cover_Show_RGB(RGB_t *source, RGB_t *end, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime)
{
	uint32_t i = offset;
	uint32_t clickTimes = count / length;
	while (clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			(source + (i + j) % count)->r = (end + (i + j) % count)->r;
			(source + (i + j) % count)->g = (end + (i + j) % count)->g;
			(source + (i + j) % count)->b = (end + (i + j) % count)->b;	
		}
		led_Show_RGB(source, count);
		delay_ms(delayTime);
		i += length;
	}
}

void led_Loop_Show_HSV(HSV_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime, uint32_t clickTimes)
{
	RGB_t rgbStart[count];
	int i = offset;
	HSV_t tmp = HSV(0, 0, 0);
	led_Clear_RGB(rgbStart, count);
	while (clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			HSV2RGB((start + (i + j) % count), rgbStart + (i + j) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		for (int j = 0; j < length; j++)
		{
			HSV2RGB(&tmp, rgbStart + (i + j) % count);
		}
		i += length;
	}
}

void led_Gradual_Show_HSV(HSV_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime)
{
	RGB_t rgbStart[count];
	int i = offset;
	int clickTimes = count * 1;
	led_Clear_RGB(rgbStart, count);
	while (clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			HSV2RGB((start + (i + j) % count), rgbStart + (i + j) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		i += length;
	}
}

void led_Breath_Show_HSV(HSV_t *start, uint32_t count, uint32_t num)
{
	RGB_t rgbStart[count];
	HSV_t tmp;
	int times = 255;
	int v;
	int first = 0;
	int clickTimes;
	int minV = 60;
	unsigned delayTimeGap = 5;
	for (int i = 0; i < count; i++)
	{
		HSV2RGB((start + i), rgbStart + i);
	}

	while (num--)
	{
		clickTimes = times;
		while (clickTimes--)
		{
			for (int i = 0; i < count; i++)
			{
				if (first)
				{
					v = 255 - (times - clickTimes) * 1;
				} 
				else 
				{
					v = (int)(start + i)->v - (times - clickTimes) * 1;
				}
				tmp.h = (start + i)->h;
				tmp.s = (start + i)->s;
				tmp.v = (uint8_t)(v >= minV ? v : minV);
				HSV2RGB(&tmp, rgbStart + i);
			}
			led_Show_RGB(rgbStart, count);
			delay_ms(delayTimeGap);
			if (v <= 0)
			{
				break;
			}
		}
		clickTimes = times;
		while (clickTimes--)
		{
			for (int i = 0; i < count; i++)
			{
				v = minV + (times - clickTimes) * 1;
				tmp.h = (start + i)->h;
				tmp.s = (start + i)->s;
				tmp.v = (uint8_t)(v >= 255 ? 255 : v);
				HSV2RGB(&tmp, rgbStart + i);
			}
			led_Show_RGB(rgbStart, count);
			delay_ms(delayTimeGap);
			if (v >= 255)
			{
				break;
			}
		}
		first = 1;
	}
}

void led_Tran_Show_RGB(RGB_t *source, RGB_t *end, uint32_t count, uint32_t tranTime)
{
	RGB_t ledRgb[count];
	int32_t rGap[count], gGap[count], bGap[count];
	int32_t init = 125;
	int32_t timeGap = tranTime / init;
	int32_t clickNum = init;
	int32_t r, g, b;
	for (int32_t i = 0; i < count; i++)
	{
		rGap[i] = (int32_t)((end + i)->r) - (int32_t)((source + i)->r);
		gGap[i] = (int32_t)((end + i)->g) - (int32_t)((source + i)->g);
		bGap[i] = (int32_t)((end + i)->b) - (int32_t)((source + i)->b);
	}
	for ( ; clickNum >= 0; clickNum--)
	{
		for (int i = 0; i < count; i++)
		{
			r = (int32_t)((source + i)->r) + rGap[i] / init * ( init - clickNum);
			g = (int32_t)((source + i)->g) + gGap[i] / init * ( init - clickNum);
			b = (int32_t)((source + i)->b) + bGap[i] / init * ( init - clickNum);
			(ledRgb + i)->r = (uint8_t)r;
			(ledRgb + i)->g = (uint8_t)g;
			(ledRgb + i)->b = (uint8_t)b;
		}
		led_Show_RGB(ledRgb, count);
		delay_ms(timeGap);
	}
}

void led_Circle_Show_RGB(RGB_t *start, uint32_t count, uint32_t delayTime, uint32_t clickTimes)
{
	RGB_t tmpRgb;
	while (clickTimes--)
	{
		tmpRgb.r = (start + count - 1)->r;
		tmpRgb.g = (start + count - 1)->g;
		tmpRgb.b = (start + count - 1)->b;
		for (int i = count - 1; i > 0; i--)
		{
			(start + i)->r = (start + i - 1)->r;
			(start + i)->g = (start + i - 1)->g;
			(start + i)->b = (start + i - 1)->b;
		}
		start->r = tmpRgb.r;
		start->g = tmpRgb.g;
		start->b = tmpRgb.b;
		led_Show_RGB(start, count);
		delay_ms(delayTime);
	}
}

void led_Circle_Show_HSV(HSV_t *start, uint32_t count, uint32_t delayTime, uint32_t clickTimes)
{
	RGB_t rgbStart[count];
	RGB_t tmpRgb;
	led_Clear_RGB(rgbStart, count);
	ARR_HSV2RGB(start, rgbStart, count);
	led_Circle_Show_RGB(rgbStart, count, delayTime, clickTimes);
}
void led_Tran_Show_HSV2RGB(HSV_t *source, RGB_t *end, uint32_t count, uint32_t tranTime)
{
	RGB_t sourceRgb[count];
	ARR_HSV2RGB(source, sourceRgb, count);
	led_Tran_Show_RGB(sourceRgb, end, count, tranTime);
}
void led_Tran_Show_HSV(HSV_t *sourceHsv, HSV_t *endHsv, uint32_t count, uint32_t tranTime)
{
	RGB_t source[count];
	RGB_t end[count];
	ARR_HSV2RGB(sourceHsv, source, count);
	ARR_HSV2RGB(endHsv, end, count);
  led_Tran_Show_RGB(source, end, count, tranTime);
}

void led_Gradual_Cover_Show_HSV(HSV_t *source, HSV_t *end, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime)
{
	RGB_t rgbStart[count];
	int i = offset;
	int clickTimes = count * 1;
	for (int i = 0; i < count; i++)
	{
		HSV2RGB((source + i % count), rgbStart + i % count);
	}
	while (clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			(source + (i + j) % count)->h = (end + (i + j) % count)->h;
			(source + (i + j) % count)->s = (end + (i + j) % count)->s;
			(source + (i + j) % count)->v = (end + (i + j) % count)->v;
			 HSV2RGB((source + (i + j) % count), rgbStart + (i + j) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		i += length;
	}
}


void led_Loop_Show_HEX(HEX_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime, uint32_t clickTimes)
{
	RGB_t rgbStart[count];
	int i = offset;
	led_Clear_RGB(rgbStart, count);
	while (clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			 HEX2RGB(*(start + (i + j) % count), rgbStart + (i + j) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		for (int j = 0; j < length; j++)
		{
			 HEX2RGB(HEX(0x000000), rgbStart + (i + j) % count);
		}
		i += length;
	}
}

void led_Gradual_Show_HEX(HEX_t *start, uint32_t count, uint32_t offset, uint32_t length, uint32_t delayTime)
{
	RGB_t rgbStart[count];
	int i = offset;
	int clickTimes = count * 1;
	led_Clear_RGB(rgbStart, count);
	while (clickTimes--)
	{
		for (int j = 0; j < length; j++)
		{
			 HEX2RGB(*(start + (i + j) % count), rgbStart + (i + j) % count);
		}
		led_Show_RGB(rgbStart, count);
		delay_ms(delayTime);
		i += length;
	}
}

// clear all
void led_Shut_RGB(uint32_t count)
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

void led_Shut_HSV(uint32_t count)
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

void led_Shut_HEX(uint32_t count)
{
	HEX_t hexLeds[count];
	for (int i = 0; i < count; i++)
	{
		hexLeds[i] = 0x000000;
	}
	 led_Show_HEX(hexLeds, count);
}
// clear all
void led_Clear_RGB(RGB_t *rgbLeds, uint32_t count)
{
	for (uint32_t i = 0; i < count; i++)
	{
		(rgbLeds + i)->r = 0;
		(rgbLeds + i)->g = 0;
		(rgbLeds + i)->b = 0;
	}
}

void led_Clear_HSV(HSV_t *hsvLeds, uint32_t count)
{
	for (int i = 0; i < count; i++)
	{
		(hsvLeds + i)->h = 0;
		(hsvLeds + i)->s = 0;
		(hsvLeds + i)->v = 0;
	}
}

void led_Clear_HEX(HEX_t *hexLeds, uint32_t count)
{
	for (int i = 0; i < count; i++)
	{
		*(hexLeds + i) = 0x000000;
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

void led_Fill_Solid_RGB(RGB_t *start, uint32_t count, RGB_t color)
{
	for (int i = 0; i < count; i++)
	{
		(start + i)->r = color.r;
		(start + i)->g = color.g;
		(start + i)->b = color.b;
	}
}

void led_Fill_Solid_HSV(HSV_t *start, uint32_t count, HSV_t color)
{
	for (int i = 0; i < count; i++)
	{
		(start + i)->h = color.h;
		(start + i)->s = color.s;
		(start + i)->v = color.v;
	}
}

void led_Fill_Solid_HEX(HEX_t *start, uint32_t count, HEX_t color)
{
	for (int i = 0; i < count; i++)
	{
		*(start + i) = color;
	}
}

void led_Fill_Gradient_RGB(RGB_t *start, uint32_t count, RGB_t startColor, RGB_t endColor)
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

void led_Fill_Gradient_HSV(HSV_t *start, uint32_t count, HSV_t startColor, HSV_t endColor)
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

void led_Fill_Gradient_HEX(HEX_t *start, uint32_t count, HEX_t startColor, HEX_t endColor)
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

void led_Fill_Line_HEX(HEX_t *start, uint32_t count, HEX_t startColor, HEX_t endColor)
{
	for (int32_t i = 1; i < count - 1; i++)
	{
		*(start + i) = (uint32_t)((int32_t)startColor + ((int32_t)endColor - (int32_t)startColor) / ((int32_t)count - 1) * i);
	}
	*start = startColor;
	*(start + count - 1) = endColor;
}

void led_Fill_Rainbow_HSV(HSV_t *start, uint32_t count, HSV_t startColor, HSV_t endColor)
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

void led_Fill_Rainbow_RGB(RGB_t *start, uint32_t count, RGB_t startColor, RGB_t endColor)
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

void led_Fill_Rainbow_HEX(HEX_t *start, uint32_t count, HEX_t startColor, HEX_t endColor)
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

