#include "stm32f10x.h"
#include "delay.h"
#include "ssd1306.h"
#include "ssd1306_conf.h"
// Image2Lcd软件，将图片取模而来，输出数据类型为C语言数组，扫描模式为数据水平，字节垂直，
// 输出灰度为单色，最大宽度和高度为64，字节内象素数据反序，字节顺序为Big Endian
// 第1个字节表示图像扫描方式，低四位为0水平扫描，为1垂直扫描。
// 第2字节表示图像输出灰度模式，0x04--16灰  0x10--16真彩色   0x18--24真彩色   0x20--32真彩色
// 第3~4字节表示图像宽度
// 第5~6字节表示图像高度
// 此处被注释掉了
const unsigned char gImage_1[512] = { /* 0X32,0X01,0X00,0X40,0X00,0X40, */
0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0X80,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X00,0X80,0X80,0XC0,0XC0,0X60,0X60,0X60,0X30,0X30,0X30,
0X30,0X30,0X30,0X30,0X30,0X30,0X70,0X60,0X60,0XE0,0XC0,0X80,0X80,0X00,0X00,0X00,
0X00,0X00,0X80,0X80,0X80,0X80,0X80,0X80,0X80,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0XF8,0XFC,0X0E,0XC7,0XE3,0X73,0X31,0X01,0XC1,0XF3,0X7F,
0X1E,0X0E,0XFC,0XFC,0XCE,0X67,0X63,0X21,0X30,0X30,0X30,0X10,0X10,0X10,0X18,0X1F,
0X13,0XFF,0X01,0X03,0X1E,0XF8,0XF0,0XF0,0XF0,0X20,0X60,0X61,0X63,0XF3,0XFE,0X9E,
0X3F,0X73,0XE1,0X81,0X1D,0X19,0X71,0X61,0X03,0X03,0X0E,0XFC,0XF0,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X07,0X0F,0X1C,0X38,0XB8,0XFC,0X7E,0X37,0X1B,0X0C,0X06,
0X03,0X01,0X01,0XC0,0XE0,0XF0,0XF8,0XFC,0XFC,0XFE,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,
0X7F,0X7F,0XCF,0X8C,0X08,0X1F,0X94,0XDF,0XDF,0X7F,0X7E,0XFE,0XFC,0XFC,0XF8,0XF1,
0XE1,0XC3,0X07,0X0F,0X1B,0X36,0XF6,0XFC,0X1C,0X1C,0X0E,0X07,0X01,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0X00,0X80,0XF0,0X7C,0X0E,0X03,0X01,0X00,0X00,0X00,0X00,0XE0,
0XF8,0XFE,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X7F,0X3F,0X1F,0X1F,0X3F,0X7F,
0X7C,0X7C,0X7C,0X03,0XFF,0XFF,0X03,0X00,0X00,0X00,0X00,0X1B,0X7F,0X7F,0X7F,0X7F,
0X3F,0X3F,0XFF,0XFE,0X78,0XE0,0X00,0X03,0X0F,0XFC,0XE0,0X00,0X00,0X00,0X00,0X00,
0X00,0X00,0X00,0X00,0XF8,0XFF,0X03,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0XFF,
0XF1,0XF1,0XF3,0XF3,0XF0,0XF1,0XE3,0X07,0X06,0X0C,0X08,0X18,0XD8,0XF8,0XB8,0X18,
0X08,0X0C,0X0E,0X0F,0X0D,0X0F,0X0C,0X0C,0X18,0X38,0X38,0X78,0XD8,0X98,0X18,0X18,
0XCC,0XE6,0XF3,0XF9,0XF8,0XFF,0X7E,0X00,0X00,0X00,0XFF,0X7C,0X00,0X00,0X00,0X00,
0X00,0X00,0X80,0X00,0X40,0X4F,0X3F,0X70,0XE0,0X80,0X00,0X00,0X00,0X00,0X00,0X01,
0X0F,0X1F,0X3F,0X7F,0X7F,0XDF,0XCF,0X80,0X80,0X80,0X80,0X00,0X03,0X07,0X0D,0X0D,
0X1B,0X1B,0X13,0X33,0X33,0X33,0X33,0X33,0X33,0X13,0X19,0X0F,0X07,0X01,0X00,0X00,
0X03,0X87,0XEF,0X7F,0X1F,0X07,0X80,0XC0,0X70,0X3E,0X0F,0X00,0X00,0X00,0X00,0X00,
0X42,0X9F,0XE0,0X70,0X48,0X44,0X42,0X41,0X01,0X21,0X21,0X22,0X26,0XAC,0XEC,0XE8,
0XF8,0XF0,0XF0,0XF0,0XF0,0X80,0XA0,0X20,0X61,0X61,0XE1,0XE1,0XE3,0XE3,0XE3,0XE3,
0XE3,0XE3,0XE2,0XE2,0XE2,0XE2,0XE6,0XE6,0XE6,0XE6,0XE2,0XE2,0XE2,0XE2,0XE3,0X73,
0X33,0X91,0XD8,0X0C,0X0E,0X07,0X03,0X01,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
0X84,0X7C,0X85,0X12,0X24,0X84,0X08,0X08,0XD0,0XF0,0XF8,0XFE,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFC,0X01,0X4F,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X03,0XF8,
0XFF,0XFF,0XFF,0XFF,0XFC,0XF0,0XC0,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,0X00,
};

void ssd1306_example(void)
{
	// ssd1306_Fill_all();
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
	ssd1306_FillRect(0, 0, 40, 40, 1);
}

void ssd1306_Show_Image(void)
{
	ssd1306_DrawArrImage(32, 0, 95, 63, (uint8_t *)gImage_1);
	delay_ms(1000);
}
