#include "Middleware_DeviceDataRecollect.h"


uint16_t	DeviceDataRecollect_DeviceNo;


uint8_t		DeviceDataRecollect_Type;


bit __DeviceDataRecollect(uint8_t *router, uint8_t mode)
{
	uint8_t		*tmpData = MiddlewareData_Malloc(MiddlewareData_SendDataNormal);
	
	uint16_t	tmpParityValue;
	
	if (!tmpData)
	{
		return 0;
	}
	// 设备编号，命令编号， 命令流水号，中继
	//
	tmpData[0] = DeviceDataRecollect_DeviceNo;
	tmpData[1] = DeviceDataRecollect_DeviceNo >> 8;
	tmpData[2] = 27;
	tmpData[4] = router[0];
	tmpData[5] = router[0];
	tmpData[6] = router[1];
	tmpData[7] = router[2];
	tmpData[8] = 0xD1;
	
	// 设备编号
	//
	tmpData[9] = DeviceDataRecollect_DeviceNo;
	tmpData[10] = DeviceDataRecollect_DeviceNo >> 8;
	
	// 设备类型
	//
	tmpData[11] = DeviceDataRecollect_Type;
	
	// 无线信道
	//
//	tmpData[12] = WirelessChannel;
	
	// 设备序列号
	//
	memset(tmpData + 13, 0xFF, 8);
	
	// 内部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(tmpData + 8, 13);
    tmpData[21] = tmpParityValue;
    tmpData[22] = tmpParityValue >> 8;
	
	// 填充字节
	//
//	memset(tmpData + 23, 0xD1, 7);
    
    // 外部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(tmpData, 30);
    tmpData[Enum_Wirelss_ParityL] = tmpParityValue;
    tmpData[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
	
	return 1;
}


bool DeviceDataRecollect_DealFrameText(uint8_t **Data)
{
	uint8_t	router[3];
	
	uint8_t	mode;
	
	// 获取设备编号
	//
	if (!Json_ReceiveFrameUintValue(Data, "dn\":\"", 5, &DeviceDataRecollect_DeviceNo))
	{
		return 0;
	}
	
	// 获取设备类型
	//
	if (!Json_ReceiveFrameCharValue(Data, "dt\":\"", 5, &DeviceDataRecollect_Type))
	{
		return 0;
	}
	
	// 从设备列表中查找路由信息
	//
//	if (!DeviceInfo_GetRouter(DeviceDataRecollect_DeviceNo, DeviceDataRecollect_Type, router))
//	{
//		return 0;
//	}
	
	// 获取指令长度
	//
	if (!Json_ReceiveFrameFirstbyteValue(Data, "mode\":\"", 7, &mode))
	{
		return 0;
	}
	
	__DeviceDataRecollect(router, mode);
	
	return 1;
}


void DeviceDataRecollect_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data)
{
	uint16_t  tmpDataLen = 0;
	
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
	memcpy(Data + tmpDataLen, "{\"cn\":\"012\",\"csn\":\"", 19);
	tmpDataLen += 19;
	
	Data[tmpDataLen++] = cmdSerialNo / 10000 + '0';
	Data[tmpDataLen++] = cmdSerialNo / 1000 % 10 + '0';
	Data[tmpDataLen++] = cmdSerialNo / 100 % 10 + '0';
	Data[tmpDataLen++] = cmdSerialNo / 10 % 10 + '0';
	Data[tmpDataLen++] = cmdSerialNo % 10 + '0';
	
	// 添加了设备编号
	//
	memcpy(Data + tmpDataLen, "\",\"dn\":\"", 8);
	tmpDataLen += 8;
	
	Data[tmpDataLen++] = DeviceDataRecollect_DeviceNo / 10000 + '0';
	Data[tmpDataLen++] = DeviceDataRecollect_DeviceNo / 1000 % 10 + '0';
	Data[tmpDataLen++] = DeviceDataRecollect_DeviceNo / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceDataRecollect_DeviceNo / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceDataRecollect_DeviceNo % 10 + '0';
	
	// 添加了设备类型
	//
	memcpy(Data + tmpDataLen, "\",\"dt\":\"", 8);
	tmpDataLen += 8;
	Data[tmpDataLen++] = DeviceDataRecollect_Type / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceDataRecollect_Type / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceDataRecollect_Type % 10 + '0';
	
	// 添加数据
	//
	memcpy(Data + tmpDataLen, "\",\"data\":[", 10); tmpDataLen += 10;
	
	while (!MiddlewareData_IsEmpty(MiddlewareData_ReceiveDataNormal))
	{
		uint8_t xdata *tmpData = MiddlewareData_Fetch(MiddlewareData_ReceiveDataNormal);
		
		uint8_t xdata tmpIndex;
		
		for (tmpIndex = 0; tmpIndex < 22; tmpIndex++)
		{
			
		}
		
		MiddlewareData_Free(MiddlewareData_ReceiveDataNormal);
	}
	
	// 负载长度字段
	//
	Data[2] = (tmpDataLen - 8) >> 8;
	
	Data[3] = (tmpDataLen - 8) ;
	
//	Ch395_Write(peerSockfd, Data, tmpDataLen);
}




























