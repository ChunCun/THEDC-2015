#ifndef __MOTOR_H
#define __MOTOR_H

//Ӳ������  ��PA6 PB0��:PA7 PB1
//Ӳ��ռ��  TIM3_PWM_CH1-4

#include "sys.h"
#include "pwm.h"

void motor_init(void);
void motor_left(int pwmval);			//��������ռ�ձ� -999 - 999 0Ϊȫ�� 999Ϊȫ�� -999Ϊȫ��ת
void motor_right(int pwmval);		//�����ҵ��ռ�ձ�


#endif

