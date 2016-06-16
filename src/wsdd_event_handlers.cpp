#include "wsddapi.h"

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

	//≤‚ ‘¥˙¬Î
	//soap_wsdd_init_ProbeMatches(soap, matches);
	//":NetworkVideoTransmitter",
	soap_wsdd_add_ProbeMatch(soap, matches,
		"urn:uuid:464A4854-4656-5242-4530-313035394100",
		//"http://192.168.3.39:12000",
		"tds:Device",
		//"onvif://www.onvif.org/Profile/Streaming onvif://www.onvif.org/Profile/G onvif://www.onvif.org/Profile/C onvif://www.onvif.org/location/country/china onvif://www.onvif.org/type/video_encoder onvif://www.onvif.org/name/IP-Camera onvif://www.onvif.org/hardware/HI3518C",
		NULL,
		NULL,
		//NULL, 10);
		"http://127.0.0.1:12000", 10);

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

