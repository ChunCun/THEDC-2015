#ifndef __CCD_H
#define __CCD_H
//Ӳ��ռ��: ADC1_CH15
//�ӿڣ�SI:PC7		CLK:PC6		AO:PC5
#include "sys.h"
#include "adc.h"
#include "delay.h"
#define SI PCout(7)
#define CLK PCout(6)




void ccd_init(void);

void ccd_get_data(void);		// �ع�ʱ��us  һ��ȡ2ms����
void ccd_binary_data(void);			//��ֵ��  һ��ȡ2000����
void ccd_autobinary(void);
void ccd_autointegration(void);
void ccd_set_integrationtime(u32 time);    //�����ع�ʱ��

u16 ccd_read_data(u8 num);
u8 ccd_read_binary(u8 num);


#endif

