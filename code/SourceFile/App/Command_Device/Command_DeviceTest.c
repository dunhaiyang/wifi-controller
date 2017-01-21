#include "Command_DeviceTest.h"


// ת�����Ե��豸ͨѶ���԰����豸
//
void DeviceTest_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[Enum_CommandNo];
    
    uint8_t tmpCommandSerialNo  = Data[Enum_CommandSerialNo];
    
    uint8_t tmpDeviceNoL        = Data[Enum_CommandContent + 0];
    
    uint8_t tmpDeviceNoH        = Data[Enum_CommandContent + 1];
    
    uint8_t tmpDeviceType       = Data[Enum_CommandContent + 2];
    
    uint8_t tmpRepeater1        = Data[Enum_CommandContent + 3];
    
    uint8_t tmpRepeater2        = Data[Enum_CommandContent + 4];
    
    uint8_t tmpRepeater3        = Data[Enum_CommandContent + 5];
    
    uint8_t tmpTestPacketNoL    = Data[Enum_CommandContent + 6];
    
    uint8_t tmpTestPacketNoH    = Data[Enum_CommandContent + 7];
    
    uint16_t tmpParityValue       = 0;
    
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
    NRF905_SendBuffer[8] = 0xA9;
    NRF905_SendBuffer[9] = tmpDeviceNoL;
    NRF905_SendBuffer[10] = tmpDeviceNoH;
    NRF905_SendBuffer[11] = tmpDeviceType;
    NRF905_SendBuffer[12] = App_Hal_Api.wireless->channelNo;
    NRF905_SendBuffer[13] = tmpTestPacketNoL;
    NRF905_SendBuffer[14] = tmpTestPacketNoH;
    
    // �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 7);
    NRF905_SendBuffer[15] = tmpParityValue;
    NRF905_SendBuffer[16] = tmpParityValue >> 8;
    
    // ����ַ�0xA3
    //
    memset(NRF905_SendBuffer + 17, 0xA9, 13);
    
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



// ת���豸���豸ͨѶ���԰�������
//
void DeviceTest_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpDeviceNoL        = Data[9];
    
    uint8_t tmpDeviceNoH        = Data[10];
    
    uint8_t tmpDeviceType       = Data[11];
    
    uint8_t tmpTestPacketNoL    = Data[13];
    
    uint8_t tmpTestPacketNoH    = Data[14];
    
    // �豸���
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // �豸����
    //
    SocketData_SendBuffer[2] = tmpDeviceType;
    
    // ���԰����
    //
    SocketData_SendBuffer[3] = tmpTestPacketNoL;
    
    SocketData_SendBuffer[4] = tmpTestPacketNoH;
    
    // �����м������԰���PC
    //
    PC_SendCommand(0x6E, tmpCommandSerialNo, SocketData_SendBuffer, 5);
}





