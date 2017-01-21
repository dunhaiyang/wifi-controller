#ifndef __LED_H_
#define __LED_H_


#include "OS_HAL.h"


enum
{
	GREEN_LED = 0x01,
	
	BLUE_LED = 0x02,
	
	YELLOW_LED = 0x04,
	
	ALL_LED = GREEN_LED | BLUE_LED | YELLOW_LED,
	
	LED_ON = 0,
	
	LED_OFF = 1,
	
	LED_SWITCH = 2,
};


typedef struct
{
	uint32_t					baseTime;						// 蜂鸣器的开始时间

	uint32_t					ledTime;						// 蜂鸣器响多久，单位由定时器0决定
	
}LedStatus;


#define 	LED_MAX				3


typedef struct
{
	// 私有接口
	//
	ProcVoidP_Void				init;
	
	// 公共接口
	//
	ProcVoid_Void				run;							// LED任务(需要周期性地调用)
	
	ProcUint8Uint16_Void		setTime;						// 设置哪一个灯亮多久
	
	ProcUint8Uint8_Void			action;							// 控制灯的行为
	
	// 私有接口
	//
	LedStatus					ledStatus[LED_MAX];				// 灯状态
	
}Led;


void Led_Init(void *self);



#endif

