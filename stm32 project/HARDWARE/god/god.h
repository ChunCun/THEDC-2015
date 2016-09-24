#ifndef __GOD_H
#define __GOD_H
//硬件连接：usart3 Rx:PB11    TX:PB10
//硬件占用：usart3 dma1_ch3					/////////////


#include "sys.h"
#include "dma.h"
#include "uart3.h"
#include "delay.h"

typedef struct{
	u8 x_pos;
	u8 y_pos;
}location;

typedef struct{

	u8 Userid;    //2bits
	u8 Status;		 //2bits
	u8 Warning;  //4bits
	u8 Trap;  //2bits
	u8 PropNum; //3bits
	u8 Effect; //3bits
	u8 Prop1id; //4bits
	u8 Prop2id; //4bits
	location User1;			//16bits
	location User2;			//16bits
	location User3;			//16bits
	location User4;			//16bits
	location Prop1;			//16bits
	location Prop2;			//16bits
	location Prop3;			//16bits
	location Prop4;			//16bits
	u8 PropResource;	//4bits
	u8 PropTarget;	//4bits
	u8 PropType;		//8bits

}GameData;

//Game Status
#define Game_Ready 0
#define Game_Start 1
#define Game_Standby 2
#define Game_Stop 3

//warning
#define Game_Warning 1
#define Game_Normal 0

//Trap
#define Trap_NULL 0
#define Trap_Swamp 1
#define Trap_Vortex 2

//Number of items
#define Num_Item_NULL 0
#define Num_Item_a 1
#define Num_Item_ab 2
#define Num_Item_abc 3
#define Num_Item_abcd 4

//type of effect
#define Effect_NULL 0
#define Effect_Defend 1
#define Effect_Attack 2
#define Effect_Trap 3

//propid
#define Prop_NULL 0
#define Prop_Sheild 1
#define Prop_Reflect 2
#define Prop_Clean 3
//
#define Prop_Bomb 5
#define Prop_Coma 6
#define Prop_Bowling 7
#define Prop_Megenet 8
#define Prop_Swamp 9
#define Prop_Mine 0x0A
#define Prop_Vortex 0x0B
//
//
#define Prop_Pick 0x0E

//


void GOD_init(void);

void GOD_Get_GameData(GameData *data);
void GOD_Use_Prop(u8 target,u8 propid);




#endif


