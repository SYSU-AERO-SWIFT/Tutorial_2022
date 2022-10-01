#ifndef _SPI1_H_
#define _SPI1_H_
#include "sys.h"

#define DMAx_SPI1                1 //0  �ر�  1����   (usart3 dma ��ͻ)
 
void SPI1_Init(void);              //��ʼ��SPI��
void SPI1_SetSpeed(u8 SpeedSet);   //����SPI�ٶ�   
u8   SPI1_ReadWriteByte(u8 TxData);//SPI���߶�дһ���ֽ�
	
#if DMAx_SPI1==1
u8 DMAx_SPI1_Init(void);
u8 DMAx_SPI1_RX(u8 *buffer,u32 len);
u8 DMAx_SPI1_TX(u8 *buffer,u32 len);
#endif

#endif

