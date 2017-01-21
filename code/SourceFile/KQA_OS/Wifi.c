#include "Wifi.h"


static	Wifi *Wifi_self;


void Wifi_LinkAP(Uint8P_Uint8P *ssid_key)
{
	HAL_WIFI_LINKAP(ssid_key->para1, ssid_key->para2);
}


void Wifi_ConnectServer(Uint8P_Uint8P *ip_port)
{
	HAL_WIFI_CONNECTSERVER(ip_port->para1, ip_port->para2);
}


void Wifi_Init(void *self)
{
	Wifi_self = self;
	
	Wifi_self->init = Wifi_Init;
	
	Wifi_self->getUart = HAL_WIFI_GETUART;
	
	Wifi_self->linkAP = Wifi_LinkAP;
	
	Wifi_self->queryMac = HAL_WIFI_QUERYMAC;
	
	Wifi_self->reboot = HAL_WIFI_REBOOT; 
	
	Wifi_self->scan = HAL_WIFI_SCAN; 
	
	Wifi_self->hotspotStatus = HAL_WIFI_HOTSPOTSTATUS; 
	
	Wifi_self->serverStatus = HAL_WIFI_SERVERSTATUS;
	
	Wifi_self->dhcp = HAL_WIFI_DHCP;
	
	Wifi_self->ping = HAL_WIFI_PING;
	
	Wifi_self->connectServer = Wifi_ConnectServer;
	
	Wifi_self->disconnectServer = HAL_WIFI_DISCONNECTSERVER; 
	
	Wifi_self->write = HAL_WIFI_SEND;
	
	Wifi_self->read = HAL_WIFI_RECEIVE;
	
	HAL_WIFI_INIT();
}



