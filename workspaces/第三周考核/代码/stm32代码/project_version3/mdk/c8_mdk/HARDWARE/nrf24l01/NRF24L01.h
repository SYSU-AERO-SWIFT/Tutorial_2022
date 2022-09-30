#ifndef _NRF24L01_H_
#define _NRF24L01_H_	 		  
#include "sys.h"   
 
/*----------------------
|GND  VCC               |
|CE   CSN               |                 //NRF24L01+ IO端口定义
|SCK  MOSI              |
|MISO IRQ               |
-----------------------*/

////////////////////////////////////////移植修改区域///////////////////////////////////////////////////////////
//.c 文件无需任何修改
#define NRF24L01_GPIOx_IRQ                  GPIOB
#define NRF24L01_IRQ_Pin                    GPIO_Pin_10
#define NRF24L01_IRQ_IN                     PBin(10)                //IRQ主机数据输入
 
#define NRF24L01_GPIOx_CE_CSN               GPIOB
#define NRF24L01_CE_Pin                     GPIO_Pin_0
#define NRF24L01_CE                         PBout(0)                //TX RX切换
#define NRF24L01_CSN_Pin                    GPIO_Pin_1
#define NRF24L01_CSN                        PBout(1)                //SPI片选信号	
#define NRF24L01_SPI_SELECT                 2                       //1:SPI1  2:SPI2
#define NRF24L01_SPI_BaudRatePrescaler_x    SPI_BaudRatePrescaler_8 //(24L01的最大SPI时钟为10Mhz)
                                                                    //根据芯片型号与SPI设置分频数值
                                                                    //103:SPI1-APB2=72M  SPI2-APB1=36M 
                                                                    //407:SPI1-APB2=84M  SPI2-APB1=42M
////////////////////////////////////////移植修改区域///////////////////////////////////////////////////////////
 
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

//配对下面的参数要一致 
//发送地址宽度：    01:3,10:4,11:5
//接收地址宽度：    01:3,10:4,11:5
//发送数据宽度：    1-32
//接收数据宽度：    1-32
//发射频率：        0~127   2400+(0~127) 

//自动应答：        0:ack off   1:ack on                 默认:on
//重发次数：        0-15  0:禁止 1-15次   16种重发延时   默认:10次，500us + 86us延时 
//发射功率：        0:-18dbm  1:-12dbm  2:-6dbm  3:0dbm  默认::0dbm
//低噪声放大器增益：0:off 1:on                           默认:on 
//crc校验方式：     0:8位   1:16位                       默认:16位  
//传输速率：        0:1Mbps 1:2Mbps                      默认:2Mbps 
#define TX_ADR_WIDTH     5   //5  detas TX address width
#define RX_ADR_WIDTH     5   //5  detas RX address width
#define TX_PLOAD_WIDTH  32   //32 detas TX payload
#define RX_PLOAD_WIDTH  32   //32 detas TX payload
#define PIN_LV           55   //0~127   2400+(0~127 )

//nrf 节点选择
#define Nrf24l01_Add_T     0
#define Nrf24l01_Add_R     1
#define Nrf24l01_Add_OFF   0xff

extern  u8  NRF24L01_TX_FLAG;
extern  u8  NRF24L01_RX_FLAG;
extern  u8  TX_ADDRESS[TX_ADR_WIDTH];
extern  u8  RX_ADDRESS[RX_ADR_WIDTH];
extern  u8  TxBuf[TX_PLOAD_WIDTH];	
extern  u8  RxBuf[RX_PLOAD_WIDTH];

//NRF24L01寄存器操作命令
#define NRF_READ_REG    0x00  //读配置寄存器,低5位为寄存器地址
#define NRF_WRITE_REG   0x20  //写配置寄存器,低5位为寄存器地址
#define RD_RX_PLOAD     0x61  //读RX有效数据,1~32字节
#define WR_TX_PLOAD     0xA0  //写TX有效数据,1~32字节
#define FLUSH_TX        0xE1  //清除TX FIFO寄存器.发射模式下用
#define FLUSH_RX        0xE2  //清除RX FIFO寄存器.接收模式下用
#define REUSE_TX_PL     0xE3  //重新使用上一包数据,CE为高,数据包被不断发送.
#define NOP             0xFF  //空操作,可以用来读状态寄存器	 
//SPI(NRF24L01)寄存器地址
#define CONFIG          0x00  //配置寄存器地址;bit7:保留;bit6:0中断RX_DR使能;bit5:0中断TX_DS使能;bit4:0中断MAX_RT(达到最大重发次数中断)使能;                                      
                              //bit3:1CRC使能;bit2:CRC模式0-8 1-16;bit1:1上电 0掉电;bit0:1接收模式,0发射模式;
#define EN_AA           0x01  //使能自动应答功能  bit0~5,对应通道0~5
#define EN_RXADDR       0x02  //接收地址允许,bit0~5,对应通道0~5
#define SETUP_AW        0x03  //设置地址宽度(所有数据通道):bit1,0:00,3字节;01,4字节;02,5字节;
#define SETUP_RETR      0x04  //建立自动重发;bit3:0,自动重发计数器;bit7:4,自动重发延时 250*x+86us
#define RF_CH           0x05  //RF通道,bit6:0,工作通道频率;
#define RF_SETUP        0x06  //RF寄存器;bit3:传输速率(0:1Mbps,1:2Mbps);bit2:1,发射功率;bit0:低噪声放大器增益
#define STATUS          0x07  //状态寄存器;bit0:TX FIFO满标志;bit3:1,接收数据通道号(最大:6);bit4,达到最多次重发
                              //bit5:数据发送完成中断;bit6:接收数据中断;
#define MAX_TX          0x10  //达到最大发送次数中断
#define TX_OK           0x20  //TX发送完成中断
#define RX_OK           0x40  //接收到数据中断

#define OBSERVE_TX      0x08  //发送检测寄存器,bit7:4,数据包丢失计数器;bit3:0,重发计数器
#define CD              0x09  //载波检测寄存器,bit0,载波检测;
#define RX_ADDR_P0      0x0A  //数据通道0接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P1      0x0B  //数据通道1接收地址,最大长度5个字节,低字节在前
#define RX_ADDR_P2      0x0C  //数据通道2接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P3      0x0D  //数据通道3接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P4      0x0E  //数据通道4接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define RX_ADDR_P5      0x0F  //数据通道5接收地址,最低字节可设置,高字节,必须同RX_ADDR_P1[39:8]相等;
#define TX_ADDR         0x10  //发送地址(低字节在前),ShockBurstTM模式下,RX_ADDR_P0与此地址相等
#define RX_PW_P0        0x11  //接收数据通道0有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P1        0x12  //接收数据通道1有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P2        0x13  //接收数据通道2有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P3        0x14  //接收数据通道3有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P4        0x15  //接收数据通道4有效数据宽度(1~32字节),设置为0则非法
#define RX_PW_P5        0x16  //接收数据通道5有效数据宽度(1~32字节),设置为0则非法
#define NRF_FIFO_STATUS 0x17  //FIFO状态寄存器;bit0,RX FIFO寄存器空标志;bit1,RX FIFO满标志;bit2,3,保留
                              //bit4,TX FIFO空标志;bit5,TX FIFO满标志;bit6,1,循环发送上一数据包.0,不循环;
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

//按照手册上的公式计算，带ack收发都是32byte，2bytecrc
//TESB = TUL + 2 . Tstby2a + TOA + TACK + TIRQ
//每次发送第一次就成功，一帧时间TESB≈623.5uS 这样算下来1s大约有1604帧(本代码f103极限测试1611-1612帧50kb/s)。
//就算每次都达到了最大重发3次，一帧时间 Tul+3*（Tstby2a+TOA+Tard）=2412us，1s约414.6帧
#endif

