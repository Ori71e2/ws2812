#include "delay.h"
#include "ws2812b.h"
#include "led.h"
#include "time.h"

// 新旧数据覆盖问题。本ws2812实现中，存在新数据覆盖旧数据问题，加入有一个较多数量的led灯珠如33个，需要0.99ms发送完毕，程序在1ms时发送第一批数据，1.99ms时才能发送完毕
// 假如在1.5ms时更新了数组数据，那么1.5ms~1.99ms之间发送的数据是新的，1ms~1.5ms之间发送的数据是旧的。
// 要注意数据发送的时间间隔。或者使用ws2812b_IsReady()函数判读dma是否在运作。
// 发送1个bit需要1.25us，1个灯珠就需要1.25 * 24 = 30us，33个灯珠30 * 30 = 990us,约等于1ms
// 除非stm32工作在突发模式（Burst Mode），或者块传输模式（Block Transfer Mode）。这种模式下CPU必须等DMA传输完整块数据后才能访存。
// 第二种是Cycle Stealing Mode（不知道中文怎么翻译，循环窃取模式？），每传输一个字节会马上把内存总线控制器交还给CPU并且发出控制请求。
// 如果这个时候CPU需要访问内存则可以马上获得内存总线的控制权对内存进行访问，CPU不需访问内存则马上获得总线控制权传输下一个字节。
// 第三种是透明模式（Transparent Mode）。设备只在CPU不使用内存控制器的时候传输数据。这是最高效的模式，但为了判断CPU什么时候访问内存什么时候不访问，硬件上的实现复杂很多。
void led_example(void) {
  RGB_t ledsRGB[NUM_LEDS];
  HSV_t ledsHSV[NUM_LEDS];
  //  HEX_t ledsHEX[NUM_LEDS];
  RGB_t ledsRGB2[NUM_LEDS];
  HSV_t ledsHSV2[NUM_LEDS];
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
	delay_ms(2000);
	led_Fill_Solid_RGB(ledsRGB, NUM_LEDS, RGB(255, 0, 0));
	led_PLoop_Show_RGB(ledsRGB, NUM_LEDS, 0, 1, delaytimeAverage, NUM_LEDS * 2, 50);
	led_Gradual_Show_RGB(ledsRGB, NUM_LEDS, 0, 1, 50);
	led_Fill_Solid_RGB(ledsRGB2, NUM_LEDS, RGB(0, 255, 0));
	led_Gradual_Cover_Show_RGB(ledsRGB, ledsRGB2, NUM_LEDS, 0, 1, 50);
	led_Fill_Solid_RGB(ledsRGB2, NUM_LEDS, RGB(0, 0, 255));
	led_Gradual_Cover_Show_RGB(ledsRGB, ledsRGB2, NUM_LEDS, 0, 1, 50);
	led_Fill_Solid_HSV(ledsHSV, NUM_LEDS, HSV(240, 255, 255));
	led_Fill_Solid_HSV(ledsHSV2, NUM_LEDS, HSV(120, 255, 200));
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
	// led_Tran_Show_HSV(ledsHSV2, ledsHSV, NUM_LEDS, 2000);
	// led_Breath_Show_HSV(ledsHSV, NUM_LEDS, 1);
	// led_Fill_Rainbow_HSV(ledsHSV2, NUM_LEDS, HSV(0, 255, 255), HSV(240, 255, 255));
	// led_Gradual_Cover_Show_HSV(ledsHSV, ledsHSV2, NUM_LEDS, 0, 1, 50);
	// led_Circle_Show_HSV(ledsHSV, NUM_LEDS, 50, NUM_LEDS * 5);
	// led_Fill_Solid_RGB(ledsRGB, NUM_LEDS, RGB(255, 0, 0));
	// led_Fill_Solid_RGB(ledsRGB2, NUM_LEDS, RGB(0, 255, 0));
	// led_Tran_Show_HSV2RGB(ledsHSV, ledsRGB, NUM_LEDS, 2000);
	// led_Tran_Show_RGB(ledsRGB, ledsRGB2, NUM_LEDS, 2000);
	// led_Tran_Show_RGB(ledsRGB2, ledsRGB, NUM_LEDS, 2000);
	// led_Gradual_Show_HSV(ledsHSV, NUM_LEDS, 0, 1, 50);
}
