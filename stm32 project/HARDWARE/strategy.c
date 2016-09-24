#include "strategy.h"

#include "usart.h"

#define k1 -100
#define k2 -100.0


#define pwm_left_straight 999
#define pwm_right_straight 999
#define track_distence 33
#define ti 5 
u8 back_left=0;
GameData game_data;
u8 previous_left=0;
u8 black_left=0;
u8 black_right=127;
u8 track_line= 64 - track_distence;							//距离/左
int delta_pwm=0;
int delta_i[ti]={0};
int sum_ti=0;
int pwm_left = pwm_left_straight;
int pwm_right = pwm_right_straight;
/////////////////////////////////////////////////////////////
void strategy_init(void)
{
	motor_init();
	ccd_init();
//	ccd_autointegration();			////////////////////
	GOD_init();
	mpu6050_init();
	mpu6050_resetzero();
	ir_init();
	TIM2_Int_Init(199,7199);			//50Hz
	TIM_Cmd(TIM2,ENABLE);
	speed_init();
}
//////////////////////////////////////////////////////////
void car_stop(void);
void car_ir(void);
void car_ccd_cal(void);
void car_go_straight(void);
void car_ccd_pwm(void);
void car_go(void);

void car_backoff(void);
u8 backoff_state=1;					//0:turn left 1:turn right
void set_back_status(u8 back);

u8 direction_wrong=0;
u8 turnaround_status=0;

u8 coma_status=0;
u8 anti_coma=0;
void car_coma(void);
u8 gostrait=0;

void prop_detect(void);
void prop_status(void);
void prop_nearby(void);

int abs(int absvalue);
////////////////////////////////////////////////////////
void car_move(void)			
{
	GOD_Get_GameData(&game_data);
	if(game_data.Status != Game_Start )
	{
		car_stop();
		gostrait=1;
		back_left=0;
		if(game_data.Status==(Game_Standby|Game_Ready))
		{
			mpu6050_resetzero();
			for(u8 i=0;i!=ti;i++)
			{
				delta_i[i]=0;
			}

		}
	}
	else
		{
			car_coma();
			car_ccd_cal();
//			if(turnaround_status==1)
//			{
//				
//				if((u8)mpu6050_get_angle()<120)
//				{
//					pwm_left=999;
//					pwm_right=-999;
//				}
//				else if(black_left<10)
//				{
//					pwm_left=999;
//					pwm_right=999;
//				}
//				else
//				{
//					turnaround_status=0;
//					direction_wrong=0;
//					mpu6050_resetzero();
//				}
//				
//			}
			if(back_left>0)
			{
				car_backoff();
			}
			else
			{

			
				if((ir_left==1)|(ir_right==1))
				{
					car_ir();
				}
				else
				{
	
					if(black_left==0)
					{
						car_go_straight();
					}
					else
					{
						mpu6050_resetzero();
						car_ccd_pwm();
						gostrait=0;
					}
				
			}			

				previous_left=black_left;
			
		}	
		
//		if(game_data.Warning==1)
//		{
//			if(direction_wrong<25)
//			{
//				direction_wrong++;
//			}
//		}
//		else if(game_data.Warning==0)
//		{
//			direction_wrong=0;
//		}
//		if(direction_wrong==25)
//		{
//			mpu6050_resetzero();
//			turnaround_status=1;
//		}
		
			prop_detect();
			prop_status();
			prop_nearby();
			if(anti_coma&((coma_status>=3)|(game_data.Effect!=Effect_Attack)))
			{
				anti_coma=0;
				coma_status=0;
			}
			if(anti_coma)
			{
				int pwm_temp;
				pwm_temp=pwm_left;
				pwm_left=-pwm_right;
				pwm_right=-pwm_temp;
			}
				car_go();
		}
}
//////////////////////////////////////////////////////////
void car_stop(void)
{
	motor_left(0);
	motor_right(0);
}

void car_ir(void)										//可修改转向速度
{
	 if((ir_left==1)&(ir_right==0))
		{
			pwm_left=999;
			pwm_right=0;
		}
		else if((ir_left==0)&(ir_right==1))
		{
			pwm_left=0;
			pwm_right=999;	
		}
}

void car_ccd_cal(void)							//计算黑边位置（从中心开始）
{		
	ccd_get_data();
	ccd_binary_data();
	
	black_left = 0;
	for(u8 i=63;i!=0;i--)
	{
		if(ccd_read_binary(i)==0)
		{
			if(ccd_read_binary(i)+ccd_read_binary(i-1)==0)
			{
				black_left = i;
				break;
			}
		}
	}
	
	black_right = 127;
	for(u8 i=64;i!=127;i++)
	{
		if(ccd_read_binary(i)==0)
		{
			if(ccd_read_binary(i)+ccd_read_binary(i+1)==0)
			{
				black_right = i;
				break;
			}
		}
	}
	
}

void car_go_straight(void)			//调数走直					//////////////////////////
{
	if(gostrait==1)
	{
		pwm_left=pwm_left_straight;
		pwm_right=pwm_right_straight;
	}
	else if((u8)mpu6050_get_angle()<60)
	{
		pwm_left=0;	
		pwm_right=pwm_right_straight;
	}
	else if((u8)mpu6050_get_angle()<120)
	{
		pwm_left=-999;
		pwm_right=999;
	}
	else
	{
		pwm_left=pwm_left_straight;
		pwm_right=pwm_right_straight;
	}
}

void car_ccd_pwm(void)				////////////////////////////////
{
	sum_ti=0;
	for(u8 i=0;i<(ti-1);i++)
	{
		delta_i[i]=delta_i[i+1];
		sum_ti+=delta_i[i];
	}
	delta_i[ti-1]=black_left-previous_left;
	sum_ti+=delta_i[ti-1];
	
	if(previous_left==black_left)
	{
		delta_pwm=k1*(black_left-track_line);
	}
	else
	{
		delta_pwm=k1*(black_left-track_line) + (int)(k2*((float)(sum_ti)/(float)ti));
	}	
	
	if(delta_pwm<0)
	{
		pwm_left=pwm_left_straight;
		pwm_right=pwm_right_straight+delta_pwm;
	}
	else
	{
		pwm_right=pwm_right_straight;
		pwm_left=pwm_left_straight-delta_pwm;
	}
	
}


void car_go(void)
{
	motor_left(pwm_left);
	motor_right(pwm_right);
}
//////////////////////////////////////////////////////////////////////////////
//倒车
void car_backoff(void)
{
	if(backoff_state==0)
	{
		pwm_left=-999;
		pwm_right=999;
	}
	else
	{
		pwm_left=999;
		pwm_right=-999;
	}
	back_left-=1;	
}

void set_back_status(u8 back)
{
	backoff_state=back;
}

u8 get_back_left(void)
{
	return back_left;
}

void set_back_left(u8 t)
{
	back_left=t;
}


/////////////////////////////////////////////////////////////////////////////////////
//道具处理
void car_coma(void)
{
	if(get_stop_speed()!=0)
	{
		if((((get_left_speed()==1)&(pwm_left<0))|((get_left_speed()==0)&(pwm_left>0)))&(((get_right_speed()==1)&(pwm_right<0))|((get_right_speed()==0)&(pwm_right>0))))
		{
			if(coma_status<6)
			{
			coma_status++;
			}
		}
		else
		{
			if(coma_status>0)
			{
			coma_status--;
			}
		}
	}
}

void prop_detect(void)					///防御
{
	
	u8 target=0;
	if(game_data.Userid==0)
	{
		target=(game_data.PropTarget&0x01);
	}
	else if(game_data.Userid==1)
	{
		target=((game_data.PropTarget&0x02)>>1);
	}
	
	if((game_data.PropType>0x0f)&(target==1)&(game_data.Effect!=Effect_Defend))
	{
		if((game_data.Prop1id==Prop_Reflect)|(game_data.Prop2id==Prop_Reflect))
		{
			GOD_Use_Prop(game_data.Userid,Prop_Reflect);
		}
		else if((game_data.Prop1id==Prop_Sheild)|(game_data.Prop2id==Prop_Sheild))
		{
			GOD_Use_Prop(game_data.Userid,Prop_Sheild);
		}
	}
	
	if(game_data.Effect==Effect_Attack)
	{
			if((game_data.Prop1id==Prop_Clean)|(game_data.Prop2id==Prop_Clean))
			{
				GOD_Use_Prop(game_data.Userid,Prop_Clean);
			}
			else if(coma_status>4)
			{
				anti_coma=1;
				coma_status=0;
			}
	}
	
}

void prop_status(void)											//攻击
{
	if(game_data.Prop1id>3)
	{
		if(game_data.Userid==0)
		{
			GOD_Use_Prop(1,game_data.Prop1id);
		}
		else
		{
			GOD_Use_Prop(0,game_data.Prop1id);
		}	
	}
	
	if(game_data.Prop2id>3)
	{
		if(game_data.Userid==0)
		{
			GOD_Use_Prop(1,game_data.Prop2id);
		}
		else
		{
			GOD_Use_Prop(0,game_data.Prop2id);
		}	
	}
}


void prop_nearby(void)
{
	if(game_data.Userid == 0)
	{
		if( (((game_data.User1.x_pos -game_data.Prop1.x_pos)<=10)&((game_data.User1.y_pos -game_data.Prop1.y_pos)<=10)) &(game_data.PropNum > 0) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User1.x_pos -game_data.Prop2.x_pos)<=10)&((game_data.User1.y_pos -game_data.Prop2.y_pos)<=10)) &(game_data.PropNum > 1) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User1.x_pos -game_data.Prop3.x_pos)<=10)&((game_data.User1.y_pos -game_data.Prop3.y_pos)<=10)) &(game_data.PropNum > 2) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User1.x_pos -game_data.Prop4.x_pos)<=10)&((game_data.User1.y_pos -game_data.Prop4.y_pos)<=10)) &(game_data.PropNum > 3) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}		
	}
	if(game_data.Userid == 1)
	{
		if( (((game_data.User2.x_pos -game_data.Prop1.x_pos)<=10)&((game_data.User2.y_pos -game_data.Prop1.y_pos)<=10)) &(game_data.PropNum > 0) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User2.x_pos -game_data.Prop2.x_pos)<=10)&((game_data.User2.y_pos -game_data.Prop2.y_pos)<=10)) &(game_data.PropNum > 1) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User2.x_pos -game_data.Prop3.x_pos)<=10)&((game_data.User2.y_pos -game_data.Prop3.y_pos)<=10)) &(game_data.PropNum > 2) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User2.x_pos -game_data.Prop4.x_pos)<=10)&((game_data.User2.y_pos -game_data.Prop4.y_pos)<=10)) &(game_data.PropNum > 3) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}		
	}
	if(game_data.Userid == 2)
	{
		if( (((game_data.User3.x_pos -game_data.Prop1.x_pos)<=10)&((game_data.User3.y_pos -game_data.Prop1.y_pos)<=10)) &(game_data.PropNum > 0) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User3.x_pos -game_data.Prop2.x_pos)<=10)&((game_data.User3.y_pos -game_data.Prop2.y_pos)<=10)) &(game_data.PropNum > 1) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User3.x_pos -game_data.Prop3.x_pos)<=10)&((game_data.User3.y_pos -game_data.Prop3.y_pos)<=10)) &(game_data.PropNum > 2) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User3.x_pos -game_data.Prop4.x_pos)<=10)&((game_data.User3.y_pos -game_data.Prop4.y_pos)<=10)) &(game_data.PropNum > 3) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}		
	}
	if(game_data.Userid == 3)
	{
		if( (((game_data.User4.x_pos -game_data.Prop1.x_pos)<=10)&((game_data.User4.y_pos -game_data.Prop1.y_pos)<=10)) &(game_data.PropNum > 0) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User4.x_pos -game_data.Prop2.x_pos)<=10)&((game_data.User4.y_pos -game_data.Prop2.y_pos)<=10)) &(game_data.PropNum > 1) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User4.x_pos -game_data.Prop3.x_pos)<=10)&((game_data.User4.y_pos -game_data.Prop3.y_pos)<=10)) &(game_data.PropNum > 2) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}
		if( (((game_data.User4.x_pos -game_data.Prop4.x_pos)<=10)&((game_data.User4.y_pos -game_data.Prop4.y_pos)<=10)) &(game_data.PropNum > 3) )
		{
				GOD_Use_Prop(game_data.Userid,Prop_Pick);
		}		
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////

int abs(int absvalue)
{
	if(absvalue>=0)
	{
		return absvalue;
	}
	else
	{
		return -absvalue;
	}
}
///////////////////////////////////////////////////////////////////////////////






