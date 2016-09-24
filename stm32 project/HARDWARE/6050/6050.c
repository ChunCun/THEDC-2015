#include "6050.h"

double zero=0;

u8 RecBuff[33];


void mpu6050_reset(void)
{
	do
	{
	MYDMA_Config(DMA1_Channel6,(u32)&USART2->DR,(u32)RecBuff,33);
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);	
	MYDMA_Enable(DMA1_Channel6);	
	while(1)
  {
		if(DMA_GetFlagStatus(DMA1_FLAG_TC6)!=RESET)	
		{
			DMA_ClearFlag(DMA1_FLAG_TC6);
			break; 
	  }
	}
	delay_ms(3);
	}while((RecBuff[0]!=0x55)|(RecBuff[1]!=0x51));
}

void mpu6050_init(void)
{
	delay_init();
	uart2_init();
	mpu6050_reset();
}

double mpu6050_get_angle(void)
{
	while((RecBuff[0]!=0x55)|(RecBuff[1]!=0x51))
	{
		mpu6050_reset();
	}
	u16 YawH=RecBuff[29];
	u16 YawL=RecBuff[30];
	double Yaw=0;
	Yaw=((double)((YawH<<8)|YawL))/32768.0*180-zero;
	if(Yaw<0)
	{
		Yaw+=360;
	}
	if(Yaw>180)
	{
		Yaw-=360;
	}
	return Yaw;
}

double mpu6050_get_omega(void)
{
	while((RecBuff[0]!=0x55)|(RecBuff[1]!=0x51))
	{
		mpu6050_reset();
	}
	u16 wzL=RecBuff[17];
	u16 wzH=RecBuff[18];
	double wz=0;
	wz=((double)((wzH<<8)|wzL))/32768.0*2000;
	if(wz>2000)
	{
		wz-=4000;
	}
	return wz;
}

void mpu6050_resetzero(void)
{
	while((RecBuff[0]!=0x55)|(RecBuff[1]!=0x51))
	{
		mpu6050_reset();
	}	
	u16 YawH=RecBuff[29];
	u16 YawL=RecBuff[30];
	zero=((double)((YawH<<8)|YawL))/32768.0*180;
}
