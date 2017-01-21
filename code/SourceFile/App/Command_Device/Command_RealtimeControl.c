#include "Command_RealtimeControl.h"


uint8_t RealtimeControl_DeviceType = 0xFF;

void RealtimeControl_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint16_t tmpParityValue       = 0;
    
    // �����豸���ͣ���Ӧ�����ʹ��
    //
    RealtimeControl_DeviceType = tmpDeviceType;
    
    
    // �豸���
    //
    NRF905_SendBuffer[0] = tmpDeviceNoL;
    
    NRF905_SendBuffer[1] = tmpDeviceNoH;
    
    // ������
    //
    NRF905_SendBuffer[2] = tmpCommandNo;
    
    // ������ˮ��
    //
    NRF905_SendBuffer[3] = tmpCommandSerialNo;
    
    // Ŀ���м�
    //
    NRF905_SendBuffer[4] = tmpRepeater1;
    
    // �м�1
    //
    NRF905_SendBuffer[5] = tmpRepeater1;
    
    // �м�2
    //
    NRF905_SendBuffer[6] = tmpRepeater2;
    
    // �м�3
    //
    NRF905_SendBuffer[7] = tmpRepeater3;
    
    // ����
    //
    NRF905_SendBuffer[8] = 0xE5;
    
    memcpy(NRF905_SendBuffer + 9, Data + 9, 8);
    
    NRF905_SendBuffer[17] = tmpDeviceNoL;
    
    NRF905_SendBuffer[18] = tmpDeviceNoH;
    
    NRF905_SendBuffer[19] = tmpDeviceType;
    
    memcpy(NRF905_SendBuffer + 20, Data + 17, 8);
    
    // �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 20);
    NRF905_SendBuffer[28] = tmpParityValue;
    NRF905_SendBuffer[29] = tmpParityValue >> 8;
    
    // �ⲿ��У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[Enum_Wirelss_ParityL] = tmpParityValue;
    NRF905_SendBuffer[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
    
    // �������ݵ������豸
    //
	App_Hal_Api.wireless->write(NRF905_SendBuffer);
	
	// �����м����������߷��͵ȴ���ʱʱ��
	//
	Pca_Start(NRF905_SendBuffer, 0);
}


void RealtimeControl_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL    = Data[0];
    
    uint8_t tmpDeviceNoH    = Data[1];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpUploadMode       = Data[9];
    
    uint8_t tmpWhiteListLen     = Data[10];
    
    uint8_t tmpUploadStatus     = Data[27];
    
    
    // �豸���
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // �豸����
    //
    SocketData_SendBuffer[2] = RealtimeControl_DeviceType;
    
    memcpy(SocketData_SendBuffer + 3, Data + 9, 8);
    
    memcpy(SocketData_SendBuffer + 11, Data + 20, 8);
    
    // �����м������԰���PC
    //
    PC_SendCommand(0x14, tmpCommandSerialNo, SocketData_SendBuffer,  19);    
}








