#ifndef _USART1_H_
#define _USART1_H_
#include "sys.h" 

#define     USART1_MAX_TX_LEN		    300   //最大发送缓存字节数，刨去\0 最大-1
#define     USART1_MAX_RX_LEN		    300   //最大接收缓存字节数，刨去\0 最大-1
extern volatile u16 USART1_RX_STA;            //接收状态标记
extern u8   USART1_TX_BUF[USART1_MAX_TX_LEN]; //发送缓冲区
extern u8   USART1_RX_BUF[USART1_MAX_RX_LEN]; //接收缓冲区		             
 
void USART1_Init(u32 bound);
void USART1_printf (char *fmt, ...);
void USART1_Send_Array (u8 *array,u16 num);
void USART1_RX_STA_SET(void);
#endif

