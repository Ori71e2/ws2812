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
			// Test_Time_Func();				//512Hz采样频率，采样1024点，可以看到2s钟周期执行FFT_test();
			FFT_test();
		}
  }
}


