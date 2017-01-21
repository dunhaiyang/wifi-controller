#include "Command_ReadWhiteList.h"


uint8_t ReadWhiteList_DeviceType = 0xFF;


void ReadWhiteList_DealData(uint8_t *Data)
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
    ReadWhiteList_DeviceType = tmpDeviceType;
    
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
    
    // ���ݣ�22�ֽڣ�
    //
    NRF905_SendBuffer[8] = 0xE9;
    NRF905_SendBuffer[9] = tmpDeviceNoL;
	NRF905_SendBuffer[10] = tmpDeviceNoH;
	NRF905_SendBuffer[11] = tmpDeviceType;
	NRF905_SendBuffer[12] = App_Hal_Api.wireless->channelNo;
    memcpy(NRF905_SendBuffer + 13, Data + 9, 5);
    
    // �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 10);
    NRF905_SendBuffer[18] = tmpParityValue;
    NRF905_SendBuffer[19] = tmpParityValue >> 8;
    
    // ����ַ�0xA3
    //
    memset(NRF905_SendBuffer + 20, 0xE9, 10);
    
    // �ⲿ��У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[30] = tmpParityValue;
    NRF905_SendBuffer[31] = tmpParityValue >> 8;
    
    // �������ݵ������豸
    //
	App_Hal_Api.wireless->write(NRF905_SendBuffer);
	
	// �����м����������߷��͵ȴ���ʱʱ��
	//
	Pca_Start(NRF905_SendBuffer, 0);
}


void ReadWhiteList_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[2];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpRepeaterNo       = Data[9];
    
    uint8_t tmpTestPacketNoL    = Data[0];
    
    uint8_t tmpTestPacketNoH    = Data[1];
	
	uint8_t tmpWhiteListLen     = Data[10];
    
    // �豸���
    //
    SocketData_SendBuffer[0] = tmpTestPacketNoL;
    SocketData_SendBuffer[1] = tmpTestPacketNoH;
    
    // �豸����
    //
    SocketData_SendBuffer[2] = ReadWhiteList_DeviceType;
    
    memcpy(SocketData_SendBuffer + 3, Data + 9, 5 + tmpWhiteListLen);
    
    // �����м������԰���PC
    //
    PC_SendCommand(0x18, DeviceDataSerialNo++, SocketData_SendBuffer, 8 + tmpWhiteListLen);
}





