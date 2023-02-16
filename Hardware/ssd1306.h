#ifndef __OLED_H
#define __OLED_H

#include "stm32f10x.h" 

#pragma diag_suppress 167, 940 //消除格式警告
extern char OLED_zfc[]; //字符转化为字符串储存于此数组

#define OLED_SCL_CLR() GPIO_ResetBits(GPIOA, GPIO_Pin_5) //时钟
#define OLED_SCL_SET() GPIO_SetBits(GPIOA, GPIO_Pin_5)

#define OLED_SDA_LOW() GPIO_ResetBits(GPIOA, GPIO_Pin_7) // MOSI主设备输出
#define OLED_SDA_HIGH() GPIO_SetBits(GPIOA, GPIO_Pin_7)

#define OLED_RST_OFF() GPIO_ResetBits(GPIOA, GPIO_Pin_4) //接低电平复位
#define OLED_RST_ON() GPIO_SetBits(GPIOA, GPIO_Pin_4)

#define OLED_DC_CMD() GPIO_ResetBits(GPIOA, GPIO_Pin_6) //模式
#define OLED_DC_DAT() GPIO_SetBits(GPIOA, GPIO_Pin_6)

void OLED_IO_Init(void);                   // GPIO和SPI初始化
void OLED_Write(u8 lie, u8 ye, u8 *ascii); //写入ASCII文字
void OLED_SendCmd(u8 TxData);              //发送命令

void OLED_Clear(void);
void OLED_ZFC(u8 x, u8 y, u8 *chr);

void OLED_Init(void);     // OLED初始化
void OLED_DMA_Init(void); // DMA初始化

#endif
