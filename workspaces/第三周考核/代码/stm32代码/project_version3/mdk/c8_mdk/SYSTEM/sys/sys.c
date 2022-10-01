#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK Mini STM32开发板
//系统中断分组设置化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/10
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************  
//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
	__ASM volatile("wfi");		  
}
//关闭所有中断
void INTX_DISABLE(void)
{		  
	__ASM volatile("cpsid i");
}
//开启所有中断
void INTX_ENABLE(void)
{
	__ASM volatile("cpsie i");		  
}
//设置栈顶地址
//addr:栈顶地址
__asm void MSR_MSP(u32 addr) 
{
    MSR MSP, r0 			//set Main Stack value
    BX r14
}
;


//stm32 通用外设初始化方案，方便不同芯片移植
void My_GPIO_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,GPIO_My_TypeDef mode,GPIO_My_TypeDef up_down,GPIO_My_TypeDef speed)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
   
	RCC_APB2PeriphClockCmd(power(2,((uint32_t)GPIOx-(uint32_t)GPIOA)/0x0400+2), ENABLE);
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin;        
 
	if(mode==GPIO_AD_IN) 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 
	if(mode==GPIO_FK_IN && up_down==GPIO_P_NO) 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	if(mode==GPIO_FK_IN && up_down==GPIO_P_DOWN)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  
	if(mode==GPIO_FK_IN && up_down==GPIO_P_UP)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
	if(mode==GPIO_KL_OUT)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
	if(mode==GPIO_TW_OUT)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	if(mode==GPIO_KL_AF_OUT)
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	if(mode==GPIO_TW_AF_OUT)		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;

 	if(speed==GPIO_2MHz)
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; 
	if(speed==GPIO_25MHz)
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	if(speed==GPIO_50MHz)
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               

	GPIO_Init(GPIOx, &GPIO_InitStructure);         	
}
;
u32 power(u32 x,u32 y)
{
	u32 mul = 1;

	u32 i;
	for( i = 0;i<y;i++)
	{
		mul = mul * x;
	}
	return mul;
}
;
u32 log_2(u32 x)
{
	u8 i=0;
	while(1)
	{
		if(power(2,i)==x)
			return i;
		else
			i++;
	}
}
;
