#include "Middleware_ControllerDeviceList.h"


bool ControllerDeviceList_DealFrameText(uint8_t **Data)
{
	uint8_t xdata mode;
	
	uint16_t  xdata deviceNo;
	
	uint8_t xdata deviceType;
	
	uint8_t xdata deviceMasterRouter[3];
	
	// 获取操作模式
	//
	if (!Json_ReceiveFrameFirstbyteValue(Data, "mode\":\"", 7, &mode))
	{
		return 0;
	}
	// 如果是更新模式，那么先清空设备列表
	//
	if (mode == 'U' || mode == 'u')
	{
//		DeviceInfo_Del_All();
	}
	
	// 获取设备列表数据
	//
	while (1)
	{
		if (!Json_ReceiveFrameUintValue(Data, "dn\":\"", 5, &deviceNo))
		{
			return 1;
		}
		if (!Json_ReceiveFrameCharValue(Data, "dt\":\"", 5, &deviceType))
		{
			return 0;
		}
		if (!Json_ReceiveFrameRouterValue(Data, "mr\":\"", 5, deviceMasterRouter))
		{
			return 0;
		}
		switch (mode)
		{
			case 'U':
			case 'u':
			case 'A':
			case 'a':
//				DeviceInfo_Add(deviceNo, deviceType, deviceMasterRouter);
				break;
			
			case 'D':
			case 'd':
//				DeviceInfo_Del(deviceNo, deviceType);
				break;
			
			default:
				return 0;
		}
	}
}




