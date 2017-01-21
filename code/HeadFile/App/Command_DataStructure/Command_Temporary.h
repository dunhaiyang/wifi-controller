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


// 控制器的状态
//
extern WiresslessChannel_Status_Typedef WiresslessChannel_Status;


// 指令发送超时
//
extern uint8_t Timeout;


// 指令重发次数
//
extern uint8_t ResendTimes;


// 开启sub PCA，给无线发送计时
//
void Pca_SubStart(uint16_t timeout, uint8_t resendTimes);


// 
//
void Pca_Start(uint8_t *str, uint8_t resendTimes);


// 停止PCA
//
void Pca_Stop(void);


// 计算和校验值
//
uint16_t Temporary_CalcSumParity(uint8_t *str, uint8_t len);




#endif



