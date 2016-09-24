#ifndef __STRATEGY_H
#define __STRATEGY_H

#include "tim2.h"
#include "sys.h"
#include "motor.h"
#include "ccd.h"
#include "god.h"
#include "6050.h"

#include "speed.h"

#include "ir.h"

void strategy_init(void);
void car_move(void);
u8 get_back_left(void);
void set_back_left(u8 t);  
void set_back_status(u8 back);

#endif

