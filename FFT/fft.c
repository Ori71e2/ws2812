#include "fft.h"
#include "mike.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#include "math.h"
#include "OLED.h"
uint32_t FFT_SourceData[SAMPLS_NUM] = {0};	//
uint32_t FFT_OutData[SAMPLS_NUM] = {0};		//
uint32_t FFT_Mag[SAMPLS_NUM/2] = {0};		  // 


#if 0

uint16_t lBufInArray[SAMPLS_NUM];

void InitBufInArray(void)
{
	unsigned short i;
	float fx;
	for(i=0; i<SAMPLS_NUM; i++)
	{
		fx = 1500 * sin(PI2 * i * 55.6 / Fs);
		lBufInArray[i] = ((signed short)fx)<<16;
	}
}
#endif

void GetPowerMag(void)
{
	signed short lX,lY;
	float X,Y,Mag;
	unsigned short i;

	#if 1
	for(i=0; i<SAMPLS_NUM/2; i++)
	{
		lX = (FFT_OutData[i] << 16) >> 16;              // 取低16位；先向高位移动16位，高位被低位取代，低位为0；然后再向低位移动16位，这样高位全为0。
		lY = (FFT_OutData[i] >> 16);                    // 取高16位。
		
		X = SAMPLS_NUM * ((float)lX) / 32768;           // 32768 = 0x8000
		Y = SAMPLS_NUM * ((float)lY) / 32768;           // 
		
		Mag = sqrt(X * X + Y * Y) / SAMPLS_NUM;
		
		if(i == 0)
			FFT_Mag[i] = (unsigned long)(Mag * 32768);
		else
			FFT_Mag[i] = (unsigned long)(Mag * 65536);
		//printf("%ld\r\n",lBufMagArray[i]);
	}
	//printf("\r\n\r\n");
	#else
	for(i=0; i<SAMPLS_NUM/2; i++)
	{
		X = (FFT_OutData[i] << 16) >> 16;
		Y = (FFT_OutData[i] >> 16);
		FFT_Mag[i] = sqrt(X * X + Y * Y);
	}
	#endif
}

// 从adc数据源复制数据
void Get_FFT_Source_Data()
{
	uint16_t i;
  // uint16_t j;

	for(i=0; i<SAMPLS_NUM; i++)
	{
		FFT_SourceData[i] = (uint32_t)(ADC_SourceData[i]);
	}
}

void FFT_test(void)
{
	// InitBufInArray();
	Get_FFT_Source_Data();
	cr4_fft_64_stm32(FFT_OutData, FFT_SourceData, SAMPLS_NUM);
	GetPowerMag();
	OLED_ShowNum(2, 1, FFT_Mag[1], 5);
	OLED_ShowNum(3, 1, FFT_Mag[10], 5);
	OLED_ShowNum(4, 1, FFT_Mag[20], 5);
	OLED_ShowNum(4, 1, FFT_Mag[31], 5);
	// OLED_ShowNum(4, 1, ADC_SourceData[30], 5);
	fft_liner_show_led(FFT_Mag);
}

void Test_Time_Func(void)			//test time
{
	static int fg = 1;

	fg = !fg;
	
	if(fg)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}else{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
}
