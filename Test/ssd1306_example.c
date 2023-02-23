#include "stm32f10x.h"
#include "delay.h"
#include "ssd1306.h"

int ssd1306_example(void)
{
	ssd1306_Fill_all();
  // ssd1306_ZFC(0, 0, "DRAGON");//在ssd1306屏幕的X轴为0，Y轴为0，显示字符串“DRAGON”

  // ssd1306_ZFC(21, 3, "Hello 2022,I Love You!!!!!!!!!");//在ssd1306屏幕的X轴为21，Y轴为3，显示字符串“Hello 2022,I Love You!!!!!!!!!”，不够显示自动换行

  // ssd1306_ZFC(4, 6, "2022");//在ssd1306屏幕的X轴为4，Y轴为6，显示字符串“2022”
}
