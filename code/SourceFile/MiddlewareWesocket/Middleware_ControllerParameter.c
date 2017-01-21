#include "Middleware_ControllerParameter.h"


bool ControllerParameter_DealFrameText(uint8_t **Data)
{
	uint8_t tmpWirelessChannel;
	
	uint8_t tmpHeartbeatInterval;
	
	if (!Json_ReceiveFrameCharValue(Data, "nwc\":\"", 6, &tmpWirelessChannel))
	{
		return 0;
	}
	
	if (!Json_ReceiveFrameCharValue(Data, "nhi\":\"", 6, &tmpHeartbeatInterval))
	{
		return 0;
	}
	
	// 修改无线信道
	//
	PWR_UP = 0; PWR_UP = 0;
	
//	WirelessChannel = tmpWirelessChannel;
	
//	NRF905_SetWireLess(); os_send_signal(THREAD_BEEP);
	
	// 修改心跳间隔
	//
//	ControlerInfo_Set_HeartbeatIntervalReload(tmpHeartbeatInterval);
	
	//门锁数据采集星期
	//
	
	// 门锁采集开始时间
	//
	
	// 门锁采集时间间隔
	//
	
	return 1;
}




