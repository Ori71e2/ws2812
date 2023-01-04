
#ifndef __MIKE_CONF_H
#define __MIKE_CONF_H

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_dma.h>
#include <misc.h>

#define SINGLECHANNEL 1

#define ADC_CHANNEL_NUMS 	3
#define SAMPLS_NUM        1024

// #define MIKE_BUFFER_SIZE     60
// #define MIKE_START_SIZE      2

#define MIKE_APB1_RCC_TIM    RCC_APB1Periph_TIM3
#define MIKE_APB2_RCC_GPIO   RCC_APB2Periph_GPIOB
#define MIKE_APB2_RCC_ADC    RCC_APB2Periph_ADC1
#define MIKE_AHB_RCC_DMA     RCC_AHBPeriph_DMA1

#define MIKE_GPIO            GPIOA
#define MIKE_GPIO_PIN        GPIO_Pin_0

#define MIKE_TIM             TIM3
#define MIKE_TIME_BASE_INIT  TIM_TimeBaseInit
#define MIKE_TIM_OCINIT      TIM_OC1Init
#define MIKE_TIM_OCPRELOAD   TIM_OC1PreloadConfig
#define MIKE_TIM_DMA_CC      TIM_DMA_CC1

#define MIKE_DMA             DMA1
#define MIKE_DMA_CHANNEL     DMA1_Channel1
#define MIKE_DMA_IRQ         DMA1_Channel1_IRQn

#define MIKE_DMA_HANDLER     DMA1_Channel1_IRQHandler
#define MIKE_DMA_IT_TC       DMA1_IT_TC1
#define MIKE_DMA_IT_HT       DMA1_IT_HT1

#define MIKE_IRQ_PRIO        0
#define MIKE_IRQ_SUBPRIO     1

#define MIKE_FREQUENCY       1000000
#define MIKE_PERIOD          1953

#define MIKE_PULSE_HIGH      21
#define MIKE_PULSE_LOW       9

#define MIKE_ADC             ADC1
#define MIKE_ADC_EXTRIG      ADC_ExternalTrigConv_T3_TRGO
#define MIKE_CHANNEL         ADC_Channel_1                     // ADC1通道8对应的是GPIOB_Pin_0
#define MIKE_CHANNEL_RANK    1
#define MIKE_DMA_ADC_DR      (MIKE_ADC->DR)
#endif //__MIKE_CONF_H
