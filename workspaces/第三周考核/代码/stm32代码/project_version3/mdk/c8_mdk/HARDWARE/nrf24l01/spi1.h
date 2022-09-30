#ifndef _SPI1_H_
#define _SPI1_H_
#include "sys.h"

#define DMAx_SPI1                1 //0  关闭  1开启   (usart3 dma 冲突)
 
void SPI1_Init(void);              //初始化SPI口
void SPI1_SetSpeed(u8 SpeedSet);   //设置SPI速度   
u8   SPI1_ReadWriteByte(u8 TxData);//SPI总线读写一个字节
	
#if DMAx_SPI1==1
u8 DMAx_SPI1_Init(void);
u8 DMAx_SPI1_RX(u8 *buffer,u32 len);
u8 DMAx_SPI1_TX(u8 *buffer,u32 len);
#endif

#endif

