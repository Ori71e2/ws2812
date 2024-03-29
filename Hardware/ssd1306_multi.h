#ifndef __ssd1306_MULTI_H
#define __ssd1306_MULTI_H

#include "stm32f10x.h" 

#pragma diag_suppress 167, 940 //消除格式警告
extern char ssd1306_multi_String[]; //字符转化为字符串储存于此数组

#define ssd1306_multi_SCL_CLR() GPIO_ResetBits(GPIOA, GPIO_Pin_5) //时钟
#define ssd1306_multi_SCL_SET() GPIO_SetBits(GPIOA, GPIO_Pin_5)

#define ssd1306_multi_SDA_LOW() GPIO_ResetBits(GPIOA, GPIO_Pin_7) // MOSI主设备输出
#define ssd1306_multi_SDA_HIGH() GPIO_SetBits(GPIOA, GPIO_Pin_7)

#define ssd1306_multi_RST_OFF() GPIO_ResetBits(GPIOA, GPIO_Pin_4) //接低电平复位
#define ssd1306_multi_RST_ON() GPIO_SetBits(GPIOA, GPIO_Pin_4)

#define ssd1306_multi_DC_CMD() GPIO_ResetBits(GPIOA, GPIO_Pin_6) //模式
#define ssd1306_multi_DC_DAT() GPIO_SetBits(GPIOA, GPIO_Pin_6)

void ssd1306_multi_IO_Init(void);                   // GPIO和SPI初始化
void ssd1306_multi_Write_Char(u8 oled_pointer, u8 lie, u8 ye, u8 *ascii); //写入ASCII文字
void ssd1306_multi_SendCmd(u8 TxData);              //发送命令

void ssd1306_multi_Clear(u8 oled_pointer);
void ssd1306_multi_Fill_all(u8 oled_pointer);
void ssd1306_multi_Write_String(u8 oled_pointer, u8 x, u8 y, u8 *chr);

void ssd1306_multi_Init(void);     // ssd1306初始化
void ssd1306_multi_DMA_Init(void); // DMA初始化

void ssd1306_multi_SetPoint(u8 oled_pointer, uint8_t x, uint8_t y, uint8_t pointV);
void ssd1306_multi_DrawLine(u8 oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 , uint8_t color);
void ssd1306_multi_DrawHLin(u8 oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1 , uint8_t color);
void ssd1306_multi_DrawVLine(u8 oled_pointer, uint8_t x0, uint8_t y0, uint8_t y1 , uint8_t color);
void ssd1306_multi_FillRect(u8 oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 , uint8_t color);
void ssd1306_multi_DrawBMP(u8 oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 , uint8_t *bmp);
void ssd1306_multi_DrawArrImage(u8 oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 , uint8_t *arrImage);
#endif
