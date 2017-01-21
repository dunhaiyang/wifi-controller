#include "Command_Network.h"


void Network_DealControlData(uint8_t *command)
{
    // 处理PC发送过来的指令
    //
    switch (command[Enum_CommandNo])
    {
        case 0x03:          // 读取一条脱机数据
            ReadOneOfflineData_DealData(command);
            break;
        
        case 0x05:          // 删除一条脱机数据
            DeleteOneOfflineData_DealData(command);
            break;
        
        case 0x07:          // 删除某个区间的脱机数据
            DeleteSomeAreaData_DealData(command);
            break;
        
        case 0x09:          // 数据结构恢复到出厂状态
            RestoreDataStructure_DealData(command);
            break;
        
        case 0x0B:			// 序列号巡查与配置
            SerialNoWatchAndConfigure_DealData(command);
            break;
        
        case 0x0D:          // 修改设备序列号
            ChangeDeviceSerialNo_DealData(command);
            break;
        
        case 0x0F:          // 初始化白名单
            WhiteListInit_DealData(command);
            break;
        
        case 0x11:          // 上传白名单
            WhiteListUpload_DealData(command);
            break;
        
        case 0x13:          // 远程控制指令
            RealtimeControl_DealData(command);
            break;
        
        case 0x14:          // 现场控制指令
            WhiteListUpload_DealData(command);
            break;
        
        case 0x15:          // 读取指针名单区的指针
            ReadWhiteListPointer_DealData(command);
            break;
		
		case 0x17:			// 读取白名单
            ReadWhiteList_DealData(command);
            break;
        
        case 0x19:          // 读写配置参数
            ReadWriteConfigureParameter_DealData(command);
            break;
        
        case 0x1B:          // 读取所有交易流水
            ReadAllTradeRecord_DealData(command);
            break;
		
		case 0x1D:			// 远程升级
			ProgramUpdate_DealData(command);
			break;
        
        case 0x31:          // 回复到出厂状态
            RestoreDefaultConfigure_DealData(command);
            break;
            break;
		
		case 0x61:			// 搜索IP
			SearchIp_SendDataToPC(command);
			break;
		
		case 0x63:			// 网络参数配置
			NetworkParameter_SendDataToPC(command);
			break;
        
        case 0x65:          // 控制器通讯测试命令
            ControlerTest_SendDataToPC(command);
            break;
        
        case 0x67:          // 中继器通讯测试
            RepeaterTest_DealData(command);
            break;
        
        case 0x69:          // 控制器参数配置
            ControlerParameter_DealData(command);
            break;
        
        case 0x6B:          // 中继器参数配置
            RepeaterParameter_DealData(command);
            break;
        
        case 0x6D:          // 设备通讯测试
            DeviceTest_DealData(command);
            break;
        
        case 0x6F:          // 控制器的设备列表配置
            ControlerDeviceList_DealData(command);
            break;
        
        case 0x72:          // 心跳应答包
            Heartbeat_DealData(command);
            break;
        
        case 0x73:          // 控制器工作模式控制
            ControlerWorkMode_DealData(command);
            break;
        
        case 0xF1:          // 一卡通设备数据应答(PC请求删除数据)
            OneCardDataUploadDelete_DealData(command);
            break;
        
        case 0xF3:          // 一卡通设备操作指令
            OneCardOperation_DealData(command);
//			printf("333\r\n");
            break;
        
        default:            // 无法识别的指令
            break;
    }
}











