#include "Middleware_Socket.h"





void MiddlewareSocket_NetworkError(void)
{
	SetStartScan(0);																			// 暂停轮询
	
	SetHeartbeatInterval(1);																	// 设置心跳间隔为1
}



// 接收网络数据任务
//
void MiddlewareSocket_FastTask(void)
{
	static	uint8_t		MiddlewareSocket_Command[80];
	
	uint16_t 	MiddlewareSocket_CommandLen = 0;
	
	// 如果没有数据，那么就从缓存中读取数据
	//
#ifdef	USING_MODULE_WIFI
	MiddlewareSocket_CommandLen = App_Hal_Api.wifi->read(MiddlewareSocket_Command);
#endif
		
#ifdef	USING_MODULE_NETWORK
	MiddlewareSocket_CommandLen = App_Hal_Api.network->readUdp(MiddlewareSocket_Command);
#endif

	// 数据不为空，信道可用或者不需要信道，校验合法；满足前面三种条件立即执行
	//
	if (MiddlewareSocket_CommandLen && 
	    (WiresslessChannel_Status == WirelessChannel_Free 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x65 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x69 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x6F 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x72 	||
		 MiddlewareSocket_Command[Enum_CommandNo] == 0x73))
	{
		if (PC_CheckCommand(MiddlewareSocket_Command, MiddlewareSocket_CommandLen))
		{
			App_Hal_Api.led->setTime(YELLOW_LED, 2);											// 亮黄灯
			
			Network_DealControlData(MiddlewareSocket_Command);									// 处理服务器数据
			
			HookFunction_ReceivePcData();														// PC不应答心跳就停止轮询设备，这里接收到PC任意数据默认有心跳，避免服务器任务繁重来不及应答心跳包
		}
	}
	
}












