#include "Command_OneCardDataUploadDelete.h"



// ������ǣ����Ӱ�쵽��ѯ�����磺������յ��豸����ɾ���ذ�����ô���Ͽ�����ѯ��ʵ����ѯ��һ̨���ѻ�
//
uint8_t   OneCardDataUploadDelete_OperationFlag = 0x55; 



void OneCardDataUploadDelete_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint16_t tmpParityValue;
    
    OneCardDataUploadDelete_OperationFlag  = Data[9];           // ���豸ɾ��Ӧ���������
    
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
    
    // Ŀ���м�, �м�1�� �м�2�� �м�3
    //
    NRF905_SendBuffer[4] = tmpRepeater1;
    NRF905_SendBuffer[5] = tmpRepeater1;
    NRF905_SendBuffer[6] = tmpRepeater2;
    NRF905_SendBuffer[7] = tmpRepeater3;
	
    
    // ������ǣ�1�� + ���ţ�4��+ ������ˮ�ţ�4�� + ��ʹ�õ�δ������2��
    //
    memcpy(NRF905_SendBuffer + 8, Data + 9, 11);
    
    
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


// ɾ��ָ��ذ�
//
void OneCardDataUploadDelete_SendDataToPC(uint8_t *Data)
{
    Data = Data;
}






