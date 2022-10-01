#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "stm32f10x_tim.h"
#include "delay.h"
#define tri PAout(7)
#define mea PAin(4)


void trigger_init(void);
void TIM3_Cap_Init(u16 arr,u16 psc);
void measure_init(void);
void TIM2_init(u16 arr,u16 psc);
u32 distance(void);
double enviroment(void);
#endif
