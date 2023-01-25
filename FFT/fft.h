#ifndef __FFT_H
#define __FFT_H

#include <stdint.h>

#define PI2   (6.28318530717959)
#define PI    (3.141592653589795)
#define Fs    ((float)256)   //²ÉÑùÆµÂÊ

void InitBufInArray(void);
void GetPowerMag(void);
void FFT_test(void);
void fft_liner_show_led1(void);
void fft_liner_show_led2(void);
#endif
