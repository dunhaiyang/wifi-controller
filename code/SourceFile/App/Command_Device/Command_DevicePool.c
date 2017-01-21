#include "Command_DevicePool.h"


uint8_t	DevicePool_DeviceType = 0;


int8_t __NextNormalDeviceList()
{
    static uint8_t index = 0;
    
    uint8_t tmpIndex = index;           // ����index��ʷֵ, ���ڷֳ�[index, 50], [0, index]��������������
    
    // ��ѯ[index, NormalDeviceListSum]�������Ч�豸�б�
    //
    for (; index < NormalDeviceListSum; index++)
    {
        if (NormalDeviceList[index].deviceValidFlag)
        {
            return index++;                 // ������Ч���豸�б����ݵ��±�
        }
    }
    
    // ���[index, NormalDeviceListSum]�Ҳ�������ô��ѯ[0, index]�������Ч�豸�б�
    //
    for (index = 0; index < tmpIndex; index++)
    {
        if (NormalDeviceList[index].deviceValidFlag)
        {
            return index++;                 // ������Ч���豸�б����ݵ��±�
        }
    }
    
    return -1;                              // �Ѿ��������豸�б�ȫ�����ݣ��Ҳ���
}


int8_t __NextSpecialDeviceList()
{
    static uint8_t index = 0;
    
    uint8_t tmpIndex = index;           // ����index��ʷֵ, ���ڷֳ�[index, 50], [0, index]��������������
    
    // ��ѯ[index, NormalDeviceListSum]�������Ч�豸�б�
    //
    for (; index < SpecialDeviceListSum; index++)
    {
        if (SpecialDeviceList[index].deviceValidFlag)
        {
            return index++;                 // ������Ч���豸�б����ݵ��±�
        }
    }
    
    // ���[index, NormalDeviceListSum]�Ҳ�������ô��ѯ[0, index]�������Ч�豸�б�
    //
    for (index = 0; index < tmpIndex; index++)
    {
        if (SpecialDeviceList[index].deviceValidFlag)
        {
            return index++;                 // ������Ч���豸�б����ݵ��±�
        }
    }
    
    return -1;                              // �Ѿ��������豸�б�ȫ�����ݣ��Ҳ���
}


void __SendDataToNormalDevice(int8_t deviceListIndex)
{
    uint16_t	tmpParityValue = 0;
    
    // �����鵽ʧ�ܴ�������һ����������ô���л�·�ɣ���·�ɺͱ���·�ɣ�
    //
    if (NormalDeviceList[deviceListIndex].deviceFailTimes > 150)
    {
        NormalDeviceList[deviceListIndex].usingDeviceRouteNow = !(NormalDeviceList[deviceListIndex].usingDeviceRouteNow);
        
        NormalDeviceList[deviceListIndex].deviceFailTimes = 0;
			
		NormalDeviceList[deviceListIndex].deviceOnline = 0;
    }
    
    // --------------  ��ʼִ����ѯָ��  -----------------
    //
    // �豸���
    //
    NRF905_SendBuffer[0] = NormalDeviceList[deviceListIndex].deviceNumber[0];
    
    NRF905_SendBuffer[1] = NormalDeviceList[deviceListIndex].deviceNumber[1];
    
    
    // ���浱ǰ��ѯ���豸����
    //
    DevicePool_DeviceType = NormalDeviceList[deviceListIndex].deviceType;
    
    
    // ������
    //
    NRF905_SendBuffer[2] = 0x01;
    
    // ������ˮ
    //
    NRF905_SendBuffer[3] = DeviceDataSerialNo++;
    
    // ʹ�ñ���·��
    //
    if (NormalDeviceList[deviceListIndex].usingDeviceRouteNow)
    {
        NRF905_SendBuffer[4] = NormalDeviceList[deviceListIndex].deviceBakRoute[0];       // Ŀ���м�
        
        
        NRF905_SendBuffer[5] = NormalDeviceList[deviceListIndex].deviceBakRoute[0];       // �м�1
        
        
        NRF905_SendBuffer[6] = NormalDeviceList[deviceListIndex].deviceBakRoute[1];       // �м�2
        
        
        NRF905_SendBuffer[7] = NormalDeviceList[deviceListIndex].deviceBakRoute[2];       // �м�3
    }
    // ʹ����·��
    //
    else
    {
        NRF905_SendBuffer[4] = NormalDeviceList[deviceListIndex].deviceMainRoute[0];       // Ŀ���м�
        
        
        NRF905_SendBuffer[5] = NormalDeviceList[deviceListIndex].deviceMainRoute[0];       // �м�1
        
        
        NRF905_SendBuffer[6] = NormalDeviceList[deviceListIndex].deviceMainRoute[1];       // �м�2
        
        
        NRF905_SendBuffer[7] = NormalDeviceList[deviceListIndex].deviceMainRoute[2];       // �м�3
    }
    
    // ����ַ�
    //
    NRF905_SendBuffer[8] = 0xF1;
    
    // �豸���
    //
    NRF905_SendBuffer[9] = NRF905_SendBuffer[0];
    
    NRF905_SendBuffer[10] = NRF905_SendBuffer[1];
    
    // �豸����
    //
    NRF905_SendBuffer[11] = NormalDeviceList[deviceListIndex].deviceType;
    
    // �����ŵ�
    //
    NRF905_SendBuffer[12] = App_Hal_Api.wireless->channelNo;
    
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
    NRF905_SendBuffer[Enum_Wirelss_ParityL] = tmpParityValue;
    NRF905_SendBuffer[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
    
    // ������ѯָ��
    //
	App_Hal_Api.wireless->write(NRF905_SendBuffer);
    
	
	// �����м����������߷��͵ȴ���ʱʱ��
	//
	Pca_Start(NRF905_SendBuffer, 0);
    
    // ��ѯʧ�ܼ�������������һ�����������л�����·�ɣ��������ѯӦ����ô���㣬��ѯӦ���߼���Command_OneCardDataUpload.c��
    //
    NormalDeviceList[deviceListIndex].deviceFailTimes++;
}


void __SendDataToSpecialDevice(int8_t deviceListIndex)
{
    uint16_t   parityValue;
    
    uint8_t   i;
    
    // --------------  ��ʼִ����ѯָ��  -----------------
    //
    // �豸���
    //
    NRF905_SendBuffer[0] = SpecialDeviceList[deviceListIndex].deviceNumber[0];
    
    NRF905_SendBuffer[1] = SpecialDeviceList[deviceListIndex].deviceNumber[1];
    
    
    // ������
    //
    NRF905_SendBuffer[2] = 0x01;
    
    
    // ������ˮ
    //
    NRF905_SendBuffer[3] = DeviceDataSerialNo++;
  
    
    NRF905_SendBuffer[4] = SpecialDeviceList[deviceListIndex].deviceMainRoute[0];       // Ŀ���м�
    
    
    NRF905_SendBuffer[5] = SpecialDeviceList[deviceListIndex].deviceMainRoute[0];       // �м�1
    
    
    NRF905_SendBuffer[6] = SpecialDeviceList[deviceListIndex].deviceMainRoute[1];       // �м�2
    
    
    NRF905_SendBuffer[7] = SpecialDeviceList[deviceListIndex].deviceMainRoute[2];       // �м�3
    
    // ����ַ�
    //
    NRF905_SendBuffer[8] = 0xF1;
    
    // �豸���
    //
    NRF905_SendBuffer[9] = NRF905_SendBuffer[0];
    
    NRF905_SendBuffer[10] = NRF905_SendBuffer[1];
    
    // �豸����
    //
    NRF905_SendBuffer[11] = 22;                                                         // ��������
    
    
    // ���浱ǰ��ѯ���豸����
    //
    DevicePool_DeviceType = 22;
    
    // �����ŵ�
    //
    NRF905_SendBuffer[12] = App_Hal_Api.wireless->channelNo;
    
    // ��\��\ʱ\��\����\��\��
    //
    NRF905_SendBuffer[13] = BCD(SysTime.second);
    
    NRF905_SendBuffer[14] = BCD(SysTime.minute);
    
    NRF905_SendBuffer[15] = BCD(SysTime.hour);
    
    NRF905_SendBuffer[16] = BCD(SysTime.day);
    
    NRF905_SendBuffer[17] = BCD(SysTime.week);
    
    NRF905_SendBuffer[18] = BCD(SysTime.month);
    
    NRF905_SendBuffer[19] = BCD(SysTime.year);
    
    // ����ַ�0xF1
    //
    memset(NRF905_SendBuffer + 20, 0xF1, 10);
    
    parityValue = 0;
    
    for (i = Enum_Wirelss_DataStart; i < Enum_Wirelss_DataStart + 12; ++i)
    {
        parityValue += NRF905_SendBuffer[i];
    }
    NRF905_SendBuffer[Enum_Wirelss_DataStart + 12] = parityValue;
    NRF905_SendBuffer[Enum_Wirelss_DataStart + 13] = parityValue >> 8;
    
    
    // ��У��
    //
    parityValue = 0;
    
    for (i = 0; i < 30; ++i)
    {
        parityValue += NRF905_SendBuffer[i];
    }
    
    NRF905_SendBuffer[Enum_Wirelss_ParityL] = parityValue;
    
    NRF905_SendBuffer[Enum_Wirelss_ParityH] = parityValue >> 8;
    
    // ������ѯָ��
    //
	App_Hal_Api.wireless->write(NRF905_SendBuffer);
	
	if (NRF905_SendBuffer[4])
	{
		SpecialDeviceList[deviceListIndex].deviceValidFlag = 0;
		
		Pca_SubStart(3000, 0);						// �ȴ�15��
	}
	else
	{
		Pca_Start(NRF905_SendBuffer, 0);			// �����м����������߷��͵ȴ���ʱʱ��
	}
}



// ��������ѯ����
// ������interval��ʾ�������룬��ѯ����һ��
//
bool DevicePool_SendDataToDevice(void)
{
    int8_t   DevicePool_SpecialDeviceListIndex;      // ������ѯ�������豸�б��±�
    
    int8_t   DevicePool_NormalDeviceListIndex;       // ������ѯ����ͨ�豸�б���±�
    
    
    // -------------- ������ѯ�����б���豸 --------------
    //
    DevicePool_SpecialDeviceListIndex = __NextSpecialDeviceList();
    
    if (DevicePool_SpecialDeviceListIndex != -1)
    {
        __SendDataToSpecialDevice(DevicePool_SpecialDeviceListIndex);
        
        return 1;
    }
    
    // -------------- ������ѯ��ͨ�б���豸 --------------
    //
    DevicePool_NormalDeviceListIndex = __NextNormalDeviceList();
    
    if (DevicePool_NormalDeviceListIndex != -1)
    {
        __SendDataToNormalDevice(DevicePool_NormalDeviceListIndex);
		
		return 1;
    }
	
	return 0;
}








