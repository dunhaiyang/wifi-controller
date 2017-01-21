#include "Command_ControlerDeviceList.h"


void ControlerDeviceList_DealData(uint8_t *Data)
{
    bool   tmpSuccess = 1;
    
    uint8_t i;
    
    uint8_t tmpSerialNo = Data[1];
    
    
    // 模式： 0x31->添加， 0x32->删除， 0x33->覆盖
    //
    uint8_t operateMode = Data[Enum_CommandContent + 0];
    
    
    // 获取设备数量
    //
    uint8_t deviceQuantity = Data[Enum_CommandContent + 1];
    
    
    // 获取设备列表数据
    //
    switch (operateMode)
    {
        // 覆盖普通设备列表模式
        //
        case 0x33:
            NormalDeviceInfo_EmptyDeviceList();      // 注意，这里没有break
        
        
        // 增加普通设备列表模式
        //
        case 0x31:
            // 没有足够的空间存储设备列表数据
            //
            if (NormalDeviceInfo_HowManySpace() < deviceQuantity)
            {
                tmpSuccess = 0;
                
                break;
            }
            // 添加所有设备列表数据
            //
            for (i = Enum_CommandContent + 2; deviceQuantity > 0; i += 9)
            {
                NormalDeviceInfo_AddDeviceList(Data + i);
                
                --deviceQuantity;
            }
            break;
            
        
        // 删除普通设备列表模式
        //
        case 0x32:
            for (i = Enum_CommandContent + 2; deviceQuantity > 0; i += 9)
            {
                NormalDeviceInfo_DeleteDeviceList(Data + i);
                
                --deviceQuantity;
            }
            break;
            
            
        // 覆盖门锁特殊设备列表模式
        //
        case 0x36:
            SpecialDeviceInfo_EmptyDeviceList();
            
        
        // 增加门锁特殊设备列表模式
        //
        case 0x34:
			// 没有足够的空间存储设备列表数据
            //
            if (SpecialDeviceInfo_HowManySpace() < deviceQuantity)
            {
                tmpSuccess = 0;
                
                break;
            }
            // 添加所有设备列表数据
            //
            for (i = Enum_CommandContent + 2; deviceQuantity > 0; i += 9)
            {
                SpecialDeviceInfo_AddDeviceList(Data + i);
                
                --deviceQuantity;
            }
            break;
        
        // 删除门锁特殊设备列表模式
        //
        case 0x35:
            for (i = Enum_CommandContent + 2; deviceQuantity > 0; i += 9)
            {
                SpecialDeviceInfo_DeleteDeviceList(Data + i);
                
                --deviceQuantity;
            }
            break;
        
        default:            // 不能存在的模式
            tmpSuccess = 0;
            break;
    }
    
    // 设置应答包数据
    //
    if (operateMode >= 0x34)
    {
        SocketData_SendBuffer[0] = SpecialDeviceInfo_HowManySpace();
    }
    else
    {
        SocketData_SendBuffer[0] = NormalDeviceInfo_HowManySpace();
    }
    SocketData_SendBuffer[1] = tmpSuccess? 0x31:0x32;
    
    // 发送给PC, Data是完整的数据包：命令号+命令流水号+命令内容长度+命令内容+异或校验
    //
    PC_SendCommand(0x70, tmpSerialNo, SocketData_SendBuffer, 2);
}








