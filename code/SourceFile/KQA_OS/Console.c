#include "Console.h"


static Console *Console_self;


#define			CONSOLE_RECEIVE_MAX							50


struct ConsoleData
{
	uint8_t	console_needPrompt:1;							// 需要打印提示符	
	
	uint8_t	console_ReceiveBufferLen:7;						// 伪终端缓存指令数据数量
	
	uint8_t console_ReceiveBuffer[CONSOLE_RECEIVE_MAX];		// 伪终端缓存指令数据
	
}Console_ReceiveData;


struct ConsoleData consoleData = {1, 0};					// 初始化为需要打印提示符


// inputString和command假设都是带有伪零的字符串
//
bool __findCommand(uint8_t *inputCommand, uint8_t *memuCommand)
{
	// 比较inputCommand前面是否包含memuCommand
	//
	while (*memuCommand)
	{
		if (*inputCommand++ != *memuCommand++)
		{
			return 0;
		}
	}
	// 满足“command”或者“command argument1 ...”
	//
	if (*inputCommand == 0 || *inputCommand == ' ')
	{
		return 1;
	}
	return 0;
}


bool __containSubstring(uint8_t *inputCommand, uint8_t *memuCommand)
{
	while (*inputCommand)
	{
		if (*inputCommand++ != *memuCommand++)
		{
			return 0;
		}
	}
	return 1;
}


void Console_Run(void)
{
	// 首次进入终端，打印提示符
	//
	if (consoleData.console_needPrompt)
	{
		consoleData.console_needPrompt = 0;
		
		HAL_CONSOLE_SENDSTRING(Console_self->prompt);
	}
	
	// 获取终端数据
	//
	while (HAL_CONSOLE_AVAILABLE())
	{
		uint8_t index;
		
		uint8_t tmpData = Uart1_ReceiveByte();
		
		// return输入指令完毕
		//
		if ('\r' == tmpData || '\n' == tmpData)
		{
			consoleData.console_ReceiveBuffer[consoleData.console_ReceiveBufferLen++] = 0;
			
			HAL_CONSOLE_SENDSTRING("\r\n");
			
			// 处理指令
			//
			for (index = 0; index < Console_self->menuEntries; index++)
			{
				if (__findCommand(consoleData.console_ReceiveBuffer, Console_self->menu[index].command))
				{
//					printf("index: %u, len: %u\r\n", (uint16_t)index, (uint16_t)(consoleData.console_ReceiveBufferLen));
					
					Console_self->menu[index].func(consoleData.console_ReceiveBuffer);
					
					HAL_CONSOLE_SENDSTRING("\r\n");
					
					break;
				}
			}
			consoleData.console_needPrompt = 1;
			
			consoleData.console_ReceiveBufferLen = 0;
			
			return;
		}
		
		// tab 补全功能
		//
		if (0x09 == tmpData)
		{
			uint8_t	similarCommand = 0;								// 相似指令名称数量
			
			uint8_t	onlyOneCommand_Index = 0;						// 相似指令名称数量只有1个的索引
			
			consoleData.console_ReceiveBuffer[consoleData.console_ReceiveBufferLen] = 0;
			
			// 查找总共有多少个相似指令
			//
			for (index = 0; index < Console_self->menuEntries; index++)
			{
				if (__containSubstring(consoleData.console_ReceiveBuffer, Console_self->menu[index].command))
				{
					similarCommand++;
					
					onlyOneCommand_Index = index;
				}
			}
			
			// 相似指令数量大于两个
			//
			if (similarCommand >= 2)
			{
				HAL_CONSOLE_SENDSTRING("\r\n");
				
				for (index = 0; index < Console_self->menuEntries; index++)
				{
					if (strstr(Console_self->menu[index].command, consoleData.console_ReceiveBuffer))
					{
						HAL_CONSOLE_SENDSTRING(Console_self->menu[index].command);
						
						HAL_CONSOLE_SENDSTRING("  ");
					}
				}
				HAL_CONSOLE_SENDSTRING("\r\n");
				
				// 从新打印提示符和输入的指令内容
				//
				HAL_CONSOLE_SENDSTRING(Console_self->prompt);
				
				HAL_CONSOLE_SENDSTRING(consoleData.console_ReceiveBuffer);
			}
			// 相似指令数量仅有一个
			//
			else if (similarCommand == 1)
			{
				uint8_t tmpInputPoint = consoleData.console_ReceiveBufferLen;			// 指令输入的点
				
				consoleData.console_ReceiveBufferLen = strlen(Console_self->menu[onlyOneCommand_Index].command);
				
				// 拷贝已经找到唯一对应的指令
				//
				strncpy(consoleData.console_ReceiveBuffer,
					   Console_self->menu[onlyOneCommand_Index].command,
					   consoleData.console_ReceiveBufferLen);
				
				consoleData.console_ReceiveBuffer[consoleData.console_ReceiveBufferLen] = 0;
				
				// 回显未输入完整的指令内容
				//
				HAL_CONSOLE_SENDSTRING(consoleData.console_ReceiveBuffer + tmpInputPoint);
			}
			
			return;
		}
		
		// backspace 退格键
		//
		if ('\b' == tmpData)
		{
			if (consoleData.console_ReceiveBufferLen > 0)
			{
				consoleData.console_ReceiveBufferLen--;
				
				HAL_CONSOLE_SENDSTRING("\b \b");
			}
			return;
		}
		
		// Ctrl + C 取消这次指令
		//
		if (0x03 == tmpData)
		{
			HAL_CONSOLE_SENDSTRING("^C\r\n");
			
			consoleData.console_needPrompt = 1;
			
			consoleData.console_ReceiveBufferLen = 0;
			
			return;
		}
		
		// Ctrl + L 清屏
		//
		if (0x0c == tmpData)
		{
			// 使用linux模拟出来的xshell清屏指令
			//
			Uart1_SendByte(0x1B); Uart1_SendByte(0x5B); Uart1_SendByte(0x48); Uart1_SendByte(0x0D);
			
			Uart1_SendByte(0x7E); Uart1_SendByte(0x20); Uart1_SendByte(0x23); Uart1_SendByte(0x20);
			
			Uart1_SendByte(0x1B); Uart1_SendByte(0x5B); Uart1_SendByte(0x4A);
			
			consoleData.console_needPrompt = 1;
			
			consoleData.console_ReceiveBufferLen = 0;
			
			return;
		}
		
		// 防止越界， 存储指令数据，并且回显
		//
		if (consoleData.console_ReceiveBufferLen < CONSOLE_RECEIVE_MAX)
		{
			Uart1_SendByte(tmpData);
			
			consoleData.console_ReceiveBuffer[consoleData.console_ReceiveBufferLen++] = tmpData;
		}
	}
}


void Console_SetPrompt(uint8_t *prompt)
{
	uint8_t	index;
	
	for (index = 0; index < PROMPT_MAX && prompt[index]; index++)
	{
		Console_self->prompt[index] = prompt[index];
	}
	Console_self->prompt[index] = 0;
}


void Console_RegisterMenu(void *menu, uint8_t menuEntries) 
{
	Console_self->menu = menu;
	
	Console_self->menuEntries = menuEntries;
}

void Console_Print(uint8_t *str)
{
	HAL_CONSOLE_SENDSTRING(str);
}


void Console_Println(uint8_t *str)
{
	HAL_CONSOLE_SENDSTRING(str);
	
	HAL_CONSOLE_SENDSTRING("\r\n");
}


void Console_PrintDec(uint8_t *str, uint16_t number)
{
	HAL_CONSOLE_SENDSTRING(str);
	
	HAL_CONSOLE_SENDBYTE(number / 10000 % 10 + '0');
	
	HAL_CONSOLE_SENDBYTE(number / 1000 % 10 + '0');
	
	HAL_CONSOLE_SENDBYTE(number / 100 % 10 + '0');
	
	HAL_CONSOLE_SENDBYTE(number / 10 % 10 + '0');
	
	HAL_CONSOLE_SENDBYTE(number % 10 + '0');
}


void Console_PrintlnDec(uint8_t *str, uint16_t number)
{
	HAL_CONSOLE_SENDSTRING(str);
	
	HAL_CONSOLE_SENDBYTE(number / 10000 % 10 + '0');
	
	HAL_CONSOLE_SENDBYTE(number / 1000 % 10 + '0');
	
	HAL_CONSOLE_SENDBYTE(number / 100 % 10 + '0');
	
	HAL_CONSOLE_SENDBYTE(number / 10 % 10 + '0');
	
	HAL_CONSOLE_SENDBYTE(number % 10 + '0');
	
	HAL_CONSOLE_SENDSTRING("\r\n");
}


void Console_Init(void *self)
{
	Console_self = self;
	
	Console_self->init = Console_Init;
	
	Console_self->print = Console_Print;
	
	Console_self->printLn = Console_Println;
	
	Console_self->printDec = Console_PrintDec;
	
	Console_self->printDecLn = Console_PrintlnDec;
	
	Console_self->run = Console_Run;
	
	Console_self->setPrompt = Console_SetPrompt;
	
	Console_self->registerMenu = Console_RegisterMenu;
	
	memcpy(Console_self->prompt, "IAP15:~$ ", 9);
	
	Console_self->menu = 0;
	
	Console_self->menuEntries = 0;
	
	HAL_CONSOLE_INIT();	
}



