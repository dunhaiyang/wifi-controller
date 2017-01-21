#include "Command_RepeaterParameter.h"


void RepeaterParameter_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo            = Data[Enum_CommandNo];
    
    uint8_t tmpCommandSerialNo      = Data[Enum_CommandSerialNo];
    
//    uint8_t tmpRepeaterNo           = Data[Enum_CommandContent + 0];      // û������
    
    uint8_t tmpRepeater1            = Data[Enum_CommandContent + 1];
    
    uint8_t tmpRepeater2            = Data[Enum_CommandContent + 2];
    
    uint8_t tmpRepeater3            = Data[Enum_CommandContent + 3];
    
    uint8_t tmpIsChange1            = Data[Enum_CommandContent + 4];
    
    uint8_t tmpNewRepeaterNo        = Data[Enum_CommandContent + 5];
    
    uint8_t tmpIsChange2            = Data[Enum_CommandContent + 6];
    
    uint8_t tmpNewWirelessChannel   = Data[Enum_CommandContent + 7];
    
    uint16_t tmpParityValue           = 0;
    
    // �豸���
    //
    NRF905_SendBuffer[0] = 0xEB;
    NRF905_SendBuffer[1] = 0xFD;
    
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
    NRF905_SendBuffer[8] = 0xA7;
    NRF905_SendBuffer[9] = tmpIsChange1;
    NRF905_SendBuffer[10] = tmpNewRepeaterNo;
    NRF905_SendBuffer[11] = tmpIsChange2;
    NRF905_SendBuffer[12] = tmpNewWirelessChannel;
    
    // �ڲ���У��
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 5);
    NRF905_SendBuffer[13] = tmpParityValue;
    NRF905_SendBuffer[14] = tmpParityValue >> 8;
    
    // ����ַ�0xA7
    //
    memset(NRF905_SendBuffer + 15, 0xA7, 15);
    
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



void RepeaterParameter_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpSerialNo         = Data[3];
    
    uint8_t tmpChangeResult1    = Data[9];
    
    uint8_t tmpNowRepeaterNo    = Data[10];
    
    uint8_t tmpChangeResult2    = Data[11];
    
    uint8_t tmpNowChannelNo     = Data[12];
    
    SocketData_SendBuffer[0] = tmpChangeResult1;
    
    SocketData_SendBuffer[1] = tmpNowRepeaterNo;
    
    SocketData_SendBuffer[2] = tmpChangeResult2;
    
    SocketData_SendBuffer[3] = tmpNowChannelNo;
    
    // �����м������ð���PC
    //
    PC_SendCommand(0x6C, tmpSerialNo, SocketData_SendBuffer, 4);
}




