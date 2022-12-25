#include "app_fft.h"
#include "drv_adc.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#include "math.h"






u32 FFT_SourceData[SAMPLS_NUM] = {0};	//fftÊäÈëÐòÁÐ
u32 FFT_OutData[SAMPLS_NUM] = {0};		//fftÊä³öÐòÁÐ
u32 FFT_Mag[SAMPLS_NUM/2] = {0};		//·ùÆµÌØÐÔÐòÁÐ£¨ÐòºÅ´ú±íÆµÂÊ·ÖÁ¿£¬Öµ´ú±í·ùÖµ´óÐ¡¡£ÓÉÓÚFFTµÄÆµÆ×½á¹ûÊÇ¹ØÓÚÄÎ¿üË¹ÌØÆµÂÊ¶Ô³ÆµÄ£¬ËùÒÔÖ»¼ÆËãÒ»°ëµÄµã¼´¿É£©


#if 0
/****************************************************************************************************
º¯ÊýÃû³Æ:InitBufInArray()
º¯Êý¹¦ÄÜ:Ä£Äâ²ÉÑùÊý¾Ý£¬²ÉÑùÊý¾ÝÖÐ°üº¬3ÖÖÆµÂÊÕýÏÒ²¨(350Hz£¬8400Hz£¬18725Hz)
²ÎÊýËµÃ÷:
±¸     ×¢:ÔÚlBufInArrayÊý×éÖÐ£¬Ã¿¸öÊý¾ÝµÄ¸ß16Î»´æ´¢²ÉÑùÊý¾ÝµÄÊµ²¿£¬µÍ16Î»´æ´¢²ÉÑùÊý¾ÝµÄÐé²¿(×ÜÊÇÎª0)
****************************************************************************************************/

u16 lBufInArray[SAMPLS_NUM];

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

/********************************************************************************************************
º¯ÊýÃû³Æ:GetPowerMag()
º¯Êý¹¦ÄÜ:¼ÆËã¸÷´ÎÐ³²¨·ùÖµ
²ÎÊýËµÃ÷:
±¸¡¡¡¡×¢:ÏÈ½«ADC_FFT_OutData·Ö½â³ÉÊµ²¿(X)ºÍÐé²¿(Y)£¬È»ºó¼ÆËã·ùÆµÌØÐÔÐòÁÐFFT_Mag
         ±¾º¯Êý²Î¿¼ÍøÒ³£ºhttps://wenku.baidu.com/view/08ccee0984868762cbaed532.html£¬¹ØÓÚ·ùÆµÌØÐÔ¼ÆËã²¿·Ö
**********************************************************************************************************/
void GetPowerMag(void)
{
	signed short lX,lY;
	float X,Y,Mag;
	unsigned short i;

	#if 1
	for(i=0; i<SAMPLS_NUM/2; i++)
	{
		lX = (FFT_OutData[i] << 16) >> 16;
		lY = (FFT_OutData[i] >> 16);
		
		X = SAMPLS_NUM * ((float)lX) / 32768;
		Y = SAMPLS_NUM * ((float)lY) / 32768;
		
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

/************************************************
*ÓÉÓÚÔÚfftÔËËã¹ý³ÌÖÐ²»ÔÊÐíÔ´Êý¾Ý¸üÐÂ
*½«Ô´Êý¾Ý¿½±´µ½ÁíÒ»¿éÄÚ´æ
*´Ë²½Öè¿ÉÒÔ±»Ìæ»»Îª£º½øÐÐfftÔËËãÊ±£¬¹Ø±Õadc×ª»»
*************************************************/
void Get_FFT_Source_Data(EN_FFT_CHANNEL channel_idx)
{
	u16 i,j;

	for(i=0; i<SAMPLS_NUM; i++)
	{
		#if SINGLECHANNEL
		FFT_SourceData[i] = (u32)ADC_SourceData[i];
		#else
		FFT_SourceData[i] = (u32)ADC_SourceData[i][channel_idx];
		#endif
	}
}

void FFT_test(void)
{
	//InitBufInArray();
	Get_FFT_Source_Data(FFT_CHANNEL_1);
	cr4_fft_1024_stm32(FFT_OutData, FFT_SourceData, SAMPLS_NUM);
	GetPowerMag();
}

void Test_Time_Func(void)			//test time
{
	static bool fg = 1;

	fg = !fg;
	
	if(fg)
	{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}else{
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
}
