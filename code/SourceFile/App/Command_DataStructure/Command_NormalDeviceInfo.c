#include "Command_NormalDeviceInfo.h"



// 设备列表, 设备列表元素数量
//
NormalDeviceInfo_Typedef NormalDeviceList[NormalDeviceListSum];



// 已经存储了多少设备列表
//
uint8_t   NormalDeviceListUsage = 0;


// 设备数据的流水号
//
uint8_t    DeviceDataSerialNo = 0;


// ============================================== 设备列表相关操作 ==================================================
// =================================================================================================================


// 初始化设备列表
//
void NormalDeviceInfo_Init(void)
{
    uint8_t index;
    
    for (index = 0; index < NormalDeviceListSum; ++index)
    {
        // 设置为无效，失败次数为0， 状态为正常， 使用主路由, 没有等待轮询设备应答
        //
        NormalDeviceList[index].deviceValidFlag = 0;
        
        NormalDeviceList[index].deviceFailTimes = 0;
			
		NormalDeviceList[index].deviceOnline = 0;
        
        NormalDeviceList[index].usingDeviceRouteNow = 0;
    }
    
    NormalDeviceListUsage = 0;
}


// 查找指定数据, 返回-1表示找不到，其他值标志找到的下标
//
int8_t NormalDeviceInfo_FindDeviceList(uint8_t deviceNoL, uint8_t deviceNoH, uint8_t deviceType)
{
    uint8_t index;
    
    for (index = 0; index < NormalDeviceListSum; index++)
    {
        if (NormalDeviceList[index].deviceValidFlag
            && NormalDeviceList[index].deviceNumber[0] == deviceNoL
            && NormalDeviceList[index].deviceNumber[1] == deviceNoH
            && NormalDeviceList[index].deviceType == deviceType)
        {
            return index;
        }
    }
    
    return -1;
}



// 增加设备列表
//
bool NormalDeviceInfo_AddDeviceList(uint8_t *deviceListAddress)
{
    int8_t  retValue;
    uint8_t index;
    
    // 查询是否已经存在
    //
    retValue = NormalDeviceInfo_FindDeviceList(deviceListAddress[0], deviceListAddress[1], deviceListAddress[2]);
    
    // 之前已经添加过了，直接返回真
    //
    if (retValue != -1)
    {
        return 1;
    }
    
    // 找到一个空闲地方保存
    //
    for (index = 0; index < NormalDeviceListSum; index++)
    {
        if (!NormalDeviceList[index].deviceValidFlag)
        {
            NormalDeviceList[index].deviceNumber[0] = deviceListAddress[0];
            
            NormalDeviceList[index].deviceNumber[1] = deviceListAddress[1];
            
            NormalDeviceList[index].deviceType = deviceListAddress[2];
            
            memcpy(NormalDeviceList[index].deviceMainRoute, deviceListAddress + 3, 3);
            
            memcpy(NormalDeviceList[index].deviceBakRoute, deviceListAddress + 6, 3);
            
            NormalDeviceList[index].deviceValidFlag = 1;
			
			NormalDeviceList[index].deviceOnline = 0;
            
            NormalDeviceListUsage++;
            
            return 1;
        }
    }
    
    return 0;
}


// 删除设备列表
//
bool NormalDeviceInfo_DeleteDeviceList(uint8_t *deviceListAddress)
{
    int8_t retValue;
    
    retValue = NormalDeviceInfo_FindDeviceList(deviceListAddress[0], deviceListAddress[1], deviceListAddress[2]);
    
    if (retValue != -1)
    {
        NormalDeviceList[retValue].deviceValidFlag = 0;
        
        NormalDeviceListUsage--;
    }
    
    return 1;
}


// 清空设备列表
//
bool NormalDeviceInfo_EmptyDeviceList(void)
{
    uint8_t index;
    
    for (index = 0; index < NormalDeviceListSum; index++)
    {
        NormalDeviceList[index].deviceValidFlag = 0;
    }
    
    NormalDeviceListUsage = 0;
    
    return 1;
}



void NormalDeviceInfo_TravelDeviceList(void)
{
    static uint8_t index;
    
    for (index = 0; index < NormalDeviceListSum; index++)
    {
        if (NormalDeviceList[index].deviceValidFlag)
        {
			App_Hal_Api.console->printDec("index:\t", 	index);
			App_Hal_Api.console->printDec("\tdevno:\t", 	NormalDeviceList[index].deviceNumber[0] | NormalDeviceList[index].deviceNumber[1] << 8);
			App_Hal_Api.console->printDecLn("\ttype:\t",	NormalDeviceList[index].deviceType);
			App_Hal_Api.console->printDec("mr0:\t",		NormalDeviceList[index].deviceMainRoute[0]);
			App_Hal_Api.console->printDec("\tmr1:\t",		NormalDeviceList[index].deviceMainRoute[0]);
			App_Hal_Api.console->printDecLn("\tmr2:\t",	NormalDeviceList[index].deviceMainRoute[0]);
			App_Hal_Api.console->printDec("br0:\t",		NormalDeviceList[index].deviceBakRoute[0]);
			App_Hal_Api.console->printDec("\tbr1:\t",		NormalDeviceList[index].deviceBakRoute[0]);
			App_Hal_Api.console->printDecLn("\tbr2:\t",	NormalDeviceList[index].deviceBakRoute[0]);
        }
    }
}







