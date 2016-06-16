#include "wsddapi.h"
#include "wsdd.nsmap"
#include <stdio.h>

#include <iostream>
#include <stdio.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

const int MAX_BUF_LEN = 255;

int main()
{
    //int port = 8080;
    //struct soap *soap = soap_new2(SOAP_IO_UDP | SOAP_XML_IGNORENS | SO_BROADCAST, SOAP_IO_UDP | SOAP_XML_IGNORENS | SO_BROADCAST);
	struct soap *soap = soap_new();
	//soap_init2(soap, SOAP_IO_UDP | SOAP_XML_IGNORENS | SO_BROADCAST, SOAP_IO_UDP | SOAP_XML_IGNORENS | SO_BROADCAST);
	//soap->connect_flags |= SO_BROADCAST;
	//soap_register_plugin(&soap, soap_wsa);
	//soap_set_namespaces(soap, namespaces);
    //soap->user = (void*)&my_state;
	soap->connect_flags |= SO_BROADCAST;

    //struct soap soap = soap_new(); // to invoke messages
    //struct soap serv = soap_new(); // for the listener and event handlers

    //soap_bind(serv, port, 100);

    const char *id = soap_wsa_rand_uuid(soap);
    //serv->user = (void*)&my_state;
    //my_state.probe_id = id;

    soap_wsdd_Probe(soap,
      SOAP_WSDD_ADHOC,      // ad-hoc mode
      SOAP_WSDD_TO_TS,      // to a TS
      "soap.udp://239.255.255.250:3702",         // address of TS
      id,                   // message ID
      NULL,                 // ReplyTo
      "tds:Device",
      NULL,
      NULL);
	struct __wsdd__ProbeMatches probe_matches;
	soap->recv_timeout = -300;
	soap_recv___wsdd__ProbeMatches(soap, &probe_matches);

    //soap_wsdd_listen(serv, -1000);
	//soap->bind_flags = SO_REUSEADDR;
	//SOCKET sk = soap_bind(soap, NULL, 3702, 100);
	//SOCKET sk = soap_bind(soap, "192.168.3.39", 3702, 100);

	//if(SOAP_OK!=soap_wsdd_Hello(soap, SOAP_WSDD_ADHOC, "soap.udp://239.255.255.250:3702", soap_wsa_rand_uuid(soap), NULL,
	//	NULL,
	//	"tds:Device tdn:NetworkVideoTransmitter",
	//	NULL, NULL, "http://127.0.0.1/onvif/device_service", 1))
 //     soap_print_fault(soap, stderr);
	//struct ip_mreq multicastRequest;
	//multicastRequest.imr_multiaddr.s_addr = inet_addr("239.255.255.250");
	////multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
	//multicastRequest.imr_interface.s_addr = inet_addr("192.168.3.39");
	//setsockopt(soap->master, IPPROTO_IP, IP_ADD_MEMBERSHIP, (const char*)&multicastRequest, sizeof(multicastRequest));

	//char buf[10] = { '1' };
	//int sent_num = sendto(sk, buf, 10, 0, NULL, 0);
	//int err = WSAGetLastError();
	//soap_wsdd_Hello(soap, SOAP_WSDD_ADHOC, "soap.udp://239.255.255.250:3702¡±, soap_wsa_rand_uuid(soap), NULL, l_cameraId, l_types, l_scopes, NULL, l_serviceAddr, 1);

    //if (!soap_valid_socket(soap_bind(soap, port, 100)))
    //{
    //  soap_print_fault(soap, stderr);
    //  exit(0);
    //}
	//soap_wsdd_listen(soap, 0); // listen for messages for 1 ms

	//wsddService wsdd_service(soap);

	//wsdd_service.accept();
	//wsdd_service.serve();
	//wsdd_service.destroy();

    //soap_wsdd_listen(soap, -1000); // listen for messages for 1 ms
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

