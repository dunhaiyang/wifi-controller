#include "APP_HAL_API.h"


// 定义模块对象，注册初始化函数
//
STATIC_DRIVER_INIT(Hardware, hardware);											// 硬件模块定义


STATIC_DRIVER_INIT(Led, led);													// 灯模块定义


STATIC_DRIVER_INIT(Beep, beep);													// 蜂鸣器模块定义


STATIC_DRIVER_INIT(Console, console);											// 伪终端模块定义


STATIC_DRIVER_INIT(Parameter, parameter);										// 参数模块定义


STATIC_DRIVER_INIT(Wireless, wireless);											// 无线模块定义


#ifdef	USING_MODULE_WIFI
STATIC_DRIVER_INIT(Wifi, wifi);													// WIFI模块定义
#endif


#ifdef	USING_MODULE_NETWORK
STATIC_DRIVER_INIT(Network, network);											// 网络模块定义
#endif


STATIC_DRIVER_INIT(Scheduler, scheduler);										// 调度器模块定义


// 初始化模块并且注册该模块所有其他成员函数
//
void App_Hal_Init(void)
{
	// ============================  硬件模块  ===============================
	//
	App_Hal_Api.hardware->init(App_Hal_Api.hardware);						
	
	
	// ============================  灯模块  =================================
	//
	App_Hal_Api.led->init(App_Hal_Api.led);									
	
	
	// ===========================  蜂鸣器模块  ==============================
	//
	App_Hal_Api.beep->init(App_Hal_Api.beep);
	
	
	// ===========================  伪终端模块  ==============================
	//
	App_Hal_Api.console->init(App_Hal_Api.console);
	
	
	// ===========================  参数模块  ==============================
	//
	App_Hal_Api.parameter->init(App_Hal_Api.parameter);
	
	
	// ============================  无线模块  ===============================
	//
	App_Hal_Api.wireless->init(App_Hal_Api.wireless);
	
	
	// ============================  WIFI模块  ================================
	//
#ifdef	USING_MODULE_WIFI

	App_Hal_Api.wifi->init(App_Hal_Api.wifi);

#endif
	
	
	// ============================  网络模块  ================================
	//
#ifdef	USING_MODULE_NETWORK

	App_Hal_Api.network->init(App_Hal_Api.network);
	
#endif

	
	// ===========================  调度器模块  ===============================
	//
	App_Hal_Api.scheduler->init(App_Hal_Api.scheduler);
}


// IPA15对象（初始化）
//
APP_HAL_API		App_Hal_Api = {		App_Hal_Init, 
	
									&hardware, 
	
									&led, 
	
									&beep, 
	
									&console, 
		
									&parameter, 
	
									&wireless, 

#ifdef	USING_MODULE_WIFI
									&wifi, 
#endif
	
#ifdef	USING_MODULE_NETWORK
									&network, 
#endif
	
									&scheduler
};






