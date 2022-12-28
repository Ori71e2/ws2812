#include "stm32f10x.h"                  // Device header
#include "delay.h"
#include "ws2812b.h"
#include "led.h"
#include "time.h"
#include "mike.h"
#include "test.h"
#include "fft.h"

int main() {
  led_Init();
  while (1)
	{
		// arm_sin_cos_example_f32();
    // led_example();
		if(mike_IsCollected())
		{
			mike_StartCollected();
			// Test_Time_Func();				//512Hz����Ƶ�ʣ�����1024�㣬���Կ���2s������ִ��FFT_test();
			FFT_test();
		}
  }
}


