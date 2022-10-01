#include "NRF24L01.h"
#include "delay.h"
#include "usart1.h"

//nrf 节点选择
#define Nrf24l01_Add_x    Nrf24l01_Add_T //节点x  两个通讯一个选T一个选R,编译后下载就好了

#if Nrf24l01_Add_x==Nrf24l01_Add_T//节点T
u8   TX_ADDRESS[TX_ADR_WIDTH]= {0x11,0x22,0x33,0x55,0x55};	//发送给别人时  对方的地址（发送帧头地址）
u8   RX_ADDRESS[RX_ADR_WIDTH]= {0x11,0x22,0x33,0x55,0x55};	//接收别人数据  自己的地址（接收校验地址）
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

#if Nrf24l01_Add_x==Nrf24l01_Add_R//节点R
u8   TX_ADDRESS[TX_ADR_WIDTH]= {0x11,0x22,0x33,0x55,0x55};	//发送给别人时  对方的地址（发送帧头地址）
u8   RX_ADDRESS[RX_ADR_WIDTH]= {0x11,0x22,0x33,0x55,0x55};	//接收别人数据  自己的地址（接收校验地址）
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

		delay_ms(10);//收的越快，发的越快。这里可以不延时，全速接收(51延时点不然printf处理不过来，不打印可以快点)
  }         
}
#endif

#if Nrf24l01_Add_x==Nrf24l01_Add_OFF//节点OFF
u8   TX_ADDRESS[TX_ADR_WIDTH];
u8   RX_ADDRESS[RX_ADR_WIDTH];
void NRF24L01_Test(void) //防止报错
{	

}
#endif

u8  NRF24L01_TX_FLAG=0;
u8  NRF24L01_RX_FLAG=0;
u8  TxBuf[TX_PLOAD_WIDTH];	
u8  RxBuf[RX_PLOAD_WIDTH];

//初始化24L01的IO口
void NRF24L01_IO_Init(void)
{ 	
	GPIO_InitTypeDef GPIO_InitStructure;
	SPI_InitTypeDef  SPI_InitStructure;			   

	My_GPIO_Init(NRF24L01_GPIOx_CE_CSN,NRF24L01_CE_Pin|NRF24L01_CSN_Pin,GPIO_TW_OUT,GPIO_P_NO,GPIO_50MHz);//推挽输出 不拉 50m
	GPIO_ResetBits(NRF24L01_GPIOx_CE_CSN,NRF24L01_CE_Pin|NRF24L01_CSN_Pin);

	My_GPIO_Init(NRF24L01_GPIOx_IRQ,NRF24L01_IRQ_Pin,GPIO_FK_IN,GPIO_P_DOWN,GPIO_50MHz);//浮空输入 下拉 50m
	GPIO_ResetBits(NRF24L01_GPIOx_IRQ,NRF24L01_IRQ_Pin);

	NRF24L01_SPI_Init();    		                                           //初始化SPI	 

	SPI_Cmd(NRF24L01_SPI, DISABLE);                                            //SPI外设不使能
	SPI_InitStructure.SPI_Direction         = SPI_Direction_2Lines_FullDuplex; //SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode              = SPI_Mode_Master;		           //SPI主机
	SPI_InitStructure.SPI_DataSize          = SPI_DataSize_8b;		           //发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL              = SPI_CPOL_Low;		               //空闲状态时钟悬空低
	SPI_InitStructure.SPI_CPHA              = SPI_CPHA_1Edge;	               //数据捕获于第1个时钟沿
	SPI_InitStructure.SPI_NSS               = SPI_NSS_Soft;		               //NSS信号由软件控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;        //定义波特率预分频的值:波特率预分频值为16
	SPI_InitStructure.SPI_FirstBit          = SPI_FirstBit_MSB;	               //数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial     = 7;	                           //CRC值计算的多项式
	SPI_Init(NRF24L01_SPI, &SPI_InitStructure);                                //初始化外设SPIx寄存器
	SPI_Cmd(NRF24L01_SPI, ENABLE);                                             //使能SPI外设

	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                   //(24L01的最大SPI时钟为10Mhz)

	NRF24L01_CE=0; 			//使能24L01
	NRF24L01_CSN=1;			//SPI片选取消 

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
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_AA,0x01);                                    //使能通道0的自动应答    
	NRF24L01_Write_Reg(NRF_WRITE_REG+EN_RXADDR,0x01);                                //使能通道0的接收地址  	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_CH,PIN_LV);	                                 //设置RF通信频率	
	NRF24L01_Write_Reg(NRF_WRITE_REG+RF_SETUP,0x0f);                                 //设置TX发射参数,0db增益,2Mbps,低噪声增益开启 
	NRF24L01_CE = 1;
}
//检测24L01是否存在  返回值:0，成功;1，失败	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i; 
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）		
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,buf,5);                                 //写入5个字节的地址.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5);                                                //读出写入的地址  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;                                                                //检测24L01错误	
	return 0;		                                                                 //检测到24L01
}

//该函数初始化NRF24L01到RX模式   设置RX地址,写RX数据宽度,选择RF频道,波特率和LNA HCURR    当CE变高后,即进入RX模式,并可以接收数据了		   
void NRF24L01_RX_Mode(void)
{
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）
	NRF24L01_CE=0;	  
	NRF24L01_Write_Buf(NRF_WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH);       //写RX0节点地址 	  
	NRF24L01_Write_Reg(NRF_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);                       //选择通道0的有效数据宽度 	    
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG, 0x0f);                                  //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式 
	NRF24L01_CE = 1;                                                                 //CE为高,进入接收模式 
}					

//该函数初始化NRF24L01到TX模式  设置TX地址,写TX数据宽度,设置RX自动应答的地址,填充TX发送数据,选择RF频道,波特率和LNA HCURR PWR_UP,CRC使能  CE为高大于10us,则启动发送.	 
void NRF24L01_TX_Mode(void)
{						
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）	
	NRF24L01_CE=0;	    
	NRF24L01_Write_Buf(NRF_WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);          //写TX节点地址
	NRF24L01_Write_Buf(NRF_WRITE_REG + RX_ADDR_P0, (u8*)TX_ADDRESS, TX_ADR_WIDTH);   //只能用接收通道0接收应答，接收方要指定应答给发送方，所以是用发送方地址应答；发送方接收应答，接收通道0地址要写成发送方地址 	
	NRF24L01_Write_Reg(NRF_WRITE_REG+SETUP_RETR,0x1a);                               //设置自动重发间隔时间:500us + 86us;最大自动重发次数:10次 
	NRF24L01_Write_Reg(NRF_WRITE_REG+CONFIG,0x0e);                                   //配置基本工作模式的参数;PWR_UP,EN_CRC,16BIT_CRC,接收模式,开启所有中断
	NRF24L01_CE=1;                                                                   //CE为高,10us后启动发送
}

//启动NRF24L01发送一次数据   txbuf:待发送数据首地址   返回值:发送完成状况
u8 NRF24L01_TxPacket(u8 *txbuf)
{
	u8 sta;
	u8 return_temp=0xff;
	NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）  
	NRF24L01_CE=0;
	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);                            //写数据到TX BUF  32个字节
	NRF24L01_CE=1;                                                                   //启动发送	   
	while(NRF24L01_IRQ_IN!=0);                                                       //等待发送完成
	sta=NRF24L01_Read_Reg(STATUS);                                                   //读取状态寄存器的值	   
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta);                                    //清除TX_DS或MAX_RT中断标志
	if(sta&MAX_TX)                                                                   //达到最大重发次数
	{
		//delay_ms(5);  //不延时会丢包	
    NRF24L01_Write_Reg(FLUSH_TX,0xff);
		return MAX_TX; 
	}
	if(sta&TX_OK)                                                                    //发送完成
	{ 
		//NRF24L01_Write_Reg(FLUSH_TX,0xff);                                         //清除TX FIFO寄存器,清接收丢失第一个，不清接收丢失最后一个
		return TX_OK;
	}
//	if(sta&RX_OK)                                                                    //接收到数据
//	{
//		return_temp=return_temp| RX_OK; 
//	}	  
	return return_temp;                                                              
}

//启动NRF24L01发送一次数据     txbuf:待发送数据首地址    返回值:0，接收完成；其他，错误代码
u8 NRF24L01_RxPacket(u8 *rxbuf)
{
	u8 sta;		    							   
    NRF24L01_SPI_SetSpeed(NRF24L01_SPI_BaudRatePrescaler_x);                         //spi速度为9Mhz（24L01的最大SPI时钟为10Mhz）	 
	sta=NRF24L01_Read_Reg(STATUS);                                                   //读取状态寄存器的值    	 
	NRF24L01_Write_Reg(NRF_WRITE_REG+STATUS,sta);                                    //清除TX_DS或MAX_RT中断标志
	if(sta&RX_OK)                                                                    //接收到数据
	{
		NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,RX_PLOAD_WIDTH);                         //读取数据
		NRF24L01_Write_Reg(FLUSH_RX,0xff);                                           //清除RX FIFO寄存器,三个接收缓存，不清除的话接收处理的慢的话会重复接收
		return RX_OK; 
	}	   
	return 0xff;                                                                     //没收到任何数据
}		

