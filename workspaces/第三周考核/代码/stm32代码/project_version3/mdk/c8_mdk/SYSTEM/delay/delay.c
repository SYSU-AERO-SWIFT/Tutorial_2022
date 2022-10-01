#include "delay.h"
#include "misc.h"

static u8  fac_us=0;							//us��ʱ������			   
static u32 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

//��ʼ���ӳٺ���
//SYSTICK��ʱ�ӹ̶�ΪHCLKʱ��
//SYSCLK:ϵͳʱ��
void delay_init(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);	//ѡ���ⲿʱ��  HCLK
	fac_us=SystemCoreClock/1000000;						//Ϊϵͳʱ�ӵ�
	fac_ms=fac_us*1000;									//��OS��,����ÿ��ms��Ҫ��systickʱ���� 
}	

//��ʱus
//usΪҪ��ʱ��us��.
void delay_us(u32 us)
{
	u32 temp;		   
	SysTick->LOAD=(u32)us*fac_us;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	temp=SysTick->VAL;
	do
	{
		temp=SysTick->CTRL;

	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����	  
}

//��ʱms
//ע��ms�ķ�Χ
//��72M������,SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:ms<=0xffffff*1000/SYSCLK
//200msΪһ�����ڣ�����200MS�����������ʱʱ�䡣���ʱʱ�� 200ms*65535
void delay_ms(u16 ms){
	u32 temp;	
	u8 t;
	u16 temp1;
	temp1=ms/200;
	for(t=0;t<temp1;t++)
	{
		SysTick->LOAD=(u32)200*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
		SysTick->VAL =0x00;							//��ռ�����
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
		temp=SysTick->VAL;
		do
		{
			temp=SysTick->CTRL;

		}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
		SysTick->VAL =0X00;       					//��ռ�����	  
	}
	if((ms%200)!=0)
	{
		SysTick->LOAD=(u32)(ms%200)*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
		SysTick->VAL =0x00;							//��ռ�����
		SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
		temp=SysTick->VAL;
		do
		{
			temp=SysTick->CTRL;

		}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
		SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
		SysTick->VAL =0X00;       					//��ռ�����	
	}		
}




