// The MIT License (MIT)
//
// Copyright (c) 2015 Aleksandr Aleshin <silencer@quadrius.net>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdint.h>
#include <string.h>

#include "bitmap.h"

#include "ws2812b.h"
#include "ws2812b_conf.h"

//------------------------------------------------------------
// Internal
//------------------------------------------------------------

// #define MIN(a, b)   ({ typeof(a) a1 = a; typeof(b) b1 = b; a1 < b1 ? a1 : b1; })

#if defined(__ICCARM__)
__packed struct PWM
#else
struct __attribute__((packed)) PWM
#endif
{
  uint16_t g[8], r[8], b[8];
};

typedef struct PWM PWM_t;
typedef void (SrcFilter_t)(void **, PWM_t **, unsigned *, unsigned);

#ifdef WS2812B_USE_GAMMA_CORRECTION
#ifdef WS2812B_USE_PRECALCULATED_GAMMA_TABLE
static const uint8_t LEDGammaTable[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
  2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10,
  10, 11, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21,
  22, 23, 23, 24, 24, 25, 26, 26, 27, 28, 28, 29, 30, 30, 31, 32, 32, 33, 34, 35, 35, 36, 37, 38,
  38, 39, 40, 41, 42, 42, 43, 44, 45, 46, 47, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 56, 57, 58,
  59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 84,
  85, 86, 87, 88, 89, 91, 92, 93, 94, 95, 97, 98, 99, 100, 102, 103, 104, 105, 107, 108, 109, 111,
  112, 113, 115, 116, 117, 119, 120, 121, 123, 124, 126, 127, 128, 130, 131, 133, 134, 136, 137,
  139, 140, 142, 143, 145, 146, 148, 149, 151, 152, 154, 155, 157, 158, 160, 162, 163, 165, 166,
  168, 170, 171, 173, 175, 176, 178, 180, 181, 183, 185, 186, 188, 190, 192, 193, 195, 197, 199,
  200, 202, 204, 206, 207, 209, 211, 213, 215, 217, 218, 220, 222, 224, 226, 228, 230, 232, 233,
  235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255 };
#endif
#endif

static inline uint8_t LEDGamma(uint8_t v)
{
#ifdef WS2812B_USE_GAMMA_CORRECTION
#ifdef WS2812B_USE_PRECALCULATED_GAMMA_TABLE
  return LEDGammaTable[v];
#else
  return (v * v + v) >> 8;
#endif
#else
  return v;
#endif
}

static volatile int DMABusy;

static PWM_t DMABuffer[WS2812B_BUFFER_SIZE];

static SrcFilter_t *DMAFilter;
static void *DMASrc;
static unsigned DMACount;

static unsigned min(unsigned a, unsigned b)
{
	if (a < b)
	{
		return a;
	} else {
		return b;
	}
}
static void SrcFilterNull(void **src, PWM_t **pwm, unsigned *count, unsigned size)
{
  memset(*pwm, 0, size * sizeof(PWM_t));
  *pwm += size;
}

static void RGB2PWM(RGB_t *rgb, PWM_t *pwm)
{
  uint8_t r = LEDGamma(rgb->r);
  uint8_t g = LEDGamma(rgb->g);
  uint8_t b = LEDGamma(rgb->b);

  uint8_t mask = 128;

  int i;
  for (i = 0; i < 8; i++)
  {
    pwm->r[i] = r & mask ? WS2812B_PULSE_HIGH : WS2812B_PULSE_LOW;
    pwm->g[i] = g & mask ? WS2812B_PULSE_HIGH : WS2812B_PULSE_LOW;
    pwm->b[i] = b & mask ? WS2812B_PULSE_HIGH : WS2812B_PULSE_LOW;

    mask >>= 1;
  }
}

static void SrcFilterRGB(void **src, PWM_t **pwm, unsigned *count, unsigned size)
{
  RGB_t *rgb = *src;
  PWM_t *p = *pwm;

  *count -= size;

  while (size--)
  {
    RGB2PWM(rgb++, p++);
  }

  *src = rgb;
  *pwm = p;
}

static void SrcFilterHSV(void **src, PWM_t **pwm, unsigned *count, unsigned size)
{
  HSV_t *hsv = *src;
  PWM_t *p = *pwm;

  *count -= size;

  while (size--)
  {
    RGB_t rgb;

    HSV2RGB(hsv++, &rgb);
    RGB2PWM(&rgb, p++);
  }

  *src = hsv;
  *pwm = p;
}

static void SrcFilterHEX(void **src, PWM_t **pwm, unsigned *count, unsigned size)
{
  HEX_t *hex = *src;
  PWM_t *p = *pwm;

  *count -= size;

  while (size--)
  {
    RGB_t rgb;

    HEX2RGB(*hex, &rgb);
		hex++;
    RGB2PWM(&rgb, p++);
  }

  *src = hex;
  *pwm = p;
}
// 只要开始发送，DMA是处于一直运转状态，直至所有数据发送完毕，发送一次完整的数据后，DMA停止发送数据，此时GPIO端口到下一次发送前置数据后、正式数据前，会一直处于低电平状态
// 此时ws2812一直会锁住之前的数据，直至接收新数据。  这点可以通过将数据发送端口连接线断开观察到。
// 1、DMAcount小于buffer size，剩余buffer区域数据填充0，pwm在这个周期内将这块数据全部发送给ws2812，buffer size超出部分被ws2812舍弃掉。
// 仅一次周期完成全部传输。
// 同时DMAcount将会被置零。
// 在下一次中断，DMAsendnext中开启下一个周期
// 2、DMAcount等于buffersize
// 3、DMAcount大于buffersize
// 不管上述哪种情况，都是通过缓冲区中转区一次性将全部数据发送完毕。
// 使用RESET编码(WS2812帧锁定编码)，也就是超过50us的低电平形成WS2812输出锁定。
// 根据WS2812控制信号协议，RESET是时长超过50us的低电平，因此，在2.5MHz的波特率下，连续输出125bit的高电平，
// 也就是16个byte的0xff，则可以产生：16 × 8 = 128 16 \times 8 = 12816×8=128个1输出，便可以产生128 × 0.4 = 51.2 μ s 128 \times 0.4 = 51.2\mu s128×0.4=51.2μs的低电平。
// 开始发送了BUFFSTARTSIZE既2*24*（0.85+0.4)=60us时间的低电平，相当于重置开始。
// 然后开始正式发送。
// 发送完毕所有数据后，停止发送，所有数据被ws2812锁定。
// 当发送的数据多于灯数量时，多余的被丢弃，相当于尾端没有接收。
// 注:  多余的数据在最后被置全部为零
static void DMASend(SrcFilter_t *filter, void *src, unsigned count)
{
  if (!DMABusy)
  {
    DMABusy = 1;

    DMAFilter = filter;
    DMASrc = src;
    DMACount = count;

    PWM_t *pwm = DMABuffer;
    PWM_t *end = &DMABuffer[WS2812B_BUFFER_SIZE];

    // Start sequence
    SrcFilterNull(NULL, &pwm, NULL, WS2812B_START_SIZE);

    // RGB PWM data
    DMAFilter(&DMASrc, &pwm, &DMACount, min(DMACount, end - pwm));

    // Rest of buffer
    if (pwm < end)
      SrcFilterNull(NULL, &pwm, NULL, end - pwm);

    // Start transfer
    DMA_SetCurrDataCounter(WS2812B_DMA_CHANNEL, sizeof(DMABuffer) / sizeof(uint16_t));

    TIM_Cmd(WS2812B_TIM, ENABLE);
    DMA_Cmd(WS2812B_DMA_CHANNEL, ENABLE);
  }
}

static void DMASendNext(PWM_t *pwm, PWM_t *end)
{
  if (!DMAFilter)
  {
    // Stop transfer
    TIM_Cmd(WS2812B_TIM, DISABLE);
    DMA_Cmd(WS2812B_DMA_CHANNEL, DISABLE);

    DMABusy = 0;
  }
    else if (!DMACount)
  {
  // Rest of buffer
    SrcFilterNull(NULL, &pwm, NULL, end - pwm);

    DMAFilter = NULL;
  }
  else
  {
    // RGB PWM data
    DMAFilter(&DMASrc, &pwm, &DMACount, min(DMACount, end - pwm));

    // Rest of buffer
  if (pwm < end)
    SrcFilterNull(NULL, &pwm, NULL, end - pwm);
  }
}

void WS2812B_DMA_HANDLER(void)
{
  if (DMA_GetITStatus(WS2812B_DMA_IT_HT) != RESET)
  {
    DMA_ClearITPendingBit(WS2812B_DMA_IT_HT);
    DMASendNext(DMABuffer, &DMABuffer[WS2812B_BUFFER_SIZE / 2]);
  }

  if (DMA_GetITStatus(WS2812B_DMA_IT_TC) != RESET)
  {
    DMA_ClearITPendingBit(WS2812B_DMA_IT_TC);
    DMASendNext(&DMABuffer[WS2812B_BUFFER_SIZE / 2], &DMABuffer[WS2812B_BUFFER_SIZE]);
  }
}

//------------------------------------------------------------
// Interface
// DMA产生PWM波，这个是stm32的一个功能
// 数据由DMABuffe，通过DMA方式，发送到WS2812B_TIM_DMA_CCR
// 
//------------------------------------------------------------

void ws2812b_Init(void)
{
  // Turn on peripheral clock
  /*
    RCC_APB1Periph_TIM4
    Peripherals 外设
    APB (Advanced Peripheral Bus) 作为高级外设总线是AMBA协议之一，也是最基本的总线协议。
    2个高级定时器（1，8），4个普通定时器（2，3，4，5），2个基本定时器（6，7），2个看门狗定时器，1个系统嘀嗒定时器
    普通定时器，具有测量输入信号的脉冲长度( 输入捕获) 或者产生输出波形( 输出比较和PWM)
  */
  RCC_APB1PeriphClockCmd(WS2812B_APB1_RCC, ENABLE);  // 自定义
  // RCC_APB2Periph_GPIOB， GPIO端口使能
  RCC_APB2PeriphClockCmd(WS2812B_APB2_RCC, ENABLE);  // 自定义
  // RCC_AHBPeriph_DMA1, AHB=Advanced High Performance Bus，高级高性能总线。
  RCC_AHBPeriphClockCmd(WS2812B_AHB_RCC, ENABLE);

  // Initialize GPIO pin
  GPIO_InitTypeDef GPIO_InitStruct;

  // GPIO_StructInit(&GPIO_InitStruct);
  // GPIO_Pin_6
  GPIO_InitStruct.GPIO_Pin = WS2812B_GPIO_PIN;  // 自定义
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;

  GPIO_Init(WS2812B_GPIO, &GPIO_InitStruct);

  // Initialize timer clock
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

  //TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
  // 72000000 / (72000000 / 24000000) = 24000000
  // 1 / 24000000 * 30 = 1.25us  = 0.85us + 0.4us
  // SystemCoreClock SYSCLK_FREQ_72MHz  72000000
  // WS2812B_FREQUENCY       24000000
  TIM_TimeBaseInitStruct.TIM_Prescaler = (SystemCoreClock / WS2812B_FREQUENCY) - 1;
  TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
  // WS2812B_PERIOD          30
  TIM_TimeBaseInitStruct.TIM_Period = WS2812B_PERIOD - 1;
  TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;

  TIM_TimeBaseInit(WS2812B_TIM, &TIM_TimeBaseInitStruct);

  // Initialize timer PWM
  TIM_OCInitTypeDef TIM_OCInitStruct;

  //TIM_OCStructInit(&TIM_OCInitStruct);

  TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_Pulse = 0;
  TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;

  // WS2812B_TIM TIM4
	// WS2812B_TIM_OCINIT TIM_OC1Init 初始化CH1
  WS2812B_TIM_OCINIT(WS2812B_TIM, &TIM_OCInitStruct);  // 自定义
  // WS2812B_TIM_OCPRELOAD TIM_OC1PreloadConfig  CH1预装载使能
  WS2812B_TIM_OCPRELOAD(WS2812B_TIM, TIM_OCPreload_Enable);

  // Initialize DMA channel
  DMA_InitTypeDef DMA_InitStruct;

  //DMA_StructInit(&DMA_InitStruct);
  // WS2812B_TIM_DMA_CCR     (WS2812B_TIM->CCR1) (TIM4->CCR1)  TIM4((TIM_TypeDef *)
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t) & WS2812B_TIM_DMA_CCR;  // 自定义，外设基址
  DMA_InitStruct.DMA_MemoryBaseAddr = (uint32_t) DMABuffer;
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStruct.DMA_BufferSize = sizeof(DMABuffer) / sizeof(uint16_t);
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	// DMA优先级
  DMA_InitStruct.DMA_Priority = DMA_Priority_High;  // 考虑自定义
  DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;

  DMA_Init(WS2812B_DMA_CHANNEL, &DMA_InitStruct);

  // Turn on timer DMA requests
	// WS2812B_TIM_DMA_CC      TIM_DMA_CC1
  TIM_DMACmd(WS2812B_TIM, WS2812B_TIM_DMA_CC, ENABLE); // 自定义,与CCR1对应

  // Initialize DMA interrupt
  NVIC_InitTypeDef NVIC_InitStruct;

  NVIC_InitStruct.NVIC_IRQChannel = WS2812B_DMA_IRQ;
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = WS2812B_IRQ_PRIO;
  NVIC_InitStruct.NVIC_IRQChannelSubPriority = WS2812B_IRQ_SUBPRIO;
  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

  NVIC_Init(&NVIC_InitStruct);

  // Enable DMA interrupt
  DMA_ITConfig(WS2812B_DMA_CHANNEL, DMA_IT_HT | DMA_IT_TC, ENABLE);
}

inline int ws2812b_IsReady(void)
{
  return !DMABusy;
}

void ws2812b_SendRGB(RGB_t *rgb, unsigned count)
{
  DMASend(&SrcFilterRGB, rgb, count);
}

void ws2812b_SendHSV(HSV_t *hsv, unsigned count)
{
  DMASend(&SrcFilterHSV, hsv, count);
}

void ws2812b_SendHEX(HEX_t *hex, unsigned count)
{
  DMASend(&SrcFilterHEX, hex, count);
}
