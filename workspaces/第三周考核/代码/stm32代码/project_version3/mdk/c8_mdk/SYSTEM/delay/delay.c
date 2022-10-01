#include "delay.h"
#include "misc.h"

static u8  fac_us=0;							//us延时倍乘数			   
static u32 fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数

//初始化延迟函数
//SYSTICK的时钟固定为HCLK时钟
//SYSCLK:系统时钟
void delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//选择外部时钟  HCLK
	fac_us=SystemCoreClock/1000000;						//为系统时钟的
	fac_ms=fac_us*1000;									//非OS下,代表每个ms需要的systick时钟数 
}	

//延时us
//us为要延时的us数.
void delay_us(u32 us)
{
	u32 temp;		   
	SysTick->LOAD=(u32)us*fac_us;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	temp=SysTick->VAL;
	do
	{
		temp=SysTick->CTRL;

	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	  
}

//延时ms
//注意ms的范围
//对72M条件下,SysTick->LOAD为24位寄存器,所以,最大延时为:ms<=0xffffff*1000/SYSCLK
//200ms为一个周期，大于200MS引入变量扩大定时时间。最大定时时间 200ms*65535
void delay_ms(u16 ms){
	u32 temp;	
	u8 t;
	u16 temp1;
	temp1=ms/200;
	for(t=0;t<temp1;t++)
	{
		SysTick->LOAD=(u32)200*fac_ms;				//时间加载(SysTick->LOAD为24bit)
		SysTick->VAL =0x00;							//清空计数器
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
		temp=SysTick->VAL;
		do
		{
			temp=SysTick->CTRL;

		}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
		SysTick->VAL =0X00;       					//清空计数器	  
	}
	if((ms%200)!=0)
	{
		SysTick->LOAD=(u32)(ms%200)*fac_ms;				//时间加载(SysTick->LOAD为24bit)
		SysTick->VAL =0x00;							//清空计数器
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
		temp=SysTick->VAL;
		do
		{
			temp=SysTick->CTRL;

		}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
		SysTick->VAL =0X00;       					//清空计数器	
	}		
}




