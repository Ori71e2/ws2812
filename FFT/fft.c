#include "fft.h"
#include "mike.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#include "math.h"
#include "OLED.h"
int32_t FFT_SourceData[SAMPLS_NUM] = {0};	//
int32_t FFT_OutData[SAMPLS_NUM] = {0};		//
int32_t FFT_Mag[SAMPLS_NUM/2] = {0};		  // 

void GetPowerMag(void)
{
	int16_t lX,lY;
	float X,Y,Mag;
	uint16_t i;
  // 除以32768再乘65536是为了符合浮点数计算规律
  // 目的就是把数据浮点化，至于为什么是除以32768。可以这么说，浮点化就好像10进制里面的科学计数法。
	// 32768=2的15次。除以32768也就是去除了浮点数后面的那个基数，只剩下前面的。
	// 1991改写成1.991*10的三次幂，再除以10的三次方，只剩下1.991，便于余下的运算。
	// 至于最后一句要乘以65536是因为我们定义的数据和我们需要求得的数据都是无符号32位的，
	// 之前已经把32位的数据拆开又分别浮点化了又开了个根号，所以再把它变回来 只需要乘以2的16次，也就是65536。
	// 比如说问你什么时候生日，你说是19911030，然而DSP是不习惯这么干的，他需要把它拆开为1991和1030。再写成1.991x10的3次方和1.030x10的3次方。然后才能进行其他的运算。
	for(i = 0; i < SAMPLS_NUM/2; i++)
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
}

// 从adc数据源复制数据
void Get_FFT_Source_Data()
{
	uint16_t i;
  // uint16_t j;

	for(i=0; i < SAMPLS_NUM; i++)
	{
		// FFT_SourceData[i] = (uint32_t)(ADC_SourceData[i]);
		FFT_SourceData[i] = ((int32_t)ADC_SourceData[i]-2048) << 16;
	}
}

void FFT_test(void)
{
	// InitBufInArray();
	Get_FFT_Source_Data();
	cr4_fft_64_stm32(FFT_OutData, FFT_SourceData, SAMPLS_NUM);
	GetPowerMag();
	// OLED_ShowNum(2, 1, FFT_Mag[1], 5);
	// OLED_ShowNum(3, 1, FFT_Mag[10], 5);
	// OLED_ShowNum(4, 1, FFT_Mag[20], 5);
	// OLED_ShowNum(4, 1, FFT_Mag[31], 5);
	// OLED_ShowNum(4, 1, ADC_SourceData[30], 5);
	fft_liner_show_led2();
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
