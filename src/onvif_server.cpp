#include <stdio.h>
#include <iostream>

#include "wsddapi.h"
#include "onvif_server.h"

#ifdef WIN32
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

//const int MAX_BUF_LEN = 255;
OnvifServer::OnvifServer():
discovery_soap_(NULL), onvif_soap_(NULL)
{}
OnvifServer::~OnvifServer()
{}

void OnvifServer::AddProfile(const ProfileInfo& info)
{
	profiles_.push_back(info);
}


const std::vector<ProfileInfo>& OnvifServer::GetProfiles()
{
	return profiles_;
}

void DiscoveryServerThread(void *user);
void OnvifServerThread(void* user);
int OnvifServer::Start(std::string host, int port)
{
	stop_ = false;
	host_ = host;
	port_ = port;

	discovery_soap_ = soap_new1(SOAP_IO_UDP | SO_BROADCAST);
	onvif_soap_ = soap_new();
	discovery_soap_->user = (void*)this;
	onvif_soap_->user = (void*)this;

	THREAD_CREATE(&discovery_server_thread_, DiscoveryServerThread, (void*)this);
	THREAD_CREATE(&onvif_server_thread_, OnvifServerThread, (void*)this);
	return 0;
}

void OnvifServer::Stop()
{
	stop_ = true;
	THREAD_JOIN(discovery_server_thread_);
	THREAD_JOIN(onvif_server_thread_);
}

void DiscoveryServerThread(void *user)
{
	OnvifServer *onvif_server = (OnvifServer*)user;
	struct soap* soap = onvif_server->GetDiscoverySoap();
	soap->bind_flags = SO_REUSEADDR;
	SOCKET sk = soap_bind(soap, NULL, 3702, 100);

	//if(SOAP_OK!=soap_wsdd_Hello(soap, SOAP_WSDD_ADHOC, "soap.udp://239.255.255.250:3702", soap_wsa_rand_uuid(soap), NULL,
	//	NULL,
	//	"tds:Device tdn:NetworkVideoTransmitter",
	//	NULL, NULL, "http://127.0.0.1/onvif/device_service", 1))
	//     soap_print_fault(soap, stderr);
	struct ip_mreq multicastRequest;
	multicastRequest.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
	//如果有多个网卡，则一般要指定
	if (onvif_server->GetHost().empty())
		multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
	else
		multicastRequest.imr_interface.s_addr = inet_addr(onvif_server->GetHost().c_str());
	setsockopt(soap->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&multicastRequest, sizeof(multicastRequest));

	while (true)
	{
		soap_wsdd_listen(soap, -500); // listen for messages for 1 ms
		if (onvif_server->IsStop())
			break;
	}
	return;
}

void OnvifServerThread(void* user)
{
	OnvifServer *onvif_server = (OnvifServer*)user;
	struct soap* soap = onvif_server->GetOnvifSoap();
	soap->accept_timeout = soap->recv_timeout = soap->recv_timeout = soap->send_timeout = -500;
	SOCKET s;
	if (onvif_server->GetHost().empty())
		s = soap_bind(soap, NULL, onvif_server->GetPort(), 100);
	else
		s = soap_bind(soap, onvif_server->GetHost().c_str(), onvif_server->GetPort(), 100);

	if (!soap_valid_socket(s))
		return;

	for (int i = 1;; i++)
	{
		s = soap_accept(soap);
		if (soap_valid_socket(s))
		{
			//fprintf(stderr, "%d: accepted %d IP=%d.%d.%d.%d ... ", i, s, (int)(soap->ip >> 24) & 0xFF, (int)(soap->ip >> 16) & 0xFF, (int)(soap->ip >> 8) & 0xFF, (int)soap->ip & 0xFF);
			soap_serve(soap);	// process RPC skeletons
			//fprintf(stderr, "served\n");
			soap_destroy(soap);
			soap_end(soap);	// clean up 
		}
		if (onvif_server->IsStop())
			break;
	}
}

int main()
{
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
	onvif_server.Start(std::string(), 12000);
	int x;
	std::cin >> x;
	onvif_server.Stop();
	return 0;
}
