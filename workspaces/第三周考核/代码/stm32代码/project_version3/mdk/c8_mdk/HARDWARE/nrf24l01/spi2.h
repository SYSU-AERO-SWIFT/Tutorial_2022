#ifndef _SPI2_H_
#define _SPI2_H_
#include "sys.h"

#define DMAx_SPI2                1 //0  关闭  1开启   (usart1 dma 冲突)
 													  
void SPI2_Init(void);              //初始化SPI口
void SPI2_SetSpeed(u8 SpeedSet);   //设置SPI速度   
u8   SPI2_ReadWriteByte(u8 TxData);//SPI总线读写一个字节

#if DMAx_SPI2==1
u8 DMAx_SPI2_Init(void);
u8 DMAx_SPI2_RX(u8 *buffer,u32 len);
u8 DMAx_SPI2_TX(u8 *buffer,u32 len);
#endif

#endif

