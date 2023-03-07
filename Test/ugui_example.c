#include "stm32f10x.h"
#include "delay.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
#include "ugui.h"
void ugui_example(void)
{
	UG_GUI my_ugui1;
	//初始化函数
	UG_Init(&my_ugui1, ssd1306_SetPoint, MAX_X, MAX_Y);
	//选择GUI
	UG_SelectGUI(&my_ugui1);
	//选择字体
	UG_FontSelect(&FONT_8X8);
	//字符显示
	UG_PutChar('B', 20, 20, C_WHITE, C_BLACK);
	delay_ms(500);
	ssd1306_Clear();
	//全屏填充函数
	UG_FillScreen(C_WHITE);
	delay_ms(1000);
	ssd1306_Clear();
	//矩形填充
	UG_FillFrame(0, 0, 50, 50, C_WHITE);
	delay_ms(1000);
	ssd1306_Clear();
	//圆角矩形填充
	UG_FillRoundFrame(0, 0, 50, 50, 10, C_WHITE);
	delay_ms(1000);
	ssd1306_Clear();
	//字符串测试
	UG_FontSelect(&FONT_16X26);
	UG_SetBackcolor(C_BLACK);
	UG_SetForecolor(C_WHITE);
	UG_PutString(0, 0, "Hello Wlord!");
	delay_ms(1000);
	ssd1306_Clear();
}
