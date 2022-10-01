#include "spi1.h"

//sck   PA5 ʱ���ź�
//miso  PA6 �������������룬�������������
//mosi  PA7 �����������������������������
//SPI1  APB2(72M)ʱ�Ӽ�72M

void SPI1_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1,  ENABLE ); 	
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                     //����������� 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOA,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7); 
	
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
	SPI_Init(SPI1, &SPI_InitStructure);                                       //��ʼ������SPIx�Ĵ���
	
	SPI_Cmd(SPI1, ENABLE);                                                    //ʹ��SPI����
	SPI1_ReadWriteByte(0xff);                                                 //��������		 
	SPI1_SetSpeed(SPI_BaudRatePrescaler_4);                                   //���岨����Ԥ��Ƶ
	
#if DMAx_SPI1==1
	DMAx_SPI1_Init();
#endif
}   
//SPI �ٶ����ú���  SPI1 APB2(72M)ʱ�Ӽ�72M
//#define SPI_BaudRatePrescaler_2        
//#define SPI_BaudRatePrescaler_4        
//#define SPI_BaudRatePrescaler_8        
//#define SPI_BaudRatePrescaler_16        
//#define SPI_BaudRatePrescaler_32        
//#define SPI_BaudRatePrescaler_64        
//#define SPI_BaudRatePrescaler_128     
//#define SPI_BaudRatePrescaler_256  
  
void SPI1_SetSpeed(u8 SPI_BaudRatePrescaler)
{
	assert_param(IS_SPI_BAUDRATE_PRESCALER(SPI_BaudRatePrescaler));
	SPI1->CR1&=0XFFC7;
	SPI1->CR1|=SPI_BaudRatePrescaler;	//����SPI1�ٶ� 
	SPI_Cmd(SPI1,ENABLE); 
} 

//SPIx ��дһ���ֽ�
//TxData:Ҫд����ֽ�
//����ֵ:��ȡ�����ֽ�
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET) //���ָ����SPI��־λ�������:���ͻ���ձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI1, TxData); //ͨ������SPIx����һ������
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)//���ָ����SPI��־λ�������:���ܻ���ǿձ�־λ
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI1); //����ͨ��SPIx������յ�����					    
}







#if DMAx_SPI1==1

u8 DMAx_SPI1_Init(void)
{
	DMA_InitTypeDef DMA1_Init;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	//DMA_SPI_RX  SPI->RAM�����ݴ���
	DMA_DeInit(DMA1_Channel2);	
	DMA1_Init.DMA_PeripheralBaseAddr=(u32)&SPI1->DR;//��������ǰװ��ʵ��RAM��ַ
	DMA1_Init.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA1_Init.DMA_BufferSize=512;
	DMA1_Init.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA1_Init.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA1_Init.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA1_Init.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA1_Init.DMA_Mode=DMA_Mode_Normal;
	DMA1_Init.DMA_Priority=DMA_Priority_High; 
	DMA1_Init.DMA_M2M=DMA_M2M_Disable;

	DMA_Init(DMA1_Channel2,&DMA1_Init); //��DMAͨ��2���г�ʼ��

	//DMA_SPI_TX  RAM->SPI�����ݴ���
	DMA_DeInit(DMA1_Channel3);
	DMA1_Init.DMA_PeripheralBaseAddr=(u32)&SPI1->DR;//��������ǰװ��ʵ��RAM��ַ
	DMA1_Init.DMA_DIR=DMA_DIR_PeripheralDST; 
	DMA1_Init.DMA_BufferSize=512;
	DMA1_Init.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA1_Init.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA1_Init.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA1_Init.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA1_Init.DMA_Mode=DMA_Mode_Normal;
	DMA1_Init.DMA_Priority=DMA_Priority_High; 
	DMA1_Init.DMA_M2M=DMA_M2M_Disable;

	DMA_Init(DMA1_Channel3,&DMA1_Init); //��DMAͨ��3���г�ʼ��

	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Rx,ENABLE); //ʹ��SPI��DMA��������
	SPI_I2S_DMACmd(SPI1,SPI_I2S_DMAReq_Tx,ENABLE); //ʹ��SPI��DMA��������

	return 0;
}

//��sd����ȡһ�����ݰ�������ʱ������DMA����
//buf:���ݻ�����
//len:Ҫ��ȡ�����ݳ���.
u8 DMAx_SPI1_RX(u8 *buffer,u32 len)
{
	u8 temp=0xff;

	DMA1_Channel2->CNDTR=len;                  //���ô�������ݳ���
	DMA1_Channel2->CMAR=(uint32_t)buffer;      //�����ڴ滺������ַ

	/*SPI��Ϊ�����������ݽ���ʱ����Ҫ��������ʱ�ӣ���˴˴�������DMAͨ��3�����*/
	DMA1_Channel3->CNDTR=len; 
	DMA1_Channel3->CMAR=(uint32_t)&temp;       //temp=0xff
	DMA1_Channel3->CCR&=~DMA_MemoryInc_Enable; //�ڴ��ַ������

	DMA_Cmd(DMA1_Channel2,ENABLE);             //��������DMAͨ��2
	DMA_Cmd(DMA1_Channel3,ENABLE);             //������DMAͨ��3
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC2));  //�ȴ�DMAͨ��2�����������
	DMA_ClearFlag(DMA1_FLAG_TC2); 
	DMA_ClearFlag(DMA1_FLAG_TC3);              //���DMAͨ��2��3�Ĵ�����ɱ�־
	DMA_Cmd(DMA1_Channel2,DISABLE);
	DMA_Cmd(DMA1_Channel3,DISABLE);            //ʹDMAͨ��2��3ֹͣ����

	DMA1_Channel3->CCR|=DMA_MemoryInc_Enable;  //��DMAͨ��3�ָ�Ϊ�ڴ��ַ������ʽ
	return 0;
}

//��sd��д��һ�����ݰ������� 512�ֽ� ����DMA����
//buf:���ݻ�����
u8 DMAx_SPI1_TX(u8 *buffer,u32 len)
{
	DMA1_Channel3->CNDTR=len;                  //����Ҫ��������ݳ���
	DMA1_Channel3->CMAR=(uint32_t)buffer;      //����RAM��������ַ

	DMA_Cmd(DMA1_Channel3,ENABLE);             //����DMA���� RAM->SPI
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC3));  //�ȴ�DMAͨ��3�������
	DMA_ClearFlag(DMA1_FLAG_TC3);              //���ͨ��3�������״̬���
	DMA_Cmd(DMA1_Channel3,DISABLE);            //ʹDMAͨ��3ֹͣ����
	return 0;
}

#endif


