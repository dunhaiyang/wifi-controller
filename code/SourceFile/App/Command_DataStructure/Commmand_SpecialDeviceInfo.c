#include "Command_SpecialDeviceInfo.h"


// 设备列表, 设备列表元素数量
//
SpecialDeviceInfo_Typedef SpecialDeviceList[SpecialDeviceListSum];


// 已经存储了多少设备列表
//
uint8_t   SpecialDeviceListUsage = 0;



// 初始化设备列表
//
void SpecialDeviceInfo_Init(void)
{
    uint8_t index;
    
    for (index = 0; index < SpecialDeviceListSum; ++index)
    {
        SpecialDeviceList[index].deviceValidFlag = 0;
    }
}


// 查找指定数据, 返回-1表示找不到，其他值标志找到的下标
//
int8_t SpecialDeviceInfo_FindDeviceList(uint8_t deviceNoL, uint8_t deviceNoH)
{
    uint8_t index;
    
    for (index = 0; index < SpecialDeviceListSum; index++)
    {
        if (SpecialDeviceList[index].deviceValidFlag &&
            SpecialDeviceList[index].deviceNumber[0] == deviceNoL && 
            SpecialDeviceList[index].deviceNumber[1] == deviceNoH)
        {
            return index;
        }
    }
    
    return -1;
}


// 增加设备列表
//
bool SpecialDeviceInfo_AddDeviceList(uint8_t *deviceListAddress)
{
    int8_t retVal;
    
    uint8_t index;
    
    retVal = SpecialDeviceInfo_FindDeviceList(deviceListAddress[0], deviceListAddress[1]);
    
    if (retVal != -1)
    {
        return 0;
    }

    for (index = 0; index < SpecialDeviceListSum; ++index)
    {
        // 正式插入设备列表数据
        //
        if (!SpecialDeviceList[index].deviceValidFlag)
        {
            SpecialDeviceList[index].deviceNumber[0] = deviceListAddress[0];
            SpecialDeviceList[index].deviceNumber[1] = deviceListAddress[1];
            
            SpecialDeviceList[index].deviceMainRoute[0] = deviceListAddress[3];
            SpecialDeviceList[index].deviceMainRoute[1] = deviceListAddress[4];
            SpecialDeviceList[index].deviceMainRoute[2] = deviceListAddress[5];
            SpecialDeviceList[index].deviceValidFlag = 1;
            
            SpecialDeviceListUsage++;
            
            return 1;
        }
    }

    return 0;
}


// 删除设备列表中设备
//
bool SpecialDeviceInfo_DeleteDeviceList(uint8_t *deviceListAddress)
{
    int8_t retVal;
    
    retVal = SpecialDeviceInfo_FindDeviceList(deviceListAddress[0], deviceListAddress[1]);
    
    if (retVal != -1)
    {
        SpecialDeviceList[retVal].deviceValidFlag = 0;
        
        SpecialDeviceListUsage--;
    }
    
    return 1;
}


// 清空设备列表
//
bool SpecialDeviceInfo_EmptyDeviceList()
{
    uint8_t index;

    for (index = 0; index < SpecialDeviceListSum; ++index)
    {
        // 正式插入设备列表数据
        //
        SpecialDeviceList[index].deviceValidFlag = 0;
    }
    
    SpecialDeviceListUsage = 0;
    
    return 1;
}















