#include "wsddapi.h"
//#include "wsdd.nsmap"
#include <stdio.h>

#include <iostream>
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

const int MAX_BUF_LEN = 255;

int main_1(int argc, char* argv[])
{
	WORD wVersionRequested;
	WSADATA wasData;//指向WinSocket信息结构的指针
	int err;

	wVersionRequested = MAKEWORD(2, 2);
	// 初始化winsock库，使用socket的前提
	err = WSAStartup(wVersionRequested, &wasData);
	if (err != 0)
	{
		return -1;
	}
	if (LOBYTE(wasData.wVersion) != 2 || HIBYTE(wasData.wVersion) != 2)
	{
		WSACleanup();
		return -1;
	}
	SOCKET conn_sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (conn_sock == INVALID_SOCKET)
	{
		err = WSAGetLastError();
		printf("socket error:%d\n", err);
		closesocket(conn_sock);
		WSACleanup();
		return -1;
	}
	bool bOpt = true;
	//打开广播选项
	setsockopt(conn_sock, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));

	//setsockopt(conn_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&bOpt, sizeof(bOpt));
	
	//int set = 1;
	//setsockopt(conn_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&set, sizeof(int));
	// 设置发往的地址
	SOCKADDR_IN saUdpServ;
	memset(&saUdpServ, 0, sizeof(saUdpServ));
	saUdpServ.sin_family = AF_INET;
	//saUdpServ.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
	saUdpServ.sin_addr.S_un.S_addr = inet_addr("239.255.255.250");
	//saUdpServ.sin_port = htons(7001);
	saUdpServ.sin_port = htons(3702);
	int nSize = sizeof(SOCKADDR_IN);	
	
	char buff[MAX_BUF_LEN];
	memset(buff, 0, MAX_BUF_LEN);
	int nLoop = 0;
	char* ip = NULL;
	while(1){
		nLoop++;
		sprintf(buff, "Message %d", nLoop);
		int nSendSize = sendto(conn_sock, buff, strlen(buff), 0, (SOCKADDR*)&saUdpServ, nSize);
		if (nSendSize == SOCKET_ERROR)
		{
			err = WSAGetLastError();
			printf("sendto error:%d\n", err);
			closesocket(conn_sock);
			WSACleanup();
			return -1;
		}
		printf("send: %s\n", buff);
		Sleep(5000);
	}
	
	closesocket(conn_sock);
	WSACleanup();
	return 0;
}
int main()
{
    //int port = 8080;
    //struct soap *soap = soap_new2(SOAP_IO_UDP | SOAP_XML_IGNORENS | SO_BROADCAST, SOAP_IO_UDP | SOAP_XML_IGNORENS | SO_BROADCAST);
	struct soap *soap = soap_new1(SOAP_IO_UDP | SO_BROADCAST);
	soap_init2(soap, SOAP_IO_UDP | SOAP_XML_IGNORENS | SO_BROADCAST, SOAP_IO_UDP | SOAP_XML_IGNORENS | SO_BROADCAST);
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
	multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
	//multicastRequest.imr_interface.s_addr = inet_addr("192.168.3.39");
	setsockopt(soap->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&multicastRequest, sizeof(multicastRequest));

	while (true)
		soap_wsdd_listen(soap, 10); // listen for messages for 1 ms

	return 0;
}
int SOAP_ENV__Fault(struct soap *soap, char *faultcode, char *faultstring, char *faultactor, struct SOAP_ENV__Detail *detail, struct SOAP_ENV__Code *SOAP_ENV__Code, struct SOAP_ENV__Reason *SOAP_ENV__Reason, char *SOAP_ENV__Node, char *SOAP_ENV__Role, struct SOAP_ENV__Detail *SOAP_ENV__Detail)
{
	//... = faultcode; // SOAP 1.1 fault code string (QName)
	//... = faultstring; // SOAP 1.1 fault string
	//... = faultactor; // SOAP 1.1 fault actor string
	//... = detail; // SOAP 1.1 fault detail struct
	//... = SOAP_ENV__Code; // SOAP 1.2 fault code struct
	//... = SOAP_ENV__Reason; // SOAP 1.2 reason struct
	//... = SOAP_ENV__Node; // SOAP 1.2 node string
	//... = SOAP_ENV__Role; // SOAP 1.2 role string
	//... = SOAP_ENV__Detail; // SOAP 1.2 detail struct
	return SOAP_OK;
}

void wsdd_event_Hello(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, const char *EndpointReference, const char *Types, const char *Scopes, const char *MatchBy, const char *XAddrs, unsigned int MetadataVersion)
{}
void wsdd_event_Bye(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, const char *EndpointReference, const char *Types, const char *Scopes, const char *MatchBy, const char *XAddrs, unsigned int *MetadataVersion)
{}
soap_wsdd_mode wsdd_event_Probe(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *Types, const char *Scopes, const char *MatchBy, struct wsdd__ProbeMatchesType *matches)
{
	printf("%s,%d\n", __FUNCTION__, __LINE__);
	printf("MessageID:%s\n", MessageID);
	printf("ReplyTo:%s\n", ReplyTo);
	printf("Types:%s\n", Types);
	printf("Scopes:%s\n", Scopes);
	printf("MatchBy:%s\n", MatchBy);

	//测试代码
	//soap_wsdd_init_ProbeMatches(soap, matches);
	//":NetworkVideoTransmitter",
	soap_wsdd_add_ProbeMatch(soap, matches,
		"urn:uuid:464A4854-4656-5242-4530-313035394100",
		//"http://192.168.8.100:10000",
		"tds:Device",
		//"onvif://www.onvif.org/Profile/Streaming onvif://www.onvif.org/Profile/G onvif://www.onvif.org/Profile/C onvif://www.onvif.org/location/country/china onvif://www.onvif.org/type/video_encoder onvif://www.onvif.org/name/IP-Camera onvif://www.onvif.org/hardware/HI3518C",
		NULL,
		NULL,
		//NULL, 10);
		"http://192.168.3.39:10000", 10);

	//<d:Scopes>onvif://www.onvif.org/Profile/Streaming onvif://www.onvif.org/Profile/G onvif://www.onvif.org/Profile/C onvif://www.onvif.org/location/country/china onvif://www.onvif.org/type/video_encoder onvif://www.onvif.org/name/IP-Camera onvif://www.onvif.org/hardware/HI3518C </d:Scopes>
	//if (soap_wsdd_ProbeMatches(soap, "soap.udp://239.255.255.250:3702", soap_wsa_rand_uuid(soap), MessageID, NULL, matches) != SOAP_OK) 
	//soap->peer.in.sin_port = htons((short)3702);
	if (soap_wsdd_ProbeMatches(soap, "soap.udp://", soap_wsa_rand_uuid(soap), MessageID, NULL, matches) != SOAP_OK)
		//if (soap_wsdd_ProbeMatches(soap, NULL, soap_wsa_rand_uuid(soap), MessageID, NULL, matches) != SOAP_OK) 
		soap_print_fault(soap, stderr);

	//return 0;
	//return SOAP_WSDD_MANAGED;
	return SOAP_WSDD_ADHOC;
}
void wsdd_event_ProbeMatches(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, struct wsdd__ProbeMatchesType *matches)
{}
soap_wsdd_mode wsdd_event_Resolve(struct soap *soap, const char *MessageID, const char *ReplyTo, const char *EndpointReference, struct wsdd__ResolveMatchType *match)
{
	return SOAP_WSDD_MANAGED;
}
void wsdd_event_ResolveMatches(struct soap *soap, unsigned int InstanceId, const char *SequenceId, unsigned int MessageNumber, const char *MessageID, const char *RelatesTo, struct wsdd__ResolveMatchType *match)
{}
