
#ifndef __MIKE_CONF_H
#define __MIKE_CONF_H

#include <stm32f10x.h>
#include <stm32f10x_rcc.h>
#include <stm32f10x_gpio.h>
#include <stm32f10x_tim.h>
#include <stm32f10x_dma.h>
#include <misc.h>

#define SAMPLS_NUM        64
// DMA1的通道1对应ADC1
// ADC1的通道0对应的GPIOA的Pin_0端口

#define MIKE_APB1_RCC_TIM    RCC_APB1Periph_TIM3
#define MIKE_APB2_RCC_GPIO   RCC_APB2Periph_GPIOA
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
// #define MIKE_PERIOD          488         // 1 / 1000000 * 488  = 0.000488s = 0.48ms, 64个数据一次dma转运进入中断, 计算周期时长为 0.488 * 64 = 31.232ms
// #define MIKE_PERIOD          976         // 1 / 1000000 * 976  = 0.000976s = 0.976ms 0.976 * 64 = 62.646ms
#define MIKE_PERIOD          (488 * 3)   // 约93ms
#define MIKE_SHOW_GAP_TIME  (MIKE_PERIOD * SAMPLS_NUM)

#define MIKE_PULSE_HIGH      21
#define MIKE_PULSE_LOW       9

#define MIKE_ADC             ADC1
#define MIKE_ADC_EXTRIG      ADC_ExternalTrigConv_T3_TRGO
#define MIKE_CHANNEL         ADC_Channel_0                     // ADC1通道0对应的是GPIOB_Pin_0
#define MIKE_CHANNEL_RANK    1
#define MIKE_DMA_ADC_DR      (MIKE_ADC->DR)

#define VCC                  3.3
#define MIKE_VCC             5.0
#define MIKE_OUT_MAX_VOLTAGE     3.3
#define MIKE_OUT_MAX_ADC_VALUE   (MIKE_OUT_MAX_VOLTAGE / VCC * 4096)
#endif //__MIKE_CONF_H
