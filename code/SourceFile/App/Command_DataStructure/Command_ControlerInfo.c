#include "Command_ControlerInfo.h"


ControlerInfo_Typedef	ControlerInfo;


#define	ControlerInfo_BaseAddress					(512 * 100)
#define ControlerInfo_BaseAddress_Magic				ControlerInfo_BaseAddress
#define	ControlerInfo_BaseAddress_Name				ControlerInfo_BaseAddress_Magic + 3
#define	ControlerInfo_BaseAddress_Info				ControlerInfo_BaseAddress_Name + 10
#define	ControlerInfo_BaseAddress_Password			ControlerInfo_BaseAddress_Info + 10


void ControlerInfo_ReadName(void)
{
	uint8_t	tmpMagic[3];
	
	// 读取魔幻数字，识别是否为出厂状态（即用户是否初始化过）
	//
	tmpMagic[0] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Magic + 0);
	tmpMagic[1] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Magic + 1);
	tmpMagic[2] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Magic + 2);
	
	// 如果魔幻数字不正确，那么初始化为默认的名称
	//
	if (tmpMagic[0] != 'F' || tmpMagic[1] != 'Q' || tmpMagic[2] != 'Y')
	{
		memcpy(ControlerInfo.Name, "初始化状态", 10);
		
		memcpy(ControlerInfo.Info, "初始化状态", 10);
		
		memset(ControlerInfo.Password, 0x08, 6);
	}
	// 如果魔幻数字正确，那么读取用户设置的名称， 并且获取附带信息
	//
	else
	{
		ControlerInfo.Name[0] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 0);
		ControlerInfo.Name[1] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 1);
		ControlerInfo.Name[2] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 2);
		ControlerInfo.Name[3] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 3);
		ControlerInfo.Name[4] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 4);
		ControlerInfo.Name[5] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 5);
		ControlerInfo.Name[6] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 6);
		ControlerInfo.Name[7] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 7);
		ControlerInfo.Name[8] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 8);
		ControlerInfo.Name[9] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Name + 9);
		
		ControlerInfo.Info[0] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 0);
		ControlerInfo.Info[1] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 1);
		ControlerInfo.Info[2] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 2);
		ControlerInfo.Info[3] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 3);
		ControlerInfo.Info[4] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 4);
		ControlerInfo.Info[5] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 5);
		ControlerInfo.Info[6] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 6);
		ControlerInfo.Info[7] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 7);
		ControlerInfo.Info[8] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 8);
		ControlerInfo.Info[9] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Info + 9);
		
		ControlerInfo.Password[0] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Password + 0);
		ControlerInfo.Password[1] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Password + 1);
		ControlerInfo.Password[2] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Password + 2);
		ControlerInfo.Password[3] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Password + 3);
		ControlerInfo.Password[4] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Password + 4);
		ControlerInfo.Password[5] = App_Hal_Api.parameter->read(ControlerInfo_BaseAddress_Password + 5);
	}
}

void ControlerInfo_WriteName(void)
{
	// 擦除第一扇区
	//
	Sector_Erase(ControlerInfo_BaseAddress);			// 擦除扇区
	
	// 写入魔幻数字
	//
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Magic + 0, 'F');
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Magic + 1, 'Q');
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Magic + 2, 'Y');
	
	// 用户设置的名称和附带信息
	//
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 0, ControlerInfo.Name[0]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 1, ControlerInfo.Name[1]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 2, ControlerInfo.Name[2]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 3, ControlerInfo.Name[3]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 4, ControlerInfo.Name[4]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 5, ControlerInfo.Name[5]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 6, ControlerInfo.Name[6]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 7, ControlerInfo.Name[7]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 8, ControlerInfo.Name[8]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Name + 9, ControlerInfo.Name[9]);
	
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 0, ControlerInfo.Info[0]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 1, ControlerInfo.Info[1]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 2, ControlerInfo.Info[2]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 3, ControlerInfo.Info[3]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 4, ControlerInfo.Info[4]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 5, ControlerInfo.Info[5]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 6, ControlerInfo.Info[6]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 7, ControlerInfo.Info[7]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 8, ControlerInfo.Info[8]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Info + 9, ControlerInfo.Info[9]);
	
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Password + 0, ControlerInfo.Password[0]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Password + 1, ControlerInfo.Password[1]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Password + 2, ControlerInfo.Password[2]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Password + 3, ControlerInfo.Password[3]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Password + 4, ControlerInfo.Password[4]);
	App_Hal_Api.parameter->write(ControlerInfo_BaseAddress_Password + 5, ControlerInfo.Password[5]);
}


#define Network_BaseAddress							(512 * 101)	
#define	Network_BaseAddress_Magic					Network_BaseAddress
#define	Network_BaseAddress_LocalIp					(Network_BaseAddress + 3)
#define Network_BaseAddress_LocalPort				(Network_BaseAddress_LocalIp + 4)
#define Network_BaseAddress_LocalGateway			(Network_BaseAddress_LocalPort + 2)
#define Network_BaseAddress_LocalMask				(Network_BaseAddress_LocalGateway + 4)

#define Network_BaseAddress_PeerIp					(Network_BaseAddress_LocalMask + 4)
#define Network_BaseAddress_PeerPort				(Network_BaseAddress_PeerIp + 4)


void ControlerInfo_ReadNetworkParameter(void)
{
	uint8_t	tmpMagic[3];
	
	// 读取魔幻数字，识别是否为出厂状态（即用户是否初始化过）
	//
	tmpMagic[0] = App_Hal_Api.parameter->read(Network_BaseAddress_Magic + 0);
	tmpMagic[1] = App_Hal_Api.parameter->read(Network_BaseAddress_Magic + 1);
	tmpMagic[2] = App_Hal_Api.parameter->read(Network_BaseAddress_Magic + 2);
	
	// 如果魔幻数字不正确，那么初始化为默认的网络参数
	//
	if (tmpMagic[0] != 'Z' || tmpMagic[1] != 'S' || tmpMagic[2] != 'S')
	{
		return;
	}
	// 如果魔幻数字正确，那么读取用户设置的网络参数
	//
	else
	{
		// 本地网络参数
		//
		NETPARA_IP[0] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalIp + 0);
		NETPARA_IP[1] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalIp + 1);
		NETPARA_IP[2] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalIp + 2);
		NETPARA_IP[3] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalIp + 3);
		
		SOCKET0_LOCALPORT =  App_Hal_Api.parameter->read(Network_BaseAddress_LocalPort + 0) << 8;
		SOCKET0_LOCALPORT |= App_Hal_Api.parameter->read(Network_BaseAddress_LocalPort + 1);
		
		NETPARA_GATEWAY[0] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalGateway + 0);
		NETPARA_GATEWAY[1] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalGateway + 1);
		NETPARA_GATEWAY[2] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalGateway + 2);
		NETPARA_GATEWAY[3] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalGateway + 3);
		
		NETPARA_MASK[0] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalMask + 0);
		NETPARA_MASK[1] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalMask + 1);
		NETPARA_MASK[2] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalMask + 2);
		NETPARA_MASK[3] = App_Hal_Api.parameter->read(Network_BaseAddress_LocalMask + 3);
		
		// 远程网络参数
		//
		SOCKET0_REMOTEIP[0] = App_Hal_Api.parameter->read(Network_BaseAddress_PeerIp + 0);
		SOCKET0_REMOTEIP[1] = App_Hal_Api.parameter->read(Network_BaseAddress_PeerIp + 1);
		SOCKET0_REMOTEIP[2] = App_Hal_Api.parameter->read(Network_BaseAddress_PeerIp + 2);
		SOCKET0_REMOTEIP[3] = App_Hal_Api.parameter->read(Network_BaseAddress_PeerIp + 3);
		
		SOCKET0_REMOTEPORT =  App_Hal_Api.parameter->read(Network_BaseAddress_PeerPort + 0) << 8;
		SOCKET0_REMOTEPORT |= App_Hal_Api.parameter->read(Network_BaseAddress_PeerPort + 1);
	}
}

void ControlerInfo_WriteNetworkParameter(void)
{
	// 擦除第一扇区
	//
	App_Hal_Api.parameter->erase(Network_BaseAddress_LocalIp);			// 擦除扇区
	
	// 写入魔幻数字
	//
	App_Hal_Api.parameter->write(Network_BaseAddress_Magic + 0, 'Z');
	App_Hal_Api.parameter->write(Network_BaseAddress_Magic + 1, 'S');
	App_Hal_Api.parameter->write(Network_BaseAddress_Magic + 2, 'S');
	
	// 本地网络参数
	//
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalIp + 0, NETPARA_IP[0]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalIp + 1, NETPARA_IP[1]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalIp + 2, NETPARA_IP[2]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalIp + 3, NETPARA_IP[3]);
	
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalPort + 0, SOCKET0_LOCALPORT >> 8);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalPort + 1, SOCKET0_LOCALPORT);
	
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalGateway + 0, NETPARA_GATEWAY[0]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalGateway + 1, NETPARA_GATEWAY[1]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalGateway + 2, NETPARA_GATEWAY[2]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalGateway + 3, NETPARA_GATEWAY[3]);
	
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalMask + 0, NETPARA_MASK[0]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalMask + 1, NETPARA_MASK[1]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalMask + 2, NETPARA_MASK[2]);
	App_Hal_Api.parameter->write(Network_BaseAddress_LocalMask + 3, NETPARA_MASK[3]);
	
	// 远程网络参数
	//
	App_Hal_Api.parameter->write(Network_BaseAddress_PeerIp + 0, SOCKET0_REMOTEIP[0]);
	App_Hal_Api.parameter->write(Network_BaseAddress_PeerIp + 1, SOCKET0_REMOTEIP[1]);
	App_Hal_Api.parameter->write(Network_BaseAddress_PeerIp + 2, SOCKET0_REMOTEIP[2]);
	App_Hal_Api.parameter->write(Network_BaseAddress_PeerIp + 3, SOCKET0_REMOTEIP[3]);
	
	App_Hal_Api.parameter->write(Network_BaseAddress_PeerPort + 0, SOCKET0_REMOTEPORT >> 8);
	App_Hal_Api.parameter->write(Network_BaseAddress_PeerPort + 1, SOCKET0_REMOTEPORT);
}


void ControlerInfo_Init(void)
{
	SetStartScan(0);
	
	SetHeartbeatNotAckTimes(0);
	
	SetFirstBootUp(0x31);
	
	SetHeartbeatInterval(5); SetHeartbeatIntervalBak(5);
	
	ControlerInfo.Version[0] = 0x17;								// 控制器版本号
	ControlerInfo.Version[1] = 0x01;
	ControlerInfo.Version[2] = 0x18;
	
	ControlerInfo_ReadName();										// 读取控制器名字
	
	ControlerInfo_ReadNetworkParameter();							// 读取网络参数
	
#ifdef	USING_MODULE_NETWORK
	
	App_Hal_Api.network->reboot();															// 重启网络模块
	
#endif
}






