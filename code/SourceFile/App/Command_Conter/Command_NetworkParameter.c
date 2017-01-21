#include "Command_NetworkParameter.h"


void NetworkParameter_SendDataToPC(uint8_t *Data)
{
	uint8_t tmpSerialNo = Data[1];
	
	// 先验证密码
	//
	if (memcmp(Data + 39, ControlerInfo.Password, 6))
	{
		BoardcastData_SendBuffer[0] = 0x32;
		
		PC_SendCommand_Boardcast(0x64, tmpSerialNo, BoardcastData_SendBuffer, 1);
		
		return;
	}
	
	// 密码通过
	//
	ControlerInfo.FirstBootup = 0x31;				// 设置为首次开机
	
	memcpy(ControlerInfo.Name, Data + 9, 10);
	
	memcpy(NETPARA_IP, Data + 19, 4);
	
	memcpy(NETPARA_MASK, Data + 23, 4);
	
	memcpy(NETPARA_GATEWAY, Data + 27, 4);
	
	memcpy(&SOCKET0_LOCALPORT, Data + 31, 2);
	
	memcpy(SOCKET0_REMOTEIP, Data + 33, 4);
	
	memcpy(&SOCKET0_REMOTEPORT, Data + 37, 2);
	
	memcpy(ControlerInfo.Password, Data + 45, 6);
	
	memcpy(ControlerInfo.Info, Data + 51, 10);
	
	// 应答
	//
	BoardcastData_SendBuffer[0] = 0x31;
	
    PC_SendCommand_Boardcast(0x64, tmpSerialNo, BoardcastData_SendBuffer, 1);
	
	//保存配置信息
	//
	ControlerInfo_WriteName();
	
	ControlerInfo_WriteNetworkParameter();
	
	// 重启
	//
//	IAP_CONTR |= 0x60;

#ifdef USING_MODULE_NETWORK
	App_Hal_Api.network->reboot();
#endif
}


