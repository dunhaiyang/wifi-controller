#include "Pc.h"


uint8_t NRF905_SendBuffer[32];


bool Wireless_CheckCommand(uint8_t *command)
{
    uint8_t   	i;
    uint16_t    parityValue = 0;
    
    // 计算和校验值
    //
    for (i = 0; i < COM_CHECKSUM_L; ++i)
    {
        parityValue += command[i];
    }
    
    if(((parityValue >> 8) == command[COM_CHECKSUM_H]) && ((parityValue & 0xFF) == command[COM_CHECKSUM_L]))
    {
        if( ((command[CMD_NAME] % 2) == 0) && (command[AIM_RELAY] == 0))   //应答命令,并且目的中继为0
        {
            return 1;
        }
    }
    return 0;
}


bool PC_CheckCommand(uint8_t *command, uint16_t commandLen)
{
    uint8_t		i;
    uint16_t	sumParityValue = 0;
    uint8_t		tmpLen = command[2] + 5;
    
    
    // 数据字节数量是否合法, 已经去掉包头，包尾以及转义字符0x10, 命令号（1）+命令流水号（1）+命令内容长度（1）+ 命令内容（N) +异或校验字（1）
    //
    if (tmpLen != commandLen)
    {
        // 打印和校验，用于调试
//		#ifdef  Uart1_Debug
//			Uart1_SendByte(tmpLen); Uart1_SendByte(Uart2_RxBufCount); Uart1_SendByte(0xDD); Uart1_SendByte(0xDD);
//		#endif
		
//		printf("tmpLen: %u, commandLen: %u\r\n", tmpLen, commandLen);
        
        return 0;
    }
    
    // 和校验
    //
    for (i = 0; i < tmpLen - 2; ++i)
    {
        sumParityValue += command[i];
    }
    
    // 打印和校验，用于调试
//	#ifdef  Uart1_Debug
//		Uart1_SendByte(sumParityValue); Uart1_SendByte(sumParityValue >> 8);
//	#endif
    
    if ((sumParityValue & 0xFF) != command[tmpLen - 2] || (sumParityValue >> 8) != command[tmpLen - 1])
    {
//		#ifdef  Uart1_Debug
//			Uart1_SendByte(0xEE);Uart1_SendByte(0xEE);
//		#endif
		
//		printf("sumParityValue: %u\r\n", sumParityValue);
        
        return 0;
    }
    
//    // 打印和校验，用于调试
//	#ifdef  Uart1_Debug
//		Uart1_SendByte(0xFF); Uart1_SendByte(0xFF);
//	#endif
    
    
    return 1;
}


void PC_SendCommand(uint8_t commandNo, uint8_t commandSerialNo, uint8_t *commandContent, uint8_t commandContentLen)
{
    uint8_t   i;
    uint16_t  parityValue = 0;
    uint8_t   tmpParityValueL;
    uint8_t   tmpParityValueH;
	uint8_t   tmpSendBufferLen = 0;
    
    // 发送包头：0x02
    //
	__SocketData_SendBuffer[tmpSendBufferLen++] = 0x02;
    
    
    // 发送命令号
    //
    if (commandNo == 0x02 || commandNo == 0x03 || commandNo == 0x10)
    {
		__SocketData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__SocketData_SendBuffer[tmpSendBufferLen++] = commandNo;
    
    // 发送命令流水号
    //
    if (commandSerialNo == 0x02 || commandSerialNo == 0x03 || commandSerialNo == 0x10)
    {
		__SocketData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__SocketData_SendBuffer[tmpSendBufferLen++] = commandSerialNo;
    
    
    // 发送命令长度
    //
    if (commandContentLen == 0x02 || commandContentLen == 0x03 || commandContentLen == 0x10)
    {
		__SocketData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__SocketData_SendBuffer[tmpSendBufferLen++] = commandContentLen;
    
    
    // 发送命令内容, 除了转义字符总共32字节
    //
    parityValue += commandNo;
    parityValue += commandSerialNo;
    parityValue += commandContentLen;
    
    for (i = 0; i < commandContentLen; ++i)
    {
        if (commandContent[i] == 0x02 || commandContent[i] == 0x03 || commandContent[i] == 0x10)
        {
			__SocketData_SendBuffer[tmpSendBufferLen++] = 0x10;
        }
		__SocketData_SendBuffer[tmpSendBufferLen++] = commandContent[i];
        
        parityValue += commandContent[i];
    }
    
    // 发送校验字(低位前，高位后)
    //
    tmpParityValueL = parityValue;
    
    if (tmpParityValueL == 0x02 || tmpParityValueL == 0x03 || tmpParityValueL == 0x10)
    {
		__SocketData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__SocketData_SendBuffer[tmpSendBufferLen++] = tmpParityValueL;
    
    tmpParityValueH = parityValue >> 8;
    
    if (tmpParityValueH == 0x02 || tmpParityValueH == 0x03 || tmpParityValueH == 0x10)
    {
		__SocketData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__SocketData_SendBuffer[tmpSendBufferLen++] = tmpParityValueH;
    
    
    // 发送包尾
    //
	__SocketData_SendBuffer[tmpSendBufferLen++] = 0x03;

#ifdef	USING_MODULE_WIFI
	
	App_Hal_Api.wifi->write(__SocketData_SendBuffer, tmpSendBufferLen);
	
#endif
	
#ifdef	USING_MODULE_NETWORK
	
	App_Hal_Api.network->writeUdp(__SocketData_SendBuffer, tmpSendBufferLen);
	
#endif
}


void PC_SendCommand_Boardcast(uint8_t commandNo, uint8_t commandSerialNo, uint8_t *commandContent, uint8_t commandContentLen)
{
    uint8_t   i;
    uint16_t  parityValue = 0;
    uint8_t   tmpParityValueL;
    uint8_t   tmpParityValueH;
	uint8_t   tmpSendBufferLen = 0;
    
    // 发送包头：0x02
    //
	__BoardcastData_SendBuffer[tmpSendBufferLen++] = 0x02;
    
    
    // 发送命令号
    //
    if (commandNo == 0x02 || commandNo == 0x03 || commandNo == 0x10)
    {
		__BoardcastData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__BoardcastData_SendBuffer[tmpSendBufferLen++] = commandNo;
    
    // 发送命令流水号
    //
    if (commandSerialNo == 0x02 || commandSerialNo == 0x03 || commandSerialNo == 0x10)
    {
		__BoardcastData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__BoardcastData_SendBuffer[tmpSendBufferLen++] = commandSerialNo;
    
    
    // 发送命令长度
    //
    if (commandContentLen == 0x02 || commandContentLen == 0x03 || commandContentLen == 0x10)
    {
		__BoardcastData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__BoardcastData_SendBuffer[tmpSendBufferLen++] = commandContentLen;
    
    
    // 发送命令内容, 除了转义字符总共32字节
    //
    parityValue += commandNo;
    parityValue += commandSerialNo;
    parityValue += commandContentLen;
    
    for (i = 0; i < commandContentLen; ++i)
    {
        if (commandContent[i] == 0x02 || commandContent[i] == 0x03 || commandContent[i] == 0x10)
        {
			__BoardcastData_SendBuffer[tmpSendBufferLen++] = 0x10;
        }
		__BoardcastData_SendBuffer[tmpSendBufferLen++] = commandContent[i];
        
        parityValue += commandContent[i];
    }
    
    // 发送校验字(低位前，高位后)
    //
    tmpParityValueL = parityValue;
    
    if (tmpParityValueL == 0x02 || tmpParityValueL == 0x03 || tmpParityValueL == 0x10)
    {
		__BoardcastData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__BoardcastData_SendBuffer[tmpSendBufferLen++] = tmpParityValueL;
    
    tmpParityValueH = parityValue >> 8;
    
    if (tmpParityValueH == 0x02 || tmpParityValueH == 0x03 || tmpParityValueH == 0x10)
    {
		__BoardcastData_SendBuffer[tmpSendBufferLen++] = 0x10;
    }
	__BoardcastData_SendBuffer[tmpSendBufferLen++] = tmpParityValueH;
    
    
    // 发送包尾
    //
	__BoardcastData_SendBuffer[tmpSendBufferLen++] = 0x03;

#ifdef	USING_MODULE_NETWORK
	
	App_Hal_Api.network->writeBoardcast(__BoardcastData_SendBuffer, tmpSendBufferLen);
	
#endif
}











