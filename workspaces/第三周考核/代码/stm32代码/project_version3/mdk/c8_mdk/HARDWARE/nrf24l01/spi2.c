#include "spi2.h"

//sck   PB13 ʱ���ź�
//miso  PB14 �������������룬�������������
//mosi  PB15 �����������������������������
//SPI2  APB1(36M)ʱ��36M

void SPI2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    //����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  
	
	SPI_StructInit(&SPI_InitStructure);                                       //�ָ�Ĭ��ֵ
	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;//����SPI�������˫�������ģʽ:SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;		            //����SPI����ģʽ:����Ϊ��SPI
	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;		            //����SPI�����ݴ�С:SPI���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;		              //����ͬ��ʱ�ӵĿ���״̬Ϊ�ߵ�ƽ
	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;	                //����ͬ��ʱ�ӵĵڶ��������أ��������½������ݱ�����
	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;		                //NSS�ź���Ӳ����NSS�ܽţ����������ʹ��SSIλ������:�ڲ�NSS�ź���SSIλ����
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;      //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ256   APB2/x
	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;	              //ָ�����ݴ����MSBλ����LSBλ��ʼ:���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial     = 7;	                            //CRCֵ����Ķ���ʽ
	SPI_Init(SPI2, &SPI_InitStructure);                                       //��ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPI2, ENABLE);                                                    //ʹ��SPI����
	SPI2_ReadWriteByte(0xff);                                                 //��������		 
	SPI2_SetSpeed(SPI_BaudRatePrescaler_4);                                   //���岨����Ԥ��Ƶ
	
#if DMAx_SPI2==1
	DMAx_SPI2_Init();
#endif
}   
//SPI �ٶ����ú���  SPI2  APB1(36M)ʱ�Ӽ�36M
//#define SPI_BaudRatePrescaler_2        
//#define SPI_BaudRatePrescaler_4        
//#define SPI_BaudRatePrescaler_8        
//#define SPI_BaudRatePrescaler_16        
//#define SPI_BaudRatePrescaler_32        
//#define SPI_BaudRatePrescaler_64        
//#define SPI_BaudRatePrescaler_128     
//#define SPI_BaudRatePrescaler_256       
  
void SPI2_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI2->CR1&=0XFFC7;
	SPI2->CR1|=SPI_BaudRatePrescaler;	//����SPI2�ٶ� 
	SPI_Cmd(SPI2,ENABLE); 
} 

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI2, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); //����ͨ��SPIx������յ�����					    
}








#if DMAx_SPI2==1

u8 DMAx_SPI2_Init(void)
{
	DMA_InitTypeDef DMA1_Init;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	//DMA_SPI_RX  SPI->RAM�����ݴ���
	DMA_DeInit(DMA1_Channel4);	
	DMA1_Init.DMA_PeripheralBaseAddr=(u32)&SPI2->DR;//��������ǰװ��ʵ��RAM��ַ
	DMA1_Init.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA1_Init.DMA_BufferSize=512;
	DMA1_Init.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA1_Init.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA1_Init.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA1_Init.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA1_Init.DMA_Mode=DMA_Mode_Normal;
	DMA1_Init.DMA_Priority=DMA_Priority_High; 
	DMA1_Init.DMA_M2M=DMA_M2M_Disable;

	DMA_Init(DMA1_Channel4,&DMA1_Init); //��DMAͨ��4���г�ʼ��

	//DMA_SPI_TX  RAM->SPI�����ݴ���
	DMA_DeInit(DMA1_Channel5);
	DMA1_Init.DMA_PeripheralBaseAddr=(u32)&SPI2->DR;//��������ǰװ��ʵ��RAM��ַ
	DMA1_Init.DMA_DIR=DMA_DIR_PeripheralDST; 
	DMA1_Init.DMA_BufferSize=512;
	DMA1_Init.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA1_Init.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA1_Init.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA1_Init.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA1_Init.DMA_Mode=DMA_Mode_Normal;
	DMA1_Init.DMA_Priority=DMA_Priority_High; 
	DMA1_Init.DMA_M2M=DMA_M2M_Disable;

	DMA_Init(DMA1_Channel5,&DMA1_Init); //��DMAͨ��5���г�ʼ��

	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Rx,ENABLE); //ʹ��SPI��DMA��������
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Tx,ENABLE); //ʹ��SPI��DMA��������

	return 0;
}

//��sd����ȡһ�����ݰ�������ʱ������DMA����
//buf:���ݻ�����
//len:Ҫ��ȡ�����ݳ���.
u8 DMAx_SPI2_RX(u8 *buffer,u32 len)
{
	u8 temp=0xff;

	DMA1_Channel4->CNDTR=len;                 //���ô�������ݳ���
	DMA1_Channel4->CMAR=(uint32_t)buffer;     //�����ڴ滺������ַ

	/*SPI��Ϊ�����������ݽ���ʱ����Ҫ��������ʱ�ӣ���˴˴�������DMAͨ��5�����*/
	DMA1_Channel5->CNDTR=len; 
	DMA1_Channel5->CMAR=(uint32_t)&temp;      //temp=0xff
	DMA1_Channel5->CCR&=~DMA_MemoryInc_Enable;//�ڴ��ַ������

	DMA_Cmd(DMA1_Channel4,ENABLE);            //��������DMAͨ��4
	DMA_Cmd(DMA1_Channel5,ENABLE);            //������DMAͨ��5
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC4)); //�ȴ�DMAͨ��4�����������
	DMA_ClearFlag(DMA1_FLAG_TC4); 
	DMA_ClearFlag(DMA1_FLAG_TC5);             //���DMAͨ��4��5�Ĵ�����ɱ�־
	DMA_Cmd(DMA1_Channel4,DISABLE);
	DMA_Cmd(DMA1_Channel5,DISABLE);           //ʹDMAͨ��4��5ֹͣ����

	DMA1_Channel5->CCR|=DMA_MemoryInc_Enable; //��DMAͨ��5�ָ�Ϊ�ڴ��ַ������ʽ
	return 0;
}

//��sd��д��һ�����ݰ������� 512�ֽ� ����DMA����
//buf:���ݻ�����
u8 DMAx_SPI2_TX(u8 *buffer,u32 len)
{
	DMA1_Channel5->CNDTR=len;                 //����Ҫ��������ݳ���
	DMA1_Channel5->CMAR=(uint32_t)buffer;     //����RAM��������ַ

	DMA_Cmd(DMA1_Channel5,ENABLE);            //����DMA���� RAM->SPI
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC5)); //�ȴ�DMAͨ��5�������
	DMA_ClearFlag(DMA1_FLAG_TC5);             //���ͨ��5�������״̬���
	DMA_Cmd(DMA1_Channel5,DISABLE);           //ʹDMAͨ��5ֹͣ����
	return 0;
}

#endif

