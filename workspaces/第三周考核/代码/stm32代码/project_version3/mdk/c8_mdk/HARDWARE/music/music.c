#include "music.h"
#include "pwm.h"
#include "delay.h"

int a[32]={38,34,30,38,38,34,30,38,30,28,
		         25,30,28,25,25,22,25,28,30,38,
	           25,22,25,28,30,38,38,51,38,38,
	           51,38};//创建数组，f=72MHZ/[(arr+1)(psc+1)]求出的arr 
;
int b[32]={500,500,500,500,500,500,500,500,500,500,
		         1000,500,500,1000,250,250,250,250,500,500,
	           250,250,250,250,500,500,500,500,1000,500,
	           500,1000};//创建数组，每一节拍延时
;

int c[54]={25,25,25,25,25,25,30,25,22,25,
	30,34,30,25,25,30,25,30,34,38,30,34,30,30,
	34,45,38,34,22,22,25,30,22,25,25,30,34,30,
25,25,25,30,34,30,25,30,34,30,45,38,34,30,38,38}
;
int d[54]={250,250,500,250,250,500,250,250,250,125,
	125,250,250,500,250,250,250,125,125,250,250,500,
	250,250,500,250,250,500,500,250,250,250,250,500,
250,250,250,250,500,500,250,250,250,250,250,250,
250,250,250,250,250,250,500,500}
;
int e[32]={38,38,25,25,22,22,25,25,28,28,30,30,
34,34,38,38,25,25,28,28,30,30,34,34,25,25,28,
28,30,30,34,34}//乐谱对应的数字
;

int f[7]={38,34,30,28,25,22,20}
;
void start_watch(void){
		u8 i=0;
   	while(1)
	{								 					 
		TIM1_PWM_Init(f[i]*100,72-1);
		TIM_SetCompare1(TIM1,f[i]*500/6);
		delay_ms(500);//每拍对应0.5s
		i++;
		if (i==7){
		break;
		}
		delay_ms(10); 
	}
	TIM_Cmd(TIM1, DISABLE);
	stop();
	
}

void two_tiger(u8 x){
	u8 j=0,i=0;
	while(1)
	{
		TIM1_PWM_Init(a[i]*100,72-1);
		TIM_SetCompare1(TIM1,a[i]*500/6);
		delay_ms(b[j]/x);
		i++;
		j++;
		if(i==32&&j==32)
			{
				//i=0,j=0;
				break;
			}
			delay_ms(10);
	}
			TIM_Cmd(TIM1, DISABLE);
	stop();
}
;

 
 void send_paper(u8 x){
	int i=0;
	int j=0;
   	while(1)
	{								 					 
		TIM1_PWM_Init(c[i]*100,72-1);
		TIM_SetCompare1(TIM1,c[i]*500/6);
		delay_ms(d[j]/x);
		i++;
		j++;
		if (i==54&&j==54){
		break;
		}
		delay_ms(10); 
	}
	TIM_Cmd(TIM1, DISABLE);
	stop();
}
;

void star(u8 x){
	u8 i=0;
   	while(1)
	{								 					 
		TIM1_PWM_Init(e[i]*100,72-1);
		TIM_SetCompare1(TIM1,e[i]*500/6);
		delay_ms(500/x);//每拍对应0.5s
		i++;
		if (i==32){
		break;
		}
		delay_ms(10); 
	}
	TIM_Cmd(TIM1, DISABLE);
	stop();
}
;

 void stop(void){
	 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_ResetBits(GPIOB,GPIO_Pin_13);						 //PG11 输出高
	 
 }
;

