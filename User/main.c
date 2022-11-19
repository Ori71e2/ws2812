#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "ws2812b.h"
#include "led.h"
#define NUM_LEDS    60

RGB_t leds[NUM_LEDS];
HSV_t leds2[NUM_LEDS];
HEX_t leds3[NUM_LEDS];
int main() {
  ws2812b_Init();
  while (1)
	{
		while (!ws2812b_IsReady()) { }; // wait
    //
    // Fill leds buffer
		/*
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i].r = 255;
			leds[i].g = 0;
			leds[i].b = 0;
		}
    led_Show_RGB(leds, NUM_LEDS);
		delay_ms(500);
		for (int i = 0; i < NUM_LEDS; i++)
		{
			led_Bright_RGB(&leds[i], 20);
		}
    ws2812b_SendRGB(leds, NUM_LEDS);
		delay_ms(500);
		*/
		led_Fill_Gradient_HEX(leds3, NUM_LEDS, HEX(0xff0000), HEX(0x00ff00));
		led_Show_HEX(leds3, NUM_LEDS);
		/*
		led_Fill_Gradient_RGB(leds, NUM_LEDS, RGB(255, 255, 0), RGB(0, 0, 255));
		led_Show_RGB(leds, NUM_LEDS);
		delay_ms(500);
    led_Shut_RGB(leds, NUM_LEDS);
		delay_ms(500);
		*/
		//led_Fill_Gradient_HEX(leds3, NUM_LEDS, HEX(0xff0000), HEX(0x00ff00));
		//led_Show_HEX(leds3, NUM_LEDS);
		//led_Fill_Solid_RGB(leds, NUM_LEDS, RGB(255, 0, 0));
		//led_Show_RGB(leds, NUM_LEDS);
		/*
		delay_ms(500);
		led_Fill_Solid_RGB(leds+10, 10, RGB(255, 0, 0));
		led_Show_RGB(leds, NUM_LEDS);
		delay_ms(500);
		led_Fill_Solid_HEX(leds3+20, 10, 0x00ff00);
		led_Show_HEX(leds3, NUM_LEDS);
		*/
		/*
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds3[i] = 0xffff00;
		}
    led_Show_HEX(leds3, NUM_LEDS);
		delay_ms(500);
		for (int i = 0; i < NUM_LEDS; i++)
		{
			led_Bright_HEX(&leds3[i], 20);
		}
    led_Show_HEX(leds3, NUM_LEDS);
		delay_ms(500);
		led_Clear_HEX(leds3, NUM_LEDS);
		delay_ms(500);
		*/
    //
		/*
    // 显示红色
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i].r = 255;
			leds[i].g = 0;
			leds[i].b = 0;
		}
    ws2812b_SendRGB(leds, NUM_LEDS);
    // 显示绿色
		delay_ms(2000);
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i].r = 0;
			leds[i].g = 255;
			leds[i].b = 0;
		}
    ws2812b_SendRGB(leds, NUM_LEDS);
    // 显示蓝色
		delay_ms(2000);
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds[i].r = 0;
			leds[i].g = 0;
			leds[i].b = 255;
		}
    ws2812b_SendRGB(leds, NUM_LEDS);
    // 显示渐变色
		delay_ms(2000);
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds2[i].h = i * 6;
			leds2[i].s = 255;
			leds2[i].v = 255;
		}
		ws2812b_SendHSV(leds2, NUM_LEDS);
    // 跑马灯
		delay_ms(2000);
		for (int j = 0; j < 60; j++)
		{
			for (int i = 0; i < NUM_LEDS; i++)
			{
				leds2[i].h = (i + j) * 6;
				leds2[i].s = 255;
				leds2[i].v = 255;
			}
			ws2812b_SendHSV(leds2, NUM_LEDS);
			delay_ms(30);
		}
    // 呼吸灯
    delay_ms(2000);
		for (int breath_times = 0; breath_times < 3; breath_times++)
		{
			for (int j = 20; j < 200; j++)
			{
				for (int i = 0; i < NUM_LEDS; i++)
				{
					leds2[i].h = 120;
					leds2[i].s = 255;
					leds2[i].v = j;
				}
				ws2812b_SendHSV(leds2, NUM_LEDS);
				delay_ms(10);
			}
			for (int j = 200 - 2; j > 20; j--)
			{
				for (int i = 0; i < NUM_LEDS; i++)
				{
					leds2[i].h = 120;
					leds2[i].s = 255;
					leds2[i].v = j;
				}
				ws2812b_SendHSV(leds2, NUM_LEDS);
				delay_ms(10);
			}
		}
    // 从头开始逐个点亮
    delay_ms(2000);
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds2[i].h = 0;
			leds2[i].s = 255;
			leds2[i].v = 0;
		}
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds2[i].v = 255;
			ws2812b_SendHSV(leds2, NUM_LEDS);
			delay_ms(50);
		}
    // 从两头开始逐个点亮
    delay_ms(2000);
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds2[i].h = 0;
			leds2[i].s = 255;
			leds2[i].v = 0;
		}
		for (int i = 0; i < NUM_LEDS; i++)
		{
			leds2[i].v = 255;
			leds2[NUM_LEDS - i - 1].v = 255;
			ws2812b_SendHSV(leds2, NUM_LEDS);
			delay_ms(50);
		}
		*/
  }
}
