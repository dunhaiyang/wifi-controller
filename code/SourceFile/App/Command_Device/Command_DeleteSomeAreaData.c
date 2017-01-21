#include "Command_DeleteSomeAreaData.h"


uint8_t DeleteSomeAreaData_DeviceType = 0xFF;


void DeleteSomeAreaData_DealData(uint8_t *Data)
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
    DeleteSomeAreaData_DeviceType = tmpDeviceType;
    
    
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
    NRF905_SendBuffer[8] = 0xF6;
    
    NRF905_SendBuffer[9] = tmpDeviceNoL;
    
    NRF905_SendBuffer[10] = tmpDeviceNoH;
    
    NRF905_SendBuffer[11] = tmpDeviceType;
    
    NRF905_SendBuffer[12] = App_Hal_Api.wireless->channelNo;
    
    memcpy(NRF905_SendBuffer + 13, Data + 9, 9);
    
    // �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 14);
    NRF905_SendBuffer[22] = tmpParityValue;
    NRF905_SendBuffer[23] = tmpParityValue >> 8;
    
    // ����ַ�0xA3
    //
    memset(NRF905_SendBuffer + 24, 0xF6, 6);
    
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


void DeleteSomeAreaData_SendDataToPC(uint8_t *Data)
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
    SocketData_SendBuffer[2] = DeleteSomeAreaData_DeviceType;
    
    memcpy(SocketData_SendBuffer + 3, Data + 13, 10);
    
    // �����м������԰���PC
    //
    PC_SendCommand(0x08, tmpCommandSerialNo, SocketData_SendBuffer, 13);
}





