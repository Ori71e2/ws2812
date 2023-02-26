#include "stm32f10x.h"
#include "delay.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
int ssd1306_example(void)
{
  /// ssd1306_Fill_all();
  ssd1306_Write_String(0, 0, (uint8_t *)"DRAGON");//在ssd1306屏幕的X轴为0，Y轴为0，显示字符串“DRAGON”
	delay_s(2);
  ssd1306_Write_String(21, 3, (uint8_t *)"Hello 2022,I Love You!!!!!!!!!");//在ssd1306屏幕的X轴为21，Y轴为3，显示字符串“Hello 2022,I Love You!!!!!!!!!”，不够显示自动换行
  delay_s(2);
  // ssd1306_Write_String(4, 6, (uint8_t *)"2022");//在ssd1306屏幕的X轴为4，Y轴为6，显示字符串“2022”
	for (uint8_t i = 0; i < MAX_Y; i++)
	{
		ssd1306_SetPoint(i, i, 1);
	}
	ssd1306_DrawLine(0, 0, MAX_X - 1, MAX_Y - 1, 1);
}
