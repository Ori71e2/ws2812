#include "stm32f10x.h"
#include "delay.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
#include "ugui.h"

void window1_callback(UG_MESSAGE* msg)
{
	if(msg->type == MSG_TYPE_OBJECT)
	{
		if(msg->id == OBJ_TYPE_BUTTON)
		{
			switch(msg->sub_id)
			{
				case BTN_ID_0:
				{
					// . . .
					break;
				}
					case BTN_ID_1:
				{
					// . . .
					break;
				}
					case BTN_ID_2:
				{
					// . . .
					break;
				}
			}
		}
	}
}
#define MAX_OBJECTS 10
void window_test(void)
{
	UG_WINDOW window_1;
	UG_BUTTON button_1;
	UG_BUTTON button_2;
	UG_BUTTON button_3;
	UG_TEXTBOX textbox_1;
	UG_OBJECT obj_buff_wnd_1[MAX_OBJECTS];
	// . . .
	UG_WindowCreate(&window_1, obj_buff_wnd_1, MAX_OBJECTS, window1_callback);
	UG_WindowSetTitleText(&window_1, "uGUI Demo Window");
	UG_WindowSetTitleTextFont(&window_1, &FONT_12X20);
	UG_ButtonCreate(&window_1, &button_1, BTN_ID_0, 10, 10, 110, 60);
	// UG_ButtonCreate(&window_1, &button_2, BTN_ID_1, 10, 80, 110, 130);
	// UG_ButtonCreate(&window_1, &button_3, BTN_ID_2, 10, 150, 110, 200);
	UG_ButtonSetFont(&window_1, BTN_ID_0, &FONT_12X20);
	UG_ButtonSetText(&window_1, BTN_ID_0, "Button\nA");
	// UG_ButtonSetFont(&window_1, BTN_ID_1, &FONT_12X20);
	// UG_ButtonSetText(&window_1, BTN_ID_1, "Button\nB");
	// UG_ButtonSetFont(&window_1, BTN_ID_2, &FONT_12X20);
	// UG_ButtonSetText(&window_1, BTN_ID_2, "Button\nC");
	// UG_TextboxCreate(&window_1, &textbox_1, TXB_ID_0, 120, 10, 310, 200);
	// UG_TextboxSetFont(&window_1, TXB_ID_0, &FONT_12X16);
	// UG_TextboxSetText(&window_1, TXB_ID_0, "This is just \na very simple \nwindow to \ndemonstrate \nsome basic \n features of uGUI!");
	// UG_TextboxSetForeColor(&window_1, TXB_ID_0, C_BLACK);
	// UG_TextboxSetAlignment(&window_1, TXB_ID_0, ALIGN_CENTER);
	UG_WindowShow(&window_1);
	// . . .
}
void ugui_example(void)
{
	UG_GUI my_ugui1;
	//初始化函数
	UG_Init(&my_ugui1, ssd1306_SetPoint, MAX_X, MAX_Y);
	//选择GUI
	// delay_ms(500);
	// ssd1306_Clear();
	// //全屏填充函数
	// UG_FillScreen(C_WHITE);
	// delay_ms(1000);
	// ssd1306_Clear();
	// //矩形填充
	// UG_FillFrame(0, 0, 50, 50, C_WHITE);
	// delay_ms(1000);
	// ssd1306_Clear();
	// //圆角矩形填充
	// UG_FillRoundFrame(0, 0, 50, 50, 10, C_WHITE);
	// delay_ms(1000);
	// ssd1306_Clear();
	// UG_DrawCircle(30, 30, 30, C_WHEAT);
	// delay_ms(1000);
	// ssd1306_Clear();
	// UG_FillCircle(30, 30, 30, C_WHEAT);
	// delay_ms(1000);
	// ssd1306_Clear();
	// UG_DrawArc(30, 30, 30, 30, C_WHEAT);
	// delay_ms(1000);
	// ssd1306_Clear();
	// UG_DrawLine(0, 0, 30, 30, C_WHEAT);
	// delay_ms(1000);
	// ssd1306_Clear();
	// UG_DrawArc(30, 30, 30, 30, C_WHEAT);
	// delay_ms(1000);
	// ssd1306_Clear();
	// UG_SelectGUI(&my_ugui1);
	// //选择字体
	// UG_FontSelect(&FONT_8X8);
	// //字符显示
	// UG_PutChar('B', 20, 20, C_WHITE, C_BLACK);
	// delay_ms(1000);
	// ssd1306_Clear();
  // UG_ConsoleSetBackcolor(C_BLACK);
  // UG_ConsoleSetForecolor(C_WHITE);
  // UG_ConsolePutString("System initialized!\n");
	// delay_ms(1000);
	// ssd1306_Clear();
	// //字符串测试
	// UG_FontSelect(&FONT_16X26);
	// UG_SetBackcolor(C_BLACK);
	// UG_SetForecolor(C_WHITE);
	// UG_PutString(0, 0, "Hello Wlord!");
	delay_ms(1000);
	ssd1306_Clear();
	window_test();
	delay_ms(1000);
	ssd1306_Clear();
}
