#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "ws2812b.h"
#include "led.h"
#include "time.h"
#define NUM_LEDS    24

RGB_t ledsRGB[NUM_LEDS];
HSV_t ledsHSV[NUM_LEDS];
HEX_t ledsHEX[NUM_LEDS];
RGB_t ledsRGB2[NUM_LEDS];
HSV_t ledsHSV2[NUM_LEDS];
int main() {
  led_Init();
  while (1)
	{
		while (!led_IsReady()) { }; // wait
    //
    // Fill ledsRGB buffer
		// led_Fill_Rainbow_RGB(ledsRGB, NUM_LEDS, RGB(255, 10, 10), RGB(10, 255, 10));
		// led_Fill_Rainbow_HSV(ledsHSV, NUM_LEDS, HSV(0, 255, 255), HSV(240, 255, 255));
		// led_Fill_Rainbow_HEX(ledsHEX, NUM_LEDS, HEX(0xff0000), HEX(0x0000ff));

		// led_Fill_Gradient_RGB(ledsRGB, NUM_LEDS, RGB(255, 255, 0), RGB(0, 0, 255));
		// led_Fill_Gradient_HSV(ledsHSV, NUM_LEDS, HSV(0, 255, 255), HSV(240, 255, 255));
		// led_Fill_Gradient_HEX(ledsHEX, NUM_LEDS, HEX(0xff0000), HEX(0x00ff00));

    // led_Gradual_Show_RGB(ledsRGB, NUM_LEDS, 0, 1, 200);
    // led_Gradual_Show_HSV(ledsHSV, NUM_LEDS, 15, 1, 200);
    // led_Gradual_Show_HEX(ledsHEX, NUM_LEDS, 15, 1, 200);
		
		// led_Loop_Show_RGB(ledsRGB, NUM_LEDS, 15, 1, 200, 2);
    // led_Loop_Show_HSV(ledsHSV, NUM_LEDS, 15, 1, 200, 2);
    // led_Loop_Show_HEX(ledsHEX, NUM_LEDS, 15, 1, 200, 2);
		
		// led_Fill_Solid_RGB(ledsRGB, NUM_LEDS, RGB(255, 0, 0));
		// led_Fill_Solid_HSV(ledsHSV, NUM_LEDS, HSV(0, 255, 255));
		// led_Fill_Solid_HEX(ledsHEX+20, 10, 0x00ff00);
		// led_Fill_Solid_RGB(ledsRGB+10, 10, RGB(255, 0, 0));
		
		// led_Show_RGB(ledsRGB, NUM_LEDS);
		// led_Show_HSV(ledsHSV, NUM_LEDS);
		// led_Show_HEX(ledsHEX, NUM_LEDS);
		
    // led_Shut_RGB(NUM_LEDS);
		// led_Shut_HSV(NUM_LEDS);
		// led_Shut_HEX(NUM_LEDS);
		
		// for (int i = 0; i < NUM_LEDS; i++)
		// {
		// 	led_Bright_RGB(&ledsRGB[i], 20);
		// 	led_Bright_HSV(&ledsHSV[i], 20);
		// 	led_Bright_HEX(&ledsHEX[i], 20);
		// }
		
		// led_Clear_RGB(ledsRGB, NUM_LEDS);
		// led_Clear_HSV(ledsHSV, NUM_LEDS);
		// led_Clear_HEX(ledsHEX, NUM_LEDS);
		// delay_ms(500);

		// led_Fill_Solid_RGB(ledsRGB, NUM_LEDS, RGB(255, 0, 0));
		// led_PLoop_Show_RGB(ledsRGB, NUM_LEDS, 0, 1, delaytimeAverage, NUM_LEDS * 2, 50);
		// led_Gradual_Show_RGB(ledsRGB, NUM_LEDS, 0, 1, 50);
		// led_Fill_Solid_RGB(ledsRGB2, NUM_LEDS, RGB(0, 255, 0));
		// led_Gradual_Cover_Show_RGB(ledsRGB, ledsRGB2, NUM_LEDS, 0, 1, 50);
		// led_Fill_Solid_RGB(ledsRGB2, NUM_LEDS, RGB(0, 0, 255));
		// led_Gradual_Cover_Show_RGB(ledsRGB, ledsRGB2, NUM_LEDS, 0, 1, 50);
		led_Fill_Solid_HSV(ledsHSV, NUM_LEDS, HSV(240, 255, 255));
		led_Show_HSV(ledsHSV, NUM_LEDS);
		delay_ms(500);
		led_Fill_Solid_HSV(ledsHSV2, NUM_LEDS, HSV(120, 155, 200));
		led_Show_HSV(ledsHSV2, NUM_LEDS);
		 delay_ms(500);
		led_Gradual_Cover_Show_HSV(ledsHSV, ledsHSV2, NUM_LEDS, 0, 1, 50);
		// for (int i = 0 ; i < 50; i++)
		// {
		// 	for (int j = 0; j < NUM_LEDS; j++)
		// 	{
		// 		if(j % 3 == 0)
		// 		{
		// 			// (ledsHSV + j)->s = (155 + 2 * i) % 256;
		// 			(ledsHSV + j)->v = (200 + 1 * i) % 256;
		// 		} else {
		// 			// (ledsHSV + j)->s = (150 - 2 * i) % 256;
		// 			(ledsHSV + j)->v = (200 - 3 * i) % 256;
		// 		}
		// 	}
		// 	led_Show_HSV(ledsHSV, NUM_LEDS);
		// 	delay_ms(60);
		// }
		// led_Circle_Show_HSV(ledsHSV, NUM_LEDS, 50, NUM_LEDS * 2);
		// led_Circle_Show_HSV(ledsHSV, NUM_LEDS, 40, NUM_LEDS * 2);
		// led_Circle_Show_HSV(ledsHSV, NUM_LEDS, 30, NUM_LEDS * 2);
		// led_Circle_Show_HSV(ledsHSV, NUM_LEDS, 20, NUM_LEDS * 2);
		// led_Circle_Show_HSV(ledsHSV, NUM_LEDS, 10, NUM_LEDS * 2);
		// led_Circle_Show_HSV(ledsHSV, NUM_LEDS, 5, NUM_LEDS * 2);
		// led_Fill_Solid_HSV(ledsHSV2, NUM_LEDS, HSV(120, 155, 200));
		led_Tran_Show_HSV(ledsHSV2, ledsHSV, NUM_LEDS, 20);
		led_Breath_Show_HSV(ledsHSV, NUM_LEDS, 1);
		// led_Fill_Rainbow_HSV(ledsHSV2, NUM_LEDS, HSV(0, 255, 255), HSV(240, 255, 255));
		// led_Gradual_Cover_Show_HSV(ledsHSV, ledsHSV2, NUM_LEDS, 0, 1, 50);
		// delay_ms(1000);
		// led_Circle_Show_HSV(ledsHSV, NUM_LEDS, 50, NUM_LEDS * 5);
		// led_Fill_Solid_RGB(ledsRGB, NUM_LEDS, RGB(255, 0, 0));
		// led_Fill_Solid_RGB(ledsRGB2, NUM_LEDS, RGB(0, 255, 0));
		// led_Tran_Show_HSV2RGB(ledsHSV, ledsRGB, NUM_LEDS, 2000);
		// led_Tran_Show_RGB(ledsRGB, ledsRGB2, NUM_LEDS, 2000);
		// led_Tran_Show_RGB(ledsRGB2, ledsRGB, NUM_LEDS, 2000);
		// led_Gradual_Show_HSV(ledsHSV, NUM_LEDS, 0, 1, 50);
  }
}


