#include "Middleware_ControllerHeartbeat.h"
//#include "Kernel_PC.h"


bool ControllerHeartbeat_DealFrameText(uint8_t **Data)
{
	uint8_t	*tmpData;
	
	if (!(Json_ReceiveFrameStringValue(Data, "dt\":\"", 5, &tmpData) &&
		tmpData[4] == '-' && 
		tmpData[7] == '-' &&
		tmpData[16] == ':' && 
		tmpData[19] == ':'))
	{
		return 0;
	}
	
//	Calibrate_Time(tmpData);
	
	return 1;
}


void ControllerHeartbeat_SendFrameTextToPc(uint8_t *Data)
{
	uint16_t	tmpDataLen = 0;
	
//	uint8_t 	tmpIndex;
	
	// websocket前缀
	//
	Data[tmpDataLen++] = 0x81;
	
	Data[tmpDataLen++] = 0xFE;
	
	// 负载长度字段
	//
	Data[tmpDataLen++] = 0x00;
	
	Data[tmpDataLen++] = 0x00;
	
	// 添加掩码
	//
	Data[tmpDataLen++] = 0x00;
	
	Data[tmpDataLen++] = 0x00;
	
	Data[tmpDataLen++] = 0x00;
	
	Data[tmpDataLen++] = 0x00;
	
	// 负载数据内容: 指令号和序列号
	//
	memcpy(Data + tmpDataLen, "{\"cn\":\"004\",\"csn\":\"", 19);
	tmpDataLen += 19;
	
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo / 10000 + '0';
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo / 1000 % 10 + '0';
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo / 100 % 10 + '0';
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo / 10 % 10 + '0';
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo % 10 + '0';
	
//	DeviceInfo_DeviceDataSerialNo++;
	
	// 负载数据内容：不在线的设备列表信息
	//
	memcpy(Data + tmpDataLen, "\",\"dld\":[", 9);
	tmpDataLen += 9;
	
	// 负载数据内容：设备类型和设备编号
	//
//	for (tmpIndex = 0; tmpIndex < DeviceInfo_DeviceMaxNum; tmpIndex++)
//	{
//		if (!(DeviceList[tmpIndex].canUseFlag || DeviceList[tmpIndex].deviceOnline))
//		{
//			memcpy(Data + tmpDataLen, "{\"dt\":\"xxx\",\"dns\":\"xxxxx\"},", 27);
//			
//			// dt
//			//
//			Data[tmpDataLen + 7] = '0';
//			Data[tmpDataLen + 8] = DeviceList[tmpIndex].deviceType / 10 % 10 + '0';
//			Data[tmpDataLen + 9] = DeviceList[tmpIndex].deviceType % 10 + '0';
//			
//			// dns
//			//
//			Data[tmpDataLen + 19] = DeviceList[tmpIndex].deviceNo / 10000 + '0';
//			Data[tmpDataLen + 20] = DeviceList[tmpIndex].deviceNo / 1000 % 10 + '0';
//			Data[tmpDataLen + 21] = DeviceList[tmpIndex].deviceNo / 100 % 10 + '0';
//			Data[tmpDataLen + 22] = DeviceList[tmpIndex].deviceNo / 10 % 10 + '0';
//			Data[tmpDataLen + 23] = DeviceList[tmpIndex].deviceNo % 10 + '0';
//			
//			tmpDataLen += 27;
//		}
//	}
	
	// 为了去掉逗号
	//
	if (Data[tmpDataLen - 1] != '[')
	{
		tmpDataLen--;
	}
	// 加上尾巴
	//
	Data[tmpDataLen++] = ']';
	Data[tmpDataLen++] = '}';
	
	// 负载长度字段
	//
	Data[2] = (tmpDataLen - 8) >> 8;
	
	Data[3] = (tmpDataLen - 8) ;
}



