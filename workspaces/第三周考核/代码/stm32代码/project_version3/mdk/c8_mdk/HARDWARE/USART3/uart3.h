#ifndef UART3_H
#define UART3_H


#include "sys.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"

#define USART3_REC_LEN  			800  	//�����������ֽ��� 200
	  	
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART3_RX_STA;         		//����״̬���

void uart3_Init(u32 baudrate);
void uart3_test(void);
void u3_printf(char *fmt,...);

#endif
