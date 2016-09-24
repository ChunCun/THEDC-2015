#include "motor.h"





void motor_init(void)
{
	TIM3_PWM_Init(999,71);			//1000Hz
	motor_left(0);
	motor_right(0);
}

void motor_left(int pwmval)
{
	if(pwmval>=0)
	{
		if(pwmval>999)
		{
			TIM_SetCompare1(TIM3,999);
			TIM_SetCompare3(TIM3,0);
		}
		else
		{
			TIM_SetCompare1(TIM3,pwmval);
			TIM_SetCompare3(TIM3,0);
		}
	}
	else
	{
		if(pwmval<-999)
		{
			TIM_SetCompare1(TIM3,0);
			TIM_SetCompare3(TIM3,999);
		}
		else
		{
			TIM_SetCompare1(TIM3,0);
			TIM_SetCompare3(TIM3,-pwmval);
		}
	}
}

void motor_right(int pwmval)
{
	if(pwmval>=0)
	{
		if(pwmval>999)
		{
			TIM_SetCompare2(TIM3,999);
			TIM_SetCompare4(TIM3,0);			
		}
		else
		{
			TIM_SetCompare2(TIM3,pwmval);
			TIM_SetCompare4(TIM3,0);
		}
	}
	else
	{
		if(pwmval<-999)
		{
			TIM_SetCompare2(TIM3,0);
			TIM_SetCompare4(TIM3,999);	
		}
		else
		{
			TIM_SetCompare2(TIM3,0);
			TIM_SetCompare4(TIM3,-pwmval);
		}
	}
}




