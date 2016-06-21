#pragma once
#include <string>

struct DateTime{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

std::string GetTimeZone();
void SetTimeZone(std::string);

struct DateTime GetLocalDateTime();
struct DateTime GetUtcDateTime();
void SetLocalDateTime(struct DateTime);
bool SetUtcDateTime(struct DateTime);

std::string GetHostName();
bool SetHostName(std::string);

void GetIpv4Address(int &idx, bool &dhcp_enabled, std::string& addr, int&prefix_length, std::string &gateway);
void SetNetworkInterface(int idx, const std::string &addr, int prefix_length, const std::string&gateway);
void SetIpv4Address(int idx, const std::string&addr, int prefix_length);
void SetGateway(int idx, const std::string&gateway);

void ShutdownSystem(bool reboot);
//unsigned long long GetCpuFreq();//获取CPU频率,单位: MHZ
std::string GetCpuManID();
std::string GetCpuType();
