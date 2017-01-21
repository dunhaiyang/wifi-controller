#ifndef COMMAND_TEMPORARY_H_
#define COMMAND_TEMPORARY_H_

#include "APP_HAL_API.h"


enum
{
    Enum_Wirelss_DeviceNoL = 0,
    
    Enum_Wirelss_DeviceNoH = 1,
    
    Enum_Wirelss_CommandNo = 2,
    
    Enum_Wirelss_CommandSerialNo = 3,
    
    Enum_Wirelss_Repeater1 = 5,
    
    Enum_Wirelss_Repeater2 = 6,
    
    Enum_Wirelss_Repeater3 = 7,
    
    Enum_Wirelss_DataStart = 8,
    
    Enum_Wirelss_DataEnd = 29,
    
    Enum_Wirelss_ParityL = 30,
    
    Enum_Wirelss_ParityH = 31,
};


enum
{
    Enum_CommandNo = 0,
    
    Enum_CommandSerialNo = 1,
    
    Enum_CommandContentLen = 2,
    
    Enum_CommandContent = 3,
};


typedef enum
{
    WirelessChannel_Busy = 1,
    
    WirelessChannel_Free = 2,
    
}WiresslessChannel_Status_Typedef;


// ��������״̬
//
extern WiresslessChannel_Status_Typedef WiresslessChannel_Status;


// ָ��ͳ�ʱ
//
extern uint8_t Timeout;


// ָ���ط�����
//
extern uint8_t ResendTimes;


// ����sub PCA�������߷��ͼ�ʱ
//
void Pca_SubStart(uint16_t timeout, uint8_t resendTimes);


// 
//
void Pca_Start(uint8_t *str, uint8_t resendTimes);


// ֹͣPCA
//
void Pca_Stop(void);


// �����У��ֵ
//
uint16_t Temporary_CalcSumParity(uint8_t *str, uint8_t len);




#endif



