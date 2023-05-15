#include "stm32f10x.h"
#include "delay.h"
#include "ssd1306_multi.h"
#include "ssd1306_multi_Font.h"
#include "ssd1306_multi_conf.h"

uint8_t ssd1306_SRAMArr[OLED_NUM][MAX_Y / 8][MAX_X]; // 图像储存在SRAM里
uint8_t oled_pointer = 0;
DMA_InitTypeDef DMA_InitStructure;
// ssd1306屏幕ISP接口初始化
void ssd1306_multi_IO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef SPI_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;   // 复用输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);            // 初始化PA5(SCL),PA7(SDA)

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;  // 推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 速度50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);            // 初始化PA4(RST),PA6(DC)

  GPIO_SetBits(GPIOA, GPIO_Pin_5 | GPIO_Pin_7); // PA5 and PA7上拉
  // GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9);

  SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;           //设置SPI单线只发送
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                       //主SPI
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                   // SPI 发送接收8位帧结构
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;                          //串行同步时钟的空闲状态为低电平
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;                        //第1个跳变沿数据被采样
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                           // NSS主机片选信号(CS)由软件控制
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16; //预分频 16

  // SPI 速度设置函数（调整传输速度快慢 只有4个分频可选）
  // SPI_BaudRatePrescaler_2 2 分频 (SPI 36M@sys 72M)
  // SPI_BaudRatePrescaler_8 8 分频 (SPI 9M@sys 72M)
  // SPI_BaudRatePrescaler_16 16 分频 (SPI 4.5M@sys 72M)
  // SPI_BaudRatePrescaler_256 256 分频 (SPI 281.25K@sys 72M)

  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB; //数据传输从 MSB 高位开始 低位为LSB
  SPI_InitStructure.SPI_CRCPolynomial = 7;           // CRC 值计算的多项式
  SPI_Init(SPI1, &SPI_InitStructure);                //根据指定的参数初始化外设 SPIx 寄存器
  SPI1->CR2 = 1 << 1;                                //允许DMA往缓冲区内发送

  SPI_Cmd(SPI1, ENABLE); //使能 SPI 外设
};

void ssd1306_multi_DMA_Init(void)
{
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE); //使能 DMA 时钟
  DMA_Cmd(DMA1_Channel3, DISABLE);
  DMA_DeInit(DMA1_Channel3);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&SPI1->DR;              // DMA 外设 ADC 基地址
  DMA_InitStructure.DMA_MemoryBaseAddr = (u32)ssd1306_SRAMArr[oled_pointer];               // DMA 内存基地址
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;                      //从储存器读取发送到外设
  DMA_InitStructure.DMA_BufferSize = MAX_X * MAX_Y / 8;                   // DMA 通道的 DMA 缓存的大小, 128 * 64 / 8 = 1024
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;        //外设地址不变
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;                 //内存地址递增
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_MemoryDataSize_Byte; // 8 位
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;         // 8 位
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;                         //工作在循环传输模式
  DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;                   // DMA 通道 x 拥有中优先级
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;                            //非内存到内存传输
  DMA_Init(DMA1_Channel3, &DMA_InitStructure);                            //根据指定的参数初始化
  // DMA_Cmd(DMA1_Channel3, DISABLE); //不使能DMA1 CH3所指示的通道
	GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9);
	switch(oled_pointer)
	{
		case 0:
			GPIO_ResetBits(GPIOA, GPIO_Pin_8);
		  GPIO_SetBits(GPIOA, GPIO_Pin_9);
			break;
		case 1:
			GPIO_ResetBits(GPIOA, GPIO_Pin_9);
		  GPIO_SetBits(GPIOA, GPIO_Pin_8);
		  break;
		default:
			break;
	}
  DMA_Cmd(DMA1_Channel3, ENABLE); //使能DMA1 CH3所指示的通道
	oled_pointer = (oled_pointer + 1) % OLED_NUM;
}
void ssd1306_TIM_Init(void)
{
  RCC_APB2PeriphClockCmd(SSD1306_MULTI_APB1_RCC_TIM, ENABLE);    // 使能定时器总线

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	// 1 / 1000000 * 1952  = 0.001952ms，一次计时完整需要的时间
	// 1 / 0.001952 = 512 Hz
	TIM_TimeBaseInitStructure.TIM_Period = SSD1306_MULTI_PERIOD - 1;							// 计数器周期，即自动重装载寄存器TIMx_ARR的值，在事件生成时更新到影子寄存器，由TIMx_CR1寄存器的ARPE位配置是否使能缓冲,设置512Hz采样频率
	TIM_TimeBaseInitStructure.TIM_Prescaler = (SystemCoreClock / SSD1306_MULTI_FREQUENCY) - 1;  // 定时器预分频器设置
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;				  // 时钟分频，不分频，TIM2-TIM5是通用定时器，基本定时器不用设置
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;			// 向上扫描
  TIM_ClearFlag(TIM1, TIM_FLAG_Update);//清中断标志位
	TIM_TimeBaseInit(SSD1306_MULTI_TIM, &TIM_TimeBaseInitStructure);
  TIM_ITConfig(TIM1,TIM_IT_Update, ENABLE);     //使能TIM6中断
	// ADC_DMA_NVIC_Configuration嵌套向量中断控制器（NVIC）

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn; //SSD1306_TIM_IRQ;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = SSD1306_MULTI_IRQ_PRIO;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority	= SSD1306_MULTI_IRQ_SUBPRIO;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	TIM_Cmd(SSD1306_MULTI_TIM, ENABLE);
}
void ssd1306_multi_SendCmd(u8 TxData) //发送命令
{
  ssd1306_multi_DC_CMD(); //命令模式

  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的 SPI标志位设置与否:发送缓存空标志位
  {
    for (u8 retry = 0; retry < 200; retry++)
    {
    }
    return;
  }
  delay_ms(100);

  SPI_I2S_SendData(SPI1, TxData); //通过外设 SPIx 发送一个数据

  ssd1306_multi_DC_DAT(); //数据模式
}
void ssd1306_SendData(void) //发送命令
{
  ssd1306_multi_DC_CMD(); //命令模式

  while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //检查指定的 SPI标志位设置与否:发送缓存空标志位
  {
    for (u8 retry = 0; retry < 200; retry++)
    {
    }
    return;
  }
  delay_ms(100);

  ssd1306_multi_DC_DAT(); //数据模式
}
// ssd1306初始化函数
void ssd1306_multi_Init(void)
{
  ssd1306_multi_IO_Init();  // 端口初始化

  delay_ms(10);    // 延时10毫秒稳定端口状态

  ssd1306_multi_RST_OFF(); // ssd1306复位
  delay_ms(10);   // 复位延时
  ssd1306_multi_RST_ON();  // 结束复位

  ssd1306_multi_SendCmd(0xae); // 关闭显示

  ssd1306_multi_SendCmd(0xd5); // 设置时钟分频因子,震荡频率
  ssd1306_multi_SendCmd(0x80); // [3:0],分频因子;[7:4],震荡频率

  ssd1306_multi_SendCmd(0x81); // 设置对比度
  ssd1306_multi_SendCmd(0x7f); // 128

  ssd1306_multi_SendCmd(0x8d); // 设置电荷泵开关
  ssd1306_multi_SendCmd(0x14); // 开

  ssd1306_multi_SendCmd(0x20); // 设置模式
  ssd1306_multi_SendCmd(0x00); // 设置为水平地址模式

  ssd1306_multi_SendCmd(0x21); // 设置列地址的起始和结束的位置
  ssd1306_multi_SendCmd(0x00); // 0
  ssd1306_multi_SendCmd(0x7f); // 127

  ssd1306_multi_SendCmd(0x22); //设置页地址的起始和结束的位置
  ssd1306_multi_SendCmd(0x00); // 0
  ssd1306_multi_SendCmd(0x07); // 7

  ssd1306_multi_SendCmd(0xc8); // 0xc9上下反置 0xc8正常
  ssd1306_multi_SendCmd(0xa1); // 0xa0左右反置 0xa1正常

  ssd1306_multi_SendCmd(0xa4); //全局显示开启;0xa4正常,0xa5无视命令点亮全屏
  ssd1306_multi_SendCmd(0xa6); //设置显示方式;bit0:1,反相显示;0,正常显示

  ssd1306_multi_SendCmd(0xaf); //开启显示
  ssd1306_multi_SendCmd(0x56);
	
  ssd1306_TIM_Init();
  ssd1306_multi_DMA_Init(); // DMA初始化
}
void SSD1306_MULTI_TIM_IRQ_HANDLER(void){
  // ssd1306_multi_SendCmd(0x56);
	// ssd1306_SendData();
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);//清除TIMx的中断待处理位:TIM 中断源 
    ssd1306_multi_DMA_Init();
	}
}
// void DMA1_Channel3_IRQHandler(void)
// {
// 	ssd1306_multi_DC_CMD();
// 	if(DMA_GetITStatus(DMA1_IT_TC3) != RESET)
// 	{
//     DMA_ClearITPendingBit(DMA1_IT_TC3);
// 	}
// }

//指定位置显示单字符，X+Y+单字符
void ssd1306_multi_Write_Char(u8 oled_pointer, u8 x, u8 y, u8 *ascii)
{
  u8 i = 0, c = *ascii;

  for (i = 0; i < 6; i++)
    ssd1306_SRAMArr[oled_pointer % OLED_NUM][y][x + i] = MULTI_CHAR_F6X8[(c - 32) * 6 + 1 + i];
}

//清屏--全灭
void ssd1306_multi_Clear(u8 oled_pointer)
{
  // for (u8 y = 0; y < 7; y++)
  //   for (u8 x = 0; x < 126; x += 6)
  //     ssd1306_Write_String(x, y, (u8 *)' ');
  for (u8 y = 0; y < MAX_Y / 8; y++)
    for (u8 x = 0; x < MAX_X; x++)
      ssd1306_SRAMArr[oled_pointer % OLED_NUM][y][x] = 0;
}
void ssd1306_multi_Fill_all(u8 oled_pointer)
{
  for (u8 y = 0; y < MAX_Y / 8; y++)
    for (u8 x = 0; x < MAX_X; x++)
      ssd1306_SRAMArr[oled_pointer % OLED_NUM][y][x] = 255;
}
char ssd1306_multi_String[] = {0}; //字符转化为字符串储存于此数组

//显示多个字符，x+y+字符串
void ssd1306_multi_Write_String(u8 oled_pointer, u8 x, u8 y, u8 *chr)
{
  u8 j = 0;

  while (chr[j] != '\0')
  {
      u8 c = chr[j];

      for (u8 i = 0; i < 6; i++)
        ssd1306_SRAMArr[oled_pointer % OLED_NUM][y][x + i] = MULTI_CHAR_F6X8[(c - 32) * 6 + 1 + i];

      x += 6;

      if (x > 120)//自动换行
      {
        x = 0;
        y++;
      }

      j++;
  }
}

void ssd1306_multi_DrawArrImage(uint8_t oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 , uint8_t *arrImage)
{
	short temp;    
  uint8_t x,y;
	uint8_t *pcolor;
	
  if( x0 > x1 )  
  {
	  temp = x1;
		x1 = x0;
		x0 = temp;   
  }
  if( y0 > y1 )   
  {
		temp = y1;
		y1 = y0;
		y0 = temp;   
  }
	pcolor = arrImage;
	for(y = y0 / 8; y <= y1 / 8; y++)
	{	
		for(x = x0; x <= x1; x++)
		{	
			ssd1306_SRAMArr[oled_pointer % OLED_NUM][y][x] = *pcolor;
			pcolor++;
		}
	}	
}

void ssd1306_multi_SetPoint(uint8_t oled_pointer, uint8_t x, uint8_t y, uint8_t pointV)
{
	if( x >= MAX_X || y >= MAX_Y )
	{
		return;
	}
	if(pointV != 0)
	  ssd1306_SRAMArr[oled_pointer % OLED_NUM][y / 8][x] |= (0x1 << (y % 8));
	else
	  ssd1306_SRAMArr[oled_pointer % OLED_NUM][y / 8][x] &= ~(0x1 << (y % 8));  
	
}

/******************************************************************************
* Description  : Bresenham's line algorithm
*******************************************************************************/	 
void ssd1306_multi_DrawLine(uint8_t oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 , uint8_t color)
{
  short dx,dy;    
  short temp;    
  if( x0 > x1 )  
  {
	  temp = x1;
		x1 = x0;
		x0 = temp;   
  }
  if( y0 > y1 )   
  {
		temp = y1;
		y1 = y0;
		y0 = temp;   
  }
  
	dx = x1-x0;    
	dy = y1-y0;    

  if( dx == 0 )   
  {
      do
      { 
        ssd1306_multi_SetPoint(oled_pointer, x0, y0, color);
        y0++;
      }
      while( y1 >= y0 ); 
		return; 
  }
  if( dy == 0 )  
  {
      do
      {
        ssd1306_multi_SetPoint(oled_pointer, x0, y0, color); 
        x0++;
      }
      while( x1 >= x0 ); 
		return;
  }

  if( dx > dy )                 
  {
	  temp = 2 * dy - dx;            
      while( x0 != x1 )
      {
	      ssd1306_multi_SetPoint(oled_pointer, x0, y0, color); 
	      x0++;                 
	      if( temp > 0 )          
	      {
	        y0++;               
	        temp += 2 * dy - 2 * dx; 
	 	  }
        else       
        {
			  temp += 2 * dy;      
			}     
      }
      ssd1306_multi_SetPoint(oled_pointer, x0, y0, color);
  }  
  else
  {
	  temp = 2 * dx - dy;                 
      while( y0 != y1 )
      {
	 	  ssd1306_multi_SetPoint(oled_pointer, x0, y0, color);  
        y0++;           
        if( temp > 0 )       
        {
          x0++;           
          temp+=2*dy-2*dx; 
        }
        else
			{
          temp += 2 * dy;
			}
      } 
      ssd1306_multi_SetPoint(oled_pointer, x0, y0, color);
	}
} 



void ssd1306_multi_DrawHLine(uint8_t oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1 , uint8_t color)
{
	ssd1306_multi_DrawLine(oled_pointer, x0, y0, x1, y0, color);
}

void ssd1306_multi_DrawVLine(uint8_t oled_pointer, uint8_t x0, uint8_t y0, uint8_t y1 , uint8_t color)
{
	ssd1306_multi_DrawLine(oled_pointer, x0, y0, x0, y1, color);
}

void ssd1306_multi_FillRect(uint8_t oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 , uint8_t color)
{
  uint8_t y;
	short temp;     

#if 0
  uint8_t x;
  if( x0 > x1 )   
  {
	  temp = x1;
		x1 = x0;
		x0 = temp;   
  }
	for(x = x0; x < x1; x++)
	{
		ssd1306_multi_DrawVLine(oled_pointer, x, y0, y1, color);
	}
#endif

  if( y0 > y1 )  
  {
		temp = y1;
		y1 = y0;
		y0 = temp;   
  }	
	for(y = y0; y < y1; y++)
	{
		ssd1306_multi_DrawHLine(oled_pointer, x0, y, x1, color);
	}	
	
}


void ssd1306_multi_DrawBMP(uint8_t oled_pointer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1 , uint8_t *bmp)
{
	short temp;    
  uint8_t x,y;
	uint8_t *pcolor;
	
  if( x0 > x1 )  
  {
	  temp = x1;
		x1 = x0;
		x0 = temp;   
  }
  if( y0 > y1 )   
  {
		temp = y1;
		y1 = y0;
		y0 = temp;   
  }
	pcolor = bmp;
	for(y = y0; y < y1; y++)
	{	
		for(x = x0; x < x1; x++)
		{	
			ssd1306_multi_SetPoint(oled_pointer, x,y,*pcolor ++);
		}
	}	
}

