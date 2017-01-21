#include "Middleware_Wireless.h"




// 接收无线数据任务
//
void MiddlewareWireless_FastTask(void)
{
	static uint8_t ReceiveWireless_Command[32];
	
	if(App_Hal_Api.wireless->avilable())                                           				// 是否有无线数据
	{
		App_Hal_Api.wireless->read(ReceiveWireless_Command);									// 接收无线数据
		
		if (Wireless_CheckCommand(ReceiveWireless_Command))                        				// 检查无线数据合法性
		{
			Pca_Stop();																			// 释放无线信道
			
			App_Hal_Api.led->setTime(BLUE_LED, 2);												// 亮绿灯
			
			Wireless_DealControlData(ReceiveWireless_Command);									// 处理无线数据
		}
	}
}




