#ifndef __COMMAND_SPECIALDEVICEINFO_H_
#define __COMMAND_SPECIALDEVICEINFO_H_



#include "APP_HAL_API.h"


// 支持最大存储的设备数据数
//
#define SpecialDeviceListSum 3


// 设备数据结构（自动轮询中使用）
//
typedef struct
{
    uint8_t deviceNumber[2];              // 设备号
    
    uint8_t deviceMainRoute[3];           // 主路由
    
    uint8_t deviceValidFlag;              // 设备有效标志
    
}SpecialDeviceInfo_Typedef;


extern SpecialDeviceInfo_Typedef SpecialDeviceList[SpecialDeviceListSum];


// 已经存储了多少设备列表
//
extern  uint8_t   SpecialDeviceListUsage;



// 初始化设备列表
//
void SpecialDeviceInfo_Init();


// 查找指定数据, 返回-1表示找不到，其他值标志找到的下标
//
int8_t SpecialDeviceInfo_FindDeviceList(uint8_t deviceNoL, uint8_t deviceNoH);


// 查询还可以存储多少个设备列表数据
//
#define SpecialDeviceInfo_HowManySpace() (SpecialDeviceListSum - SpecialDeviceListUsage)


// 增加设备列表
//
bool SpecialDeviceInfo_AddDeviceList(uint8_t *deviceListAddress);


// 删除设备列表中设备
//
bool SpecialDeviceInfo_DeleteDeviceList(uint8_t *deviceListAddress);


// 清空设备列表
//
bool SpecialDeviceInfo_EmptyDeviceList();







#endif
