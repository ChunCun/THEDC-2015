#include "ccd.h"


u16 ccd_data_temp=0;
u32 integration_time=3500;
u16 ccd_data[128]={0};
u8 ccd_binary[128]={0};

void ccd_init(void)
{
//GPIO Init
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;   //CLK
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;   //SI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	SI =0;
	CLK =0;
//adc init	
	Adc_Init();
}

void ccd_integration(void)
{
	SI =0;
	CLK =0;
  delay_us(1);
	SI =1;
	for(u8 n=0;n<128;n++)
	{
		delay_us(1);
		CLK =1;			
		SI =0;
		delay_us(1);	
		Get_Adc(15);
		CLK =0;
	}
	
	
	for(u32 n=0;n<(integration_time/2);n++)
	{
		delay_us(1);
		CLK =1;
		delay_us(1);
		CLK =0;
  }
}

void ccd_set_integrationtime(u32 time)
{
	integration_time=time;
}


void ccd_autointegration(void)
{
	u16 max=0;
	u16 min=4095;
	

	while((min>1300)|(max<3500))
	{
		ccd_get_data();
		max=0;
		min=4095;
		for(u8 i=3;i!=125;i++)
		{
			if(max<ccd_data[i])
			{
				max=ccd_data[i];
			}
			if(min>ccd_data[i])
			{
				min=ccd_data[i];
			}
		}
		if((max>5000)|(min<500))			//限制极限
		{
			break;
		}
		if(max<3500)
		{
			integration_time+=200;
		}
		else if(min>1300)
		{
			integration_time-=200;
		}
		
//	if(integration_time>3900)		//////////////////////
//	{
//		integration_time=4800;
//	}
//	else
//	{
//		integration_time=2800;
//	}
	}
//	binary_middle=((max/2)+(min/2));			//
	
}

void ccd_get_data(void)
{
	ccd_integration();				///////
	SI =0;
	CLK =0;
  delay_us(1);
	SI =1;
	for(u8 n=0;n<128;n++)
	{
		delay_us(1);
		CLK =1;		
		SI =0;
		delay_us(1);	
		ccd_data[n]=Get_Adc(15);
		CLK =0;
	}
	
	delay_us(1);
  CLK =1;
	delay_us(1);
	CLK =0;
}

//////////////////////////////////////////////////////////////////
void ccd_binary_data(void)
{
	for(u8 i=0;i!=30;i++)
	{
		if(ccd_data[i]>(1300))
		{
			ccd_binary[i]=1;
		}
		else
		{
			ccd_binary[i]=0;
		}
	}
		for(u8 i=30;i!=50;i++)
	{
		if(ccd_data[i]>2000)
		{
			ccd_binary[i]=1;
		}
		else
		{
			ccd_binary[i]=0;
		}
	}
		for(u8 i=50;i!=85;i++)
	{
		if(ccd_data[i]>2500)
		{
			ccd_binary[i]=1;
		}
		else
		{
			ccd_binary[i]=0;
		}
	}
		for(u8 i=85;i!=100;i++)
	{
		if(ccd_data[i]>2000)
		{
			ccd_binary[i]=1;
		}
		else
		{
			ccd_binary[i]=0;
		}
	}
		for(u8 i=100;i!=128;i++)
	{
		if(ccd_data[i]>(1300))
		{
			ccd_binary[i]=1;
		}
		else
		{
			ccd_binary[i]=0;
		}
	}

}
////////////////////////////////////////////////////////////////

u16 ccd_read_data(u8 num)
{
	return(ccd_data[num]);
}

u8 ccd_read_binary(u8 num)
{
	return(ccd_binary[num]);
}

