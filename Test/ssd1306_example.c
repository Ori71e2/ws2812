#include "stm32f10x.h"
#include "delay.h"
#include "OLED.h"

int ssd1306_example(void)
{
  Delay_Init();//延时初始化
  OLED_Init();//OLED_SPI初始化
  OLED_ZFC(0, 0, "DRAGON");//在OLED屏幕的X轴为0，Y轴为0，显示字符串“DRAGON”

  OLED_ZFC(21, 3, "Hello 2022,I Love You!!!!!!!!!");//在OLED屏幕的X轴为21，Y轴为3，显示字符串“Hello 2022,I Love You!!!!!!!!!”，不够显示自动换行

  OLED_ZFC(4, 6, "2022");//在OLED屏幕的X轴为4，Y轴为6，显示字符串“2022”
}
