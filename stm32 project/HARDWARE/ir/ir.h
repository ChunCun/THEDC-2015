#ifndef __IR_H
#define __IR_H


//right			//IR5		C0
//left			//IR1		C1


#include "sys.h"

#define ir_left GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)
#define ir_right GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_0)
#define ir_middle GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_4)

void ir_init(void);



#endif



