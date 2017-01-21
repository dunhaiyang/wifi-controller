#include "Command_DevicePool.h"


uint8_t	DevicePool_DeviceType = 0;


int8_t __NextNormalDeviceList()
{
    static uint8_t index = 0;
    
    uint8_t tmpIndex = index;           // 保存index历史值, 用于分成[index, 50], [0, index]两个区间来搜索
    
    // 查询[index, NormalDeviceListSum]区间的有效设备列表
    //
    for (; index < NormalDeviceListSum; index++)
    {
        if (NormalDeviceList[index].deviceValidFlag)
        {
            return index++;                 // 返回有效的设备列表数据的下标
        }
    }
    
    // 如果[index, NormalDeviceListSum]找不到，那么查询[0, index]区间的有效设备列表
    //
    for (index = 0; index < tmpIndex; index++)
    {
        if (NormalDeviceList[index].deviceValidFlag)
        {
            return index++;                 // 返回有效的设备列表数据的下标
        }
    }
    
    return -1;                              // 已经搜索了设备列表全部数据，找不到
}


int8_t __NextSpecialDeviceList()
{
    static uint8_t index = 0;
    
    uint8_t tmpIndex = index;           // 保存index历史值, 用于分成[index, 50], [0, index]两个区间来搜索
    
    // 查询[index, NormalDeviceListSum]区间的有效设备列表
    //
    for (; index < SpecialDeviceListSum; index++)
    {
        if (SpecialDeviceList[index].deviceValidFlag)
        {
            return index++;                 // 返回有效的设备列表数据的下标
        }
    }
    
    // 如果[index, NormalDeviceListSum]找不到，那么查询[0, index]区间的有效设备列表
    //
    for (index = 0; index < tmpIndex; index++)
    {
        if (SpecialDeviceList[index].deviceValidFlag)
        {
            return index++;                 // 返回有效的设备列表数据的下标
        }
    }
    
    return -1;                              // 已经搜索了设备列表全部数据，找不到
}


void __SendDataToNormalDevice(int8_t deviceListIndex)
{
    uint16_t	tmpParityValue = 0;
    
    // 如果检查到失败次数大于一定次数，那么就切换路由（主路由和备份路由）
    //
    if (NormalDeviceList[deviceListIndex].deviceFailTimes > 150)
    {
        NormalDeviceList[deviceListIndex].usingDeviceRouteNow = !(NormalDeviceList[deviceListIndex].usingDeviceRouteNow);
        
        NormalDeviceList[deviceListIndex].deviceFailTimes = 0;
			
		NormalDeviceList[deviceListIndex].deviceOnline = 0;
    }
    
    // --------------  开始执行轮询指令  -----------------
    //
    // 设备编号
    //
    NRF905_SendBuffer[0] = NormalDeviceList[deviceListIndex].deviceNumber[0];
    
    NRF905_SendBuffer[1] = NormalDeviceList[deviceListIndex].deviceNumber[1];
    
    
    // 保存当前轮询的设备类型
    //
    DevicePool_DeviceType = NormalDeviceList[deviceListIndex].deviceType;
    
    
    // 命令编号
    //
    NRF905_SendBuffer[2] = 0x01;
    
    // 命令流水
    //
    NRF905_SendBuffer[3] = DeviceDataSerialNo++;
    
    // 使用备份路由
    //
    if (NormalDeviceList[deviceListIndex].usingDeviceRouteNow)
    {
        NRF905_SendBuffer[4] = NormalDeviceList[deviceListIndex].deviceBakRoute[0];       // 目的中继
        
        
        NRF905_SendBuffer[5] = NormalDeviceList[deviceListIndex].deviceBakRoute[0];       // 中继1
        
        
        NRF905_SendBuffer[6] = NormalDeviceList[deviceListIndex].deviceBakRoute[1];       // 中继2
        
        
        NRF905_SendBuffer[7] = NormalDeviceList[deviceListIndex].deviceBakRoute[2];       // 中继3
    }
    // 使用主路由
    //
    else
    {
        NRF905_SendBuffer[4] = NormalDeviceList[deviceListIndex].deviceMainRoute[0];       // 目的中继
        
        
        NRF905_SendBuffer[5] = NormalDeviceList[deviceListIndex].deviceMainRoute[0];       // 中继1
        
        
        NRF905_SendBuffer[6] = NormalDeviceList[deviceListIndex].deviceMainRoute[1];       // 中继2
        
        
        NRF905_SendBuffer[7] = NormalDeviceList[deviceListIndex].deviceMainRoute[2];       // 中继3
    }
    
    // 填充字符
    //
    NRF905_SendBuffer[8] = 0xF1;
    
    // 设备编号
    //
    NRF905_SendBuffer[9] = NRF905_SendBuffer[0];
    
    NRF905_SendBuffer[10] = NRF905_SendBuffer[1];
    
    // 设备类型
    //
    NRF905_SendBuffer[11] = NormalDeviceList[deviceListIndex].deviceType;
    
    // 无线信道
    //
    NRF905_SendBuffer[12] = App_Hal_Api.wireless->channelNo;
    
    // 秒\分\时\日\星期\月\年
    //
    NRF905_SendBuffer[13] = BCD(SysTime.second);
    
    NRF905_SendBuffer[14] = BCD(SysTime.minute);
    
    NRF905_SendBuffer[15] = BCD(SysTime.hour);
    
    NRF905_SendBuffer[16] = BCD(SysTime.day);
    
    NRF905_SendBuffer[17] = BCD(SysTime.week);
    
    NRF905_SendBuffer[18] = BCD(SysTime.month);
    
    NRF905_SendBuffer[19] = BCD(SysTime.year);
    
    // 内部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer + 8, 12);
    NRF905_SendBuffer[20] = tmpParityValue;
    NRF905_SendBuffer[21] = tmpParityValue >> 8;
    
    // 填充字符0xF1
    //
    memset(NRF905_SendBuffer + 22, 0xF1, 8);
    
    // 外部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[Enum_Wirelss_ParityL] = tmpParityValue;
    NRF905_SendBuffer[Enum_Wirelss_ParityH] = tmpParityValue >> 8;
    
    // 发送轮询指令
    //
	App_Hal_Api.wireless->write(NRF905_SendBuffer);
    
	
	// 根据中继来设置无线发送等待超时时间
	//
	Pca_Start(NRF905_SendBuffer, 0);
    
    // 轮询失败计数自增，到达一定数量，会切换主副路由；如果有轮询应答，那么清零，轮询应答逻辑在Command_OneCardDataUpload.c中
    //
    NormalDeviceList[deviceListIndex].deviceFailTimes++;
}


void __SendDataToSpecialDevice(int8_t deviceListIndex)
{
    uint16_t   parityValue;
    
    uint8_t   i;
    
    // --------------  开始执行轮询指令  -----------------
    //
    // 设备编号
    //
    NRF905_SendBuffer[0] = SpecialDeviceList[deviceListIndex].deviceNumber[0];
    
    NRF905_SendBuffer[1] = SpecialDeviceList[deviceListIndex].deviceNumber[1];
    
    
    // 命令编号
    //
    NRF905_SendBuffer[2] = 0x01;
    
    
    // 命令流水
    //
    NRF905_SendBuffer[3] = DeviceDataSerialNo++;
  
    
    NRF905_SendBuffer[4] = SpecialDeviceList[deviceListIndex].deviceMainRoute[0];       // 目的中继
    
    
    NRF905_SendBuffer[5] = SpecialDeviceList[deviceListIndex].deviceMainRoute[0];       // 中继1
    
    
    NRF905_SendBuffer[6] = SpecialDeviceList[deviceListIndex].deviceMainRoute[1];       // 中继2
    
    
    NRF905_SendBuffer[7] = SpecialDeviceList[deviceListIndex].deviceMainRoute[2];       // 中继3
    
    // 填充字符
    //
    NRF905_SendBuffer[8] = 0xF1;
    
    // 设备编号
    //
    NRF905_SendBuffer[9] = NRF905_SendBuffer[0];
    
    NRF905_SendBuffer[10] = NRF905_SendBuffer[1];
    
    // 设备类型
    //
    NRF905_SendBuffer[11] = 22;                                                         // 电子门锁
    
    
    // 保存当前轮询的设备类型
    //
    DevicePool_DeviceType = 22;
    
    // 无线信道
    //
    NRF905_SendBuffer[12] = App_Hal_Api.wireless->channelNo;
    
    // 秒\分\时\日\星期\月\年
    //
    NRF905_SendBuffer[13] = BCD(SysTime.second);
    
    NRF905_SendBuffer[14] = BCD(SysTime.minute);
    
    NRF905_SendBuffer[15] = BCD(SysTime.hour);
    
    NRF905_SendBuffer[16] = BCD(SysTime.day);
    
    NRF905_SendBuffer[17] = BCD(SysTime.week);
    
    NRF905_SendBuffer[18] = BCD(SysTime.month);
    
    NRF905_SendBuffer[19] = BCD(SysTime.year);
    
    // 填充字符0xF1
    //
    memset(NRF905_SendBuffer + 20, 0xF1, 10);
    
    parityValue = 0;
    
    for (i = Enum_Wirelss_DataStart; i < Enum_Wirelss_DataStart + 12; ++i)
    {
        parityValue += NRF905_SendBuffer[i];
    }
    NRF905_SendBuffer[Enum_Wirelss_DataStart + 12] = parityValue;
    NRF905_SendBuffer[Enum_Wirelss_DataStart + 13] = parityValue >> 8;
    
    
    // 和校验
    //
    parityValue = 0;
    
    for (i = 0; i < 30; ++i)
    {
        parityValue += NRF905_SendBuffer[i];
    }
    
    NRF905_SendBuffer[Enum_Wirelss_ParityL] = parityValue;
    
    NRF905_SendBuffer[Enum_Wirelss_ParityH] = parityValue >> 8;
    
    // 发送轮询指令
    //
	App_Hal_Api.wireless->write(NRF905_SendBuffer);
	
	if (NRF905_SendBuffer[4])
	{
		SpecialDeviceList[deviceListIndex].deviceValidFlag = 0;
		
		Pca_SubStart(3000, 0);						// 等待15秒
	}
	else
	{
		Pca_Start(NRF905_SendBuffer, 0);			// 根据中继来设置无线发送等待超时时间
	}
}



// 函数：轮询发送
// 参数：interval表示：多少秒，轮询发送一次
//
bool DevicePool_SendDataToDevice(void)
{
    int8_t   DevicePool_SpecialDeviceListIndex;      // 正在轮询的特殊设备列表下标
    
    int8_t   DevicePool_NormalDeviceListIndex;       // 正在轮询的普通设备列表的下标
    
    
    // -------------- 优先轮询特殊列表的设备 --------------
    //
    DevicePool_SpecialDeviceListIndex = __NextSpecialDeviceList();
    
    if (DevicePool_SpecialDeviceListIndex != -1)
    {
        __SendDataToSpecialDevice(DevicePool_SpecialDeviceListIndex);
        
        return 1;
    }
    
    // -------------- 次优轮询普通列表的设备 --------------
    //
    DevicePool_NormalDeviceListIndex = __NextNormalDeviceList();
    
    if (DevicePool_NormalDeviceListIndex != -1)
    {
        __SendDataToNormalDevice(DevicePool_NormalDeviceListIndex);
		
		return 1;
    }
	
	return 0;
}








