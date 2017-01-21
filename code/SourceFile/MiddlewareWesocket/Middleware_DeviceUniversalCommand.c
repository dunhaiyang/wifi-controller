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
	// �豸��ţ������ţ� ������ˮ�ţ��м�
	//
	tmpData[0] = DeviceUniversalCommand_DeviceNo;
	tmpData[1] = DeviceUniversalCommand_DeviceNo >> 8;
	tmpData[2] = 19;
	tmpData[4] = router[0];
	tmpData[5] = router[0];
	tmpData[6] = router[1];
	tmpData[7] = router[2];
	tmpData[8] = 0xE5;
	
	// �豸���к�
	//
	memset(tmpData + 9, 0xFF, 8);
	
	// �豸���
	//
	tmpData[17] = DeviceUniversalCommand_DeviceNo;
	tmpData[18] = DeviceUniversalCommand_DeviceNo >> 8;
	
	// �豸����
	//
	tmpData[19] = DeviceUniversalCommand_DeviceType;
	
	// ����ֵ
	//
	for (index = 0; index < len; index++)
	{
//		tmpData[20 + index] = (QuickTransferTable[tmpContent[index * 2 + 0]] << 4) + 
//								QuickTransferTable[tmpContent[index * 2 + 1]];
	}
	// �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(tmpData + 8, 20);
    tmpData[28] = tmpParityValue;
    tmpData[29] = tmpParityValue >> 8;
    
    // �ⲿ��У��
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
	
	// ��ȡ�豸���
	//
	if (!Json_ReceiveFrameUintValue(Data, "dn\":\"", 5, &DeviceUniversalCommand_DeviceNo))
	{
		return 0;
	}
	
	// ��ȡ�豸����
	//
	if (!Json_ReceiveFrameCharValue(Data, "dt\":\"", 5, &DeviceUniversalCommand_DeviceType))
	{
		return 0;
	}
	
	// ���豸�б��в���·����Ϣ
	//
//	if (!DeviceInfo_GetRouter(DeviceUniversalCommand_DeviceNo, DeviceUniversalCommand_DeviceType, router))
//	{
//		return 0;
//	}
	
	// ��ȡָ���
	//
	if (!Json_ReceiveFrameCharValue(Data, "len\":\"", 6, &len))
	{
		return 0;
	}
	
	// ��ȡָ������
	//
	if (!Json_ReceiveFrameStringValue(Data, "cc\":[", 5, &tmpContent))
	{
		return 0;
	}
	
	// ��װͨ�ÿ���ָ��
	//
	while (*tmpContent == '"')
	{
		// ��������
		//
		tmpContent++;
		
		// ��ȡ����
		//
		if (!__DeviceUniversalCommand(router, len, tmpContent))
		{
			MiddlewareData_Empty_SendDataNormal();
			
			return 0;
		}
		// �����Ѿ���ȡ��������
		//
		tmpContent = tmpContent + 2 * len;
		
		// ���������ַ�
		//
		tmpContent += 2;
	}
	
	return 1;
}



void DeviceUniversalCommand_SendFrameTextToPc(uint16_t cmdSerialNo, uint8_t *Data)
{
	uint16_t	tmpDataLen = 0;
	
	// websocketǰ׺
	//
	Data[tmpDataLen++] = 0x81;
	
	Data[tmpDataLen++] = 0xFE;
	
	// ���س����ֶ�
	//
	Data[tmpDataLen++] = 0x00;
	
	Data[tmpDataLen++] = 0x00;
	
	// �������
	//
	Data[tmpDataLen++] = 0x00;
	
	Data[tmpDataLen++] = 0x00;
	
	Data[tmpDataLen++] = 0x00;
	
	Data[tmpDataLen++] = 0x00;
	
	// ������������: ָ��ź����к�
	//
	memcpy(Data + tmpDataLen, "{\"cn\":\"010\",\"csn\":\"", 19);
	tmpDataLen += 19;
	
	Data[tmpDataLen++] = cmdSerialNo / 10000 + '0';
	Data[tmpDataLen++] = cmdSerialNo / 1000 % 10 + '0';
	Data[tmpDataLen++] = cmdSerialNo / 100 % 10 + '0';
	Data[tmpDataLen++] = cmdSerialNo / 10 % 10 + '0';
	Data[tmpDataLen++] = cmdSerialNo % 10 + '0';
	
	// ������豸���
	//
	memcpy(Data + tmpDataLen, "\",\"dn\":\"", 8);
	tmpDataLen += 8;
	
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo / 10000 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo / 1000 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceNo % 10 + '0';
	
	// ������豸����
	//
	memcpy(Data + tmpDataLen, "\",\"dt\":\"", 8);
	tmpDataLen += 8;
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceType / 100 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceType / 10 % 10 + '0';
	Data[tmpDataLen++] = DeviceUniversalCommand_DeviceType % 10 + '0';
	
	// Ӧ����
	//
	memcpy(Data + tmpDataLen, "\",\"rcheck\":true}", 16);
	
	tmpDataLen += 16;
	
	// ������н��
	//
	MiddlewareData_Empty_ReceiveDataUrgency();
	
	// ���س����ֶ�
	//
	Data[2] = (tmpDataLen - 8) >> 8;
	
	Data[3] = (tmpDataLen - 8) ;
	
//	Ch395_Write(peerSockfd, Data, tmpDataLen);
	
//	printf("universal pc end\r\n");
}


