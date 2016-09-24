#ifndef __6050_H
#define __6050_H
//Ӳ�����ӣ�usart2 Rx:PA3
//Ӳ��ռ�ã�usart2 dma1_ch6


#include "sys.h"
#include "dma.h"
#include "uart2.h"
#include "delay.h"


void mpu6050_init(void);
void mpu6050_resetzero(void);				//����ǰֵ����Ϊ�Ƕ����
double mpu6050_get_angle(void);			//�������¿�����㿪ʼ��ʱ��Ϊ�������������� -180`180 deg  
double mpu6050_get_omega(void);    //�������¿���ʱ��Ϊ�������������� -2000��2000 deg/s

#endif


