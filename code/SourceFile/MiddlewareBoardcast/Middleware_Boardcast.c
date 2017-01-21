#include "Middleware_Boardcast.h"


#ifdef	USING_MODULE_NETWORK


// 接收网络数据任务
//
void MiddlewareBoardcast_FastTask(void)
{
	static	uint8_t		MiddlewareBoardcast_Command[80];
	
	uint16_t 	MiddlewareBoardcast_CommandLen = 0;
	
	// 读取数据
	//
	MiddlewareBoardcast_CommandLen = App_Hal_Api.network->readBoardcast(MiddlewareBoardcast_Command);

	// 数据不为空，信道可用或者不需要信道，校验合法；满足前面三种条件立即执行
	//
	if (MiddlewareBoardcast_CommandLen &&
		(MiddlewareBoardcast_Command[Enum_CommandNo] == 0x61 || MiddlewareBoardcast_Command[Enum_CommandNo] == 0x63))
	{
		if (PC_CheckCommand(MiddlewareBoardcast_Command, MiddlewareBoardcast_CommandLen))
		{
			App_Hal_Api.led->setTime(YELLOW_LED, 2);											// 亮黄灯
			
			Network_DealControlData(MiddlewareBoardcast_Command);								// 处理服务器数据
		}
	}
	
}



#endif








