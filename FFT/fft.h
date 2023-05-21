#ifndef __FFT_H
#define __FFT_H

#include <stdint.h>
#include "mike.h"

#define PI2   (6.28318530717959)
#define PI    (3.141592653589795)
#define Fs    ((float)256)   //²ÉÑùÆµÂÊ
extern int32_t FFT_Mag[SAMPLS_NUM / 2];
void InitBufInArray(void);
void GetPowerMag(void);
void FFT_test(void);
void fft_liner_show_led1(void);
void fft_liner_show_led2(void);
#endif
