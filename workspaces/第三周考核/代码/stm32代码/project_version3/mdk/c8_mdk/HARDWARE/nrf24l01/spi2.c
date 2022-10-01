#include "spi2.h"

//sck   PB13 时钟信号
//miso  PB14 主器件数据输入，从器件数据输出
//mosi  PB15 主器件数据输出，从器件数据输入
//SPI2  APB1(36M)时钟36M

void SPI2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );
	RCC_APB1PeriphClockCmd(	RCC_APB1Periph_SPI2,  ENABLE );
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;                    //复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);  
	
	SPI_StructInit(&SPI_InitStructure);                                       //恢复默认值
	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex;//设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;		            //设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;		            //设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_High;		              //串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_2Edge;	                //串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;		                //NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;      //定义波特率预分频的值:波特率预分频值为256   APB2/x
	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;	              //指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial     = 7;	                            //CRC值计算的多项式
	SPI_Init(SPI2, &SPI_InitStructure);                                       //初始化外设SPIx寄存器
	
	SPI_Cmd(SPI2, ENABLE);                                                    //使能SPI外设
	SPI2_ReadWriteByte(0xff);                                                 //启动传输		 
	SPI2_SetSpeed(SPI_BaudRatePrescaler_4);                                   //定义波特率预分频
	
#if DMAx_SPI2==1
	DMAx_SPI2_Init();
#endif
}   
//SPI 速度设置函数  SPI2  APB1(36M)时钟即36M
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
	SPI2->CR1|=SPI_BaudRatePrescaler;	//设置SPI2速度 
	SPI_Cmd(SPI2,ENABLE); 
} 

//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u8 retry=0;				 	
	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET) //检查指定的SPI标志位设置与否:发送缓存空标志位
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPI_I2S_SendData(SPI2, TxData); //通过外设SPIx发送一个数据
	retry=0;

	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET) //检查指定的SPI标志位设置与否:接受缓存非空标志位
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPI_I2S_ReceiveData(SPI2); //返回通过SPIx最近接收的数据					    
}








#if DMAx_SPI2==1

u8 DMAx_SPI2_Init(void)
{
	DMA_InitTypeDef DMA1_Init;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);

	//DMA_SPI_RX  SPI->RAM的数据传输
	DMA_DeInit(DMA1_Channel4);	
	DMA1_Init.DMA_PeripheralBaseAddr=(u32)&SPI2->DR;//启动传输前装入实际RAM地址
	DMA1_Init.DMA_DIR=DMA_DIR_PeripheralSRC;
	DMA1_Init.DMA_BufferSize=512;
	DMA1_Init.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA1_Init.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA1_Init.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA1_Init.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA1_Init.DMA_Mode=DMA_Mode_Normal;
	DMA1_Init.DMA_Priority=DMA_Priority_High; 
	DMA1_Init.DMA_M2M=DMA_M2M_Disable;

	DMA_Init(DMA1_Channel4,&DMA1_Init); //对DMA通道4进行初始化

	//DMA_SPI_TX  RAM->SPI的数据传输
	DMA_DeInit(DMA1_Channel5);
	DMA1_Init.DMA_PeripheralBaseAddr=(u32)&SPI2->DR;//启动传输前装入实际RAM地址
	DMA1_Init.DMA_DIR=DMA_DIR_PeripheralDST; 
	DMA1_Init.DMA_BufferSize=512;
	DMA1_Init.DMA_PeripheralInc=DMA_PeripheralInc_Disable;
	DMA1_Init.DMA_MemoryInc=DMA_MemoryInc_Enable;
	DMA1_Init.DMA_PeripheralDataSize=DMA_PeripheralDataSize_Byte;
	DMA1_Init.DMA_MemoryDataSize=DMA_MemoryDataSize_Byte;
	DMA1_Init.DMA_Mode=DMA_Mode_Normal;
	DMA1_Init.DMA_Priority=DMA_Priority_High; 
	DMA1_Init.DMA_M2M=DMA_M2M_Disable;

	DMA_Init(DMA1_Channel5,&DMA1_Init); //对DMA通道5进行初始化

	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Rx,ENABLE); //使能SPI的DMA接收请求
	SPI_I2S_DMACmd(SPI2,SPI_I2S_DMAReq_Tx,ENABLE); //使能SPI的DMA发送请求

	return 0;
}

//从sd卡读取一个数据包的内容时候启动DMA传输
//buf:数据缓存区
//len:要读取的数据长度.
u8 DMAx_SPI2_RX(u8 *buffer,u32 len)
{
	u8 temp=0xff;

	DMA1_Channel4->CNDTR=len;                 //设置传输的数据长度
	DMA1_Channel4->CMAR=(uint32_t)buffer;     //设置内存缓冲区地址

	/*SPI作为主机进行数据接收时必须要主动产生时钟，因此此处必须有DMA通道5的配合*/
	DMA1_Channel5->CNDTR=len; 
	DMA1_Channel5->CMAR=(uint32_t)&temp;      //temp=0xff
	DMA1_Channel5->CCR&=~DMA_MemoryInc_Enable;//内存地址非自增

	DMA_Cmd(DMA1_Channel4,ENABLE);            //首先启动DMA通道4
	DMA_Cmd(DMA1_Channel5,ENABLE);            //再启动DMA通道5
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC4)); //等待DMA通道4接收数据完成
	DMA_ClearFlag(DMA1_FLAG_TC4); 
	DMA_ClearFlag(DMA1_FLAG_TC5);             //清除DMA通道4与5的传输完成标志
	DMA_Cmd(DMA1_Channel4,DISABLE);
	DMA_Cmd(DMA1_Channel5,DISABLE);           //使DMA通道4与5停止工作

	DMA1_Channel5->CCR|=DMA_MemoryInc_Enable; //将DMA通道5恢复为内存地址自增方式
	return 0;
}

//向sd卡写入一个数据包的内容 512字节 启动DMA传输
//buf:数据缓存区
u8 DMAx_SPI2_TX(u8 *buffer,u32 len)
{
	DMA1_Channel5->CNDTR=len;                 //设置要传输的数据长度
	DMA1_Channel5->CMAR=(uint32_t)buffer;     //设置RAM缓冲区地址

	DMA_Cmd(DMA1_Channel5,ENABLE);            //启动DMA传输 RAM->SPI
	while(!DMA_GetFlagStatus(DMA1_FLAG_TC5)); //等待DMA通道5传输完成
	DMA_ClearFlag(DMA1_FLAG_TC5);             //清除通道5传输完成状态标记
	DMA_Cmd(DMA1_Channel5,DISABLE);           //使DMA通道5停止工作
	return 0;
}

#endif

