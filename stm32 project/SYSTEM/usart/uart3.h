#ifndef __UART3_H
#define __UART3_H
#include "sys.h" 

#define USART_REC_LEN  			200  	//�����������ֽ��� 200





void uart3_init(void);		//��ʼ������Ӳ���豸�������ж�
void Uart3_PutChar(u8 ch);	            //����1����1�ֽ�


#endif
