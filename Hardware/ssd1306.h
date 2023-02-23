#ifndef __ssd1306_H
#define __ssd1306_H

#include "stm32f10x.h" 

#pragma diag_suppress 167, 940 //消除格式警告
extern char ssd1306_zfc[]; //字符转化为字符串储存于此数组

#define ssd1306_SCL_CLR() GPIO_ResetBits(GPIOA, GPIO_Pin_5) //时钟
#define ssd1306_SCL_SET() GPIO_SetBits(GPIOA, GPIO_Pin_5)

#define ssd1306_SDA_LOW() GPIO_ResetBits(GPIOA, GPIO_Pin_7) // MOSI主设备输出
#define ssd1306_SDA_HIGH() GPIO_SetBits(GPIOA, GPIO_Pin_7)

#define ssd1306_RST_OFF() GPIO_ResetBits(GPIOA, GPIO_Pin_4) //接低电平复位
#define ssd1306_RST_ON() GPIO_SetBits(GPIOA, GPIO_Pin_4)

#define ssd1306_DC_CMD() GPIO_ResetBits(GPIOA, GPIO_Pin_6) //模式
#define ssd1306_DC_DAT() GPIO_SetBits(GPIOA, GPIO_Pin_6)

void ssd1306_IO_Init(void);                   // GPIO和SPI初始化
void ssd1306_Write(u8 lie, u8 ye, u8 *ascii); //写入ASCII文字
void ssd1306_SendCmd(u8 TxData);              //发送命令

void ssd1306_Clear(void);
void ssd1306_Fill_all(void);
void ssd1306_ZFC(u8 x, u8 y, u8 *chr);

void ssd1306_Init(void);     // ssd1306初始化
void ssd1306_DMA_Init(void); // DMA初始化

#endif
