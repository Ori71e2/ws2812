#include "fft.h"
#include "mike.h"
#include "math.h"
#include "led.h"
#define NUM_LEDS    24
RGB_t ledsRGB[NUM_LEDS];
void fft_show_led(uint32_t *fft_mag)
{
  uint32_t num = *(fft_mag + SAMPLS_NUM / 2 - 1);
	led_Clear_RGB(ledsRGB, NUM_LEDS);
  led_Fill_Solid_RGB(ledsRGB, num % NUM_LEDS, RGB(255, 0, 0));
	led_Show_RGB(ledsRGB, NUM_LEDS);
}
