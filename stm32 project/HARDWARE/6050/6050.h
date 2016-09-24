#ifndef __6050_H
#define __6050_H
//硬件连接：usart2 Rx:PA3
//硬件占用：usart2 dma1_ch6


#include "sys.h"
#include "dma.h"
#include "uart2.h"
#include "delay.h"


void mpu6050_init(void);
void mpu6050_resetzero(void);				//将当前值设置为角度零点
double mpu6050_get_angle(void);			//从上往下看从零点开始逆时针为正（无论正反） -180`180 deg  
double mpu6050_get_omega(void);    //从上往下看逆时针为正（无论正反） -2000·2000 deg/s

#endif


