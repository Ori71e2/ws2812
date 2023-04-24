#ifndef __SSD1306_CONF_H
#define __SSD1306_CONF_H

#define  MAX_X  128
#define  MAX_Y  64
#define  ssd1306_Code

#define SSD1306_APB1_RCC_TIM    RCC_APB2Periph_TIM1
#define SSD1306_APB2_RCC_GPIO   RCC_APB2Periph_GPIOA
#define SSD1306_APB2_RCC_ADC    RCC_APB2Periph_ADC1
#define SSD1306_AHB_RCC_DMA     RCC_AHBPeriph_DMA1

#define SSD1306_GPIO            GPIOA
#define SSD1306_GPIO_PIN        GPIO_Pin_0

#define SSD1306_TIM             TIM1
#define SSD1306_TIME_BASE_INIT  TIM_TimeBaseInit
#define SSD1306_TIM_OCINIT      TIM_OC1Init
#define SSD1306_TIM_OCPRELOAD   TIM_OC1PreloadConfig
#define SSD1306_TIM_DMA_CC      TIM_DMA_CC1

#define SSD1306_DMA             DMA1
#define SSD1306_DMA_CHANNEL     DMA1_Channel3
#define SSD1306_DMA_IRQ         DMA1_Channel3_IRQn

#define SSD1306_DMA_HANDLER     DMA1_Channel3_IRQHandler
#define SSD1306_DMA_IT_TC       DMA1_IT_TC3
#define SSD1306_DMA_IT_HT       DMA1_IT_HT3

#define SSD1306_TIM_IRQ         TIM1_UP_IRQn
#define SSD1306_TIM_IRQ_HANDLER TIM1_UP_IRQHandler
#define SSD1306_IRQ_PRIO        0
#define SSD1306_IRQ_SUBPRIO     1

#define SSD1306_FREQUENCY       1000000
// #define SSD1306_PERIOD          488         // 1 / 1000000 * 488  = 0.000488s = 0.48ms, 64个数据一次dma转运进入中断, 计算周期时长为 0.488 * 64 = 31.232ms
// #define SSD1306_PERIOD          976         // 1 / 1000000 * 976  = 0.000976s = 0.976ms 0.976 * 64 = 62.646ms
#define SSD1306_PERIOD          (488 * 3)   // 约93ms
#define SSD1306_SHOW_GAP_TIME  (SSD1306_PERIOD * SAMPLS_NUM * 0.8)

#define SSD1306_PULSE_HIGH      21
#define SSD1306_PULSE_LOW       9

#endif
