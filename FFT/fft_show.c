#include "fft.h"
#include "mike.h"
#include "math.h"
#include "led.h"
#include "OLED.h"
RGB_t ledsRGB[NUM_LEDS];
HSV_t ledsHSV[NUM_LEDS];
HSV_t ledsHSV2[NUM_LEDS];
void fft_liner_show_led(uint32_t *fft_mag)
{
	uint32_t max_value = 0;
	for (int i = 0; i < SAMPLS_NUM; i++)
	{
		if (max_value < ADC_SourceData[i])
		{
			max_value = ADC_SourceData[i];
		}
	}
	float f_num = NUM_LEDS * max_value / MIKE_OUT_MAX_ADC_VALUE;
	int32_t i_num = NUM_LEDS * max_value / MIKE_OUT_MAX_ADC_VALUE;
	if (NUM_LEDS - f_num < 0.5)
	{
		i_num = NUM_LEDS;
	}
	
	OLED_ShowNum(3, 1, i_num, 5);
	OLED_ShowNum(4, 1, max_value, 5);
	led_Clear_RGB(ledsRGB, NUM_LEDS);
  // led_Fill_Solid_RGB(ledsRGB, i_num, RGB(255, 0, 0));
	led_Fill_Gradient_RGB(ledsRGB, NUM_LEDS, RGB(0, 0, 255), RGB(255, 0, 0));
	for (int i = i_num; i < NUM_LEDS; i++)
	{
		ledsRGB[i].r = 0;
		ledsRGB[i].g = 0;
		ledsRGB[i].b = 0;
	}
	led_Show_RGB(ledsRGB, NUM_LEDS);
	// led_Clear_HSV(ledsHSV, NUM_LEDS);
	// led_Clear_HSV(ledsHSV2, NUM_LEDS);
	// led_Fill_Gradient_HSV(ledsHSV, i_num, HSV(0, 255, 255), HSV((0 + 240) * i_num / NUM_LEDS, 255, 255));
	// for (int i = 0; i < i_num; i++)
	// {
	// 	(ledsHSV2 + i)->h = (ledsHSV + i_num - i - 1)->h;
	// 	(ledsHSV2 + i)->s = (ledsHSV + i_num - i - 1)->s;
	// 	(ledsHSV2 + i)->v = (ledsHSV + i_num - i - 1)->v;
	// }
	// led_Show_HSV(ledsHSV2, NUM_LEDS);
}
