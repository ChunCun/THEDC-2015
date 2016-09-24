#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "ccd.h"
#include "motor.h"
#include "god.h"
#include "ir.h"
#include "strategy.h"
#include "tim4.h"
#include "speed.h"


int main(void)
{
	NVIC_Configuration();
	delay_init();
	uart_init(115200);
	strategy_init();
	TIM4_Int_Init();
	u8 key_up=1;	 
	while(1)
	{
		if(key_up&&(triger_left==1|triger_right==1))
		{
            
		delay_us(300);
		key_up=0;
		if(triger_left==1)
    {
			set_stop_speed(1);
			TIM4->CNT=0;
			if(in_left==1)
			{
				set_left_speed(1);
			}
			else
			{
				set_left_speed(0);
			}
		}
		if(triger_right==1)
		{
			set_stop_speed(1);
			TIM4->CNT=0;
			if(in_right==1)
			{
				set_right_speed(0);
			}
			else
			{
				set_right_speed(1);
			}
		}
	}else if((triger_left==0&triger_right==0))key_up=1; 
		
			if(ir_middle==1)
			{
				delay_us(500);
				if(ir_middle==1)
				{
					if((ir_left==1)&(ir_right==1))
					{
						set_back_left(10);
					}
					else if((ir_left==1)&(ir_right==0))
					{
						set_back_status(1);
						set_back_left(1);
					}
					else if((ir_right==1)&(ir_left==0))
					{
						set_back_status(0);
						set_back_left(1);
					}
				}
			}
			
	}
	

}


