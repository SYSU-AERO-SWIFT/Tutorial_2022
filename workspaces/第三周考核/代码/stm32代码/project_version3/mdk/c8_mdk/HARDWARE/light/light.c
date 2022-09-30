#include "light.h"

void light_init(void){
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(GPIOA,GPIO_Pin_5);						 //PG11 输出高
	
	
}

