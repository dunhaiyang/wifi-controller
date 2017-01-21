#include "Middleware_Menu.h"


/*
	=============  1. α�ն�ָ��(֧��xshell)  =================
*/

#ifdef	USING_MODULE_WIFI

void Menu_Iwconfig(void *argument)
{
	Uint8P_Uint8P uint8p_uint8p;
	
	// ������ָ������
	//
	argument = strtok(argument, " ");
	
	if (argument)
	{
		// ��������һ������
		//
		argument = strtok(0, " ");
		
		if (argument)
		{
			// ---------��ȡ���ڲ�����
			//
			if (strcmp(argument, "getUart") == 0)
			{
				App_Hal_Api.wifi->getUart();
				
				return;
			}
			// ---------ɨ��wifi�ȵ�
			//
			else if (strcmp(argument, "scan") == 0)
			{
				App_Hal_Api.wifi->scan();
				
				return;
			}
			// ---------����wifi�ȵ�
			//
			else if (strcmp(argument, "ssid") == 0)
			{
				// ������ssid����Ĳ���
				//
				uint8p_uint8p.para1 = strtok(0, " ");
				
				// ������password
				//
				argument = strtok(0, " ");
				
				// ������password����Ĳ���
				//
				uint8p_uint8p.para2 = strtok(0, " ");
				
				if (uint8p_uint8p.para1 && uint8p_uint8p.para2)
				{
					App_Hal_Api.wifi->linkAP(&uint8p_uint8p);
				}
				
				return;
			}
			// ---------��ѯwifi�ȵ�����״̬
			//
			else if (strcmp(argument, "hotspot") == 0)
			{
				App_Hal_Api.wifi->hotspotStatus();
				
				return;
			}
			// ---------����dhcp�������
			//
			else if (strcmp(argument, "dhcp") == 0)
			{
				App_Hal_Api.wifi->dhcp();
				
				return;
			}
			// ----------ping ip
			//
			else if (strcmp(argument, "ping") == 0)
			{
				if (uint8p_uint8p.para1 = strtok(0, " "))
				{
					App_Hal_Api.wifi->ping(uint8p_uint8p.para1);
				}
				
				return;
			}
			// ---------���ӷ�����
			//
			else if (strcmp(argument, "con") == 0)
			{
				if (uint8p_uint8p.para1 = strtok(0, " "))
				{
					if (uint8p_uint8p.para2 = strtok(0, " "))
					{
						App_Hal_Api.wifi->connectServer(&uint8p_uint8p);
					}
				}
				
				return;
			}
			// ---------������������
			//
			else if (strcmp(argument, "write") == 0)
			{
				if (uint8p_uint8p.para1 = strtok(0, " "))
				{
					App_Hal_Api.wifi->write(uint8p_uint8p.para1, strlen(uint8p_uint8p.para1));
				}
				
				return;
			}
			// ---------��ѯMAC��ַ
			//
			else if (strcmp(argument, "mac") == 0)
			{
				App_Hal_Api.wifi->queryMac();
				
				return;
			}
			// ---------��������ģ��
			//
			else if (strcmp(argument, "reboot") == 0)
			{
				App_Hal_Api.wifi->reboot();
				
				return;
			}
		}
	}
	App_Hal_Api.console->printLn("iwconfig getUart");
	App_Hal_Api.console->printLn("iwconfig scan");
	App_Hal_Api.console->printLn("iwconfig ssid xxx password xxxxxxxx");
	App_Hal_Api.console->printLn("iwconfig hotspot");
	App_Hal_Api.console->printLn("iwconfig dhcp");
	App_Hal_Api.console->printLn("iwconfig ping xxx.xxx.xxx.xx");
	App_Hal_Api.console->printLn("iwconfig con xxx.xxx.xxx.xxx xxxxx");
	App_Hal_Api.console->printLn("iwconfig write this_is_data");
	App_Hal_Api.console->printLn("iwconfig mac");
	App_Hal_Api.console->printLn("iwconfig reboot");
}
	
#endif

#ifdef	USING_MODULE_NETWORK

void Menu_Ifconfig(void *argument)
{
	argument = argument;
	
	// ������ָ������
	//
	argument = strtok(argument, " ");
	
	if (argument)
	{
		// ��������һ������
		//
		argument = strtok(0, " ");
		
		if (argument)
		{
			// ---------��ȡ�������в���
			//
			if (strcmp(argument, "all") == 0)
			{
				App_Hal_Api.network->allParameters();			
				
				return;
			}
			else if (strcmp(argument, "reboot") == 0)
			{
				App_Hal_Api.network->reboot();			
				
				return;
			}
		}
	}
	App_Hal_Api.console->printLn("ifconfig all");
	App_Hal_Api.console->printLn("ifconfig reboot");
}
	
#endif

void Menu_Controller(void *argument)
{
	argument = strtok(argument, " ");
	
	if (argument)
	{
		// ��������һ������
		//
		argument = strtok(0, " ");
		
		if (argument)
		{
			// ---------����wifi
			//
			if (strcmp(argument, "info") == 0)
			{
				uint32_t tmpSystemCoreTime = App_Hal_Api.scheduler->milliseconds();
				
				App_Hal_Api.console->printDecLn("wirelessChannel: ",  App_Hal_Api.wireless->channelNo);
				
				App_Hal_Api.console->printDecLn("WiresslessChannel_Status: ",  WiresslessChannel_Status);
				
				App_Hal_Api.console->printDec("day: ", tmpSystemCoreTime / 1000 / 3600 / 24);
				
				App_Hal_Api.console->printDec("\thour: ", tmpSystemCoreTime / 1000 / 3600 % 24);
				
				App_Hal_Api.console->printDec("\tminute: ", tmpSystemCoreTime / 1000 / 60 % 60);
				
				App_Hal_Api.console->printDec("\tsecond: ", tmpSystemCoreTime / 1000 % 60);
				
				App_Hal_Api.console->printDecLn("\tmillsecond: ", tmpSystemCoreTime % 1000);
				
				return;
			}
			// ---------��������Զ�̷�����
			//
			else if (strcmp(argument, "set") == 0)
			{
				return;
			}
		}
	}
	App_Hal_Api.console->printLn("controller info");
	App_Hal_Api.console->printLn("controller set");
}


void Menu_Device(void *argument)
{
	argument = argument;
	
	NormalDeviceInfo_TravelDeviceList();
}


void Menu_Data(void *argument)
{
	argument = argument;
}


void Menu_Uname(void *argument)
{
	argument = argument;

#ifdef	USING_MODULE_WIFI
	
	App_Hal_Api.console->printLn("version: 2017-01-09 WIFI");

#endif
	
#ifdef	USING_MODULE_NETWORK
	
	App_Hal_Api.console->printLn("version: 2017-01-09 CH395");

#endif
}


void Menu_Reboot(void *argument)
{
	argument = argument;
	
	App_Hal_Api.scheduler->delayMilliseconds(5000);
	
	App_Hal_Api.hardware->reboot();
}


Menu	menu[6] = {

#ifdef	USING_MODULE_WIFI
	
	{"iwconfig", 		Menu_Iwconfig},
	
#endif
	
#ifdef	USING_MODULE_NETWORK
	
	{"ifconfig", 		Menu_Ifconfig},
	
#endif
	
	{"controller", 		Menu_Controller},
	
	{"device", 			Menu_Device},
	
	{"data", 			Menu_Data},
	
	{"uname", 			Menu_Uname},
	
	{"reboot", 			Menu_Reboot},
	
};
