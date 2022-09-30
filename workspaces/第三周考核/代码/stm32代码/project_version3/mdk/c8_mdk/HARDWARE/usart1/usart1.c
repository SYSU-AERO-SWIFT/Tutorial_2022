#include "usart1.h"	  
#include "stdarg.h"
//USART1_TX   GPIOA.9
//USART1_RX	  GPIOA.10

u8   USART1_TX_BUF[USART1_MAX_TX_LEN]; 		//���ͻ���,���USART1_MAX_TX_LEN-1�ֽ�
u8   USART1_RX_BUF[USART1_MAX_RX_LEN]; 		//���ջ���,���USART1_MAX_RX_LEN-1�ֽ�

volatile u16 USART1_RX_STA=0;               //bit15:������ɱ�־   bit14~0:���յ�����Ч�ֽ���Ŀ   

void USART1_Init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
 
	//USARTx_TX 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;	 
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	//USARTx_RX 
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);  

	//NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel                   = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = 0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;		 
	NVIC_Init(&NVIC_InitStructure);	 

	//USARTx��ʼ�� 
	USART_InitStructure.USART_BaudRate            = bound; 
	USART_InitStructure.USART_WordLength          = USART_WordLength_8b; 
	USART_InitStructure.USART_StopBits            = USART_StopBits_1; 
	USART_InitStructure.USART_Parity              = USART_Parity_No; 
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
	USART_InitStructure.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx; 

	//ʹ������
	USART_Init(USART1, &USART_InitStructure);     //��ʼ������
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�������ڿ���IDEL�ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���
	USART1_printf("USART1 OK...\r\n");
}

void USART1_printf (char *fmt, ...)
{
	u16 i = 0;
	va_list arg_ptr;
	va_start(arg_ptr, fmt); 
	vsnprintf((char *)USART1_TX_BUF, USART1_MAX_TX_LEN+1, fmt, arg_ptr);
	va_end(arg_ptr);

	while ((i < USART1_MAX_TX_LEN) && USART1_TX_BUF[i])
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
		USART_SendData(USART1, (u8) USART1_TX_BUF[i++]);	
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC)  == RESET);
	}
}
  
void USART1_Send_Array (u8 *array,u16 num)
{
	u16 i=0;
	while (i < num)
	{
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
		USART_SendData(USART1, (u8) array[i++]);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC)  == RESET);
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)               // �����ж�
	{
		USART_ReceiveData(USART1);                                      //��������жϱ�־
		USART1_RX_STA_SET();
		//��Ӵ�����,�����������ѯ����

	}	
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE) == SET)               // ��� ORE ��־,��ֹ�������ж����������ڽ����ж�ǰ��
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);
		USART_ReceiveData(USART1);
	}
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)               //�����ж� 
	{
		u8 res = USART_ReceiveData(USART1);	                            //��ȡ���յ�������	
		if ((USART1_RX_STA&0x8000)==0 && 
			(USART1_RX_STA&0X7FFF)<USART1_MAX_RX_LEN-1)                 //�ɵĲ������µ�����,�������鳤�ȵ�����
		{
			USART1_RX_BUF[USART1_RX_STA&0X7FFF]=res;
			USART1_RX_STA++;
		}
	}
}

void USART1_RX_STA_SET(void)
{
	if (USART1_RX_BUF[(USART1_RX_STA&0X7FFF)-2]=='\r') 
	{
		USART1_RX_BUF[(USART1_RX_STA&0X7FFF)-2]=0;		                //�յ�\r\n��ɾ��\r\n�����\0
		USART1_RX_STA=USART1_RX_STA-2;                                  //ɾ��\r\n����2
	}
	else                                                            
	{ 
		USART1_RX_BUF[(USART1_RX_STA&0X7FFF)]='\0';		                //û�յ�\r\n��ֱ�����\0
	}
	USART1_RX_STA|=0x8000;	                                            //��ǽ��������
}

