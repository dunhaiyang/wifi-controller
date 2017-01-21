#include "Command_SerialNoWatchAndConfigure.h"


uint8_t SerialNoWatchAndConfigure_DeviceType = 0xFF;


void SerialNoWatchAndConfigure_DealData(uint8_t *Data)
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
    SerialNoWatchAndConfigure_DeviceType = tmpDeviceType;
    
    
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
    NRF905_SendBuffer[8] = 0xFA;
    
    memcpy(NRF905_SendBuffer + 9, Data + 9, 16);
    
    // �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 17);
    NRF905_SendBuffer[25] = tmpParityValue;
    NRF905_SendBuffer[26] = tmpParityValue >> 8;
    
    // ����ַ�0xA3
    //
    NRF905_SendBuffer[27] = 0xFA;
    NRF905_SendBuffer[28] = 0xFA;
    NRF905_SendBuffer[29] = 0xFA;
    
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


void SerialNoWatchAndConfigure_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[0];
    
    uint8_t tmpDeviceNoH        = Data[1];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    // �豸���
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // �豸����
    //
    SocketData_SendBuffer[2] = SerialNoWatchAndConfigure_DeviceType;
    
    memcpy(SocketData_SendBuffer + 3, Data + 17, 8);
    
    // �����м������԰���PC
    //
    PC_SendCommand(0x0C, tmpCommandSerialNo, SocketData_SendBuffer, 11);
}





