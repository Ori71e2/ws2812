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
  // ����32768�ٳ�65536��Ϊ�˷��ϸ������������
  // Ŀ�ľ��ǰ����ݸ��㻯������Ϊʲô�ǳ���32768��������ô˵�����㻯�ͺ���10��������Ŀ�ѧ��������
	// 32768=2��15�Ρ�����32768Ҳ����ȥ���˸�����������Ǹ�������ֻʣ��ǰ��ġ�
	// 1991��д��1.991*10�������ݣ��ٳ���10�����η���ֻʣ��1.991���������µ����㡣
	// �������һ��Ҫ����65536����Ϊ���Ƕ�������ݺ�������Ҫ��õ����ݶ����޷���32λ�ģ�
	// ֮ǰ�Ѿ���32λ�����ݲ��ֱַ𸡵㻯���ֿ��˸����ţ������ٰ�������� ֻ��Ҫ����2��16�Σ�Ҳ����65536��
	// ����˵����ʲôʱ�����գ���˵��19911030��Ȼ��DSP�ǲ�ϰ����ô�ɵģ�����Ҫ������Ϊ1991��1030����д��1.991x10��3�η���1.030x10��3�η���Ȼ����ܽ������������㡣
	for(i = 0; i < SAMPLS_NUM/2; i++)
	{
		lX = (FFT_OutData[i] << 16) >> 16;              // ȡ��16λ�������λ�ƶ�16λ����λ����λȡ������λΪ0��Ȼ�������λ�ƶ�16λ��������λȫΪ0��
		lY = (FFT_OutData[i] >> 16);                    // ȡ��16λ��
		
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

// ��adc����Դ��������
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
