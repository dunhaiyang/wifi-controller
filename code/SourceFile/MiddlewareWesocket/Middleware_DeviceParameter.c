#include "Middleware_DeviceParameter.h"


uint16_t	DeviceParameter_DeviceNo;


uint8_t		DeviceParameter_DeviceType;


uint8_t		DeviceParameter_IsWrite;


bool __Write_DealFrameText(uint8_t *router, uint8_t pn, uint8_t *dc)
{
	uint8_t 	 *tmpData = MiddlewareData_Malloc(MiddlewareData_SendDataNormal);
	
	uint16_t  	tmpParityValue;
	
	if (!tmpData)
	{
		return 0;
	}
	// 设备编号，命令编号， 命令流水号，中继
	//
	tmpData[0] = DeviceParameter_DeviceNo;
	tmpData[1] = DeviceParameter_DeviceNo >> 8;
	tmpData[2] = 25;
	tmpData[4] = router[0];
	tmpData[5] = router[0];
	tmpData[6] = router[1];
	tmpData[7] = router[2];
	tmpData[8] = 0xEB;
	tmpData[9] = DeviceParameter_DeviceNo;
	tmpData[10] = DeviceParameter_DeviceNo >> 8;
	tmpData[11] = DeviceParameter_DeviceType;
	tmpData[12] = pn;
	tmpData[13] = 0x88;				// 默认都是8字节
//	tmpData[14] = (QuickTransferTable[dc[0]] << 4) | (QuickTransferTable[dc[1]]);
//	tmpData[15] = (QuickTransferTable[dc[2]] << 4) | (QuickTransferTable[dc[3]]);
//	tmpData[16] = (QuickTransferTable[dc[4]] << 4) | (QuickTransferTable[dc[5]]);
//	tmpData[17] = (QuickTransferTable[dc[6]] << 4) | (QuickTransferTable[dc[7]]);
//	tmpData[18] = (QuickTransferTable[dc[8]] << 4) | (QuickTransferTable[dc[9]]);
//	tmpData[19] = (QuickTransferTable[dc[10]] << 4) | (QuickTransferTable[dc[11]]);
//	tmpData[20] = (QuickTransferTable[dc[12]] << 4) | (QuickTransferTable[dc[13]]);
//	tmpData[21] = (QuickTransferTable[dc[14]] << 4) | (QuickTransferTable[dc[15]]);
	
	// 计算校验
	//
	tmpParityValue = Temporary_CalcSumParity(tmpData, 30);
    tmpData[Enum_Wirelss_ParityL] = tmpParityValue;
    tmpData[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
	
	return 1;
}


bool __Read_DealFrameText(uint8_t *router, uint8_t pn)
{
	uint8_t	 	*tmpData = MiddlewareData_Malloc(MiddlewareData_SendDataNormal);
	
	uint16_t	tmpParityValue;
	
	if (!tmpData)
	{
		return 0;
	}
	// 设备编号，命令编号， 命令流水号，中继
	//
	tmpData[0] = DeviceParameter_DeviceNo;
	tmpData[1] = DeviceParameter_DeviceNo >> 8;
	tmpData[2] = 25;
	tmpData[4] = router[0];
	tmpData[5] = router[0];
	tmpData[6] = router[1];
	tmpData[7] = router[2];
	tmpData[8] = 0xEB;
	tmpData[9] = DeviceParameter_DeviceNo;
	tmpData[10] = DeviceParameter_DeviceNo >> 8;
	tmpData[11] = DeviceParameter_DeviceType;
	tmpData[12] = pn;
	tmpData[13] = 0x08;				// 默认都是8字节
	
	// 计算校验
	//
	tmpParityValue = Temporary_CalcSumParity(tmpData, 30);
    tmpData[Enum_Wirelss_ParityL] = tmpParityValue;
    tmpData[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
	
	return 1;
}



bool DeviceParameter_DealFrameText(uint8_t **Data)
{
	uint8_t		router[3];
	
	uint8_t		pn;
	
	uint8_t		*dc;
	
	// 获取设备编号
	//
	if (!Json_ReceiveFrameUintValue(Data, "dn\":\"", 5, &DeviceParameter_DeviceNo))
	{
		return 0;
	}
	
	// 获取设备类型
	//
	if (!Json_ReceiveFrameCharValue(Data, "dt\":\"", 5, &DeviceParameter_DeviceType))
	{
		return 0;
	}
	
	// 从设备列表中查找路由信息
	//
//	if (!DeviceInfo_GetRouter(DeviceParameter_DeviceNo, DeviceParameter_DeviceType, router))
//	{
//		return 0;
//	}
	
	// 获取读写模式
	//
	if (!Json_ReceiveFrameFirstbyteValue(Data, "rwf\":\"", 6, &DeviceParameter_IsWrite))
	{
		return 0;
	}
	printf("iswrite: %c\r\n", DeviceParameter_IsWrite);
	
	// 分解为无线指令数据包
	//
	while (1)
	{
		if (!Json_ReceiveFrameCharValue(Data, "pn\":\"", 5, &pn))
		{
			return 1;
		}
		
		if (DeviceParameter_IsWrite == 'W' || DeviceParameter_IsWrite == 'w')
		{
			if (!Json_ReceiveFrameStringValue(Data, "dc\":\"", 5, &dc))
			{
				return 0;
			}
			
			// 存储写参数指令
			//
			if (!__Write_DealFrameText(router, pn, dc))
			{
				return 0;
			}
		}
		else if (DeviceParameter_IsWrite == 'R' || DeviceParameter_IsWrite == 'r')
		{
			// 存储读参数指令
			//
			if (!__Read_DealFrameText(router, pn))
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
}

	
void DeviceParameter_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data)
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
	memcpy(Data + tmpDataLen, "{\"cn\":\"008\",\"csn\":\"", 19);
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
	
	Data[tmpDataLen++] = DeviceParameter_DeviceNo / 10000 + '0';
	Data[tmpDataLen++] = DeviceParameter_DeviceNo / 1000 % 10 + '0';
	Data[tmpDataLen++] = DeviceParameter_DeviceNo / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceParameter_DeviceNo / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceParameter_DeviceNo % 10 + '0';
	
	// 添加了设备类型
	//
	memcpy(Data + tmpDataLen, "\",\"dt\":\"", 8);
	tmpDataLen += 8;
	Data[tmpDataLen++] = DeviceParameter_DeviceType / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceParameter_DeviceType / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceParameter_DeviceType % 10 + '0';
	
	// 写参数的应答包
	//
	if (DeviceParameter_IsWrite == 'W' || DeviceParameter_IsWrite == 'w')
	{
		memcpy(Data + tmpDataLen, "\",\"rcheck\":true}", 16);
		
		tmpDataLen += 16;
		
		MiddlewareData_Empty_ReceiveDataNormal();
	}
	// 读参数的应答包
	else if (DeviceParameter_IsWrite == 'R' || DeviceParameter_IsWrite == 'r')
	{
		uint8_t  *tmpData;
		
		memcpy(Data + tmpDataLen, "\",\"ds\":[", 8);
		
		tmpDataLen += 8;
		
		while (tmpData = MiddlewareData_Fetch(MiddlewareData_ReceiveDataNormal))
		{
			memcpy(Data + tmpDataLen,"{\"pn\":\"", 7);
			tmpDataLen += 7;
			
			Data[tmpDataLen++] = tmpData[12] / 100 % 10 + '0';
			Data[tmpDataLen++] = tmpData[12] / 10 % 10 + '0';
			Data[tmpDataLen++] = tmpData[12] % 10 + '0';
			
			memcpy(Data + tmpDataLen,"\",\"dc\":\"", 8);
			tmpDataLen += 8;
			
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[14] >> 4];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[14] & 0x0F];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[15] >> 4];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[15] & 0x0F];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[16] >> 4];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[16] & 0x0F];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[17] >> 4];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[17] & 0x0F];
//			
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[18] >> 4];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[18] & 0x0F];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[19] >> 4];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[19] & 0x0F];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[20] >> 4];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[20] & 0x0F];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[21] >> 4];
//			Data[tmpDataLen++] = QuickTransferTable_1[tmpData[21] & 0x0F];
			
			Data[tmpDataLen++] = '"';
			Data[tmpDataLen++] = '}';
			Data[tmpDataLen++] = ',';
			
			MiddlewareData_Free(MiddlewareData_ReceiveDataNormal);
		}
		if (Data[tmpDataLen - 1] == ',')
		{
			Data[tmpDataLen - 1] = ']';
		}
		Data[tmpDataLen++] = '}';
	}
	// 可能性极低
	else
	{
		MiddlewareData_Empty_ReceiveDataNormal();
		
		return;
	}
	
	// 负载长度字段
	//
	Data[2] = (tmpDataLen - 8) >> 8;
	
	Data[3] = (tmpDataLen - 8) ;
	
//	Ch395_Write(peerSockfd, Data, tmpDataLen);
}


