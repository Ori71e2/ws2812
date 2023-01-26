#ifndef _DRV_ADC_H_
#define _DRV_ADC_H_

#include <stdint.h>
#include "stm32f10x.h"
#include "mike_conf.h"
#define SAMPLS_NUM        64
typedef enum {
	FFT_CHANNEL_1 = 0,
	FFT_CHANNEL_2,
	FFT_CHANNEL_3,
} EN_FFT_CHANNEL;


#ifdef __cplusplus
extern "C" {
#endif

extern uint16_t ADC_SourceData[SAMPLS_NUM];

void mike_Init(void);
int mike_IsCollected(void);
void mike_StartCollected(void);
	
#ifdef __cplusplus
}
#endif

#endif
