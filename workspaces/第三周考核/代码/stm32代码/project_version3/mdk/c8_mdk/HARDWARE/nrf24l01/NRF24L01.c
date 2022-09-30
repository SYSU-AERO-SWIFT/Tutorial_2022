#include "NRF24L01.h"
#include "delay.h"
#include "usart1.h"

//nrf �ڵ�ѡ��
#define Nrf24l01_Add_x    Nrf24l01_Add_T //�ڵ�x  ����ͨѶһ��ѡTһ��ѡR,��������ؾͺ���

#if Nrf24l01_Add_x==Nrf24l01_Add_T//�ڵ�T
u8   TX_ADDRESS[TX_ADR_WIDTH]= {0x11,0x22,0x33,0x55,0x55};	//���͸�����ʱ  �Է��ĵ�ַ������֡ͷ��ַ��
u8   RX_ADDRESS[RX_ADR_WIDTH]= {0x11,0x22,0x33,0x55,0x55};	//���ձ�������  �Լ��ĵ�ַ������У���ַ��
void NRF24L01_Test(void)
{	
	u16 i = 0;
	NRF24L01_Init();    		

	while(NRF24L01_Check())
	{
		USART1_printf("NRF24L01 Error\r\n");
		delay_ms(1000);
	}
	USART1_printf("NRF24L01  TX  OK...\r\n");
  
	NRF24L01_TX_Mode(); 
	while(1)
	{	
		NRF24L01_TX_FLAG= NRF24L01_TxPacket(TxBuf);        		   				 
		if(NRF24L01_TX_FLAG==TX_OK)
		{
			USART1_printf("%s","fasong:");
			for (i = 0;i< RX_PLOAD_WIDTH;i++)
				USART1_printf("%3d,",(u16)TxBuf[i]);
			USART1_printf("\r\n");
			TxBuf[0]++;  
		}
	}	
}
#endif

#if Nrf24l01_Add_x==Nrf24l01_Add_R//�ڵ�R
u8   TX_ADDRESS[TX_ADR_WIDTH]= {0x11,0x22,0x33,0x55,0x55};	//���͸�����ʱ  �Է��ĵ�ַ������֡ͷ��ַ��
u8   RX_ADDRESS[RX_ADR_WIDTH]= {0x11,0x22,0x33,0x55,0x55};	//���ձ�������  �Լ��ĵ�ַ������У���ַ��
void NRF24L01_Test(void) 
{	
	u32 old=0,error=0;

	NRF24L01_Init();    	

	while(NRF24L01_Check())
	{
		printf("NRF24L01 Error\r\n");
		delay_ms(1000);
	}
	USART1_printf("NRF24L01  RX  OK...\r\n");
          
	NRF24L01_RX_Mode(); 
	while(1)
	{	  
		NRF24L01_RX_FLAG=NRF24L01_RxPacket(RxBuf);	
		if(NRF24L01_RX_FLAG==RX_OK)
		{
			printf("RxBuf=%3d  old=%3d  error=%3d",(u16)RxBuf[0],(u16)old,(u16)error);
			printf("\r\n"); 
			if((RxBuf[0]!=(old+1))&&(RxBuf[0]!=0))
			{
				printf("Rx error\r\n");
				error++;
			} 
			old=RxBuf[0];
		}

		delay_ms(10);//�յ�Խ�죬����Խ�졣������Բ���ʱ��ȫ�ٽ���(51��ʱ�㲻Ȼprintf��������������ӡ���Կ��)
  }         
}
#endif

#if Nrf24l01_Add_x==Nrf24l01_Add_OFF//�ڵ�OFF
u8   TX_ADDRESS[TX_ADR_WIDTH];
u8   RX_ADDRESS[RX_ADR_WIDTH];
void NRF24L01_Test(void) //��ֹ����
{	

}
#endif

u8  NRF24L01_TX_FLAG=0;
u8  NRF24L01_RX_FLAG=0;
u8  TxBuf[TX_PLOAD_WIDTH];	
u8  RxBuf[RX_PLOAD_WIDTH];

//��ʼ��24L01��IO��
void NRF24L01_IO_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;			   

	My_GPIO_Init(NRF24L01_GPIOx_CE_CSN,NRF24L01_CE_Pin|NRF24L01_CSN_Pin,GPIO_TW_OUT,GPIO_P_NO,GPIO_50MHz);//������� ���� 50m
	GPIO_ResetBits(NRF24L01_GPIOx_CE_CSN,NRF24L01_CE_Pin|NRF24L01_CSN_Pin);

	My_GPIO_Init(NRF24L01_GPIOx_IRQ,NRF24L01_IRQ_Pin,GPIO_FK_IN,GPIO_P_DOWN,GPIO_50MHz);//�������� ���� 50m
	GPIO_ResetBits(NRF24L01_GPIOx_IRQ,NRF24L01_IRQ_Pin);

	NRF24L01_SPI_Init();    		                                           //��ʼ��SPI	 

	SPI_Cmd(NRF24L01_SPI, DISABLE);                                            //SPI���費ʹ��
	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex; //SPI����Ϊ˫��˫��ȫ˫��
	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;		           //SPI����
	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;		           //���ͽ���8λ֡�ṹ
	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;		               //����״̬ʱ�����յ�
	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_1Edge;	               //���ݲ����ڵ�1��ʱ����
	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;		               //NSS�ź����������
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;        //���岨����Ԥ��Ƶ��ֵ:������Ԥ��ƵֵΪ16
	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;	               //���ݴ����MSBλ��ʼ
	SPI_InitStructure.SPI_CRCPolynomial     = 7;	                           //CRCֵ����Ķ���ʽ
	SPI_Init(NRF24L01_SPI, &SPI_InitStructure);                                //��ʼ������SPIx�Ĵ���
	SPI_Cmd(NRF24L01_SPI, ENABLE);                                             //ʹ��SPI����

	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                   //(24L01�����SPIʱ��Ϊ10Mhz)

	NRF24L01_CE=0; 			//ʹ��24L01
	NRF24L01_CSN=1;			//SPIƬѡȡ�� 

	NRF24L01_Clear_TxBuf();
}

void NRF24L01_Clear_TxBuf(void)
{
	u8 i=0;
	for (i = 0;i< TX_PLOAD_WIDTH;i++)
		TxBuf[i]=0;	
}

void NRF24L01_Clear_RxBuf(void)
{
	u8 i=0;
	for (i = 0;i<RX_PLOAD_WIDTH;i++)
		RxBuf[i]=0;	
} 

u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;
	NRF24L01_CSN = 0;                               
	NRF24L01_SPI_ReadWriteByte(reg);              
	reg_val = NRF24L01_SPI_ReadWriteByte(0);       
	NRF24L01_CSN = 1;                              
	return(reg_val);         
}

u8 NRF24L01_Write_Reg(u8 reg, u8 value)
{
	u8 status;
	NRF24L01_CSN = 0;                              
	status = NRF24L01_SPI_ReadWriteByte(reg);      
	NRF24L01_SPI_ReadWriteByte(value);              
	NRF24L01_CSN = 1;                              
	return(status);            
}

u8 NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 values)
{
	u8 status,u8_ctr;
	NRF24L01_CSN = 0;                    		       
	status = NRF24L01_SPI_ReadWriteByte(reg);       
	for(u8_ctr=0;u8_ctr<values;u8_ctr++)
		pBuf[u8_ctr] = NRF24L01_SPI_ReadWriteByte(0);   
	NRF24L01_CSN = 1;                           
	return status;                   
}

u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 values)
{
	u8 status,u8_ctr;
	NRF24L01_CSN = 0;           									      
	status = NRF24L01_SPI_ReadWriteByte(reg);   
	for(u8_ctr=0; u8_ctr<values; u8_ctr++) 
	NRF24L01_SPI_ReadWriteByte(*pBuf++);
	NRF24L01_CSN = 1;          										
	return(status);    
}


void NRF24L01_Init(void)
{
	NRF24L01_IO_Init();
	NRF24L01_CE=0;	  
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);                                    //ʹ��ͨ��0���Զ�Ӧ��    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);                                //ʹ��ͨ��0�Ľ��յ�ַ  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,PIN_LV);	                                 //����RFͨ��Ƶ��	
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);                                 //����TX�������,0db����,2Mbps,���������濪�� 
	NRF24L01_CE = 1;
}
//���24L01�Ƿ����  ����ֵ:0���ɹ�;1��ʧ��	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i; 
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��		
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);                                 //д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5);                                                //����д��ĵ�ַ  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;                                                                //���24L01����	
	return 0;		                                                                 //��⵽24L01
}

//�ú�����ʼ��NRF24L01��RXģʽ   ����RX��ַ,дRX���ݿ��,ѡ��RFƵ��,�����ʺ�LNA HCURR    ��CE��ߺ�,������RXģʽ,�����Խ���������		   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��
	NRF24L01_CE=0;	  
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);       //дRX0�ڵ��ַ 	  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);                       //ѡ��ͨ��0����Ч���ݿ�� 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);                                  //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ 
	NRF24L01_CE = 1;                                                                 //CEΪ��,�������ģʽ 
}					

//�ú�����ʼ��NRF24L01��TXģʽ  ����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR PWR_UP,CRCʹ��  CEΪ�ߴ���10us,����������.	 
void NRF24L01_TX_Mode(void)
{						
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��	
	NRF24L01_CE=0;	    
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);          //дTX�ڵ��ַ
	NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, (u8*)TX_ADDRESS, TX_ADR_WIDTH);   //ֻ���ý���ͨ��0����Ӧ�𣬽��շ�Ҫָ��Ӧ������ͷ����������÷��ͷ���ַӦ�𣻷��ͷ�����Ӧ�𣬽���ͨ��0��ַҪд�ɷ��ͷ���ַ 	
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);                               //�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10�� 
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);                                   //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE=1;                                                                   //CEΪ��,10us����������
}

//����NRF24L01����һ������   txbuf:�����������׵�ַ   ����ֵ:�������״��
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
	u8 return_temp=0xff;
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��  
	NRF24L01_CE=0;
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);                            //д���ݵ�TX BUF  32���ֽ�
	NRF24L01_CE=1;                                                                   //��������	   
	while(NRF24L01_IRQ_IN!=0);                                                       //�ȴ��������
	sta=NRF24L01_Read_Reg(STATUS);                                                   //��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta);                                    //���TX_DS��MAX_RT�жϱ�־
	if(sta&MAX_TX)                                                                   //�ﵽ����ط�����
	{
		//delay_ms(5);  //����ʱ�ᶪ��	
    NRF24L01_Write_Reg(FLUSH_TX,0xff);
		return MAX_TX; 
	}
	if(sta&TX_OK)                                                                    //�������
	{ 
		//NRF24L01_Write_Reg(FLUSH_TX,0xff);                                         //���TX FIFO�Ĵ���,����ն�ʧ��һ����������ն�ʧ���һ��
		return TX_OK;
	}
//	if(sta&RX_OK)                                                                    //���յ�����
//	{
//		return_temp=return_temp| RX_OK; 
//	}	  
	return return_temp;                                                              
}

//����NRF24L01����һ������     txbuf:�����������׵�ַ    ����ֵ:0��������ɣ��������������
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
    NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi�ٶ�Ϊ9Mhz��24L01�����SPIʱ��Ϊ10Mhz��	 
	sta=NRF24L01_Read_Reg(STATUS);                                                   //��ȡ״̬�Ĵ�����ֵ    	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta);                                    //���TX_DS��MAX_RT�жϱ�־
	if(sta&RX_OK)                                                                    //���յ�����
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);                         //��ȡ����
		NRF24L01_Write_Reg(FLUSH_RX,0xff);                                           //���RX FIFO�Ĵ���,�������ջ��棬������Ļ����մ�������Ļ����ظ�����
		return RX_OK; 
	}	   
	return 0xff;                                                                     //û�յ��κ�����
}		

