#include <ctime>
#include <iostream>
//#include <Windows.h>
//#include <winsock2.h>
//#include <iphlpapi.h>
//#include <stdio.h>
//#include <stdlib.h>
//#pragma comment(lib, "IPHLPAPI.lib")
#include <winsock2.h>
#include <iphlpapi.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <stdarg.h>  // For va_start, etc.
#include <memory>    // For std::unique_ptr
#include "system_utils.h"

#pragma comment(lib, "IPHLPAPI.lib")

namespace suresecure_onvif{

	std::string string_format(const std::string fmt, ...) {
		int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
		std::string str;
		va_list ap;
		while (1) {     // Maximum two passes on a POSIX system...
			str.resize(size);
			va_start(ap, fmt);
			int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
			va_end(ap);
			if (n > -1 && n < size) {  // Everything worked
				str.resize(n);
				return str;
			}
			if (n > -1)  // Needed size returned
				size = n + 1;   // For null char
			else
				size *= 2;      // Guess at a larger size (OS specific)
		}
		return str;
	}
	//std::string string_format(const std::string fmt_str, ...) {
	//    int final_n, n = ((int)fmt_str.size()) * 2; /* Reserve two times as much as the length of the fmt_str */
	//    std::string str;
	//    std::unique_ptr<char[]> formatted;
	//    va_list ap;
	//    while(1) {
	//        formatted.reset(new char[n]); /* Wrap the plain char array into the unique_ptr */
	//        strcpy(&formatted[0], fmt_str.c_str());
	//        va_start(ap, fmt_str);
	//        final_n = vsnprintf(&formatted[0], n, fmt_str.c_str(), ap);
	//        va_end(ap);
	//        if (final_n < 0 || final_n >= n)
	//            n += abs(final_n - n + 1);
	//        else
	//            break;
	//    }
	//    return std::string(formatted.get());
	//}


	std::string GetTimeZone()
	{
		//TIME_ZONE_INFORMATION time_zone_info;
		//GetTimeZoneInformation(&time_zone_info);
		//return std::string(time_zone_info.StandardName);
		return std::string("GMT +8");
	}
	void SetTimeZone(std::string);

	struct DateTime GetLocalDateTime()
	{
		SYSTEMTIME system_time;
		GetLocalTime(&system_time);
		struct DateTime ret;
		ret.year = system_time.wYear;
		ret.month = system_time.wMonth;
		ret.day = system_time.wDay;
		ret.hour = system_time.wHour;
		ret.minute = system_time.wMinute;
		ret.second = system_time.wSecond;
		return ret;
	}
	struct DateTime GetUtcDateTime()
	{
		SYSTEMTIME system_time;
		GetSystemTime(&system_time);
		struct DateTime ret;
		ret.year = system_time.wYear;
		ret.month = system_time.wMonth;
		ret.day = system_time.wDay;
		ret.hour = system_time.wHour;
		ret.minute = system_time.wMinute;
		ret.second = system_time.wSecond;
		return ret;
	}
	void SetLocalDateTime(struct DateTime date_time)
	{
		SYSTEMTIME dt;
		dt.wYear = date_time.year;
		dt.wMonth = date_time.month;
		dt.wDay = date_time.day;
		dt.wHour = date_time.hour;
		dt.wMinute = date_time.minute;
		dt.wSecond = date_time.second;
		SetLocalTime(&dt);
	}
	bool SetUtcDateTime(struct DateTime date_time)
	{
		SYSTEMTIME dt;
		dt.wYear = date_time.year;
		dt.wMonth = date_time.month;
		dt.wDay = date_time.day;
		dt.wHour = date_time.hour;
		dt.wMinute = date_time.minute;
		dt.wSecond = date_time.second;
		dt.wMilliseconds = 0;
		bool ret = SetSystemTime(&dt);
		DWORD error;
		if (!ret)
		{
			error = GetLastError();
		}
		return ret;
	}

	std::string GetHostName()
	{
		char name[200];
		gethostname(name, 200);
		return std::string(name);
	}
	bool SetHostName(std::string)
	{
		//sethostname()
		return true;
	}

	void GetIpv4Address(int &idx, bool &dhcp_enabled, std::string& addr, int&prefix_length, std::string &gateway);

	void EnableDhcp(int idx)
	{
		std::string cmd = string_format("netsh interface ip set address %d dhcp", idx);
		system(cmd.c_str());
		return;
	}

	//void SetNetworkInterface(int idx, const std::string &addr, int prefix_length, const std::string&gateway=std::string())
	void SetNetworkInterface(int idx, const std::string &addr, int prefix_length, const std::string&gateway)
	{
		//name source ip netmask gateway
		"netsh interface ip set address 28 static 192.168.1.120 255.255.255.0 192.168.1.1";
		std::string cmd = string_format("netsh interface ip set address %d static %s/%d gateway=%s", idx, addr.c_str(), prefix_length,
			gateway.c_str());
		system(cmd.c_str());
		return;
	}

	void SetIpv4Address(int idx, const std::string&addr, int prefix_length)
	{
		bool dhcp_enabled;
		std::string old_addr, old_gateway;
		int old_prefix_length;
		GetIpv4Address(idx, dhcp_enabled, old_addr, old_prefix_length, old_gateway);
		return SetNetworkInterface(idx, addr, prefix_length, old_gateway);
	}

	void SetGateway(int idx, const std::string&gateway)
	{
		bool dhcp_enabled;
		std::string old_addr, old_gateway;
		int old_prefix_length;
		GetIpv4Address(idx, dhcp_enabled, old_addr, old_prefix_length, old_gateway);
		//cannot set netmask without ip address
		//if (dhcp_enabled)
		//	return false;
		return SetNetworkInterface(idx, old_addr, old_prefix_length, gateway);
	}

#define WORKING_BUFFER_SIZE 15000
#define MAX_TRIES 3

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

	//int main(int argc, char **argv)
	void GetIpv4Address(int &idx, bool &dhcp_enabled, std::string& addr, int&prefix_length, std::string &gateway)
	{
		/* Declare and initialize variables */

		DWORD dwSize = 0;
		DWORD dwRetVal = 0;

		unsigned int i = 0;

		// Set the flags to pass to GetAdaptersAddresses
		ULONG flags = GAA_FLAG_INCLUDE_PREFIX | GAA_FLAG_INCLUDE_GATEWAYS;

		// default to unspecified address family (both)
		ULONG family = AF_UNSPEC;

		LPVOID lpMsgBuf = NULL;

		PIP_ADAPTER_ADDRESSES pAddresses = NULL;
		ULONG outBufLen = 0;
		ULONG Iterations = 0;

		PIP_ADAPTER_ADDRESSES pCurrAddresses = NULL;
		PIP_ADAPTER_UNICAST_ADDRESS pUnicast = NULL;
		PIP_ADAPTER_ANYCAST_ADDRESS pAnycast = NULL;
		PIP_ADAPTER_MULTICAST_ADDRESS pMulticast = NULL;
		IP_ADAPTER_DNS_SERVER_ADDRESS *pDnServer = NULL;
		IP_ADAPTER_PREFIX *pPrefix = NULL;

		//if (atoi(argv[1]) == 4)
		family = AF_INET;
		//else if (atoi(argv[1]) == 6)
		//    family = AF_INET6;

		// Allocate a 15 KB buffer to start with.
		outBufLen = WORKING_BUFFER_SIZE;

		do {

			pAddresses = (IP_ADAPTER_ADDRESSES *)MALLOC(outBufLen);
			if (pAddresses == NULL) {
				printf
					("Memory allocation failed for IP_ADAPTER_ADDRESSES struct\n");
				exit(1);
			}

			dwRetVal =
				GetAdaptersAddresses(family, flags, NULL, pAddresses, &outBufLen);

			if (dwRetVal == ERROR_BUFFER_OVERFLOW) {
				FREE(pAddresses);
				pAddresses = NULL;
			}
			else {
				break;
			}

			Iterations++;

		} while ((dwRetVal == ERROR_BUFFER_OVERFLOW) && (Iterations < MAX_TRIES));

		if (dwRetVal == NO_ERROR) {
			// If successful, output some information from the data we received
			pCurrAddresses = pAddresses;
			bool matched = false;
			while (pCurrAddresses){
				if (idx < 0)
				{
					idx = pCurrAddresses->IfIndex;
					matched = true;
					break;
				}
				else if (pCurrAddresses->IfIndex == idx)
				{
					matched = true;
					break;
				}
				pCurrAddresses = pCurrAddresses->Next;
			}
			if (!matched)
				return;
			//while (pCurrAddresses) 
			//printf("\tLength of the IP_ADAPTER_ADDRESS struct: %ld\n",
			//       pCurrAddresses->Length);
			//         printf("\tIfIndex (IPv4 interface): %u\n", pCurrAddresses->IfIndex);
			//         printf("\tAdapter name: %s\n", pCurrAddresses->AdapterName);

			//printf("\tDHCP enabled:%d\n", pCurrAddresses->Dhcpv4Enabled);
			dhcp_enabled = pCurrAddresses->Dhcpv4Enabled;

			pUnicast = pCurrAddresses->FirstUnicastAddress;
			if (pUnicast != NULL) {
				for (i = 0; pUnicast != NULL; i++)
				{
					SOCKADDR_IN* ipv4 = reinterpret_cast<SOCKADDR_IN*>(pUnicast->Address.lpSockaddr);

					//char str_buffer[100] = { 0 };
					//inet_ntoa(AF_INET, &(ipv4->sin_addr), str_buffer, 100);
					std::string ip_addr(inet_ntoa(ipv4->sin_addr));
					//int x = ip_addr.compare("169.254");
					//x = ip_addr.find_first_of("169.254");
					//x = ip_addr.("169.254");
					if (ip_addr.compare(0, 7, "169.254") != 0)
					{
						addr = std::string(ip_addr);
						prefix_length = pUnicast->OnLinkPrefixLength;
						break;
					}
					//printf("\tUnicast Address: %s\n", str_buffer);
					//pUnicast->Address.lpSockaddr->sa_data
					pUnicast = pUnicast->Next;
				}
				//printf("\tNumber of Unicast Addresses: %d\n", i);
			}

			//pAnycast = pCurrAddresses->FirstAnycastAddress;
			//if (pAnycast) {
			//    for (i = 0; pAnycast != NULL; i++)
			//        pAnycast = pAnycast->Next;
			//    printf("\tNumber of Anycast Addresses: %d\n", i);
			//} else
			//    printf("\tNo Anycast Addresses\n");

			//pMulticast = pCurrAddresses->FirstMulticastAddress;
			//if (pMulticast) {
			//    for (i = 0; pMulticast != NULL; i++)
			//        pMulticast = pMulticast->Next;
			//    printf("\tNumber of Multicast Addresses: %d\n", i);
			//} else
			//    printf("\tNo Multicast Addresses\n");

			//        pDnServer = pCurrAddresses->FirstDnsServerAddress;
			//        if (pDnServer) {
			//for (i = 0; pDnServer != NULL; i++)
			//{
			//	sockaddr_in *dns = (sockaddr_in*)(pDnServer->Address.lpSockaddr);
			//	printf("\tDNS Server Address: %s\n", inet_ntoa(dns->sin_addr));
			//                pDnServer = pDnServer->Next;
			//}
			//            printf("\tNumber of DNS Server Addresses: %d\n", i);
			//        } else
			//            printf("\tNo DNS Server Addresses\n");
			//pCurrAddresses->FirstGatewayAddress->Address;
			PIP_ADAPTER_GATEWAY_ADDRESS_LH curgateway = pCurrAddresses->FirstGatewayAddress;
			//while (curgateway != NULL)
			if (curgateway != NULL)
			{
				sockaddr_in *gateway_sockin = (sockaddr_in*)(curgateway->Address.lpSockaddr);
				//printf("\tFirst Gateway: %s\n", inet_ntoa(gateway->sin_addr));
				gateway = std::string(inet_ntoa(gateway_sockin->sin_addr));
				//curgateway = curgateway->Next;
			}
			//printf("\tDNS Suffix: %wS\n", pCurrAddresses->DnsSuffix);
			//printf("\tDescription: %wS\n", pCurrAddresses->Description);
			//printf("\tFriendly name: %wS\n", pCurrAddresses->FriendlyName);

			//if (pCurrAddresses->PhysicalAddressLength != 0) {
			//    printf("\tPhysical address: ");
			//    for (i = 0; i < (int) pCurrAddresses->PhysicalAddressLength;
			//         i++) {
			//        if (i == (pCurrAddresses->PhysicalAddressLength - 1))
			//            printf("%.2X\n",
			//                   (int) pCurrAddresses->PhysicalAddress[i]);
			//        else
			//            printf("%.2X-",
			//                   (int) pCurrAddresses->PhysicalAddress[i]);
			//    }
			//}
			//printf("\tFlags: %ld\n", pCurrAddresses->Flags);
			//printf("\tMtu: %lu\n", pCurrAddresses->Mtu);
			//printf("\tIfType: %ld\n", pCurrAddresses->IfType);
			//printf("\tOperStatus: %ld\n", pCurrAddresses->OperStatus);
			//printf("\tIpv6IfIndex (IPv6 interface): %u\n",
			//       pCurrAddresses->Ipv6IfIndex);
			//printf("\tZoneIndices (hex): ");
			//for (i = 0; i < 16; i++)
			//    printf("%lx ", pCurrAddresses->ZoneIndices[i]);
			//printf("\n");

			//printf("\tTransmit link speed: %I64u\n", pCurrAddresses->TransmitLinkSpeed);
			//printf("\tReceive link speed: %I64u\n", pCurrAddresses->ReceiveLinkSpeed);

			//pPrefix = pCurrAddresses->FirstPrefix;
			//if (pPrefix) {
			//    for (i = 0; pPrefix != NULL; i++)
			//        pPrefix = pPrefix->Next;
			//    printf("\tNumber of IP Adapter Prefix entries: %d\n", i);
			//} else
			//    printf("\tNumber of IP Adapter Prefix entries: 0\n");

			//printf("\n");

			//pCurrAddresses = pCurrAddresses->Next;
		}
		else {
			//return false;
			//printf("Call to GetAdaptersAddresses failed with error: %d\n",
			//       dwRetVal);
			//if (dwRetVal == ERROR_NO_DATA)
			//    printf("\tNo addresses were found for the requested parameters\n");
			//else {

			//    if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER |
			//            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
			//            NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),   
			//            // Default language
			//            (LPTSTR) & lpMsgBuf, 0, NULL)) {
			//        printf("\tError: %s", lpMsgBuf);
			//        LocalFree(lpMsgBuf);
			//        if (pAddresses)
			//            FREE(pAddresses);
			//        exit(1);
			//    }
			//}
		}

		if (pAddresses) {
			FREE(pAddresses);
		}

		return;
	}

	void ShutdownSystem(bool reboot)
	{
		HANDLE hToken;
		TOKEN_PRIVILEGES tkp;

		//获取进程标志
		if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
			return;
		//qFatal("Failed to Open Process Token!");

		//获取关机特权的LUID
		LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
		tkp.PrivilegeCount = 1;
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		//获取这个进程的关机特权
		AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
		if (GetLastError() != ERROR_SUCCESS)
		{
			printf("Failed to Adjust Token Privileges!");
			return;
		}

		// 强制关闭计算机
		if (reboot)
			ExitWindowsEx(EWX_REBOOT, 0);
		else
			ExitWindowsEx(EWX_SHUTDOWN, 0);
		return;
	}

	//用来存储eax,ebx,ecx,edx四个寄存器的信息
	DWORD deax;
	DWORD debx;
	DWORD decx;
	DWORD dedx;
	static void ExeCPUID(DWORD veax)  //初始化CPU
	{
		__asm
		{
			mov eax, veax
				cpuid
				mov deax, eax
				mov debx, ebx
				mov decx, ecx
				mov dedx, edx
		}
	}

	/*    在Intel Pentium以上级别的CPU中，有一个称为“时间戳（Time Stamp）”的部件，
			它以64位无符号整型数的格式，记录了自CPU上电以来所经过的时钟周期数。
			由于目前的CPU主频都非常高，因此这个部件可以达到纳秒级的计时精度。
			这个精确性是上述两种方法所无法比拟的。
			在Pentium以上的CPU中，提供了一条机器指令RDTSC（Read Time Stamp Counter）
			来读取这个时间戳的数字，并将其保存在EDX:EAX寄存器对中
			*/
	//unsigned long long GetCpuFreq()//获取CPU频率,单位: MHZ
	//{
	//    unsigned long long start,over;
	//    _asm
	//    {
	//        RDTSC
	//                mov start,eax
	//    }
	//    Sleep(50);
	//    _asm
	//    {
	//        RDTSC
	//                mov over,eax
	//    }
	//    return (over-start)/50000;
	//}
	/*   把eax = 0作为输入参数，可以得到CPU的制造商信息。
			 cpuid指令执行以后，会返回一个12字符的制造商信息，
			 前四个字符的ASC码按低位到高位放在ebx，中间四个放在edx，最后四个字符放在ecx。
			 */
	std::string GetCpuManID()//获取制造商信息
	{
		char ID[25];
		memset(ID, 0, sizeof(ID));

		ExeCPUID(0);          //初始化
		memcpy(ID + 0, &debx, 4); //制造商信息复制到数组
		memcpy(ID + 4, &dedx, 4);
		memcpy(ID + 8, &decx, 4);

		return std::string(ID);
	}

	/*  在我的电脑上点击右键，选择属性，可以在窗口的下面看到一条CPU的信息，
			这就是CPU的商标字符串。CPU的商标字符串也是通过cpuid得到的。
			由于商标的字符串很长(48个字符)，所以不能在一次cpuid指令执行时全部得到，
			所以intel把它分成了3个操作，eax的输入参数分别是0x80000002,0x80000003,0x80000004，
			每次返回的16个字符，按照从低位到高位的顺序依次放在eax, ebx, ecx, edx。
			因此，可以用循环的方式，每次执行完以后保存结果，然后执行下一次cpuid。
			*/
	std::string GetCpuType()
	{
		const DWORD id = 0x80000002; //从0x80000002开始,到0x80000004结束
		char CPUType[49];//用来存储CPU型号信息
		memset(CPUType, 0, sizeof(CPUType));//初始化数组

		for (DWORD t = 0; t < 3; t++)
		{
			ExeCPUID(id + t);
			//每次循环结束,保存信息到数组
			memcpy(CPUType + 16 * t + 0, &deax, 4);
			memcpy(CPUType + 16 * t + 4, &debx, 4);
			memcpy(CPUType + 16 * t + 8, &decx, 4);
			memcpy(CPUType + 16 * t + 12, &dedx, 4);
		}

		return std::string(CPUType);
	}
}
