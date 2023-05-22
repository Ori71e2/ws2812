#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "ws2812b.h"
#include "led.h"
#include "time.h"
#include "mike.h"
#include "test.h"
#include "fft.h"
#include "OLED.h"
#include "ssd1306.h"
#include "ssd1306_multi.h"
int main() {
	delay_ms(2000);
  led_Init();
	mike_Init();
	// OLED_Init();
	ssd1306_Init();
	// ssd1306_example();
  // ssd1306_multi_Init();
  while (1)
	{
		// ssd1306_Show_Image();
		// ugui_example();
		// ssd1306_multi_Show_Image();
		// ssd1306_multi_example();
		// ugui_multi_example();
		if(mike_IsCollected())
		{
			mike_StartCollected();
			FFT_test();
		}
  }
}


