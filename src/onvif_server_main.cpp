#include <stdio.h>
#include <iostream>

#include "wsddapi.h"
#include "onvif_server.h"

#include "system_utils.h"

int main()
{
	//GetTimeZone();
	//return 0;
	//system("");
	int idx;
	bool dhcp_enabled;
	std::string addr, gateway;
	int prefix_length;
	GetIpv4Address(idx, dhcp_enabled, addr, prefix_length, gateway);
	//SetNetworkInterface(28, "192.168.1.28", 24, "192.168.1.1");
	//SetNetworkInterface(28, "192.168.1.29", 24);
	//SetGateway(28, "192.168.1.110");
//void ShutdownSystem(bool reboot);
	//unsigned long long x = GetCpuFreq();//获取CPU频率,单位: MHZ
	//std::string y = GetCpuManID();
	//std::string z = GetCpuType();

	
	OnvifServer onvif_server;
	ProfileInfo info;
	info.height = 640;
	info.width = 480;
	info.name = "first";
	info.frame_rate = 30;
	info.uri = "first_uri";
	onvif_server.AddProfile(info);
	info.name = "second";
	info.uri = "second_uri";
	onvif_server.AddProfile(info);
	onvif_server.Start(idx, 12000);
	int x;
	std::cin >> x;
	onvif_server.Stop();
	return 0;
}

