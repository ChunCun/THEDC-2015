#include "god.h"


u8 GodRecBuff[23]={0};


void GOD_reset(void)
{
	do
	{
		MYDMA_Config(DMA1_Channel3,(u32)&USART3->DR,(u32)GodRecBuff,23);
		USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE);	
		MYDMA_Enable(DMA1_Channel3);	
		while(1)
		{
			if(DMA_GetFlagStatus(DMA1_FLAG_TC3)!=RESET)	
			{
				DMA_ClearFlag(DMA1_FLAG_TC3);
				break; 
			}
		}
		delay_ms(120);
	}while((GodRecBuff[21]!=0x0D)|(GodRecBuff[22]!=0x0A));
}

void GOD_init(void)
{
	delay_init();
	uart3_init();
	GOD_reset();
}

void GOD_Get_GameData(GameData *data)
{
	data->Userid = (GodRecBuff[0]>>6);
	data->Status = ((GodRecBuff[0]&0x30)>>4);
	data->Warning=(GodRecBuff[0]&0x0F);

	data->Trap=((GodRecBuff[1]&0xC0)>>6);
	data->PropNum=((GodRecBuff[1]&0x38)>>3);
	data->Effect=((GodRecBuff[1]&0x07));

	data->Prop1id=((GodRecBuff[2])>>4);
	data->Prop2id=((GodRecBuff[2])&0x0F);

	data->User1.x_pos=GodRecBuff[3];
	data->User1.y_pos=GodRecBuff[4];

	data->User2.x_pos=GodRecBuff[5];
	data->User2.y_pos=GodRecBuff[6];

	data->User3.x_pos=GodRecBuff[7];
	data->User3.y_pos=GodRecBuff[8];

	data->User4.x_pos=GodRecBuff[9];
	data->User4.y_pos=GodRecBuff[10];

	data->Prop1.x_pos=GodRecBuff[11];
	data->Prop1.y_pos=GodRecBuff[12];

	data->Prop2.x_pos=GodRecBuff[13];
	data->Prop2.y_pos=GodRecBuff[14];

	data->Prop3.x_pos=GodRecBuff[15];
	data->Prop3.y_pos=GodRecBuff[16];

	data->Prop4.x_pos=GodRecBuff[17];
	data->Prop4.y_pos=GodRecBuff[18];

	data->PropResource=(GodRecBuff[19]>>4);
	data->PropTarget=(GodRecBuff[19]&0x0F);

	data->PropType=(GodRecBuff[20]);

}

void GOD_Use_Prop(u8 target,u8 propid)
{
	u8 temp_data=0;
	temp_data=((GodRecBuff[0]>>6)<<6)+(target<<4)+propid;
	for(u8 i=0;i!=5;i++)
	{
	Uart3_PutChar(temp_data);
	Uart3_PutChar(0x0D);
	Uart3_PutChar(0x0A);
	}
}


