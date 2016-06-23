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

//#ifndef SURESECURE_ONVIF_DLL_DECL
//# if defined(_WIN32) && !defined(__CYGWIN__) && defined(_WINDLL)
//#   define SURESECURE_ONVIF_DLL_DECL __declspec(dllimport)
//# else
//#   define SURESECURE_ONVIF_DLL_DECL
//# endif
//#endif

#if defined(WIN32)
# define THREAD_TYPE HANDLE
#elif defined(_POSIX_THREADS) || defined(_SC_THREADS)
# define THREAD_TYPE pthread_t
#endif

struct soap;
namespace suresecure_onvif{

	struct ProfileInfo{
		int height;
		int width;
		int frame_rate;
		std::string name;//using as profile token
		std::string uri;
	};

	class OnvifServer{
	public:
		OnvifServer();
		~OnvifServer();
		int Start(int network_interface_idx, int port);
		void Stop();

		void AddProfile(const ProfileInfo &info);
		const std::vector<ProfileInfo>& GetProfiles();
		//void DeleteProfile(int idx);
		//const std::vector<ProfileInfo>& GetProfiles();
		struct soap* GetDiscoverySoap(){ return discovery_soap_; }
		struct soap* GetOnvifSoap(){ return onvif_soap_; }
		bool IsStop(){ return stop_; }
		//const std::string& GetHost(){ return host_; }
		int GetNetworkInterfaceIdx(){ return network_interface_idx_; }
		int GetPort(){ return port_; }

		void SetFirmwareVersion(const std::string& ver){ firmware_version_ = ver; }
		void SetManufacturer(const std::string& manu){ manufacturer_ = manu; }
		void SetModel(const std::string& model){ model_ = model; }
		void SetSerailNumber(const std::string& sn){ serial_number_ = sn; }
		void SetHardwareId(const std::string& hid){ hardwareid_ = hid; }

		const std::string& GetFirmwareVersion(){ return firmware_version_; }
		const std::string& GetManufacturer(){ return manufacturer_; }
		const std::string& GetModel(){ return model_; }
		const std::string& GetSerailNumber(){ return serial_number_; }
		const std::string& GetHardwareId(){ return hardwareid_; }
	private:
		std::vector<ProfileInfo> profiles_;
		//std::string host_;
		int network_interface_idx_;
		int port_;
		bool stop_;
		struct soap *discovery_soap_;
		struct soap *onvif_soap_;
		THREAD_TYPE discovery_server_thread_;
		THREAD_TYPE onvif_server_thread_;

		//identification
		std::string firmware_version_;
		std::string manufacturer_;
		std::string model_;
		std::string serial_number_;
		std::string hardwareid_;
	};
}
