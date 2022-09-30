#ifndef _USART1_H_
#define _USART1_H_
#include "sys.h" 

#define     USART1_MAX_TX_LEN		    300   //����ͻ����ֽ�������ȥ\0 ���-1
#define     USART1_MAX_RX_LEN		    300   //�����ջ����ֽ�������ȥ\0 ���-1
extern volatile u16 USART1_RX_STA;            //����״̬���
extern u8   USART1_TX_BUF[USART1_MAX_TX_LEN]; //���ͻ�����
extern u8   USART1_RX_BUF[USART1_MAX_RX_LEN]; //���ջ�����		             
 
void USART1_Init(u32 bound);
void USART1_printf (char *fmt, ...);
void USART1_Send_Array (u8 *array,u16 num);
void USART1_RX_STA_SET(void);
#endif

