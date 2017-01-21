#ifndef __MIDDLEWARE_MENU_H_
#define __MIDDLEWARE_MENU_H_


#include "Command_Wireless.h"

#include "Command_Network.h"


/*
	=============  1. Œ±÷’∂À÷∏¡Ó(÷ß≥÷xshell)  =================
*/

#ifdef	USING_MODULE_WIFI
void Menu_Iwconfig(void *argument);
#endif


#ifdef	USING_MODULE_NETWORK
void Menu_Ifconfig(void *argument);
#endif


void Menu_Controller(void *argument);


void Menu_Device(void *argument);


void Menu_Data(void *argument);


void Menu_Uname(void *argument);


void Menu_Reboot(void *argument);


extern	Menu	menu[6];


#endif




