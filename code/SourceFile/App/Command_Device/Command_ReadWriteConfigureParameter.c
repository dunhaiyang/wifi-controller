#include "Command_ReadWriteConfigureParameter.h"


uint8_t ReadWriteConfigureParameter_DeviceType = 0xFF;


void ReadWriteConfigureParameter_DealData(uint8_t *Data)
{
    uint8_t tmpCommandNo        = Data[0];
    
    uint8_t tmpCommandSerialNo  = Data[1];
    
    uint8_t tmpDeviceNoL        = Data[3];
    
    uint8_t tmpDeviceNoH        = Data[4];
    
    uint8_t tmpDeviceType       = Data[5];
    
    uint8_t tmpRepeater1        = Data[6];
    
    uint8_t tmpRepeater2        = Data[7];
    
    uint8_t tmpRepeater3        = Data[8];
    
    uint8_t tmpParameterNo      = Data[9];
    
    uint8_t tmpReadWriteFlag    = Data[10];
    
    uint8_t tmpWriteLen         = Data[11];
    
    uint16_t tmpParityValue       = 0;
    
    // 保存设备类型，在应答包中使用
    //
    ReadWriteConfigureParameter_DeviceType = tmpDeviceType;
    
    // 设备编号
    //
    NRF905_SendBuffer[0] = tmpDeviceNoL;
    NRF905_SendBuffer[1] = tmpDeviceNoH;
    
    // 命令编号
    //
    NRF905_SendBuffer[2] = tmpCommandNo;
    
    // 命令流水号
    //
    NRF905_SendBuffer[3] = tmpCommandSerialNo;
    
    // 目的中继
    //
    NRF905_SendBuffer[4] = tmpRepeater1;
    NRF905_SendBuffer[5] = tmpRepeater1;
    NRF905_SendBuffer[6] = tmpRepeater2;
    NRF905_SendBuffer[7] = tmpRepeater3;
    
    // 数据（22字节）
    //
    NRF905_SendBuffer[8] = 0xEB;
    NRF905_SendBuffer[9] = tmpDeviceNoL;
    NRF905_SendBuffer[10] = tmpDeviceNoH;
    NRF905_SendBuffer[11] = tmpDeviceType;
    NRF905_SendBuffer[12] = tmpParameterNo;                                     // 参数编号
    NRF905_SendBuffer[13] = tmpWriteLen;                                        // 参数长度
    if (tmpReadWriteFlag)                                                       // 读写标志： 0 - 读， 1 - 写
    {
        NRF905_SendBuffer[13] |= 0x80;
        
        memcpy(NRF905_SendBuffer + 14, Data + 12, tmpWriteLen);
    }
    else
    {
        NRF905_SendBuffer[13] &= 0x7F;
        
        memset(NRF905_SendBuffer + 14, 0xEB, 16);
    }
    
    // 外部和校验
    //
    tmpParityValue = Temporary_CalcSumParity(NRF905_SendBuffer, 30);
    NRF905_SendBuffer[30] = tmpParityValue;
    NRF905_SendBuffer[31] = tmpParityValue >> 8;
    
    // 发送数据到无线设备
    //
//    Wireless_SendDataToDevice(NRF905_SendBuffer);
	
	// 根据中继来设置无线发送等待超时时间
	//
	Pca_Start(NRF905_SendBuffer, 0);
}


void ReadWriteConfigureParameter_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpDeviceNoL        = Data[0];
    
    uint8_t tmpDeviceNoH        = Data[1];
    
    uint8_t tmpCommandNo        = Data[2];
    
    uint8_t tmpCommandSerialNo  = Data[3];
    
    uint8_t tmpReadWriteResult  = Data[8];
    
    uint8_t tmpParameterNo      = Data[12];
    
    uint8_t tmpRWParameterLen   = Data[13];
    
    uint8_t tmpCommandContentLen;
    
    // 设备编号
    //
    SocketData_SendBuffer[0] = tmpDeviceNoL;
    SocketData_SendBuffer[1] = tmpDeviceNoH;
    
    // 设备类型
    //
    SocketData_SendBuffer[2] = ReadWriteConfigureParameter_DeviceType;
    
    // 参数编号
    //
    SocketData_SendBuffer[3] = tmpParameterNo;
    
    // 读写标志位
    //
    SocketData_SendBuffer[4] = ((tmpRWParameterLen & 0x80)? 0x01:0x00);
    
    // 读写结果
    //
    SocketData_SendBuffer[5] = tmpReadWriteResult;
    
    // 计算总共需要发送多少字节(设备编号, 设备类型, 参数编号, 读写标志位, 读写结果)
    //
    tmpCommandContentLen = 6;
    
    // 如果是读，那么就有数据
    //
    if (!SocketData_SendBuffer[4])
    {
        SocketData_SendBuffer[6] = tmpRWParameterLen & 0x7F;                        // 读参数长度
        
        memcpy(SocketData_SendBuffer + 7, Data + 14, SocketData_SendBuffer[6]);             // 读参数的数据
        
        tmpCommandContentLen += (SocketData_SendBuffer[6] + 1);                     // 要计算上读参数的字节数
    }
    
    // 发送中继器测试包给PC
    //
    PC_SendCommand(0x1A, tmpCommandSerialNo, SocketData_SendBuffer, tmpCommandContentLen);
}





