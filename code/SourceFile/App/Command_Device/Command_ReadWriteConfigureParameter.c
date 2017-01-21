#include "Command_ReadWriteConfigureParameter.h"


uint8_t ReadWriteConfigureParameter_DeviceType = 0xFF;


void ReadWriteConfigureParameter_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint8_t tmpParameterNo      = Data[9];
    
    uint8_t tmpReadWriteFlag    = Data[10];
    
    uint8_t tmpWriteLen         = Data[11];
    
    uint16_t tmpParityValue       = 0;
    
    // �����豸���ͣ���Ӧ�����ʹ��
    //
    ReadWriteConfigureParameter_DeviceType = tmpDeviceType;
    
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
    NRF905_SendBuffer[5] = tmpRepeater1;
    NRF905_SendBuffer[6] = tmpRepeater2;
    NRF905_SendBuffer[7] = tmpRepeater3;
    
    // ���ݣ�22�ֽڣ�
    //
    NRF905_SendBuffer[8] = 0xEB;
    NRF905_SendBuffer[9] = tmpDeviceNoL;
    NRF905_SendBuffer[10] = tmpDeviceNoH;
    NRF905_SendBuffer[11] = tmpDeviceType;
    NRF905_SendBuffer[12] = tmpParameterNo;                                     // �������
    NRF905_SendBuffer[13] = tmpWriteLen;                                        // ��������
    if (tmpReadWriteFlag)                                                       // ��д��־�� 0 - ���� 1 - д
    {
        NRF905_SendBuffer[13] |= 0x80;
        
        memcpy(NRF905_SendBuffer + 14, Data + 12, tmpWriteLen);
    }
    else
    {
        NRF905_SendBuffer[13] &= 0x7F;
        
        memset(NRF905_SendBuffer + 14, 0xEB, 16);
    }
    
    // �ⲿ��У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[30] = tmpParityValue;
    NRF905_SendBuffer[31] = tmpParityValue >> 8;
    
    // �������ݵ������豸
    //
//    Wireless_SendDataToDevice(NRF905_SendBuffer);
	
	// �����м����������߷��͵ȴ���ʱʱ��
	//
	Pca_Start(NRF905_SendBuffer, 0);
}


void ReadWriteConfigureParameter_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[0];
    
    uint8_t tmpDeviceNoH        = Data[1];
    
    uint8_t tmpCommandNo        = Data[2];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpReadWriteResult  = Data[8];
    
    uint8_t tmpParameterNo      = Data[12];
    
    uint8_t tmpRWParameterLen   = Data[13];
    
    uint8_t tmpCommandContentLen;
    
    // �豸���
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // �豸����
    //
    SocketData_SendBuffer[2] = ReadWriteConfigureParameter_DeviceType;
    
    // �������
    //
    SocketData_SendBuffer[3] = tmpParameterNo;
    
    // ��д��־λ
    //
    SocketData_SendBuffer[4] = ((tmpRWParameterLen & 0x80)? 0x01:0x00);
    
    // ��д���
    //
    SocketData_SendBuffer[5] = tmpReadWriteResult;
    
    // �����ܹ���Ҫ���Ͷ����ֽ�(�豸���, �豸����, �������, ��д��־λ, ��д���)
    //
    tmpCommandContentLen = 6;
    
    // ����Ƕ�����ô��������
    //
    if (!SocketData_SendBuffer[4])
    {
        SocketData_SendBuffer[6] = tmpRWParameterLen & 0x7F;                        // ����������
        
        memcpy(SocketData_SendBuffer + 7, Data + 14, SocketData_SendBuffer[6]);             // ������������
        
        tmpCommandContentLen += (SocketData_SendBuffer[6] + 1);                     // Ҫ�����϶��������ֽ���
    }
    
    // �����м������԰���PC
    //
    PC_SendCommand(0x1A, tmpCommandSerialNo, SocketData_SendBuffer, tmpCommandContentLen);
}





