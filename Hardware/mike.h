#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_

#include "stm32f10x.h"

#define SINGLECHANNEL 0

#define ADC_CHANNEL_NUMS 	3
#define SAMPLS_NUM        1024

typedef enum {
	FFT_CHANNEL_1 = 0,
	FFT_CHANNEL_2,
	FFT_CHANNEL_3,
} EN_FFT_CHANNEL;


#if SINGLECHANNEL
extern uint16_t ADC_SourceData[SAMPLS_NUM];
#else
extern uint16_t ADC_SourceData[SAMPLS_NUM][ADC_CHANNEL_NUMS];
#endif

void mike_Init(void);

#endif
