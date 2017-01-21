#include "Middleware_DeviceWhiteList.h"


uint16_t	DeviceWhiteList_DeviceNo;

uint8_t		DeviceWhiteList_DeviceType;


bool __Operate_WhiteList(uint8_t *router, uint8_t mode, uint8_t len, uint8_t *whiteListData)
{
	uint8_t		*tmpData = MiddlewareData_Malloc(MiddlewareData_SendDataNormal);
	
	uint8_t		index;
	
	uint16_t 	tmpParityValue;
	
	if (!tmpData)
	{
		return 0;
	}
	// 设备编号，命令编号， 命令流水号，中继
	//
	tmpData[0] = DeviceWhiteList_DeviceNo;
	tmpData[1] = DeviceWhiteList_DeviceNo >> 8;
	tmpData[2] = 17;
	tmpData[4] = router[0];
	tmpData[5] = router[0];
	tmpData[6] = router[1];
	tmpData[7] = router[2];
	tmpData[8] = 0xE3;
	if (mode == 'A')
	{
		tmpData[9] = 0x31;
	}
	else if (mode == 'U')
	{
		tmpData[9] = 0x32;
	}
	else if (mode == 'D')
	{
		tmpData[9] = 0x33;
	}
	tmpData[10] = len;
	
	for (index = 0; index < len; index++)
	{
//		tmpData[11 + index] = (QuickTransferTable[whiteListData[index * 2 + 0]] << 4) + 
//								QuickTransferTable[whiteListData[index * 2 + 1]];
	}
	// 计算内校验
	//
	tmpParityValue = Temporary_CalcSumParity(tmpData + 8, 19);
    tmpData[27] = tmpParityValue;
    tmpData[28] = tmpParityValue >> 8;
	
	
	// 计算外校验
	//
	tmpParityValue = Temporary_CalcSumParity(tmpData, 30);
    tmpData[Enum_Wirelss_ParityL] = tmpParityValue;
    tmpData[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
	
	return 1;
}


bool __Init_WhiteList(uint8_t *router)
{
	uint8_t		*tmpData = MiddlewareData_Malloc(MiddlewareData_SendDataNormal);
	
	uint16_t  	tmpParityValue;
	
	if (!tmpData)
	{
		return 0;
	}
	// 设备编号，命令编号， 命令流水号，中继
	//
	tmpData[0] = DeviceWhiteList_DeviceNo;
	tmpData[1] = DeviceWhiteList_DeviceNo >> 8;
	tmpData[2] = 15;
	tmpData[4] = router[0];
	tmpData[5] = router[0];
	tmpData[6] = router[1];
	tmpData[7] = router[2];
	tmpData[8] = 0xE1;
	tmpData[9] = DeviceWhiteList_DeviceNo;
	tmpData[10] = DeviceWhiteList_DeviceNo >> 8;
	tmpData[11] = DeviceWhiteList_DeviceType;
//	tmpData[12] = WirelessChannel;
	memset(tmpData + 13, 0xFF, 8);
	
	// 内部和校验
	//
	tmpParityValue = Temporary_CalcSumParity(tmpData + 8, 13);
    tmpData[21] = tmpParityValue;
    tmpData[22] = tmpParityValue >> 8;
	
	memset(tmpData + 23, 0xE1, 7);
	
	// 计算校验
	//
	tmpParityValue = Temporary_CalcSumParity(tmpData, 30);
    tmpData[Enum_Wirelss_ParityL] = tmpParityValue;
    tmpData[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
	
	printf("to init white list\r\n");
	
	return 1;
}


bool DeviceWhiteList_DealFrameText(uint8_t **Data)
{
	uint8_t		router[3];
	
	uint8_t		mode;
	
	uint8_t		len;
	
	uint8_t 	*tmpWhiteList;
	
	// 获取设备编号
	//
	if (!Json_ReceiveFrameUintValue(Data, "dn\":\"", 5, &DeviceWhiteList_DeviceNo))
	{
		return 0;
	}
	
	// 获取设备类型
	//
	if (!Json_ReceiveFrameCharValue(Data, "dt\":\"", 5, &DeviceWhiteList_DeviceType))
	{
		return 0;
	}
	
	// 从设备列表中查找路由信息
	//
//	if (!DeviceInfo_GetRouter(DeviceWhiteList_DeviceNo, DeviceWhiteList_DeviceType, router))
//	{
//		return 0;
//	}
	
	// 获取操作模式
	//
	if (!Json_ReceiveFrameFirstbyteValue(Data, "mode\":\"", 7, &mode))
	{
		return 0;
	}
	
	switch (mode)
	{
		case 'A':
		case 'D':
		case 'U':
			// 获取名单长度
			//
			if (!Json_ReceiveFrameCharValue(Data, "len\":\"", 6, &len))
			{
				return 0;
			}
			
			// 获取名单数据
			//
			if (!Json_ReceiveFrameStringValue(Data, "wd\":[", 5, &tmpWhiteList))
			{
				return 0;
			}
			while (*tmpWhiteList == '"')
			{
				// 跳过引号
				//
				tmpWhiteList++;
				
				// 获取数据
				//
				if (!__Operate_WhiteList(router, mode, len, tmpWhiteList))
				{
					MiddlewareData_Empty_SendDataNormal();
					
					return 0;
				}
				// 跳过已经获取到的数据
				//
				tmpWhiteList = tmpWhiteList + 2 * len;
				
				// 跳过两个字符
				//
				tmpWhiteList += 2;
			}
			break;
		
		case 'I':
			if (!__Init_WhiteList(router))
			{
				return 0;
			}
			break;
			
		default:
			return 0;
	}
	
	return 1;
}


void DeviceWhiteList_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data)
{
	uint16_t	tmpDataLen = 0;
	
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
	memcpy(Data + tmpDataLen, "{\"cn\":\"011\",\"csn\":\"", 19);
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
	
	Data[tmpDataLen++] = DeviceWhiteList_DeviceNo / 10000 + '0';
	Data[tmpDataLen++] = DeviceWhiteList_DeviceNo / 1000 % 10 + '0';
	Data[tmpDataLen++] = DeviceWhiteList_DeviceNo / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceWhiteList_DeviceNo / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceWhiteList_DeviceNo % 10 + '0';
	
	// 添加了设备类型
	//
	memcpy(Data + tmpDataLen, "\",\"dt\":\"", 8);
	tmpDataLen += 8;
	Data[tmpDataLen++] = DeviceWhiteList_DeviceType / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceWhiteList_DeviceType / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceWhiteList_DeviceType % 10 + '0';
	
	// 应答结果
	//
	memcpy(Data + tmpDataLen, "\",\"rcheck\":true}", 16);
	
	tmpDataLen += 16;
	
	// 清楚所有结果
	//
	MiddlewareData_Empty_ReceiveDataNormal();
	
	// 负载长度字段
	//
	Data[2] = (tmpDataLen - 8) >> 8;
	
	Data[3] = (tmpDataLen - 8) ;
	
//	Ch395_Write(peerSockfd, Data, tmpDataLen);
}





