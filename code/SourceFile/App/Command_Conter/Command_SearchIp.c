#include "Command_SearchIp.h"


void SearchIp_SendDataToPC(uint8_t *Data)
{
    uint8_t tmpSerialNo = Data[1];
	
	memcpy(BoardcastData_SendBuffer + 0, ControlerInfo.Version, 3);
	
	memcpy(BoardcastData_SendBuffer + 3, ControlerInfo.Name, 10);
	
	memcpy(BoardcastData_SendBuffer + 13, NETPARA_MAC, 6);
	
	memcpy(BoardcastData_SendBuffer + 19, NETPARA_IP, 4);
	
	memcpy(BoardcastData_SendBuffer + 23, NETPARA_MASK, 4);
	
	memcpy(BoardcastData_SendBuffer + 27, NETPARA_GATEWAY, 4);
	
	memcpy(BoardcastData_SendBuffer + 31, &SOCKET0_LOCALPORT, 2);
	
	memcpy(BoardcastData_SendBuffer + 33, SOCKET0_REMOTEIP, 4);
	
	memcpy(BoardcastData_SendBuffer + 37, &(SOCKET0_REMOTEPORT), 2);
	
	memcpy(BoardcastData_SendBuffer + 39, ControlerInfo.Info, 10);
	
	//
    PC_SendCommand_Boardcast(0x62, tmpSerialNo, BoardcastData_SendBuffer, 49);
}









