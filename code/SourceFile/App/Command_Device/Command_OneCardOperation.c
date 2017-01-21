#include "Command_OneCardOperation.h"


void OneCardOperation_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint16_t  tmpParityValue;
    
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
    
    
    // Ŀ���м�, �м�1���м�2�� �м�3
    //
    NRF905_SendBuffer[4] = tmpRepeater1;
    NRF905_SendBuffer[5] = tmpRepeater1;
    NRF905_SendBuffer[6] = tmpRepeater2;
    NRF905_SendBuffer[7] = tmpRepeater3;
    
    // ��Ҫ����
    //
    memcpy(NRF905_SendBuffer + 8, Data + 9, 22);
    
    // ��У��
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



void OneCardOperation_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[0];
    
    uint8_t tmpDeviceNoH        = Data[1];

    uint8_t tmpCommandNo        = Data[2];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpRepeater1        = Data[5];
    
    uint8_t tmpRepeater2        = Data[6];
    
    uint8_t tmpRepeater3        = Data[7];
    
    uint8_t tmpOperationResult  = Data[8];
    
    // �豸���
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    
    // �豸����
    //
    SocketData_SendBuffer[2] = 0x01;                   // Ĭ�������ѻ�
    
    
    // Ŀ���м�, �м�1���м�2�� �м�3
    //
    SocketData_SendBuffer[3] = tmpRepeater1;
    SocketData_SendBuffer[4] = tmpRepeater2;
    SocketData_SendBuffer[5] = tmpRepeater3;
    
    
    // �޸Ľ����1��+ ���ţ�4�� + ������ˮ�ţ�4��
    //
    memcpy(SocketData_SendBuffer + 6, Data + 8, 9);
	
    // �����м������԰���PC
    //
    PC_SendCommand(0xF4, tmpCommandSerialNo, SocketData_SendBuffer,  15);
}






