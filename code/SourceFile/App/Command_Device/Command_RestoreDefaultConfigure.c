#include "Command_RestoreDefaultConfigure.h"

uint8_t RestoreDefaultConfigure_DeviceType = 0xFF;

void RestoreDefaultConfigure_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint8_t tmpRestoreFlag1     = Data[9];
    
    uint8_t tmpRestoreFlag2     = Data[10];
    
    uint16_t tmpParityValue       = 0;
    
    // �����豸���ͣ���Ӧ�����ʹ��
    //
    RestoreDefaultConfigure_DeviceType = tmpDeviceType;
    
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
    NRF905_SendBuffer[8] = tmpRestoreFlag1;
    NRF905_SendBuffer[9] = tmpRestoreFlag2;
    
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


void RestoreDefaultConfigure_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[0];
    
    uint8_t tmpDeviceNoH        = Data[1];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpOperationResult  = Data[8];
    
    
    // �豸���
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // �豸���
    //
    SocketData_SendBuffer[2] = RestoreDefaultConfigure_DeviceType;
    
    // ָ��ִ�н��
    //
    SocketData_SendBuffer[3] = tmpOperationResult;
    
    // �����м������԰���PC
    //
    PC_SendCommand(0x32, tmpCommandSerialNo, SocketData_SendBuffer, 4);
}





