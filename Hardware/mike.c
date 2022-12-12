#include "mike.h"
#include "mike_conf.h"

#if SINGLECHANNEL
static uint16_t ADC_SourceData[SAMPLS_NUM] = {0};
#else
static uint16_t ADC_SourceData[SAMPLS_NUM][ADC_CHANNEL_NUMS] = {0};
#endif
static volatile int ADCFinish;
/***********************************************************************************************************************************************
*adc初始化配置
*1.目     的：用ADC采样值进行fft运算，求取采样后波形相关属性（本例主要分析50Hz正选波，及高/低次谐波）
*2.方     案：计划ADC采样频率为512Hz，采样1024个点进行fft运算，使频域分辨率达到0.5Hz
*3.配     置：由于ADC本身不能配置到512Hz，采用tim3定时触发采样
*4.其     他：当系统时钟为72MHz时，ADC时钟最慢是9MHz，采样周期最大约为256个时钟周期，所以ADC本身采样频率最慢约为35156.25Hz（大于我需要的512Hz）
*            为什么要选512Hz：由于采用标准fft基4算法（采样点数必须是4的倍数），为了使频域分辨率为识别方便（0.5Hz），又为了满足采样定理
*            本来计划采样5120个点（使频域分辨率达到0.1Hz），但是单片机RAM空间不够，有条件的可以尝试
*5.相关知识：采样定理：采样频率需大于被采样波形频率的两倍
*            频域分辨率 = fs/N，（fs：采样频率，N：采样点数）
*            幅频特性序列：FFT_Mag[i]代表的意思，频率分量为i*(fs/N)的幅值为FFT_Mag[i]
************************************************************************************************************************************************/
void mike_Init(void)
{
	// ADC_GPIO_Configuration();
	
	//ADC_TIM2_Configuration();

	// ADC_TIM3_Configuration();

	// ADC_DMA_Configuration();

	// ADC_Configuration();


	RCC_APB1PeriphClockCmd(MIKE_APB1_RCC, ENABLE);
	RCC_APB2PeriphClockCmd(MIKE_APB2_RCC, ENABLE);				// 使能GPIOB时钟
	RCC_AHBPeriphClockCmd(MIKE_AHB_RCC, ENABLE);


	GPIO_InitTypeDef GPIO_InitStructure;
 
	GPIO_InitStructure.GPIO_Pin = MIKE_GPIO_PIN;		     // 管脚0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;				 // 模拟输入模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MIKE_GPIO, &GPIO_InitStructure);					 // GPIO组
	

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	
	TIM_TimeBaseInitStructure.TIM_Period = MIKE_PERIOD - 1;							// 设置512Hz采样频率
	TIM_TimeBaseInitStructure.TIM_Prescaler = (SystemCoreClock / MIKE_FREQUENCY) - 1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				  // 时钟分频，TIM3是通用定时器，基本定时器不用设置
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;			// 向上扫描
	TIM_TimeBaseInit(MIKE_TIM, &TIM_TimeBaseInitStructure);
	
	TIM_SelectOutputTrigger(MIKE_TIM, TIM_TRGOSource_Update);					  // 选择TRGO作为触发源为定时器更新时间

	TIM_Cmd(MIKE_TIM, ENABLE);															            // 开启定时器


	DMA_InitTypeDef  DMA_InitStructure;

	DMA_DeInit(MIKE_DMA_CHANNEL);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) & MIKE_TIM_DMA_CCR;
	DMA_InitStructure.DMA_MemoryBaseAddr     = (u32)ADC_SourceData;
	DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;
	#if SINGLECHANNEL
	DMA_InitStructure.DMA_BufferSize         = sizeof(ADC_SourceData) / sizeof(uint16_t); // SAMPLS_NUM
	#else
	DMA_InitStructure.DMA_BufferSize         = sizeof(ADC_SourceData) / sizeof(uint16_t); // ADC_CHANNEL_NUMS*SAMPLS_NUM
	#endif
	DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode               = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
	DMA_Init(MIKE_DMA_CHANNEL, &DMA_InitStructure);

	DMA_Cmd(MIKE_DMA_CHANNEL, ENABLE);//使能DMA	

	// ADC_DMA_NVIC_Configuration
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = MIKE_DMA_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MIKE_IRQ_PRIO;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority	= MIKE_IRQ_SUBPRIO;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	DMA_ITConfig(MIKE_DMA_CHANNEL, MIKE_DMA_IT_TC, ENABLE);

	DMA_ClearITPendingBit(MIKE_DMA_IT_TC);

	ADC_InitTypeDef  ADC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);

	ADC_DeInit(MIKE_ADC);
	ADC_InitStructure.ADC_Mode               = ADC_Mode_Independent;
	#if SINGLECHANNEL
	ADC_InitStructure.ADC_ScanConvMode       = DISABLE;								//如果是多通道，打开扫描模式
	ADC_InitStructure.ADC_NbrOfChannel       = 1;
	#else
	ADC_InitStructure.ADC_ScanConvMode       = ENABLE;								//如果是单通道，关闭扫描模式
	ADC_InitStructure.ADC_NbrOfChannel       = ADC_CHANNEL_NUMS;
	#endif
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_T3_TRGO;					//选择TIM3外部触发
	ADC_InitStructure.ADC_DataAlign          = ADC_DataAlign_Right;
	ADC_Init(MIKE_ADC, &ADC_InitStructure);

	//==========================================================================   
	ADC_RegularChannelConfig(MIKE_ADC, MIKE_CHANNEL,  MIKE_CHANNEL_RANK, ADC_SampleTime_239Cycles5);	//AI_VS_A1
	#if (!SINGLECHANNEL)
	ADC_RegularChannelConfig(MIKE_ADC, ADC_Channel_4,  2, ADC_SampleTime_239Cycles5);	//AI_VS_B1
	ADC_RegularChannelConfig(MIKE_ADC, ADC_Channel_5,  3, ADC_SampleTime_239Cycles5);	//AI_VS_C1
	#endif

	ADC_DMACmd(MIKE_ADC, ENABLE);
	
	ADC_Cmd(MIKE_ADC, ENABLE);
	
	ADC_ResetCalibration(MIKE_ADC);
	while(ADC_GetResetCalibrationStatus(MIKE_ADC));
	ADC_StartCalibration(MIKE_ADC);
	while(ADC_GetCalibrationStatus(MIKE_ADC));

	ADC_ExternalTrigConvCmd(MIKE_ADC, ENABLE);
	//ADC_SoftwareStartConvCmd(MIKE_ADC, ENABLE);
}

//ADC_DMA中断服务程序
void WS2812B_DMA_HANDLER(void)
{
	if(DMA_GetITStatus(MIKE_DMA_IT_TC) != RESET)
	{
		ADCFinish = 1;
		DMA_ClearITPendingBit(MIKE_DMA_IT_TC);
	}
}


inline int mike_IsReady(void)
{
  return ADCFinish;
}