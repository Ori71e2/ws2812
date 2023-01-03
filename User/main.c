#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "ws2812b.h"
#include "led.h"
#include "time.h"
#include "mike.h"
#include "test.h"
#include "fft.h"
#include "OLED.h"
int main() {
  // led_Init();
	mike_Init();
	OLED_Init();
	OLED_ShowNum(1, 1, ADC_SourceData[0], 5);
	// OLED_ShowChar(1, 1, 'A');
	// OLED_ShowString(1, 3, "HelloWorld!");
	OLED_ShowNum(2, 1, 12345, 5);
	// OLED_ShowSignedNum(2, 7, -66, 2);
	// OLED_ShowHexNum(3, 1, 0xAA55, 4);
	// OLED_ShowBinNum(4, 1, 0xAA55, 16);
	int i = 1;
  while (1)
	{
		// arm_sin_cos_example_f32();
    led_example();
	  // OLED_ShowNum(1, 1, ADC_SourceData[0], 5);
		// OLED_ShowNum(3, 1, mike_IsCollected(), 5);
		// if(mike_IsCollected())
		// {
		//   OLED_ShowNum(2, 1, i++, 5);
		// 	OLED_ShowNum(4, 1, mike_IsCollected(), 5);
		// 	mike_StartCollected();
			// Test_Time_Func();				//512Hz采样频率，采样1024点，可以看到2s钟周期执行FFT_test();
			// FFT_test();
		// }
  }
}


