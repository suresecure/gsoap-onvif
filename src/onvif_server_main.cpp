#include <stdio.h>
#include <iostream>

#include "wsddapi.h"
#include "onvif_server.h"
//#include "glog/logging.h"

#include "system_utils.h"

using namespace suresecure_onvif;

int main(int argc, char**argv)
{
	//google::InitGoogleLogging(argv[0]);
	//google::LogToStderr();
	//LOG(INFO) << "xyz";
	
	int idx = -1;
	bool dhcp_enabled;
	std::string addr, gateway;
	int prefix_length;
	GetIpv4Address(idx, dhcp_enabled, addr, prefix_length, gateway);

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

