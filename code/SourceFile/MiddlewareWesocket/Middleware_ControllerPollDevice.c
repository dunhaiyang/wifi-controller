#include "Middleware_ControllerPollDevice.h"


void __SendPollDataToDevice(uint8_t index)
{
	uint16_t   tmpParityValue = 0;
    
	// ÿ�η�����ѯ���豸����ʧ�ܴ�������Ӧ�������
	//
//    DeviceInfo_Set_FailTimes(index);
    
    // �豸���
    //
//    NRF905_SendBuffer[0] = DeviceList[index].deviceNo;
//    
//    NRF905_SendBuffer[1] = DeviceList[index].deviceNo >> 8;
    
    // ������
    //
    NRF905_SendBuffer[2] = 0x01;
    
    // ������ˮ
    //
    NRF905_SendBuffer[3] = 0x00;
	
    // ʹ����·��
    //
//	NRF905_SendBuffer[4] = DeviceList[index].deviceMasterRouter[0];       // Ŀ���м�
//	
//	NRF905_SendBuffer[5] = DeviceList[index].deviceMasterRouter[0];       // �м�1
//	
//	NRF905_SendBuffer[6] = DeviceList[index].deviceMasterRouter[1];       // �м�2
//	
//	NRF905_SendBuffer[7] = DeviceList[index].deviceMasterRouter[2];       // �м�3
    
    // ����ַ�
    //
    NRF905_SendBuffer[8] = 0xF1;
    
    // �豸���
    //
    NRF905_SendBuffer[9] = NRF905_SendBuffer[0];
    
    NRF905_SendBuffer[10] = NRF905_SendBuffer[1];
    
    // �豸����
    //
//    NRF905_SendBuffer[11] = DeviceList[index].deviceType;
    
    // �����ŵ�
    //
//    NRF905_SendBuffer[12] = WirelessChannel;
    
    // ��\��\ʱ\��\����\��\��
    //
    NRF905_SendBuffer[13] = BCD(SysTime.second);
    
    NRF905_SendBuffer[14] = BCD(SysTime.minute);
    
    NRF905_SendBuffer[15] = BCD(SysTime.hour);
    
    NRF905_SendBuffer[16] = BCD(SysTime.day);
    
    NRF905_SendBuffer[17] = BCD(SysTime.week);
    
    NRF905_SendBuffer[18] = BCD(SysTime.month);
    
    NRF905_SendBuffer[19] = BCD(SysTime.year);
    
    // �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 12);
    NRF905_SendBuffer[20] = tmpParityValue;
    NRF905_SendBuffer[21] = tmpParityValue >> 8;
    
    // ����ַ�0xF1
    //
    memset(NRF905_SendBuffer + 22, 0xF1, 8);
    
    // �ⲿ��У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[30] = tmpParityValue;
    NRF905_SendBuffer[31] = tmpParityValue >> 8;
    
    // ������ѯָ��
    //
//    Wireless_SendDataToDevice(NRF905_SendBuffer);
    
	
	// �����м����������߷��͵ȴ���ʱʱ��
	//
	Pca_Start(NRF905_SendBuffer, 0);
}


// ������ѯָ��豸���豸��Ӧ�������֣�
// һ����ֱ�����ݣ���ʵʱ���ѻ����� һ���Ǽ�����ݣ����ѻ��豸�� ��Ҫ��һ����ȡ�ѻ����ݣ�
//
void ControllerPollDevice_SendPollDataToDevice(void)
{
//	static uint8_t index = 0;
//	
//	for (; index < DeviceInfo_DeviceMaxNum; index++)
//	{
//		if (!DeviceList[index].canUseFlag)
//		{
//			COM_GREEN = 0;							// ���̵�
//			
//			__SendPollDataToDevice(index);			// ������ѯ����
//			
//			DeviceInfo_CurrentIndex = index++;		// ����øո��豸��ѯ������
//			
//			printf("poll\r\n");
//	
//			COM_GREEN = 1;							// ���̵�
//			
//			return;
//		}
//	}
//	index = 0;
}


// ���ͼ������, 
//
void ControllerPollDevice_ReadDirectData(void)
{
	// ���ڶ�ȡ�ѻ����ݽ׶�
	//
//	if (OneCardDataUpload_IndirectCount--)
//	{
//		ReadOneOfflineData_DealData();
//	}
//	// ������ȡ�ѻ����ݽ׶�
//	//
//	else
//	{
//		OneCardDataUpload_PollDeviceStatus = 2;
//	}
}


// �ָ�����ѯ״̬
//
void ControllerPollDevice_RecoverPollStatus(void)
{
//	if (OneCardDataUpload_RecoverCount)
//	{
//		OneCardDataUpload_RecoverCount--;
//	}
//	else
//	{
//		OneCardDataUpload_PollDeviceStatus = 0;
//	}
}


















