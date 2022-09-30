#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "NRF24L01.h"
#include "pwm.h"
#include "oled.h"
#include "key.h"
#include "adc.h"
#include "sys.h"
#include "malloc.h"

u8 *rem;
u8 one=0,two=0,three=0,four=0,len=3;
u8 mode=0,step=0;


void fresh_oled(void){
	OLED_Clear();
	OLED_ShowString(0,0, "one ",12);
	OLED_ShowNum(27,0,one,3,16);
	OLED_ShowString(64,0, "two ",12);
	OLED_ShowNum(94,0,two,3,16);
	OLED_ShowString(0,30, "three ",12);
	OLED_ShowNum(30,30,three,3,16);
	OLED_ShowString(64,30, "four ",12);
	OLED_ShowNum(94,30,four,3,16);
	OLED_Refresh_Gram();
}
;
void circle(u8 x,u8 angle){
	double pack=0;
	if(angle>180)return;
	pack=(double)angle/180*2+0.5;
	if(x==1){
		one=angle;
		TIM_SetCompare1(TIM1,200-(u8)(pack*10));
	}else if(x==2&&(180-three)>(angle-20)&&(180-three-angle)<100){
		two=angle;
		TIM_SetCompare1(TIM2,200-(u8)(pack*10));
	}else if(x==3&&(180-angle)>(two-20)&&(180-angle-two)<100){
		three=angle;
		TIM_SetCompare1(TIM3,200-(u8)(pack*10));
	}else if(x==4&&angle>80&&angle<=133){
		four=angle;
		TIM_SetCompare4(TIM4,200-(u8)(pack*10));
	}
}
;

void send(void){
					NRF24L01_TX_Mode();
				TxBuf[0]=5;
				TxBuf[1]=one;
				TxBuf[2]=two;
				TxBuf[3]=three;
				TxBuf[4]=four;
	      TxBuf[5]=len;
				while(NRF24L01_TxPacket(TxBuf)!=TX_OK);
				NRF24L01_RX_Mode();
}
;
void deal(void){
		if(RxBuf[0]!=0){
			if(RxBuf[1]=='a'){
				if(two<=180-len)
				circle(2,two+len);
			}else if(RxBuf[1]=='q'){
		    if(two>=len)
				circle(2,two-len);
			}else if(RxBuf[1]=='d'){
        if(three>=len)
				circle(3,three-len);
			}else if(RxBuf[1]=='e'){
		    if(three<=180-len)
				circle(3,three+len);
			}else if(RxBuf[1]=='k'){
		    if(one<=180-len)
				circle(1,one+len);
			}else if(RxBuf[1]==';'){
		    if(one>=len)
				circle(1,one-len);
			}else if(RxBuf[1]=='o'){
		    if(four<=180-len)
				circle(4,four+len);
			}else if(RxBuf[1]=='l'){
		    if(four>=len)
				circle(4,four-len);
			}else if(RxBuf[1]=='r'){
					circle(1,90);
	        circle(2,90);
	        circle(3,45);
	        circle(4,100);
			}else if(RxBuf[1]<='9'&&RxBuf[1]>='1'){
				len=(RxBuf[1]-'0')*3;
			}
		}
}
;
void mode0(void){
		NRF24L01_RX_Mode();
		while(NRF24L01_RxPacket(RxBuf)!=RX_OK);
    deal();
		send();

}
;
void mode1(void){
	u8 i;
	for(i=1;i<=4;i++){
		circle(i,(u8)((double)(Get_Adc_Average(i,70))/4096*180));
	}
	
	
	if(step==0&&KEY2==0){
		delay_ms(10);
		while(KEY2==0);
		step=1;
	}
	if(step==1&&four>=117){
		rem[1]=one;rem[2]=two;rem[3]=three;
		step=2;
	}
	if(step==2&&four<=90){
		rem[4]=one;rem[5]=two;rem[6]=three;
		step=3;
	}
	if(step==3&&KEY2==0){
		delay_ms(10);
		while(KEY2==0);
		circle(1,rem[1]);delay_ms(2000);
		circle(2,rem[2]);delay_ms(2000);
		circle(3,rem[3]);delay_ms(2000);
		circle(4,80);delay_ms(2000);
		circle(4,127);delay_ms(2000);
		circle(1,rem[4]);delay_ms(2000);
		circle(2,rem[5]);delay_ms(2000);
		circle(3,rem[6]);delay_ms(2000);
		circle(4,80);delay_ms(2000);
		step=0;
	}
}
;
int main(void)
{	

	//SystemInit();
  delay_init();            //延时函数初始化
Adc_Init();	
	mem_init();
	rem=mymalloc(10);
  TIM1_PWM_Init(199,7199);
	TIM2_PWM_Init(199,7199);
	TIM3_PWM_Init(199,7199);
	TIM4_PWM_Init(199,7199);
	OLED_Init();
	key_init();
	circle(1,90);
	delay_ms(500);
	circle(2,90);
	delay_ms(500);
	circle(3,45);
	delay_ms(500);
	circle(4,100);
	NRF24L01_Init();
	while(NRF24L01_Check()){
		delay_ms(2000);
		circle(1,80);
		delay_ms(2000);
		circle(1,100);
	};
/*
	while(1){
		if(KEY1==0){
			delay_ms(5);
			while(KEY1==0);
		circle(1,120);
		 delay_ms(1000);
			circle(1,30);
			delay_ms(1000);
	}
		
	}*/
	
	while(1){
		if(KEY1==0){
			delay_ms(10);
			while(KEY1==0);
			if(mode==1){
			    mode=0;
	circle(1,80);
			}else if(mode==0){
			    mode=1;
	circle(1,120);
			}
			delay_ms(1000);
		}
		if(mode==1){
			mode1();
		}else if(mode==0){
			mode0();
		}
				fresh_oled();	
	}
}

