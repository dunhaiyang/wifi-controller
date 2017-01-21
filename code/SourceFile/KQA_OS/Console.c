#include "Console.h"


static Console *Console_self;


#define			CONSOLE_RECEIVE_MAX							50


struct ConsoleData
{
	uint8_t	console_needPrompt:1;							// ��Ҫ��ӡ��ʾ��	
	
	uint8_t	console_ReceiveBufferLen:7;						// α�ն˻���ָ����������
	
	uint8_t console_ReceiveBuffer[CONSOLE_RECEIVE_MAX];		// α�ն˻���ָ������
	
}Console_ReceiveData;


struct ConsoleData consoleData = {1, 0};					// ��ʼ��Ϊ��Ҫ��ӡ��ʾ��


// inputString��command���趼�Ǵ���α����ַ���
//
bool __findCommand(uint8_t *inputCommand, uint8_t *memuCommand)
{
	// �Ƚ�inputCommandǰ���Ƿ����memuCommand
	//
	while (*memuCommand)
	{
		if (*inputCommand++ != *memuCommand++)
		{
			return 0;
		}
	}
	// ���㡰command�����ߡ�command argument1 ...��
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
	// �״ν����նˣ���ӡ��ʾ��
	//
	if (consoleData.console_needPrompt)
	{
		consoleData.console_needPrompt = 0;
		
		HAL_CONSOLE_SENDSTRING(Console_self->prompt);
	}
	
	// ��ȡ�ն�����
	//
	while (HAL_CONSOLE_AVAILABLE())
	{
		uint8_t index;
		
		uint8_t tmpData = Uart1_ReceiveByte();
		
		// return����ָ�����
		//
		if ('\r' == tmpData || '\n' == tmpData)
		{
			consoleData.console_ReceiveBuffer[consoleData.console_ReceiveBufferLen++] = 0;
			
			HAL_CONSOLE_SENDSTRING("\r\n");
			
			// ����ָ��
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
		
		// tab ��ȫ����
		//
		if (0x09 == tmpData)
		{
			uint8_t	similarCommand = 0;								// ����ָ����������
			
			uint8_t	onlyOneCommand_Index = 0;						// ����ָ����������ֻ��1��������
			
			consoleData.console_ReceiveBuffer[consoleData.console_ReceiveBufferLen] = 0;
			
			// �����ܹ��ж��ٸ�����ָ��
			//
			for (index = 0; index < Console_self->menuEntries; index++)
			{
				if (__containSubstring(consoleData.console_ReceiveBuffer, Console_self->menu[index].command))
				{
					similarCommand++;
					
					onlyOneCommand_Index = index;
				}
			}
			
			// ����ָ��������������
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
				
				// ���´�ӡ��ʾ���������ָ������
				//
				HAL_CONSOLE_SENDSTRING(Console_self->prompt);
				
				HAL_CONSOLE_SENDSTRING(consoleData.console_ReceiveBuffer);
			}
			// ����ָ����������һ��
			//
			else if (similarCommand == 1)
			{
				uint8_t tmpInputPoint = consoleData.console_ReceiveBufferLen;			// ָ������ĵ�
				
				consoleData.console_ReceiveBufferLen = strlen(Console_self->menu[onlyOneCommand_Index].command);
				
				// �����Ѿ��ҵ�Ψһ��Ӧ��ָ��
				//
				strncpy(consoleData.console_ReceiveBuffer,
					   Console_self->menu[onlyOneCommand_Index].command,
					   consoleData.console_ReceiveBufferLen);
				
				consoleData.console_ReceiveBuffer[consoleData.console_ReceiveBufferLen] = 0;
				
				// ����δ����������ָ������
				//
				HAL_CONSOLE_SENDSTRING(consoleData.console_ReceiveBuffer + tmpInputPoint);
			}
			
			return;
		}
		
		// backspace �˸��
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
		
		// Ctrl + C ȡ�����ָ��
		//
		if (0x03 == tmpData)
		{
			HAL_CONSOLE_SENDSTRING("^C\r\n");
			
			consoleData.console_needPrompt = 1;
			
			consoleData.console_ReceiveBufferLen = 0;
			
			return;
		}
		
		// Ctrl + L ����
		//
		if (0x0c == tmpData)
		{
			// ʹ��linuxģ�������xshell����ָ��
			//
			Uart1_SendByte(0x1B); Uart1_SendByte(0x5B); Uart1_SendByte(0x48); Uart1_SendByte(0x0D);
			
			Uart1_SendByte(0x7E); Uart1_SendByte(0x20); Uart1_SendByte(0x23); Uart1_SendByte(0x20);
			
			Uart1_SendByte(0x1B); Uart1_SendByte(0x5B); Uart1_SendByte(0x4A);
			
			consoleData.console_needPrompt = 1;
			
			consoleData.console_ReceiveBufferLen = 0;
			
			return;
		}
		
		// ��ֹԽ�磬 �洢ָ�����ݣ����һ���
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



