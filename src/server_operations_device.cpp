#include "soapStub.h"
#include "soapH.h"
#include "onvif_server.h"
#include "system_utils.h"

#ifdef WIN32
#define KKKK
#else
#endif

//#define LOCAL_ADDRESS ()

using namespace suresecure_onvif;
/** Web service operation '__tds__GetCapabilities' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCapabilities(struct soap*soap, _tds__GetCapabilities *tds__GetCapabilities, _tds__GetCapabilitiesResponse &tds__GetCapabilitiesResponse)
{
	struct sockaddr sock_addr;
	int addrlen = sizeof(sock_addr);
	struct in_addr in_addr;
	int ret = getsockname(soap->socket, &sock_addr, &addrlen);
	struct sockaddr_in *sock_addr_in = (struct sockaddr_in*)&sock_addr;
	char str[INET_ADDRSTRLEN];

	inet_ntop(AF_INET, &(sock_addr_in->sin_addr), str, INET_ADDRSTRLEN);

	//wchar_t addrstr[20];
	//DWORD addrstrlen = 20;
	//WSAAddressToString(&sock_addr, addrlen, NULL, addrstr, &addrstrlen);

	tds__GetCapabilitiesResponse.Capabilities = soap_new_tt__Capabilities(soap);

	tt__DeviceCapabilities *device_capabilities = soap_new_tt__DeviceCapabilities(soap);
	tds__GetCapabilitiesResponse.Capabilities->Device = device_capabilities;

	tt__NetworkCapabilities *network_capabilities = soap_new_tt__NetworkCapabilities(soap);
	tt__SystemCapabilities *system_capabilities = soap_new_tt__SystemCapabilities(soap);

	device_capabilities->XAddr = "http://127.0.0.1:12000";
	device_capabilities->Network = network_capabilities;
	device_capabilities->System = system_capabilities;

	tt__MediaCapabilities *media_capabilities = soap_new_tt__MediaCapabilities(soap);
	tds__GetCapabilitiesResponse.Capabilities->Media = media_capabilities;

	media_capabilities->XAddr = "http://127.0.0.1:12000";
	tt__RealTimeStreamingCapabilities *rt_streaming_cap = soap_new_tt__RealTimeStreamingCapabilities(soap);
	media_capabilities->StreamingCapabilities = rt_streaming_cap;
	bool *rtsp = soap_new_bool(soap);
	*rtsp = true;
	rt_streaming_cap->RTP_USCORERTSP_USCORETCP = rt_streaming_cap->RTP_USCORETCP = rtsp;

	tt__CapabilitiesExtension *cap_ext = soap_new_tt__CapabilitiesExtension(soap);
	tt__DeviceIOCapabilities *device_io_cap = soap_new_tt__DeviceIOCapabilities(soap);
	device_io_cap->AudioOutputs = device_io_cap->AudioSources = device_io_cap->RelayOutputs = device_io_cap->VideoOutputs = 0;
	device_io_cap->VideoSources = 1;
	device_io_cap->XAddr = "http://127.0.0.1:12000";
	cap_ext->DeviceIO = device_io_cap;
	tds__GetCapabilitiesResponse.Capabilities->Extension = cap_ext;

	printf("Device: Get capabilities!\n");
	return SOAP_OK;
}

/** Web service operation '__tds__GetServices' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServices(struct soap* soap, _tds__GetServices *tds__GetServices, _tds__GetServicesResponse &tds__GetServicesResponse)
{
	//tds__GetServices;
	//tds__GetServicesResponse;
	tds__Service *device_service = soap_new_tds__Service(soap);
	device_service->Namespace = "http://www.onvif.org/ver10/device/wsdl";
	device_service->XAddr = "http://127.0.0.1:12000";
	tds__Service *media_service = soap_new_tds__Service(soap);
	media_service->Namespace = "http://www.onvif.org/ver10/media/wsdl";
	media_service->XAddr = "http://127.0.0.1:12000";
	tds__Service *device_io_service = soap_new_tds__Service(soap);
	device_io_service->Namespace = "http://www.onvif.org/ver10/deviceIO/wsdl";
	device_io_service->XAddr = "http://127.0.0.1:12000";

	tds__GetServicesResponse.Service.push_back(device_service);
	tds__GetServicesResponse.Service.push_back(media_service);
	tds__GetServicesResponse.Service.push_back(device_io_service);
	printf("Get services!\n");
	return SOAP_OK;
}
/** Web service operation '__tds__GetDeviceInformation' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDeviceInformation(struct soap*soap, _tds__GetDeviceInformation *tds__GetDeviceInformation, _tds__GetDeviceInformationResponse &tds__GetDeviceInformationResponse)
{
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	tds__GetDeviceInformationResponse.FirmwareVersion = onvif_server->GetFirmwareVersion();
	tds__GetDeviceInformationResponse.Manufacturer = onvif_server->GetManufacturer();
	tds__GetDeviceInformationResponse.Model = onvif_server->GetModel();
	tds__GetDeviceInformationResponse.SerialNumber = onvif_server->GetSerailNumber();
	tds__GetDeviceInformationResponse.HardwareId = onvif_server->GetHardwareId();
	printf("__tds__GetDeviceInformation\n");
	return SOAP_OK;
}
/** Web service operation '__tds__GetScopes' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetScopes(struct soap*soap, _tds__GetScopes *tds__GetScopes, _tds__GetScopesResponse &tds__GetScopesResponse)
{
	std::vector<std::string> scope_items;
	scope_items.push_back("onvif://www.onvif.org/Profile/Streaming");
	scope_items.push_back("onvif://www.onvif.org/Profile/G");
	scope_items.push_back("onvif://www.onvif.org/Profile/C");
	scope_items.push_back("onvif://www.onvif.org/location/country/china");
	scope_items.push_back("onvif://www.onvif.org/type/video_encoder");
	scope_items.push_back("onvif://www.onvif.org/name/IP-Camera");
	//scope_items.push_back("onvif://www.onvif.org/hardware/HI3518C");

	tds__GetScopesResponse.Scopes;
	for (int i = 0; i < scope_items.size(); ++i)
	{
		tt__Scope *scope = soap_new_tt__Scope(soap);
		scope->ScopeDef = tt__ScopeDefinition__Fixed;
		scope->ScopeItem = scope_items[i];
		tds__GetScopesResponse.Scopes.push_back(scope);
	}
	printf("__tds__GetScopes\n");
	return SOAP_OK;
}
/** Web service operation '__tds__GetServiceCapabilities' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetServiceCapabilities(struct soap*, _tds__GetServiceCapabilities *tds__GetServiceCapabilities, _tds__GetServiceCapabilitiesResponse &tds__GetServiceCapabilitiesResponse)
{
	printf("Get services capabilities!\n");
	return SOAP_OK;
}
/** Web service operation '__tds__GetSystemDateAndTime' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemDateAndTime(struct soap*soap, _tds__GetSystemDateAndTime *tds__GetSystemDateAndTime, _tds__GetSystemDateAndTimeResponse &tds__GetSystemDateAndTimeResponse)
{
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime;
	tt__SystemDateTime *system_date_time = soap_new_tt__SystemDateTime(soap);
	tds__GetSystemDateAndTimeResponse.SystemDateAndTime = system_date_time;
	system_date_time->DateTimeType = tt__SetDateTimeType__Manual;
	system_date_time->DaylightSavings = false;
	system_date_time->TimeZone = soap_new_tt__TimeZone(soap);
	system_date_time->TimeZone->TZ = "(GMT+08:00) Beijing, Chongqing, Hong Kong SAR, Urumqi";
	//system_date_time->TimeZone->TZ = "UTC+08:00";

	struct DateTime ldt = GetLocalDateTime();
	tt__DateTime *local_date_time = soap_new_tt__DateTime(soap);
	system_date_time->LocalDateTime = local_date_time;
	tt__Date *local_date = soap_new_tt__Date(soap);
	local_date_time->Date = local_date;
	local_date->Year = ldt.year;
	local_date->Month = ldt.month;
	local_date->Day = ldt.day;
	tt__Time *local_time = soap_new_tt__Time(soap);
	local_date_time->Time = local_time;
	local_time->Hour = ldt.hour;
	local_time->Minute = ldt.minute;
	local_time->Second = ldt.second;

	struct DateTime udt = GetUtcDateTime();
	tt__DateTime *utc_date_time = soap_new_tt__DateTime(soap);
	system_date_time->UTCDateTime = utc_date_time;
	tt__Date *utc_date = soap_new_tt__Date(soap);
	utc_date_time->Date = utc_date;
	utc_date->Year = udt.year;
	utc_date->Month = udt.month;
	utc_date->Day = udt.day;
	tt__Time *utc_time = soap_new_tt__Time(soap);
	utc_date_time->Time = utc_time;
	utc_time->Hour = udt.hour;
	utc_time->Minute = udt.minute;
	utc_time->Second = udt.second;

	printf("__tds__GetSystemDateAndTime\n");
	return SOAP_OK;
}
/** Web service operation '__tds__SetSystemDateAndTime' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemDateAndTime(struct soap*, _tds__SetSystemDateAndTime *tds__SetSystemDateAndTime, _tds__SetSystemDateAndTimeResponse &tds__SetSystemDateAndTimeResponse)
{
	tds__SetSystemDateAndTime->DateTimeType;
	if (tds__SetSystemDateAndTime->DateTimeType == tt__SetDateTimeType__Manual &&
		tds__SetSystemDateAndTime->UTCDateTime != NULL)
	{
		tt__DateTime *dt = tds__SetSystemDateAndTime->UTCDateTime;
		struct DateTime udt;
		udt.year = dt->Date->Year;
		udt.month = dt->Date->Month;
		udt.day = dt->Date->Day;
		udt.hour = dt->Time->Hour;
		udt.minute = dt->Time->Minute;
		udt.second = dt->Time->Second;
		SetUtcDateTime(udt);
	}
	struct DateTime udt;
	printf("__tds__SetSystemDateAndTime\n");
	return SOAP_OK;
}

/** Web service operation '__tds__GetHostname' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetHostname(struct soap*soap, _tds__GetHostname *tds__GetHostname, _tds__GetHostnameResponse &tds__GetHostnameResponse)
{ 
	tt__HostnameInformation *hostname = soap_new_tt__HostnameInformation(soap);
	tds__GetHostnameResponse.HostnameInformation = hostname;
	hostname->FromDHCP = false;
	hostname->Name = soap_new_std__string(soap);
	hostname->Name->assign(GetHostName());
	printf("__tds__GetHostname\n"); 
	return SOAP_OK; 
}
/** Web service operation '__tds__SetHostname' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostname(struct soap*, _tds__SetHostname *tds__SetHostname, _tds__SetHostnameResponse &tds__SetHostnameResponse){ printf("__tds__SetHostname\n"); return SOAP_OK; }
/** Web service operation '__tds__GetDiscoveryMode' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDiscoveryMode(struct soap*, _tds__GetDiscoveryMode *tds__GetDiscoveryMode, _tds__GetDiscoveryModeResponse &tds__GetDiscoveryModeResponse)
{
	tds__GetDiscoveryModeResponse.DiscoveryMode = tt__DiscoveryMode__Discoverable;
	printf("__tds__GetDiscoveryMode\n");
	return SOAP_OK;
}
/** Web service operation '__tds__SetDiscoveryMode' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDiscoveryMode(struct soap*, _tds__SetDiscoveryMode *tds__SetDiscoveryMode, _tds__SetDiscoveryModeResponse &tds__SetDiscoveryModeResponse){ printf("__tds__SetDiscoveryMode\n"); return SOAP_OK; }

/** Web service operation '__tds__GetNetworkInterfaces' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkInterfaces(struct soap* soap, _tds__GetNetworkInterfaces *tds__GetNetworkInterfaces, _tds__GetNetworkInterfacesResponse &tds__GetNetworkInterfacesResponse)
{ 
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	bool dhcp_enabled;
	std::string addr, gateway;
	int prefix_length;

	int idx = onvif_server->GetNetworkInterfaceIdx();
	GetIpv4Address(idx, dhcp_enabled, addr, prefix_length, gateway);
	//for (int i = 0; i < 2; ++i)
	//{
	tt__NetworkInterface * netinter = soap_new_tt__NetworkInterface(soap);
	tds__GetNetworkInterfacesResponse.NetworkInterfaces.push_back(netinter);
	netinter->token = "0";
	netinter->Enabled = true;
	tt__IPv4NetworkInterface *ipv4net = soap_new_tt__IPv4NetworkInterface(soap);
	netinter->IPv4 = ipv4net;
	ipv4net->Enabled = true;
	tt__IPv4Configuration *ipv4cfg = soap_new_tt__IPv4Configuration(soap);
	ipv4net->Config = ipv4cfg;
	//ipv4cfg->DHCP = dhcp_enabled;
	ipv4cfg->DHCP = false;
	tt__PrefixedIPv4Address *ipv4addr = soap_new_tt__PrefixedIPv4Address(soap);
	ipv4cfg->Manual.push_back(ipv4addr);
	ipv4addr->Address = addr;
	ipv4addr->PrefixLength = prefix_length;
	//}

	printf("__tds__GetNetworkInterfaces\n"); 
	return SOAP_OK; 
}
/** Web service operation '__tds__SetNetworkInterfaces' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkInterfaces(struct soap*soap, _tds__SetNetworkInterfaces *tds__SetNetworkInterfaces, _tds__SetNetworkInterfacesResponse &tds__SetNetworkInterfacesResponse)
{ 
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	tt__NetworkInterfaceSetConfiguration *netinter = tds__SetNetworkInterfaces->NetworkInterface;
	if (netinter->Enabled != NULL && *(netinter->Enabled) && netinter->IPv4 != NULL && 
		(netinter->IPv4->DHCP == NULL || !*(netinter->IPv4->DHCP))
		&& netinter->IPv4->Enabled!=NULL && *(netinter->IPv4->Enabled))
	{
		tt__IPv4NetworkInterfaceSetConfiguration *ipv4set = netinter->IPv4;
		if (ipv4set->Manual.size() > 0)
		{
			tt__PrefixedIPv4Address *ipv4addr = ipv4set->Manual[0];
			//ipv4addr->Address;
			//ipv4addr->PrefixLength;
			SetIpv4Address(onvif_server->GetNetworkInterfaceIdx(), ipv4addr->Address, ipv4addr->PrefixLength);
		}
	}
	printf("__tds__SetNetworkInterfaces\n"); 
	return SOAP_OK; 
}
/** Web service operation '__tds__GetNetworkDefaultGateway' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkDefaultGateway(struct soap*soap, _tds__GetNetworkDefaultGateway *tds__GetNetworkDefaultGateway, _tds__GetNetworkDefaultGatewayResponse &tds__GetNetworkDefaultGatewayResponse)
{
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	bool dhcp_enabled;
	std::string addr, gateway;
	int prefix_length;

	int idx = onvif_server->GetNetworkInterfaceIdx();
	GetIpv4Address(idx, dhcp_enabled, addr, prefix_length, gateway);
	tt__NetworkGateway *cur_gateway = soap_new_tt__NetworkGateway(soap);
	tds__GetNetworkDefaultGatewayResponse.NetworkGateway = cur_gateway;
	cur_gateway->IPv4Address.push_back(gateway);
	printf("__tds__GetNetworkDefaultGateway\n"); 
	return SOAP_OK; 
}
/** Web service operation '__tds__SetNetworkDefaultGateway' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkDefaultGateway(struct soap*soap, _tds__SetNetworkDefaultGateway *tds__SetNetworkDefaultGateway, _tds__SetNetworkDefaultGatewayResponse &tds__SetNetworkDefaultGatewayResponse)
{ 
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	int idx = onvif_server->GetNetworkInterfaceIdx();
	if (tds__SetNetworkDefaultGateway->IPv4Address.size() > 0)
	{
		std::string set_gateway = tds__SetNetworkDefaultGateway->IPv4Address[0];
		SetGateway(idx, set_gateway);
	}
	printf("__tds__SetNetworkDefaultGateway\n"); 
	return SOAP_OK; 
}
/** Web service operation '__tds__GetDNS' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDNS(struct soap*soap, _tds__GetDNS *tds__GetDNS, _tds__GetDNSResponse &tds__GetDNSResponse)
{ 
	printf("__tds__GetDNS\n"); 
	return SOAP_OK; 
}
/** Web service operation '__tds__SetDNS' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDNS(struct soap*soap, _tds__SetDNS *tds__SetDNS, _tds__SetDNSResponse &tds__SetDNSResponse){ printf("__tds__SetDNS\n"); return SOAP_OK; }

/** Web service operation '__tds__GetNetworkProtocols' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNetworkProtocols(struct soap*, _tds__GetNetworkProtocols *tds__GetNetworkProtocols, _tds__GetNetworkProtocolsResponse &tds__GetNetworkProtocolsResponse){ printf("__tds__GetNetworkProtocols\n"); return SOAP_OK; }
/** Web service operation '__tds__SetNetworkProtocols' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNetworkProtocols(struct soap*, _tds__SetNetworkProtocols *tds__SetNetworkProtocols, _tds__SetNetworkProtocolsResponse &tds__SetNetworkProtocolsResponse){ printf("__tds__SetNetworkProtocols\n"); return SOAP_OK; }

/** Web service operation '__tds__SystemReboot' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SystemReboot(struct soap*, _tds__SystemReboot *tds__SystemReboot, _tds__SystemRebootResponse &tds__SystemRebootResponse)
{ 
	ShutdownSystem(true);
	printf("__tds__SystemReboot\n"); 
	return SOAP_OK; 
}

/** Web service operation '__tds__SetSystemFactoryDefault' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetSystemFactoryDefault(struct soap*, _tds__SetSystemFactoryDefault *tds__SetSystemFactoryDefault, _tds__SetSystemFactoryDefaultResponse &tds__SetSystemFactoryDefaultResponse){ printf("__tds__SetSystemFactoryDefault\n"); return SOAP_OK; }
/** Web service operation '__tds__UpgradeSystemFirmware' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__UpgradeSystemFirmware(struct soap*, _tds__UpgradeSystemFirmware *tds__UpgradeSystemFirmware, _tds__UpgradeSystemFirmwareResponse &tds__UpgradeSystemFirmwareResponse){ printf("__tds__UpgradeSystemFirmware\n"); return SOAP_OK; }
/** Web service operation '__tds__RestoreSystem' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__RestoreSystem(struct soap*, _tds__RestoreSystem *tds__RestoreSystem, _tds__RestoreSystemResponse &tds__RestoreSystemResponse){ printf("__tds__RestoreSystem\n"); return SOAP_OK; }
/** Web service operation '__tds__GetSystemBackup' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemBackup(struct soap*, _tds__GetSystemBackup *tds__GetSystemBackup, _tds__GetSystemBackupResponse &tds__GetSystemBackupResponse){ printf("__tds__GetSystemBackup\n"); return SOAP_OK; }
/** Web service operation '__tds__GetSystemLog' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemLog(struct soap*, _tds__GetSystemLog *tds__GetSystemLog, _tds__GetSystemLogResponse &tds__GetSystemLogResponse){ printf("__tds__GetSystemLog\n"); return SOAP_OK; }
/** Web service operation '__tds__GetSystemSupportInformation' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemSupportInformation(struct soap*, _tds__GetSystemSupportInformation *tds__GetSystemSupportInformation, _tds__GetSystemSupportInformationResponse &tds__GetSystemSupportInformationResponse){ printf("__tds__GetSystemSupportInformation\n"); return SOAP_OK; }
/** Web service operation '__tds__SetScopes' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetScopes(struct soap*, _tds__SetScopes *tds__SetScopes, _tds__SetScopesResponse &tds__SetScopesResponse){ printf("__tds__SetScopes\n"); return SOAP_OK; }
/** Web service operation '__tds__AddScopes' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__AddScopes(struct soap*, _tds__AddScopes *tds__AddScopes, _tds__AddScopesResponse &tds__AddScopesResponse){ printf("__tds__AddScopes\n"); return SOAP_OK; }
/** Web service operation '__tds__RemoveScopes' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveScopes(struct soap*, _tds__RemoveScopes *tds__RemoveScopes, _tds__RemoveScopesResponse &tds__RemoveScopesResponse){ printf("__tds__RemoveScopes\n"); return SOAP_OK; }
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteDiscoveryMode(struct soap*, _tds__GetRemoteDiscoveryMode *tds__GetRemoteDiscoveryMode, _tds__GetRemoteDiscoveryModeResponse &tds__GetRemoteDiscoveryModeResponse){ printf("__tds__GetRemoteDiscoveryMode\n"); return SOAP_OK; }
/** Web service operation '__tds__SetRemoteDiscoveryMode' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteDiscoveryMode(struct soap*, _tds__SetRemoteDiscoveryMode *tds__SetRemoteDiscoveryMode, _tds__SetRemoteDiscoveryModeResponse &tds__SetRemoteDiscoveryModeResponse){ printf("__tds__SetRemoteDiscoveryMode\n"); return SOAP_OK; }
/** Web service operation '__tds__GetDPAddresses' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDPAddresses(struct soap*, _tds__GetDPAddresses *tds__GetDPAddresses, _tds__GetDPAddressesResponse &tds__GetDPAddressesResponse){ printf("__tds__GetDPAddresses\n"); return SOAP_OK; }
/** Web service operation '__tds__GetEndpointReference' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetEndpointReference(struct soap*, _tds__GetEndpointReference *tds__GetEndpointReference, _tds__GetEndpointReferenceResponse &tds__GetEndpointReferenceResponse){ printf("__tds__GetEndpointReference\n"); return SOAP_OK; }
/** Web service operation '__tds__GetRemoteUser' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRemoteUser(struct soap*, _tds__GetRemoteUser *tds__GetRemoteUser, _tds__GetRemoteUserResponse &tds__GetRemoteUserResponse){ printf("__tds__GetRemoteUser\n"); return SOAP_OK; }
/** Web service operation '__tds__SetRemoteUser' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRemoteUser(struct soap*, _tds__SetRemoteUser *tds__SetRemoteUser, _tds__SetRemoteUserResponse &tds__SetRemoteUserResponse){ printf("__tds__SetRemoteUser\n"); return SOAP_OK; }
/** Web service operation '__tds__GetUsers' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetUsers(struct soap*, _tds__GetUsers *tds__GetUsers, _tds__GetUsersResponse &tds__GetUsersResponse){ printf("__tds__GetUsers\n"); return SOAP_OK; }
/** Web service operation '__tds__CreateUsers' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateUsers(struct soap*, _tds__CreateUsers *tds__CreateUsers, _tds__CreateUsersResponse &tds__CreateUsersResponse){ printf("__tds__CreateUsers\n"); return SOAP_OK; }
/** Web service operation '__tds__DeleteUsers' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteUsers(struct soap*, _tds__DeleteUsers *tds__DeleteUsers, _tds__DeleteUsersResponse &tds__DeleteUsersResponse){ printf("__tds__DeleteUsers\n"); return SOAP_OK; }
/** Web service operation '__tds__SetUser' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetUser(struct soap*, _tds__SetUser *tds__SetUser, _tds__SetUserResponse &tds__SetUserResponse){ printf("__tds__SetUser\n"); return SOAP_OK; }
/** Web service operation '__tds__GetWsdlUrl' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetWsdlUrl(struct soap*, _tds__GetWsdlUrl *tds__GetWsdlUrl, _tds__GetWsdlUrlResponse &tds__GetWsdlUrlResponse){ printf("__tds__GetWsdlUrl\n"); return SOAP_OK; }
/** Web service operation '__tds__SetDPAddresses' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDPAddresses(struct soap*, _tds__SetDPAddresses *tds__SetDPAddresses, _tds__SetDPAddressesResponse &tds__SetDPAddressesResponse){ printf("__tds__SetDPAddresses\n"); return SOAP_OK; }
/** Web service operation '__tds__SetHostnameFromDHCP' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetHostnameFromDHCP(struct soap*, _tds__SetHostnameFromDHCP *tds__SetHostnameFromDHCP, _tds__SetHostnameFromDHCPResponse &tds__SetHostnameFromDHCPResponse){ printf("__tds__SetHostnameFromDHCP\n"); return SOAP_OK; }
/** Web service operation '__tds__GetNTP' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetNTP(struct soap*, _tds__GetNTP *tds__GetNTP, _tds__GetNTPResponse &tds__GetNTPResponse){ printf("__tds__GetNTP\n"); return SOAP_OK; }
/** Web service operation '__tds__SetNTP' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetNTP(struct soap*, _tds__SetNTP *tds__SetNTP, _tds__SetNTPResponse &tds__SetNTPResponse){ printf("__tds__SetNTP\n"); return SOAP_OK; }
/** Web service operation '__tds__GetDynamicDNS' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDynamicDNS(struct soap*, _tds__GetDynamicDNS *tds__GetDynamicDNS, _tds__GetDynamicDNSResponse &tds__GetDynamicDNSResponse){ printf("__tds__GetDynamicDNS\n"); return SOAP_OK; }
/** Web service operation '__tds__SetDynamicDNS' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDynamicDNS(struct soap*, _tds__SetDynamicDNS *tds__SetDynamicDNS, _tds__SetDynamicDNSResponse &tds__SetDynamicDNSResponse){ printf("__tds__SetDynamicDNS\n"); return SOAP_OK; }
/** Web service operation '__tds__GetZeroConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetZeroConfiguration(struct soap*, _tds__GetZeroConfiguration *tds__GetZeroConfiguration, _tds__GetZeroConfigurationResponse &tds__GetZeroConfigurationResponse){ printf("__tds__GetZeroConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__SetZeroConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetZeroConfiguration(struct soap*, _tds__SetZeroConfiguration *tds__SetZeroConfiguration, _tds__SetZeroConfigurationResponse &tds__SetZeroConfigurationResponse){ printf("__tds__SetZeroConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__GetIPAddressFilter' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetIPAddressFilter(struct soap*, _tds__GetIPAddressFilter *tds__GetIPAddressFilter, _tds__GetIPAddressFilterResponse &tds__GetIPAddressFilterResponse){ printf("__tds__GetIPAddressFilter\n"); return SOAP_OK; }
/** Web service operation '__tds__SetIPAddressFilter' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetIPAddressFilter(struct soap*, _tds__SetIPAddressFilter *tds__SetIPAddressFilter, _tds__SetIPAddressFilterResponse &tds__SetIPAddressFilterResponse){ printf("__tds__SetIPAddressFilter\n"); return SOAP_OK; }
/** Web service operation '__tds__AddIPAddressFilter' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__AddIPAddressFilter(struct soap*, _tds__AddIPAddressFilter *tds__AddIPAddressFilter, _tds__AddIPAddressFilterResponse &tds__AddIPAddressFilterResponse){ printf("__tds__AddIPAddressFilter\n"); return SOAP_OK; }
/** Web service operation '__tds__RemoveIPAddressFilter' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__RemoveIPAddressFilter(struct soap*, _tds__RemoveIPAddressFilter *tds__RemoveIPAddressFilter, _tds__RemoveIPAddressFilterResponse &tds__RemoveIPAddressFilterResponse){ printf("__tds__RemoveIPAddressFilter\n"); return SOAP_OK; }
/** Web service operation '__tds__GetAccessPolicy' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetAccessPolicy(struct soap*, _tds__GetAccessPolicy *tds__GetAccessPolicy, _tds__GetAccessPolicyResponse &tds__GetAccessPolicyResponse){ printf("__tds__GetAccessPolicy\n"); return SOAP_OK; }
/** Web service operation '__tds__SetAccessPolicy' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetAccessPolicy(struct soap*, _tds__SetAccessPolicy *tds__SetAccessPolicy, _tds__SetAccessPolicyResponse &tds__SetAccessPolicyResponse){ printf("__tds__SetAccessPolicy\n"); return SOAP_OK; }
/** Web service operation '__tds__CreateCertificate' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateCertificate(struct soap*, _tds__CreateCertificate *tds__CreateCertificate, _tds__CreateCertificateResponse &tds__CreateCertificateResponse){ printf("__tds__CreateCertificate\n"); return SOAP_OK; }
/** Web service operation '__tds__GetCertificates' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificates(struct soap*, _tds__GetCertificates *tds__GetCertificates, _tds__GetCertificatesResponse &tds__GetCertificatesResponse){ printf("__tds__GetCertificates\n"); return SOAP_OK; }
/** Web service operation '__tds__GetCertificatesStatus' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificatesStatus(struct soap*, _tds__GetCertificatesStatus *tds__GetCertificatesStatus, _tds__GetCertificatesStatusResponse &tds__GetCertificatesStatusResponse){ printf("__tds__GetCertificatesStatus\n"); return SOAP_OK; }
/** Web service operation '__tds__SetCertificatesStatus' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetCertificatesStatus(struct soap*, _tds__SetCertificatesStatus *tds__SetCertificatesStatus, _tds__SetCertificatesStatusResponse &tds__SetCertificatesStatusResponse){ printf("__tds__SetCertificatesStatus\n"); return SOAP_OK; }
/** Web service operation '__tds__DeleteCertificates' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteCertificates(struct soap*, _tds__DeleteCertificates *tds__DeleteCertificates, _tds__DeleteCertificatesResponse &tds__DeleteCertificatesResponse){ printf("__tds__DeleteCertificates\n"); return SOAP_OK; }
/** Web service operation '__tds__GetPkcs10Request' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetPkcs10Request(struct soap*, _tds__GetPkcs10Request *tds__GetPkcs10Request, _tds__GetPkcs10RequestResponse &tds__GetPkcs10RequestResponse){ printf("__tds__GetPkcs10Request\n"); return SOAP_OK; }
/** Web service operation '__tds__LoadCertificates' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCertificates(struct soap*, _tds__LoadCertificates *tds__LoadCertificates, _tds__LoadCertificatesResponse &tds__LoadCertificatesResponse){ printf("__tds__LoadCertificates\n"); return SOAP_OK; }
/** Web service operation '__tds__GetClientCertificateMode' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetClientCertificateMode(struct soap*, _tds__GetClientCertificateMode *tds__GetClientCertificateMode, _tds__GetClientCertificateModeResponse &tds__GetClientCertificateModeResponse){ printf("__tds__GetClientCertificateMode\n"); return SOAP_OK; }
/** Web service operation '__tds__SetClientCertificateMode' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetClientCertificateMode(struct soap*, _tds__SetClientCertificateMode *tds__SetClientCertificateMode, _tds__SetClientCertificateModeResponse &tds__SetClientCertificateModeResponse){ printf("__tds__SetClientCertificateMode\n"); return SOAP_OK; }
/** Web service operation '__tds__GetRelayOutputs' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetRelayOutputs(struct soap*, _tds__GetRelayOutputs *tds__GetRelayOutputs, _tds__GetRelayOutputsResponse &tds__GetRelayOutputsResponse){ printf("__tds__GetRelayOutputs\n"); return SOAP_OK; }
/** Web service operation '__tds__SetRelayOutputSettings' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputSettings(struct soap*, _tds__SetRelayOutputSettings *tds__SetRelayOutputSettings, _tds__SetRelayOutputSettingsResponse &tds__SetRelayOutputSettingsResponse){ printf("__tds__SetRelayOutputSettings\n"); return SOAP_OK; }
/** Web service operation '__tds__SetRelayOutputState' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetRelayOutputState(struct soap*, _tds__SetRelayOutputState *tds__SetRelayOutputState, _tds__SetRelayOutputStateResponse &tds__SetRelayOutputStateResponse){ printf("__tds__SetRelayOutputState\n"); return SOAP_OK; }
/** Web service operation '__tds__SendAuxiliaryCommand' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SendAuxiliaryCommand(struct soap*, _tds__SendAuxiliaryCommand *tds__SendAuxiliaryCommand, _tds__SendAuxiliaryCommandResponse &tds__SendAuxiliaryCommandResponse){ printf("__tds__SendAuxiliaryCommand\n"); return SOAP_OK; }
/** Web service operation '__tds__GetCACertificates' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCACertificates(struct soap*, _tds__GetCACertificates *tds__GetCACertificates, _tds__GetCACertificatesResponse &tds__GetCACertificatesResponse){ printf("__tds__GetCACertificates\n"); return SOAP_OK; }
/** Web service operation '__tds__LoadCertificateWithPrivateKey' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCertificateWithPrivateKey(struct soap*, _tds__LoadCertificateWithPrivateKey *tds__LoadCertificateWithPrivateKey, _tds__LoadCertificateWithPrivateKeyResponse &tds__LoadCertificateWithPrivateKeyResponse){ printf("__tds__LoadCertificateWithPrivateKey\n"); return SOAP_OK; }
/** Web service operation '__tds__GetCertificateInformation' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetCertificateInformation(struct soap*, _tds__GetCertificateInformation *tds__GetCertificateInformation, _tds__GetCertificateInformationResponse &tds__GetCertificateInformationResponse){ printf("__tds__GetCertificateInformation\n"); return SOAP_OK; }
/** Web service operation '__tds__LoadCACertificates' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__LoadCACertificates(struct soap*, _tds__LoadCACertificates *tds__LoadCACertificates, _tds__LoadCACertificatesResponse &tds__LoadCACertificatesResponse){ printf("__tds__LoadCACertificates\n"); return SOAP_OK; }
/** Web service operation '__tds__CreateDot1XConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateDot1XConfiguration(struct soap*, _tds__CreateDot1XConfiguration *tds__CreateDot1XConfiguration, _tds__CreateDot1XConfigurationResponse &tds__CreateDot1XConfigurationResponse){ printf("__tds__CreateDot1XConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__SetDot1XConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetDot1XConfiguration(struct soap*, _tds__SetDot1XConfiguration *tds__SetDot1XConfiguration, _tds__SetDot1XConfigurationResponse &tds__SetDot1XConfigurationResponse){ printf("__tds__SetDot1XConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__GetDot1XConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot1XConfiguration(struct soap*, _tds__GetDot1XConfiguration *tds__GetDot1XConfiguration, _tds__GetDot1XConfigurationResponse &tds__GetDot1XConfigurationResponse){ printf("__tds__GetDot1XConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__GetDot1XConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot1XConfigurations(struct soap*, _tds__GetDot1XConfigurations *tds__GetDot1XConfigurations, _tds__GetDot1XConfigurationsResponse &tds__GetDot1XConfigurationsResponse){ printf("__tds__GetDot1XConfigurations\n"); return SOAP_OK; }
/** Web service operation '__tds__DeleteDot1XConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteDot1XConfiguration(struct soap*, _tds__DeleteDot1XConfiguration *tds__DeleteDot1XConfiguration, _tds__DeleteDot1XConfigurationResponse &tds__DeleteDot1XConfigurationResponse){ printf("__tds__DeleteDot1XConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__GetDot11Capabilities' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Capabilities(struct soap*, _tds__GetDot11Capabilities *tds__GetDot11Capabilities, _tds__GetDot11CapabilitiesResponse &tds__GetDot11CapabilitiesResponse){ printf("__tds__GetDot11Capabilities\n"); return SOAP_OK; }
/** Web service operation '__tds__GetDot11Status' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetDot11Status(struct soap*, _tds__GetDot11Status *tds__GetDot11Status, _tds__GetDot11StatusResponse &tds__GetDot11StatusResponse){ printf("__tds__GetDot11Status\n"); return SOAP_OK; }
/** Web service operation '__tds__ScanAvailableDot11Networks' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__ScanAvailableDot11Networks(struct soap*, _tds__ScanAvailableDot11Networks *tds__ScanAvailableDot11Networks, _tds__ScanAvailableDot11NetworksResponse &tds__ScanAvailableDot11NetworksResponse){ printf("__tds__ScanAvailableDot11Networks\n"); return SOAP_OK; }
/** Web service operation '__tds__GetSystemUris' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetSystemUris(struct soap*, _tds__GetSystemUris *tds__GetSystemUris, _tds__GetSystemUrisResponse &tds__GetSystemUrisResponse){ printf("__tds__GetSystemUris\n"); return SOAP_OK; }
/** Web service operation '__tds__StartFirmwareUpgrade' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__StartFirmwareUpgrade(struct soap*, _tds__StartFirmwareUpgrade *tds__StartFirmwareUpgrade, _tds__StartFirmwareUpgradeResponse &tds__StartFirmwareUpgradeResponse){ printf("__tds__StartFirmwareUpgrade\n"); return SOAP_OK; }
/** Web service operation '__tds__StartSystemRestore' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__StartSystemRestore(struct soap*, _tds__StartSystemRestore *tds__StartSystemRestore, _tds__StartSystemRestoreResponse &tds__StartSystemRestoreResponse){ printf("__tds__StartSystemRestore\n"); return SOAP_OK; }
/** Web service operation '__tds__GetStorageConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetStorageConfigurations(struct soap*, _tds__GetStorageConfigurations *tds__GetStorageConfigurations, _tds__GetStorageConfigurationsResponse &tds__GetStorageConfigurationsResponse){ printf("__tds__GetStorageConfigurations\n"); return SOAP_OK; }
/** Web service operation '__tds__CreateStorageConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__CreateStorageConfiguration(struct soap*, _tds__CreateStorageConfiguration *tds__CreateStorageConfiguration, _tds__CreateStorageConfigurationResponse &tds__CreateStorageConfigurationResponse){ printf("__tds__CreateStorageConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__GetStorageConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__GetStorageConfiguration(struct soap*, _tds__GetStorageConfiguration *tds__GetStorageConfiguration, _tds__GetStorageConfigurationResponse &tds__GetStorageConfigurationResponse){ printf("__tds__GetStorageConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__SetStorageConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__SetStorageConfiguration(struct soap*, _tds__SetStorageConfiguration *tds__SetStorageConfiguration, _tds__SetStorageConfigurationResponse &tds__SetStorageConfigurationResponse){ printf("__tds__SetStorageConfiguration\n"); return SOAP_OK; }
/** Web service operation '__tds__DeleteStorageConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tds__DeleteStorageConfiguration(struct soap*, _tds__DeleteStorageConfiguration *tds__DeleteStorageConfiguration, _tds__DeleteStorageConfigurationResponse &tds__DeleteStorageConfigurationResponse){ printf("__tds__DeleteStorageConfiguration\n"); return SOAP_OK; }
