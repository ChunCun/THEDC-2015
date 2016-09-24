#ifndef __SPEED_H
#define __SPEED_H

#include "sys.h"
#define triger_left GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)
#define in_left GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)
#define triger_right GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3)
#define in_right GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9)

void speed_init(void);
u8 get_left_speed(void);
u8 get_right_speed(void);
u8 get_stop_speed(void);
void set_left_speed(u8 ls);
void set_right_speed(u8 rs);
void set_stop_speed(u8 ss);

#endif

