#ifndef __MOTOR_H
#define __MOTOR_H

//硬件连接  左：PA6 PB0右:PA7 PB1
//硬件占用  TIM3_PWM_CH1-4

#include "sys.h"
#include "pwm.h"

void motor_init(void);
void motor_left(int pwmval);			//设置左电机占空比 -999 - 999 0为全低 999为全高 -999为全倒转
void motor_right(int pwmval);		//设置右电机占空比


#endif

