#include "Middleware_Task.h"



// 轮询任务
//
bool PollDeviceTask(void)
{
	if (IsStartScan() &&
		(WiresslessChannel_Status == WirelessChannel_Free))  									// 开启轮询，无线信道空闲，那么就轮询
	{
		if (DevicePool_SendDataToDevice())
		{
			App_Hal_Api.led->setTime(GREEN_LED, 2);												// 亮绿灯
			
//			printf("111\r\n");
			
			return 1;
		}
	}
	return 0;
}


// 伪终端任务
//
bool ConsoleRunTask(void)
{
	App_Hal_Api.console->run();
	
	return 1;
}


// 周期性任务
//
bool PeriodTask(void)
{
//	App_Hal_Api.hardware->feedWatchdog();
		
	if (0 == --ControlerInfo.HeartbeatInterval)
	{
		RestoreHeartbeatInterval();																// 心跳计时重置
		
		Heartbeat_SendDataToPC();																// 发送心跳包
		
//		App_Hal_Api.wireless->changeChannel(0x07);
		
		App_Hal_Api.led->setTime(YELLOW_LED, 2);												// 亮绿灯
	}
		
	return 1;
}


/*
	任务调度表 - 所有正式的任务不是在fast_loop中，都应该列在这里
	第一个成员变量是任务函数
	第二个成员变量是任务函数调用的频率，单位是（5ms）
	第三个成员变量是任务函数需要的最大延迟执行时间，单位是（1ms）
*/
Task	task[3] = {
	
	// 轮询任务 (5ms一次，最大执行延迟不要超过5ms)
	//
	{PollDeviceTask,		6,		40},
	
	// 伪终端任务 (30ms一次，最大执行延迟不要超过50ms)
	//
	{ConsoleRunTask,		6,		40},
	
	// 周期性任务（1000ms一次，最大执行延迟不要超过1200ms）
	//
	{PeriodTask,			200,	1200},
};












