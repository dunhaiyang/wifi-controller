#include "Command_Wireless.h"



void Wireless_DealControlData(uint8_t *command)
{
    switch (command[Enum_Wirelss_CommandNo])
    {
        case 0x04:   // 读取一条脱机数据
            ReadOneOfflineData_SendDataToPC(command);
            break;
        
        case 0x06:   // 删除一条脱机数据
            DeleteOneOfflineData_SendDataToPC(command);
            break;  
        
        case 0x08:   // 删除某个区间的脱机数据
            DeleteSomeAreaData_SendDataToPC(command);
            break;
        
        case 0x0A:   // 数据结构恢复到出厂状态
            RestoreDataStructure_SendDataToPC(command);
            break;
        
        case 0x0C:   // 序列号巡查与配置
            SerialNoWatchAndConfigure_SendDataToPC(command);
            break;
        
        case 0x0E:   // 修改设备序列号
            ChangeDeviceSerialNo_SendDataToPC(command);
            break;
        
        case 0x10:   // 初始化白名单
            WhiteListInit_SendDataToPC(command);
            break;
        
        case 0x12:   // 名单上传应答
            WhiteListUpload_SendDataToPC(command);
            break;
        
        case 0x14:   // 现场控制指令
            RealtimeControl_SendDataToPC(command);
            break;
        
        case 0x16:   // 读取指定名单区的指针
            ReadWhiteListPointer_SendDataToPC(command);
            break;
		
		case 0x18:	 // 读取白名单
			ReadWhiteList_SendDataToPC(command);
			break;
        
        case 0x1A:   // 读写配置参数
            ReadWriteConfigureParameter_SendDataToPC(command);
            break;
        
        case 0x1C:   // 读取所有交易流水
            ReadAllTradeRecord_SendDataToPC(command);
            break;
		
		case 0x1E:	 // 远程升级的程序
			ProgramUpdate_SendDataToPC(command);
			break;
        
        case 0x32:   // 恢复出厂状态应答
            RestoreDefaultConfigure_SendDataToPC(command);
            break;
        
        case 0x68:   // 中继器通讯测试应答
            RepeaterTest_SendDataToPC(command);
            break;
        
        case 0x6C:   // 中继器配置应答
            RepeaterParameter_SendDataToPC(command);
            break;
        
        case 0x6E:   // 设备通讯测试应答
            DeviceTest_SendDataToPC(command);
            break;
        
        case 0xE0:   // 轮询应答（实时数据）
        case 0xE2:   // 轮询应答（脱机数据）
        case 0x02:   // 兼容一卡通标准版设备
            OneCardDataUpload_SendDataToPC(command);
//			printf("222\r\n");
            break;
        
        case 0xF2:   // 设备数据删除应答
            OneCardDataUploadDelete_SendDataToPC(command);
            break;
        
        case 0xF4:   // 一卡通设备操作指令应答
            OneCardOperation_SendDataToPC(command);
            break;
        
        default:     // 非法应答
            return;
    }
	App_Hal_Api.led->setTime(YELLOW_LED, 2);											// 亮黄灯
}



















