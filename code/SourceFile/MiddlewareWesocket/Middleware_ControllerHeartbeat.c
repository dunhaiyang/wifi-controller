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
	memcpy(Data + tmpDataLen, "{\"cn\":\"004\",\"csn\":\"", 19);
	tmpDataLen += 19;
	
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo / 10000 + '0';
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo / 1000 % 10 + '0';
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo / 100 % 10 + '0';
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo / 10 % 10 + '0';
//	Data[tmpDataLen++] = DeviceInfo_DeviceDataSerialNo % 10 + '0';
	
//	DeviceInfo_DeviceDataSerialNo++;
	
	// �����������ݣ������ߵ��豸�б���Ϣ
	//
	memcpy(Data + tmpDataLen, "\",\"dld\":[", 9);
	tmpDataLen += 9;
	
	// �����������ݣ��豸���ͺ��豸���
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
	
	// Ϊ��ȥ������
	//
	if (Data[tmpDataLen - 1] != '[')
	{
		tmpDataLen--;
	}
	// ����β��
	//
	Data[tmpDataLen++] = ']';
	Data[tmpDataLen++] = '}';
	
	// ���س����ֶ�
	//
	Data[2] = (tmpDataLen - 8) >> 8;
	
	Data[3] = (tmpDataLen - 8) ;
}



