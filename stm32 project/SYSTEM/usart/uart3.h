#ifndef __UART3_H
#define __UART3_H
#include "sys.h" 

#define USART_REC_LEN  			200  	//定义最大接收字节数 200





void uart3_init(void);		//初始化串口硬件设备，启用中断
void Uart3_PutChar(u8 ch);	            //串口1发送1字节


#endif
