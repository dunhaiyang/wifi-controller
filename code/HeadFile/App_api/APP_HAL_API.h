#ifndef __APP_HAL_API_H_
#define __APP_HAL_API_H_


#include "APP_HAL.h"


// IAP15控制器：芯片功能和外设功能的抽象层
//
typedef struct
{
	// 公有接口
	//
	ProcVoid_Void		init;					// 初始化函数（程序一开始就要调用，用于初始化操作系统底层）
	
	// 公有成员变量
	//
	Hardware			*hardware;				// 硬件模块
	
	Led					*led;					// 灯模块
	
	Beep				*beep;					// 蜂鸣器模块
	
	Console				*console;				// 伪终端模块
	
	Parameter			*parameter;				// 参数模块
	
	Wireless			*wireless;				// 无线模块(NF905)

#ifdef	USING_MODULE_WIFI
	Wifi				*wifi;					// WIFI模块(TI公司)
#endif

#ifdef	USING_MODULE_NETWORK
	Network				*network;				// 网络模块(自产CH395)
#endif
	
	Scheduler			*scheduler; 			// 调度器模块
	
}APP_HAL_API;


extern	APP_HAL_API		App_Hal_Api;


#endif


