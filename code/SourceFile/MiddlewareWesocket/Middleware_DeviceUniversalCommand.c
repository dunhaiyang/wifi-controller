#include "Middleware_DeviceUniversalCommand.h"



uint16_t	DeviceUniversalCommand_DeviceNo;

uint8_t		DeviceUniversalCommand_DeviceType;


bool __DeviceUniversalCommand(uint8_t *router, uint8_t len, uint8_t *tmpContent)
{
	uint8_t 	*tmpData = MiddlewareData_Malloc(MiddlewareData_SendDataUrgency);
	
	uint8_t 	index;
	
	uint16_t  	tmpParityValue;
	
	if (!tmpData)
	{
		return 0;
	}
	// 设备编号，命令编号， 命令流水号，中继
	//
	tmpData[0] = DeviceUniversalCommand_DeviceNo;
	tmpData[1] = DeviceUniversalCommand_DeviceNo >> 8;
	tmpData[2] = 19;
	tmpData[4] = router[0];
	tmpData[5] = router[0];
	tmpData[6] = router[1];
	tmpData[7] = router[2];
	tmpData[8] = 0xE5;
	
	// 设备序列号
	//
	memset(tmpData + 9, 0xFF, 8);
	
	// 设备编号
	//
	tmpData[17] = DeviceUniversalCommand_DeviceNo;
	tmpData[18] = DeviceUniversalCommand_DeviceNo >> 8;
	
	// 设备类型
	//
	tmpData[19] = DeviceUniversalCommand_DeviceType;
	
	// 控制值
	//
	for (index = 0; index < len; index++)
	{
//		tmpData[20 + index] = (QuickTransferTable[tmpContent[index * 2 + 0]] << 4) + 
//								QuickTransferTable[tmpContent[index * 2 + 1]];
	}
	// 内部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(tmpData + 8, 20);
    tmpData[28] = tmpParityValue;
    tmpData[29] = tmpParityValue >> 8;
    
    // 外部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(tmpData, 30);
    tmpData[Enum_Wirelss_ParityL] = tmpParityValue;
    tmpData[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
	
	return 1;
}


bool DeviceUniversalCommand_DealFrameText(uint8_t **Data)
{
	uint8_t		router[3];
	
	uint8_t		len;
	
	uint8_t		*tmpContent;
	
	// 获取设备编号
	//
	if (!Json_ReceiveFrameUintValue(Data, "dn\":\"", 5, &DeviceUniversalCommand_DeviceNo))
	{
		return 0;
	}
	
	// 获取设备类型
	//
	if (!Json_ReceiveFrameCharValue(Data, "dt\":\"", 5, &DeviceUniversalCommand_DeviceType))
	{
		return 0;
	}
	
	// 从设备列表中查找路由信息
	//
//	if (!DeviceInfo_GetRouter(DeviceUniversalCommand_DeviceNo, DeviceUniversalCommand_DeviceType, router))
//	{
//		return 0;
//	}
	
	// 获取指令长度
	//
	if (!Json_ReceiveFrameCharValue(Data, "len\":\"", 6, &len))
	{
		return 0;
	}
	
	// 获取指令内容
	//
	if (!Json_ReceiveFrameStringValue(Data, "cc\":[", 5, &tmpContent))
	{
		return 0;
	}
	
	// 封装通用控制指令
	//
	while (*tmpContent == '"')
	{
		// 跳过引号
		//
		tmpContent++;
		
		// 获取数据
		//
		if (!__DeviceUniversalCommand(router, len, tmpContent))
		{
			MiddlewareData_Empty_SendDataNormal();
			
			return 0;
		}
		// 跳过已经获取到的数据
		//
		tmpContent = tmpContent + 2 * len;
		
		// 跳过两个字符
		//
		tmpContent += 2;
	}
	
	return 1;
}



void DeviceUniversalCommand_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data)
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
	memcpy(Data + tmpDataLen, "{\"cn\":\"010\",\"csn\":\"", 19);
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
	
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo / 10000 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo / 1000 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo % 10 + '0';
	
	// 添加了设备类型
	//
	memcpy(Data + tmpDataLen, "\",\"dt\":\"", 8);
	tmpDataLen += 8;
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceType / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceType / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceType % 10 + '0';
	
	// 应答结果
	//
	memcpy(Data + tmpDataLen, "\",\"rcheck\":true}", 16);
	
	tmpDataLen += 16;
	
	// 清楚所有结果
	//
	MiddlewareData_Empty_ReceiveDataUrgency();
	
	// 负载长度字段
	//
	Data[2] = (tmpDataLen - 8) >> 8;
	
	Data[3] = (tmpDataLen - 8) ;
	
//	Ch395_Write(peerSockfd, Data, tmpDataLen);
	
//	printf("universal pc end\r\n");
}


