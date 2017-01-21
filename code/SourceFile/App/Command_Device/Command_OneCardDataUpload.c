#include "Command_OneCardDataUpload.h"


void OneCardDataUpload_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[Enum_Wirelss_DeviceNoL];
    
    uint8_t tmpDeviceNoH        = Data[Enum_Wirelss_DeviceNoH];
    
    uint8_t tmpCommandNo        = Data[Enum_Wirelss_CommandNo];      // 轮询应答包有两种：实时数据 - 0xF0, 脱机数据 - 0xF1
    
    uint8_t tmpCommandSerialNo  = Data[Enum_Wirelss_CommandSerialNo];
    
    uint8_t tmpRepeater1        = Data[Enum_Wirelss_Repeater1];
    
    uint8_t tmpRepeater2        = Data[Enum_Wirelss_Repeater2];
    
    uint8_t  tmpRepeater3        = Data[Enum_Wirelss_Repeater3];
    
    uint8_t tmpTradeType        = Data[Enum_Wirelss_DataStart];
    
    int8_t  findDeviceList      = -1;                                // 初始化未查找失败
    
    
    // 1.如果设备轮询应答包中有数据(没有数据的条件：如果是实时数据， 并且交易类型是88; 或者是标准版脱机数据(门锁除外)，并且开始物理地址和结束物理地址一样),那么就上报给PC
    //
    if ( !((0xE0 == tmpCommandNo && 0x88 == tmpTradeType) || 
		 (0x02 == tmpCommandNo && 22 != DevicePool_DeviceType && !memcmp(Data + 12, Data + 15, 3) && Data[9] == 0)) )
    {
        // 设备编号
        //
        SocketData_SendBuffer[0] = tmpDeviceNoL;
        
        SocketData_SendBuffer[1] = tmpDeviceNoH;
        
        // 设备类型
        //
        SocketData_SendBuffer[2] = DevicePool_DeviceType;
        
        // 中继123
        //
        SocketData_SendBuffer[3] = tmpRepeater1;
        
        SocketData_SendBuffer[4] = tmpRepeater2;
        
        SocketData_SendBuffer[5] = tmpRepeater3;
        
        // 数据类型(0xE0:实时数据， 0xE2：脱机数据)
        //
        if (0xE0 == tmpCommandNo)                       // 实时数据
        {
            SocketData_SendBuffer[6] = 0x31;
        }
        else if (0xE2 == tmpCommandNo)                  // 脱机数据
        {
            
            SocketData_SendBuffer[6] = 0x32;
        }
        else if (0x02 == tmpCommandNo)                  // 标准版的脱机数据
        {
            SocketData_SendBuffer[6] = 0x33;
        }
        else
        {
            SocketData_SendBuffer[6] = 0x34;
        }
        
        // 复制主要数据(22字节)
        //
        memcpy(SocketData_SendBuffer + 7, Data + Enum_Wirelss_DataStart, 22);
        
            
        // 发送数据上报包给PC
        //
        PC_SendCommand(0xF0, tmpCommandSerialNo, SocketData_SendBuffer,  29);
    }
    
    
    // 2. 根据设备类型来区别对待普通设备（实时消费机等）和特殊设备（无线门锁）
    //
    // 特殊设备
    //
    if (22 == DevicePool_DeviceType)
    {
        findDeviceList = SpecialDeviceInfo_FindDeviceList(tmpDeviceNoL, tmpDeviceNoH);
        
        if (findDeviceList != -1)
        {
            // 轮询应答成功，删除特殊设备列表的设备
            //
            SpecialDeviceList[findDeviceList].deviceValidFlag = 0;
			
			if (SpecialDeviceListUsage > 0)
			{
				SpecialDeviceListUsage--;
			}
        }
    }
    // 普通设备
    //
    else
    {
        // 3.查找设备列表中设备路由配置信息
        //
        findDeviceList = NormalDeviceInfo_FindDeviceList(tmpDeviceNoL, tmpDeviceNoH, DevicePool_DeviceType);
    
        if (findDeviceList != -1)
        {
            // 轮询应答成功，那么轮询失败次数清零
            //
            NormalDeviceList[findDeviceList].deviceFailTimes = 0;
                
            // 在线设备，设置设备状态为在线
            //
            NormalDeviceList[findDeviceList].deviceOnline = 1;
        }
    }
}





