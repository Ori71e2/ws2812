#include "fft.h"
#include "mike.h"
#include "math.h"
#include "led.h"
#include "OLED.h"
#include "ssd1306.h"
RGB_t ledsRGB[NUM_LEDS];
RGB_t ledsRGB2[NUM_LEDS];
HSV_t ledsHSV[NUM_LEDS];
HSV_t ledsHSV2[NUM_LEDS];
static int32_t pre_num = 0, next_num = 0;
static int32_t first = 0;
void fft_liner_show_led1(void)
{
	uint32_t max_value = 0;
	for (int i = 0; i < SAMPLS_NUM; i++)
	{
		if (max_value < ADC_SourceData[i])
		{
			max_value = ADC_SourceData[i];
		}
	}
	float f_num = NUM_LEDS * max_value / MIKE_OUT_MAX_ADC_VALUE;
	int32_t i_num = NUM_LEDS * max_value / MIKE_OUT_MAX_ADC_VALUE;
	if (NUM_LEDS - f_num < 0.5)
	{
		i_num = NUM_LEDS;
	}
	
	// OLED_ShowNum(3, 1, i_num, 5);
	// OLED_ShowNum(4, 1, max_value, 5);
	led_Clear_RGB(ledsRGB, NUM_LEDS);
  // led_Fill_Solid_RGB(ledsRGB, i_num, RGB(255, 0, 0));
	led_Fill_Gradient_RGB(ledsRGB, NUM_LEDS, RGB(0, 0, 255), RGB(255, 0, 0));
	for (int i = i_num; i < NUM_LEDS; i++)
	{
		ledsRGB[i].r = 0;
		ledsRGB[i].g = 0;
		ledsRGB[i].b = 0;
	}
	led_Show_RGB(ledsRGB, NUM_LEDS);
	// led_Clear_HSV(ledsHSV, NUM_LEDS);
	// led_Clear_HSV(ledsHSV2, NUM_LEDS);
	// led_Fill_Gradient_HSV(ledsHSV, i_num, HSV(0, 255, 255), HSV((0 + 240) * i_num / NUM_LEDS, 255, 255));
	// for (int i = 0; i < i_num; i++)
	// {
	// 	(ledsHSV2 + i)->h = (ledsHSV + i_num - i - 1)->h;
	// 	(ledsHSV2 + i)->s = (ledsHSV + i_num - i - 1)->s;
	// 	(ledsHSV2 + i)->v = (ledsHSV + i_num - i - 1)->v;
	// }
	// led_Show_HSV(ledsHSV2, NUM_LEDS);
}

void fft_liner_show_led2(void)
{
	uint32_t max_value = 0;
	int32_t gap = 0;
	for (int i = 0; i < SAMPLS_NUM; i++)
	{
		if (max_value < ADC_SourceData[i])
		{
			max_value = ADC_SourceData[i];
		}
	}
	float f_num = NUM_LEDS * max_value / MIKE_OUT_MAX_ADC_VALUE;
	next_num = NUM_LEDS * max_value / MIKE_OUT_MAX_ADC_VALUE;
	if (NUM_LEDS - f_num < 0.5)
	{
		next_num = NUM_LEDS;
	}
	gap = next_num - pre_num;
	if (first == 0)
	{
		led_Clear_RGB(ledsRGB, NUM_LEDS);
		led_Fill_Gradient_RGB(ledsRGB2, NUM_LEDS, RGB(0, 0, 255), RGB(255, 0, 0));
		first = 1;
	}
	if (gap == 0)
	{
	}
	else if (gap > 0)
	{
		for (int poisition = pre_num; poisition < next_num; poisition++)
		{
			ledsRGB[poisition].r = ledsRGB2[poisition].r;
			ledsRGB[poisition].g = ledsRGB2[poisition].g;
			ledsRGB[poisition].b = ledsRGB2[poisition].b;
			led_Show_RGB(ledsRGB, NUM_LEDS);
		  delay_us(MIKE_SHOW_GAP_TIME / 1 / gap);	
		}
	}
	else if (gap < 0)
	{
		for (int poisition = pre_num - 1; poisition >= next_num; poisition--)
		{
			ledsRGB[poisition].r = 0;
			ledsRGB[poisition].g = 0;
			ledsRGB[poisition].b = 0;
			led_Show_RGB(ledsRGB, NUM_LEDS);
			delay_us(MIKE_SHOW_GAP_TIME / 1 / (-gap));
		}
	}
	pre_num = next_num;
}
/****************************************************************************
* 名称：GUI_LineWith()
* 功能：画任意两点之间的直线，并且可设置线的宽度。
* 入口参数： x0		直线起点的x坐标值
*           y0		直线起点的y坐标值
*           x1      直线终点的x坐标值
*           y1      直线终点的y坐标值
*           with    线宽(0-50)
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_LineWidth(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint8_t with, uint8_t color)
{  
	 int32_t   dx;						// 直线x轴差值变量
   int32_t   dy;          			// 直线y轴差值变量
   int8_t    dx_sym;					// x轴增长方向，为-1时减值方向，为1时增值方向
   int8_t    dy_sym;					// y轴增长方向，为-1时减值方向，为1时增值方向
   int32_t   dx_x2;					// dx*2值变量，用于加快运算速度
   int32_t   dy_x2;					// dy*2值变量，用于加快运算速度
   int32_t   di;						// 决策变量
   
   int32_t   wx, wy;					// 线宽变量
   int32_t   draw_a, draw_b;
   
   /* 参数过滤 */
   if(with==0) return;
   if(with>50) with = 50;
   
   dx = x1-x0;						// 求取两点之间的差值
   dy = y1-y0;
   
   wx = with/2;
   wy = with-wx-1;
   
   /* 判断增长方向，或是否为水平线、垂直线、点 */
   if(dx>0)							// 判断x轴方向
   {  dx_sym = 1;					// dx>0，设置dx_sym=1
   }
   else
   {  if(dx < 0)
      {  dx_sym = -1;				// dx<0，设置dx_sym=-1
      }
      else
      {  /* dx==0，画垂直线，或一点 */
         wx = x0-wx;
         if(wx<0) wx = 0;
         wy = x0+wy;
         
         while(1)
         {  x0 = wx;
            ssd1306_DrawVLine(x0, y0, y1, color);
            if(wx>=wy) break;
            wx++;
         }
         
      	 return;
      }
   }
   
   if(dy>0)							// 判断y轴方向
   {  dy_sym = 1;					// dy>0，设置dy_sym=1
   }
   else
   {  if(dy<0)
      {  dy_sym = -1;				// dy<0，设置dy_sym=-1
      }
      else
      {  /* dy==0，画水平线，或一点 */
         wx = y0-wx;
         if(wx<0) wx = 0;
         wy = y0+wy;
         
         while(1)
         {  y0 = wx;
            ssd1306_DrawHLine(x0, y0, x1, color);
            if(wx>=wy) break;
            wx++;
         }
      	 return;
      }
   }
    
   /* 将dx、dy取绝对值 */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* 计算2倍的dx及dy值 */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* 使用Bresenham法进行画直线 */
   if(dx>=dy)						// 对于dx>=dy，则使用x轴为基准
   {  di = dy_x2 - dx;
      while(x0!=x1)
      {  /* x轴向增长，则宽度在y方向，即画垂直线 */
         draw_a = y0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = y0+wy;
         ssd1306_DrawVLine(x0, draw_a, draw_b, color);
         
         x0 += dx_sym;				
         if(di<0)
         {  di += dy_x2;			// 计算出下一步的决策值
         }
         else
         {  di += dy_x2 - dx_x2;
            y0 += dy_sym;
         }
      }
      draw_a = y0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = y0+wy;
      ssd1306_DrawVLine(x0, draw_a, draw_b, color);
   }
   else								// 对于dx<dy，则使用y轴为基准
   {  di = dx_x2 - dy;
      while(y0!=y1)
      {  /* y轴向增长，则宽度在x方向，即画水平线 */
         draw_a = x0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = x0+wy;
         ssd1306_DrawHLine(draw_a, y0, draw_b, color);
         
         y0 += dy_sym;
         if(di<0)
         {  di += dx_x2;
         }
         else
         {  di += dx_x2 - dy_x2;
            x0 += dx_sym;
         }
      }
      draw_a = x0-wx;
      if(draw_a<0) draw_a = 0;
      draw_b = x0+wy;
      ssd1306_DrawHLine(draw_a, y0, draw_b, color);
   } 
  
}
uint8_t prt = 512 / 64;	//量化显示的比例
void fft_arr_show_oled1(void)
{
	uint16_t i = 0;
	uint8_t x = 0;
	uint8_t y = 0;
	ssd1306_Clear();
	/*******************显示*******************/
	for(i = 0; i < 32; i++)	//间隔的取32个频率出来显示
	{
		x = (i<<2);	//i*4
		y = 63 -(FFT_Mag[x+1] / prt) - 2;	//加1是为了丢掉第一个直流分量
		if(y > 63)
		{
			y = 63;
		}
	  GUI_LineWidth(x,y,x,63,3,1);
		
	// 	//画下落的点
	// 	if(fall_pot[i]>y) fall_pot[i] = y;
	// 	else
	// 	{
	// 			if(fall_pot[i]>63) fall_pot[i]=63;
	// 			GUI_LineWith(x,fall_pot[i],x,fall_pot[i]+3,3,1);
	// 			fall_pot[i] += 2 ;
	// 	}
	}
	// GUI_Exec();
}
