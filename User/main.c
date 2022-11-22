#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "ws2812b.h"
#include "led.h"
#define NUM_LEDS    60

RGB_t ledsRGB[NUM_LEDS];
HSV_t ledsHSV[NUM_LEDS];
HEX_t ledsHEX[NUM_LEDS];
int main() {
  ws2812b_Init();
  while (1)
	{
		while (!ws2812b_IsReady()) { }; // wait
    //
    // Fill ledsRGB buffer
		led_Fill_Rainbow_RGB(ledsRGB, NUM_LEDS, RGB(255, 10, 10), RGB(10, 255, 10));
		// led_Fill_Rainbow_HSV(ledsHSV, NUM_LEDS, HSV(0, 255, 255), HSV(240, 255, 255));
		// led_Fill_Rainbow_HEX(ledsHEX, NUM_LEDS, HEX(0xff0000), HEX(0x0000ff));

		// led_Fill_Gradient_RGB(ledsRGB, NUM_LEDS, RGB(255, 255, 0), RGB(0, 0, 255));
		// led_Fill_Gradient_HSV(ledsHSV, NUM_LEDS, HSV(0, 255, 255), HSV(240, 255, 255));
		// led_Fill_Gradient_HEX(ledsHEX, NUM_LEDS, HEX(0xff0000), HEX(0x00ff00));

    // led_Gradual_Show_RGB(ledsRGB, NUM_LEDS, 15, 1, 200);
    // led_Gradual_Show_HSV(ledsHSV, NUM_LEDS, 15, 1, 200);
    // led_Gradual_Show_HEX(ledsHEX, NUM_LEDS, 15, 1, 200);
		
		led_Loop_Show_RGB(ledsRGB, NUM_LEDS, 15, 1, 200, 2);
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
  }
}
