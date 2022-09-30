#ifndef _NRF24L01_H_
#define _NRF24L01_H_	 		  
#include "sys.h"   
 
/*----------------------
|GND  VCC               |
|CE   CSN               |                 //NRF24L01+ IO�˿ڶ���
|SCK  MOSI              |
|MISO IRQ               |
-----------------------*/

////////////////////////////////////////��ֲ�޸�����///////////////////////////////////////////////////////////
//.c �ļ������κ��޸�
#define NRF24L01_GPIOx_IRQ                  GPIOB
#define NRF24L01_IRQ_Pin                    GPIO_Pin_10
#define NRF24L01_IRQ_IN                     PBin(10)                //IRQ������������
 
#define NRF24L01_GPIOx_CE_CSN               GPIOB
#define NRF24L01_CE_Pin                     GPIO_Pin_0
#define NRF24L01_CE                         PBout(0)                //TX RX�л�
#define NRF24L01_CSN_Pin                    GPIO_Pin_1
#define NRF24L01_CSN                        PBout(1)                //SPIƬѡ�ź�	
#define NRF24L01_SPI_SELECT                 2                       //1:SPI1  2:SPI2
#define NRF24L01_SPI_BaudRatePrescaler_x    SPI_BaudRatePrescaler_8 //(24L01�����SPIʱ��Ϊ10Mhz)
                                                                    //����оƬ�ͺ���SPI���÷�Ƶ��ֵ
                                                                    //103:SPI1-APB2=72M  SPI2-APB1=36M 
                                                                    //407:SPI1-APB2=84M  SPI2-APB1=42M
////////////////////////////////////////��ֲ�޸�����///////////////////////////////////////////////////////////
 
#if NRF24L01_SPI_SELECT==1
	#include "spi1.h"
	#define NRF24L01_SPI                      SPI1
	#define NRF24L01_SPI_Init                 SPI1_Init
	#define NRF24L01_SPI_ReadWriteByte        SPI1_ReadWriteByte
	#define NRF24L01_SPI_SetSpeed             SPI1_SetSpeed
	#if DMAx_SPI1==1
	#define NRF24L01_DMA                      1 
	#define NRF24L01_DMAx_SPIx_RX             DMAx_SPI1_RX
	#define NRF24L01_DMAx_SPIx_TX             DMAx_SPI1_TX
	#endif		
#endif
#if NRF24L01_SPI_SELECT==2
	#include "spi2.h"
	#define NRF24L01_SPI                      SPI2
	#define NRF24L01_SPI_Init                 SPI2_Init
	#define NRF24L01_SPI_ReadWriteByte        SPI2_ReadWriteByte
	#define NRF24L01_SPI_SetSpeed             SPI2_SetSpeed
	#if DMAx_SPI2==1
	#define NRF24L01_DMA                      1 
	#define NRF24L01_DMAx_SPIx_RX             DMAx_SPI2_RX
	#define NRF24L01_DMAx_SPIx_TX             DMAx_SPI2_TX
	#endif		
#endif

//�������Ĳ���Ҫһ�� 
//���͵�ַ��ȣ�    01:3,10:4,11:5
//���յ�ַ��ȣ�    01:3,10:4,11:5
//�������ݿ�ȣ�    1-32
//�������ݿ�ȣ�    1-32
//����Ƶ�ʣ�        0~127   2400+(0~127) 

//�Զ�Ӧ��        0:ack off   1:ack on                 Ĭ��:on
//�ط�������        0-15  0:��ֹ 1-15��   16���ط���ʱ   Ĭ��:10�Σ�500us + 86us��ʱ 
//���书�ʣ�        0:-18dbm  1:-12dbm  2:-6dbm  3:0dbm  Ĭ��::0dbm
//�������Ŵ������棺0:off 1:on                           Ĭ��:on 
//crcУ�鷽ʽ��     0:8λ   1:16λ                       Ĭ��:16λ  
//�������ʣ�        0:1Mbps 1:2Mbps                      Ĭ��:2Mbps 
#define TX_ADR_WIDTH     5   //5  detas TX address width
#define RX_ADR_WIDTH     5   //5  detas RX address width
#define TX_PLOAD_WIDTH  32   //32 detas TX payload
#define RX_PLOAD_WIDTH  32   //32 detas TX payload
#define PIN_LV           55   //0~127   2400+(0~127 )

//nrf �ڵ�ѡ��
#define Nrf24l01_Add_T     0
#define Nrf24l01_Add_R     1
#define Nrf24l01_Add_OFF   0xff

extern  u8  NRF24L01_TX_FLAG;
extern  u8  NRF24L01_RX_FLAG;
extern  u8  TX_ADDRESS[TX_ADR_WIDTH];
extern  u8  RX_ADDRESS[RX_ADR_WIDTH];
extern  u8  TxBuf[TX_PLOAD_WIDTH];	
extern  u8  RxBuf[RX_PLOAD_WIDTH];

//NRF24L01�Ĵ�����������
#define NRF_READ_REG    0x00  //�����üĴ���,��5λΪ�Ĵ�����ַ
#define NRF_WRITE_REG   0x20  //д���üĴ���,��5λΪ�Ĵ�����ַ
#define RD_RX_PLOAD     0x61  //��RX��Ч����,1~32�ֽ�
#define WR_TX_PLOAD     0xA0  //дTX��Ч����,1~32�ֽ�
#define FLUSH_TX        0xE1  //���TX FIFO�Ĵ���.����ģʽ����
#define FLUSH_RX        0xE2  //���RX FIFO�Ĵ���.����ģʽ����
#define REUSE_TX_PL     0xE3  //����ʹ����һ������,CEΪ��,���ݰ������Ϸ���.
#define NOP             0xFF  //�ղ���,����������״̬�Ĵ���	 
//SPI(NRF24L01)�Ĵ�����ַ
#define CONFIG          0x00  //���üĴ�����ַ;bit7:����;bit6:0�ж�RX_DRʹ��;bit5:0�ж�TX_DSʹ��;bit4:0�ж�MAX_RT(�ﵽ����ط������ж�)ʹ��;                                      
                              //bit3:1CRCʹ��;bit2:CRCģʽ0-8 1-16;bit1:1�ϵ� 0����;bit0:1����ģʽ,0����ģʽ;
#define EN_AA           0x01  //ʹ���Զ�Ӧ����  bit0~5,��Ӧͨ��0~5
#define EN_RXADDR       0x02  //���յ�ַ����,bit0~5,��Ӧͨ��0~5
#define SETUP_AW        0x03  //���õ�ַ���(��������ͨ��):bit1,0:00,3�ֽ�;01,4�ֽ�;02,5�ֽ�;
#define SETUP_RETR      0x04  //�����Զ��ط�;bit3:0,�Զ��ط�������;bit7:4,�Զ��ط���ʱ 250*x+86us
#define RF_CH           0x05  //RFͨ��,bit6:0,����ͨ��Ƶ��;
#define RF_SETUP        0x06  //RF�Ĵ���;bit3:��������(0:1Mbps,1:2Mbps);bit2:1,���书��;bit0:�������Ŵ�������
#define STATUS          0x07  //״̬�Ĵ���;bit0:TX FIFO����־;bit3:1,��������ͨ����(���:6);bit4,�ﵽ�����ط�
                              //bit5:���ݷ�������ж�;bit6:���������ж�;
#define MAX_TX          0x10  //�ﵽ����ʹ����ж�
#define TX_OK           0x20  //TX��������ж�
#define RX_OK           0x40  //���յ������ж�

#define OBSERVE_TX      0x08  //���ͼ��Ĵ���,bit7:4,���ݰ���ʧ������;bit3:0,�ط�������
#define CD              0x09  //�ز����Ĵ���,bit0,�ز����;
#define RX_ADDR_P0      0x0A  //����ͨ��0���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P1      0x0B  //����ͨ��1���յ�ַ,��󳤶�5���ֽ�,���ֽ���ǰ
#define RX_ADDR_P2      0x0C  //����ͨ��2���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P3      0x0D  //����ͨ��3���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P4      0x0E  //����ͨ��4���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define RX_ADDR_P5      0x0F  //����ͨ��5���յ�ַ,����ֽڿ�����,���ֽ�,����ͬRX_ADDR_P1[39:8]���;
#define TX_ADDR         0x10  //���͵�ַ(���ֽ���ǰ),ShockBurstTMģʽ��,RX_ADDR_P0��˵�ַ���
#define RX_PW_P0        0x11  //��������ͨ��0��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P1        0x12  //��������ͨ��1��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P2        0x13  //��������ͨ��2��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P3        0x14  //��������ͨ��3��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P4        0x15  //��������ͨ��4��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define RX_PW_P5        0x16  //��������ͨ��5��Ч���ݿ��(1~32�ֽ�),����Ϊ0��Ƿ�
#define NRF_FIFO_STATUS 0x17  //FIFO״̬�Ĵ���;bit0,RX FIFO�Ĵ����ձ�־;bit1,RX FIFO����־;bit2,3,����
                              //bit4,TX FIFO�ձ�־;bit5,TX FIFO����־;bit6,1,ѭ��������һ���ݰ�.0,��ѭ��;
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void NRF24L01_IO_Init(void);
u8   NRF24L01_Read_Reg(u8 reg);
u8   NRF24L01_Write_Reg(u8 reg, u8 value);
u8   NRF24L01_Read_Buf(u8 reg, u8 *pBuf, u8 values);
u8   NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 values);

void NRF24L01_Test(void);
void NRF24L01_Init(void);
u8   NRF24L01_Check(void);   
void NRF24L01_RX_Mode(void);
void NRF24L01_TX_Mode(void);
u8   NRF24L01_TxPacket(u8 *txbuf);
u8   NRF24L01_RxPacket(u8 *rxbuf);
void NRF24L01_Clear_TxBuf(void);
void NRF24L01_Clear_RxBuf(void);

//�����ֲ��ϵĹ�ʽ���㣬��ack�շ�����32byte��2bytecrc
//TESB = TUL + 2 . Tstby2a + TOA + TACK + TIRQ
//ÿ�η��͵�һ�ξͳɹ���һ֡ʱ��TESB��623.5uS ����������1s��Լ��1604֡(������f103���޲���1611-1612֡50kb/s)��
//����ÿ�ζ��ﵽ������ط�3�Σ�һ֡ʱ�� Tul+3*��Tstby2a+TOA+Tard��=2412us��1sԼ414.6֡
#endif

