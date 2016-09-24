#include "speed.h"
#include "delay.h"
#include "usart.h"

	u8 left_speed=0;
	u8 right_speed=0;
	u8 stop_speed=0;

void speed_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init(GPIOC,&GPIO_InitStructure);	
}

u8 get_left_speed(void)
{
	return left_speed;
}
u8 get_right_speed(void)
{
	return right_speed;
}
u8 get_stop_speed(void)
{
	return stop_speed;
}
void set_left_speed(u8 ls)
{
	left_speed=ls;
}
void set_right_speed(u8 rs)
{
	right_speed=rs;
}
void set_stop_speed(u8 ss)
{
	stop_speed=ss;
}

