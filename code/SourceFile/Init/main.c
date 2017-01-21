
// === 伪终端（控制台）指令
//
#include "Middleware_Menu.h"


// === 软实时任务
//
#include "Middleware_Task.h"


// === 广播搜索
//
#include "Middleware_Boardcast.h"


// === 无线（zigbee）
//
#include "Middleware_Wireless.h"


// === 网络（wifi或者enthernet）
//
#include "Middleware_Socket.h"


/*
	=====================  4. settup（只执行一次）  =====================
*/

void setup(void)
{
	// 系统初始化
	//
	App_Hal_Api.init();																			// 初始化IAP15操作系统
	
	App_Hal_Api.console->registerMenu(menu, sizeof(menu)/sizeof(menu[0]));						// 注册伪终端指令
	
	App_Hal_Api.scheduler->registerTask(task, sizeof(task)/sizeof(task[0]));					// 注册任务

#ifdef	USING_MODULE_NETWORK
	
	App_Hal_Api.network->registerErrorFunction(MiddlewareSocket_NetworkError);					// 注册网络出错回调函数
	
#endif
	
	// APP初始化
	//
	ControlerInfo_Init();																		// 控制器参数初始化
	
	NormalDeviceInfo_Init();																	// 普通设备列表初始化
	
	SpecialDeviceInfo_Init();																	// 特殊设备列表初始化
	
	
	// 提醒控制器初始化完毕
	//
	App_Hal_Api.led->setTime(ALL_LED, 1000);													// 亮灯1000ms
	
	App_Hal_Api.beep->setTime(50);																// 开启蜂鸣50ms
}



/*
	====================  5. loop（死循环）  =========================
*/
void fast_loop(void)
{
	App_Hal_Api.led->run();																		// 执行灯任务
	
	App_Hal_Api.beep->run();																	// 执行蜂鸣器任务
	
#ifdef	USING_MODULE_NETWORK
	
	App_Hal_Api.network->run();																	// 执行网络底层函数
	
	MiddlewareBoardcast_FastTask();																// 接收广播数据任务
	
#endif
	
	MiddlewareWireless_FastTask();																// 接收无线数据任务
	
	MiddlewareSocket_FastTask();																// 接收网络数据任务
}


void loop(void)
{
	static uint32_t loopTime = 0;
	
	fast_loop();
	
	if (HAL_DIFFERENT4_TIME(App_Hal_Api.scheduler->milliseconds(), loopTime) >= 5)
	{
		loopTime = App_Hal_Api.scheduler->milliseconds();
		
		App_Hal_Api.scheduler->ticksIncrease();
		
//		if (App_Hal_Api.scheduler->ticks % 200 == 0)
//		{
//			printf("milliseconds = %lu\r\n", App_Hal_Api.scheduler->milliseconds());
//		}
	}
	App_Hal_Api.scheduler->run();
}


/*
	====================  6. main macro  ======================
*/
APP_HAL_IAP15_MAIN()

