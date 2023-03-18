#include "stm32f10x.h"
#include "delay.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
#include "ugui.h"

void window0_callback(UG_MESSAGE* msg)
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
	UG_WINDOW window_0;
	UG_BUTTON button_0;
	UG_BUTTON button_1;
	UG_TEXTBOX textbox_1;
	UG_OBJECT obj_buff_wnd_0[MAX_OBJECTS];
  UG_SetBackcolor(C_BLACK);
	// . . .
	UG_WindowCreate(&window_0, obj_buff_wnd_0, MAX_OBJECTS, window0_callback);
	UG_WindowSetBackColor(&window_0, C_BLACK);
	UG_WindowSetStyle(&window_0, WND_STYLE_2D | WND_STYLE_SHOW_TITLE);

	UG_WindowSetTitleTextFont(&window_0, &FONT_4X6);
	UG_WindowSetTitleColor(&window_0, C_BLACK);
	UG_WindowSetTitleTextColor(&window_0, C_WHITE);

	UG_WindowShow(&window_0);
	UG_Update();
	delay_ms(1000);

	UG_WindowSetTitleText(&window_0, "uGUI Demo Window");
	UG_Update();
	delay_ms(1000);
	UG_ButtonCreate(&window_0, &button_0, BTN_ID_0, 5, 10, 50, 40);
	UG_ButtonSetFont(&window_0, BTN_ID_0, &FONT_4X6);
	UG_ButtonSetText(&window_0, BTN_ID_0, "Button\nA");
	UG_ButtonSetBackColor(&window_0, BTN_ID_0, C_WHITE);
	UG_ButtonSetForeColor(&window_0, BTN_ID_0, C_BLACK);
	UG_Update();
	delay_ms(1000);
	
	UG_ButtonCreate(&window_0, &button_1, BTN_ID_1, 70, 10, 115, 40);
	UG_ButtonSetFont(&window_0, BTN_ID_1, &FONT_4X6);
	UG_ButtonSetText(&window_0, BTN_ID_1, "Button\nB");
	UG_ButtonSetBackColor(&window_0, BTN_ID_1, C_WHITE);
	UG_ButtonSetForeColor(&window_0, BTN_ID_1, C_BLACK);
	UG_Update();
	delay_ms(1000);
	
	UG_ButtonHide(&window_0, BTN_ID_0);
	UG_ButtonDelete(&window_0, BTN_ID_0);
	UG_Update();
	delay_ms(1000);	
	
	UG_ButtonHide(&window_0, BTN_ID_1);
	UG_ButtonDelete(&window_0, BTN_ID_1);
	UG_Update();
	delay_ms(1000);
	
	UG_TextboxCreate(&window_0, &textbox_1, TXB_ID_0, 5, 10, 115, 40);
	UG_TextboxSetBackColor(&window_0, TXB_ID_0, C_WHITE);
	UG_TextboxSetFont(&window_0, TXB_ID_0, &FONT_4X6);
	UG_TextboxSetForeColor(&window_0, TXB_ID_0, C_BLACK);
	UG_TextboxSetText(&window_0, TXB_ID_0, "This is just a very \nsimple window to \ndemonstrate some basic \nfeatures of uGUI!");
	UG_TextboxSetAlignment(&window_0, TXB_ID_0, ALIGN_CENTER);
	UG_Update();
	delay_ms(1000);
	
	UG_TextboxHide(&window_0, TXB_ID_0);
	UG_TextboxDelete(&window_0, TXB_ID_0);
	UG_Update();
	delay_ms(1000);
	
	UG_WindowSetStyle(&window_0, WND_STYLE_2D | WND_STYLE_HIDE_TITLE);
	UG_Update();
	delay_ms(1000);
	// . . .
}
void ugui_example(void)
{
	UG_GUI my_ugui1;
	//初始化函数
	UG_Init(&my_ugui1, (void *)ssd1306_SetPoint, MAX_X, MAX_Y);
	UG_DriverRegister(DRIVER_DRAW_LINE, (void *)ssd1306_DrawLine);
	UG_DriverRegister(DRIVER_FILL_FRAME, (void *)ssd1306_FillRect);
	UG_DriverEnable(DRIVER_DRAW_LINE);
	UG_DriverEnable(DRIVER_FILL_FRAME);
	// 选择GUI
	delay_ms(500);
	ssd1306_Clear();
	//字符串测试
	UG_FontSelect(&FONT_10X16);
	UG_PutString(0, 0, "Test Start");
	delay_ms(1000);
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
	UG_DrawCircle(30, 30, 30, C_WHEAT);
	delay_ms(1000);
	ssd1306_Clear();
	UG_FillCircle(30, 30, 30, C_WHEAT);
	delay_ms(1000);
	ssd1306_Clear();
	UG_DrawArc(30, 30, 30, 30, C_WHEAT);
	delay_ms(1000);
	ssd1306_Clear();
	UG_DrawLine(0, 0, 30, 30, C_WHEAT);
	delay_ms(1000);
	ssd1306_Clear();
	UG_DrawArc(30, 30, 30, 30, C_WHEAT);
	delay_ms(1000);
	ssd1306_Clear();
	UG_SelectGUI(&my_ugui1);
	//选择字体
	UG_FontSelect(&FONT_8X8);
	//字符显示
	UG_PutChar('B', 20, 20, C_WHITE, C_BLACK);
	delay_ms(1000);
	ssd1306_Clear();
  UG_ConsoleSetBackcolor(C_BLACK);
  UG_ConsoleSetForecolor(C_WHITE);
  UG_ConsolePutString("System initialized!\n");
	delay_ms(1000);
	ssd1306_Clear();
	//字符串测试
	UG_FontSelect(&FONT_16X26);
	UG_PutString(0, 0, "Hello Wlord!");
	delay_ms(1000);
	ssd1306_Clear();
	window_test();
	delay_ms(1000);
	ssd1306_Clear();
}
