#include "fft.h"
#include "mike.h"
#include "math.h"
#include "led.h"
#include "OLED.h"
RGB_t ledsRGB[NUM_LEDS];
RGB_t ledsRGB2[NUM_LEDS];
HSV_t ledsHSV[NUM_LEDS];
HSV_t ledsHSV2[NUM_LEDS];
static int32_t pre_num = 0, next_num = 0;
static int32_t first = 0;
void fft_liner_show_led1(void)
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
	
	// OLED_ShowNum(3, 1, i_num, 5);
	// OLED_ShowNum(4, 1, max_value, 5);
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

void fft_liner_show_led2(void)
{
	uint32_t max_value = 0;
	int32_t gap = 0;
	for (int i = 0; i < SAMPLS_NUM; i++)
	{
		if (max_value < ADC_SourceData[i])
		{
			max_value = ADC_SourceData[i];
		}
	}
	float f_num = NUM_LEDS * max_value / MIKE_OUT_MAX_ADC_VALUE;
	next_num = NUM_LEDS * max_value / MIKE_OUT_MAX_ADC_VALUE;
	if (NUM_LEDS - f_num < 0.5)
	{
		next_num = NUM_LEDS;
	}
	gap = next_num - pre_num;
	if (first == 0)
	{
		led_Clear_RGB(ledsRGB, NUM_LEDS);
		led_Fill_Gradient_RGB(ledsRGB2, NUM_LEDS, RGB(0, 0, 255), RGB(255, 0, 0));
		first = 1;
	}
	if (gap == 0)
	{
	}
	else if (gap > 0)
	{
		for (int poisition = pre_num; poisition < next_num; poisition++)
		{
			ledsRGB[poisition].r = ledsRGB2[poisition].r;
			ledsRGB[poisition].g = ledsRGB2[poisition].g;
			ledsRGB[poisition].b = ledsRGB2[poisition].b;
			led_Show_RGB(ledsRGB, NUM_LEDS);
		  delay_us(MIKE_SHOW_GAP_TIME / 1 / gap);	
		}
	}
	else if (gap < 0)
	{
		for (int poisition = pre_num - 1; poisition >= next_num; poisition--)
		{
			ledsRGB[poisition].r = 0;
			ledsRGB[poisition].g = 0;
			ledsRGB[poisition].b = 0;
			led_Show_RGB(ledsRGB, NUM_LEDS);
			delay_us(MIKE_SHOW_GAP_TIME / 1 / (-gap));
		}
	}
	pre_num = next_num;
}
uint8_t prt = 10;	//量化显示的比例
void fft_arr_show_led1(void)
{
	uint16_t i = 0;
	uint8_t x = 0;
	uint8_t y = 0;
	
	/*******************显示*******************/
	for(i = 0; i < 32; i++)	//间隔的取32个频率出来显示
	{
		x = (i<<2);	//i*4
		y = 63-(FFT_Mag[x+1] / prt) - 2;	//加1是为了丢掉第一个直流分量
		if(y > 63)
		{
			y = 63;
		}
	// 	GUI_LineWith(x,y,x,63,3,1);
		
	// 	//画下落的点
	// 	if(fall_pot[i]>y) fall_pot[i] = y;
	// 	else
	// 	{
	// 			if(fall_pot[i]>63) fall_pot[i]=63;
	// 			GUI_LineWith(x,fall_pot[i],x,fall_pot[i]+3,3,1);
	// 			fall_pot[i] += 2 ;
	// 	}
	}
	// GUI_Exec();
}
