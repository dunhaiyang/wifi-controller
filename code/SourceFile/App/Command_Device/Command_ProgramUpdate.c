#include "Command_ProgramUpdate.h"


void ProgramUpdate_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[Enum_CommandNo];
    
    uint8_t tmpCommandSerialNo  = Data[Enum_CommandSerialNo];
    
    uint8_t tmpDeviceNoL        = Data[Enum_CommandContent + 0];
    
    uint8_t tmpDeviceNoH        = Data[Enum_CommandContent + 1];
    
    uint8_t tmpDeviceType       = Data[Enum_CommandContent + 2];
    
    uint8_t tmpRepeater1        = Data[Enum_CommandContent + 3];
    
    uint8_t tmpRepeater2        = Data[Enum_CommandContent + 4];
    
    uint8_t tmpRepeater3        = Data[Enum_CommandContent + 5];
    
    uint8_t tmpDataLen    		= Data[Enum_CommandContent + 6];
    
    uint8_t tmpPacketSerialNoL  = Data[Enum_CommandContent + 7];
    
    uint8_t tmpPacketSerialNoH  = Data[Enum_CommandContent + 8];
    
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
    NRF905_SendBuffer[8] = tmpDataLen;
    NRF905_SendBuffer[9] = tmpDeviceNoL;
    NRF905_SendBuffer[10] = tmpDeviceNoH;
    NRF905_SendBuffer[11] = tmpDeviceType;
    NRF905_SendBuffer[12] = tmpPacketSerialNoL;
    NRF905_SendBuffer[13] = tmpPacketSerialNoH;
 
	// ��������
	//
	memcpy(NRF905_SendBuffer + 14, Data + 12, 16);
    
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
void ProgramUpdate_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpCommandSerialNo  = Data[3];
	
	uint8_t tmpReceiveResult	= Data[8];
    
    uint8_t tmpDeviceNoL        = Data[9];
    
    uint8_t tmpDeviceNoH        = Data[10];
    
    uint8_t tmpDeviceType       = Data[11];
    
    uint8_t tmpPacketSerialNoL  = Data[12];
    
    uint8_t tmpPacketSerialNoH  = Data[13];
    
    // �豸���
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // �豸����
    //
    SocketData_SendBuffer[2] = tmpDeviceType;
	
	// ���ս��
	//
	SocketData_SendBuffer[3] = tmpReceiveResult;
    
    // ���������
    //
    SocketData_SendBuffer[4] = tmpPacketSerialNoL;
    
    SocketData_SendBuffer[5] = tmpPacketSerialNoH;
	
	// �����������
	//
	memcpy(SocketData_SendBuffer + 6, Data + 14, 16);
    
    // ���ͳ�������Ӧ�����PC
    //
    PC_SendCommand(0x1E, tmpCommandSerialNo, SocketData_SendBuffer, 22);
}






