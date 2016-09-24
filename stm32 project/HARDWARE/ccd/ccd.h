#ifndef __CCD_H
#define __CCD_H
//硬件占用: ADC1_CH15
//接口：SI:PC7		CLK:PC6		AO:PC5
#include "sys.h"
#include "adc.h"
#include "delay.h"
#define SI PCout(7)
#define CLK PCout(6)




void ccd_init(void);

void ccd_get_data(void);		// 曝光时间us  一般取2ms左右
void ccd_binary_data(void);			//二值化  一般取2000左右
void ccd_autobinary(void);
void ccd_autointegration(void);
void ccd_set_integrationtime(u32 time);    //设置曝光时间

u16 ccd_read_data(u8 num);
u8 ccd_read_binary(u8 num);


#endif

