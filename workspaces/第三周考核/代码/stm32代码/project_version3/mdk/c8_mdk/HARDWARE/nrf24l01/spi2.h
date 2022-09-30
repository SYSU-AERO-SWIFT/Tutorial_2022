#ifndef _SPI2_H_
#define _SPI2_H_
#include "sys.h"

#define DMAx_SPI2                1 //0  �ر�  1����   (usart1 dma ��ͻ)
 													  
void SPI2_Init(void);              //��ʼ��SPI��
void SPI2_SetSpeed(u8 SpeedSet);   //����SPI�ٶ�   
u8   SPI2_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�

#if DMAx_SPI2==1
u8 DMAx_SPI2_Init(void);
u8 DMAx_SPI2_RX(u8 *buffer,u32 len);
u8 DMAx_SPI2_TX(u8 *buffer,u32 len);
#endif

#endif

