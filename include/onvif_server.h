#pragma once
#include <string>
#include <vector>

#ifndef WIN32
# include <unistd.h>	/* defines _POSIX_THREADS if pthreads are available */
#else
# define ssize_t int
# include <io.h>
# include <sys/types.h>
# include <process.h>
# include <windows.h>
#endif

#if defined(_POSIX_THREADS) || defined(_SC_THREADS)
# include <pthread.h>
#endif

struct ProfileInfo{
	int height;
	int width;
	int frame_rate;
	std::string name;//using as profile token
	std::string uri;
};

struct soap;

#if defined(WIN32)
# define THREAD_TYPE HANDLE
#elif defined(_POSIX_THREADS) || defined(_SC_THREADS)
# define THREAD_TYPE pthread_t
#endif

class OnvifServer{
public:
	OnvifServer();
	~OnvifServer();
	int Start(std::string host, int port);
	void Stop();

	void AddProfile(const ProfileInfo &info);
	const std::vector<ProfileInfo>& GetProfiles();
	//void DeleteProfile(int idx);
	//const std::vector<ProfileInfo>& GetProfiles();
	struct soap* GetDiscoverySoap(){ return discovery_soap_; }
	struct soap* GetOnvifSoap(){ return onvif_soap_; }
	bool IsStop(){ return stop_; }
	std::string GetHost(){ return host_; }
	int GetPort(){ return port_; }
private:
	std::vector<ProfileInfo> profiles_;
	std::string host_;
	int port_;
	bool stop_;
	struct soap *discovery_soap_;
	struct soap *onvif_soap_;
	THREAD_TYPE discovery_server_thread_;
	THREAD_TYPE onvif_server_thread_;
};
