#include "key.h"


void key_init(){
  GPIO_InitTypeDef  GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
 	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;				 //PG11�˿�����
 	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;		 //�������
 	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStruct);				 //��ʼ��IO��		
	
	
}
;
