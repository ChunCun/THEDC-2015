#ifndef __UART2_H
#define __UART2_H
#include "sys.h" 

#define USART_REC_LEN  			200  	//�����������ֽ��� 200


void uart2_init(void);		//��ʼ������Ӳ���豸�������ж�
void Uart2_PutChar(u8 ch);	            //����1����1�ֽ�


#endif

