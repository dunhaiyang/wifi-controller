#include "Command_WhiteListUpload.h"


uint8_t WhiteListUpload_DeviceType = 0xFF;

// ����������ϱ�����
//
void WhiteListUpload_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint8_t tmpWhiteListLen     = Data[10];
    
    uint16_t tmpParityValue       = 0;
    
    // �����豸���ͣ���Ӧ�����ʹ��
    //
    WhiteListUpload_DeviceType = tmpDeviceType;
    
    
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
    NRF905_SendBuffer[8] = 0xE3;
    memcpy(NRF905_SendBuffer + 9, Data + 9, tmpWhiteListLen + 2);
    NRF905_SendBuffer[29] = 0xE3;
    
    // �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 19);
    NRF905_SendBuffer[27] = tmpParityValue;
    NRF905_SendBuffer[28] = tmpParityValue >> 8;
    
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


void WhiteListUpload_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL    	= Data[0];
    
    uint8_t tmpDeviceNoH    	= Data[1];
    
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
    SocketData_SendBuffer[2] = WhiteListUpload_DeviceType;
	
	// �ϴ����
	//
	SocketData_SendBuffer[3] = Data[27];
    
    memcpy(SocketData_SendBuffer + 4, Data + 9, 2 + tmpWhiteListLen);
    
    // �����м������԰���PC
    //
    PC_SendCommand(0x12, tmpCommandSerialNo, SocketData_SendBuffer,  tmpWhiteListLen + 6);
}





