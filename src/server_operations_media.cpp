#include "soapStub.h"
#include "soapH.h"
#include "onvif_server.h"

using namespace suresecure_onvif;
/** Web service operation '__trt__GetServiceCapabilities' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetServiceCapabilities(struct soap*, _trt__GetServiceCapabilities *trt__GetServiceCapabilities, _trt__GetServiceCapabilitiesResponse &trt__GetServiceCapabilitiesResponse)
{
	printf("Media: Get Service Capabilities!\n");
	return SOAP_OK; 
}
/** Web service operation '__trt__GetVideoSources' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSources(struct soap*soap, _trt__GetVideoSources *trt__GetVideoSources, _trt__GetVideoSourcesResponse &trt__GetVideoSourcesResponse)
{
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	std::vector<ProfileInfo> profiles = onvif_server->GetProfiles();
	for (int i = 0; i < profiles.size(); ++i)
	{
		tt__VideoSource *vs_0 = soap_new_tt__VideoSource(soap);
		vs_0->token = "vsrc_"+profiles[i].name;
		vs_0->Framerate = profiles[i].frame_rate;
		tt__VideoResolution *resolution = soap_new_tt__VideoResolution(soap);
		resolution->Height = profiles[i].height;
		resolution->Width = profiles[i].width;
		vs_0->Resolution = resolution;
		trt__GetVideoSourcesResponse.VideoSources.push_back(vs_0);
	}
	printf("Media: Get video sources!\n");
	return SOAP_OK;
}
static tt__Profile* CreateProfile(struct soap*soap, ProfileInfo profile_info)
{
	tt__Profile *profile0 = soap_new_tt__Profile(soap);
	profile0->Name = profile_info.name;
	profile0->token = profile_info.name;
	tt__VideoSourceConfiguration *vsconfig = soap_new_tt__VideoSourceConfiguration(soap);
	profile0->VideoSourceConfiguration = vsconfig;
	vsconfig->SourceToken = "vsrc_" + profile_info.name;
	vsconfig->Bounds = soap_new_tt__IntRectangle(soap);
	vsconfig->Bounds->x = vsconfig->Bounds->y = 1;
	vsconfig->Bounds->height = profile_info.height;
	vsconfig->Bounds->width = profile_info.width;
	vsconfig->Name = "vsrc_cfg_" + profile_info.name;
	vsconfig->UseCount = 1;
	vsconfig->token = "vsrc_cfg_" + profile_info.name;

	tt__VideoEncoderConfiguration *vcconfig = soap_new_tt__VideoEncoderConfiguration(soap);
	profile0->VideoEncoderConfiguration = vcconfig;
	vcconfig->Quality = 100;
	vcconfig->Encoding = tt__VideoEncoding__H264;
	vcconfig->Resolution = soap_new_tt__VideoResolution(soap);
	vcconfig->Resolution->Height = profile_info.height;
	vcconfig->Resolution->Width = profile_info.width;
	vcconfig->Name = "venc_cfg_" + profile_info.name;
	vcconfig->UseCount = 1;
	vcconfig->token = "venc_cfg_" + profile_info.name;
	return profile0;
}
/** Web service operation '__trt__GetProfiles' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfiles(struct soap*soap, _trt__GetProfiles *trt__GetProfiles, _trt__GetProfilesResponse &trt__GetProfilesResponse)
{
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	std::vector<ProfileInfo> profiles = onvif_server->GetProfiles();
	for (int i = 0; i < profiles.size(); ++i)
	{
		tt__Profile *profile0 = CreateProfile(soap, profiles[i]);
		trt__GetProfilesResponse.Profiles.push_back(profile0);
	}
	printf("Media: Get profiles!\n");
	return SOAP_OK;
}
static int FindProfile(std::vector<ProfileInfo> profiles, std::string token)
{
	int target_idx = -1;
	for (int i = 0; i < profiles.size(); ++i)
	{
		if (profiles[i].name == token)
		{
			target_idx = i;
			break;
		}
	}
	return target_idx;
}

/** Web service operation '__trt__GetProfile' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetProfile(struct soap*soap, _trt__GetProfile *trt__GetProfile, _trt__GetProfileResponse &trt__GetProfileResponse)
{
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	std::vector<ProfileInfo> profiles = onvif_server->GetProfiles();
	int target_idx = FindProfile(profiles, trt__GetProfile->ProfileToken);
	if (target_idx == -1)
		return SOAP_OK;
	ProfileInfo target_profile = profiles[target_idx];
	tt__Profile *profile0 = CreateProfile(soap, target_profile);
	trt__GetProfileResponse.Profile = profile0;

	printf("Media: Get profile!\n");
	return SOAP_OK;
}
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetStreamUri(struct soap*soap, _trt__GetStreamUri *trt__GetStreamUri, _trt__GetStreamUriResponse &trt__GetStreamUriResponse)
{
	OnvifServer *onvif_server = (OnvifServer*)soap->user;
	std::vector<ProfileInfo> profiles = onvif_server->GetProfiles();
	int idx = FindProfile(profiles, trt__GetStreamUri->ProfileToken);
	if (idx == -1)
		return SOAP_OK;
	tt__MediaUri * media_uri = soap_new_tt__MediaUri(soap);
	media_uri->Uri = profiles[idx].uri;
	trt__GetStreamUriResponse.MediaUri = media_uri;
	printf("Media: Get stream uri!\n");
	return SOAP_OK;
}
/** Web service operation '__trt__GetVideoSourceConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurations(struct soap*soap, _trt__GetVideoSourceConfigurations *trt__GetVideoSourceConfigurations, _trt__GetVideoSourceConfigurationsResponse &trt__GetVideoSourceConfigurationsResponse)
{
	printf("Media: Get video source configurations!\n");
	return SOAP_OK;
}
/** Web service operation '__trt__GetVideoEncoderConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurations(struct soap*, _trt__GetVideoEncoderConfigurations *trt__GetVideoEncoderConfigurations, _trt__GetVideoEncoderConfigurationsResponse &trt__GetVideoEncoderConfigurationsResponse)
{
	printf("Media: Get video encoder configurations!\n");
	return SOAP_OK;
}
/** Web service operation '__trt__GetStreamUri' (returns SOAP_OK or error code) */
/** Web service operation '__trt__GetAudioSources' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSources(struct soap*, _trt__GetAudioSources *trt__GetAudioSources, _trt__GetAudioSourcesResponse &trt__GetAudioSourcesResponse){ printf("__trt__GetAudioSources\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioOutputs' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputs(struct soap*, _trt__GetAudioOutputs *trt__GetAudioOutputs, _trt__GetAudioOutputsResponse &trt__GetAudioOutputsResponse){ printf("__trt__GetAudioOutputs\n"); return SOAP_OK; }
/** Web service operation '__trt__CreateProfile' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__CreateProfile(struct soap*, _trt__CreateProfile *trt__CreateProfile, _trt__CreateProfileResponse &trt__CreateProfileResponse){ printf("__trt__CreateProfile\n"); return SOAP_OK; }
/** Web service operation '__trt__AddVideoEncoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoEncoderConfiguration(struct soap*, _trt__AddVideoEncoderConfiguration *trt__AddVideoEncoderConfiguration, _trt__AddVideoEncoderConfigurationResponse &trt__AddVideoEncoderConfigurationResponse){ printf("__trt__AddVideoEncoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__AddVideoSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoSourceConfiguration(struct soap*, _trt__AddVideoSourceConfiguration *trt__AddVideoSourceConfiguration, _trt__AddVideoSourceConfigurationResponse &trt__AddVideoSourceConfigurationResponse){ printf("__trt__AddVideoSourceConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__AddAudioEncoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioEncoderConfiguration(struct soap*, _trt__AddAudioEncoderConfiguration *trt__AddAudioEncoderConfiguration, _trt__AddAudioEncoderConfigurationResponse &trt__AddAudioEncoderConfigurationResponse){ printf("__trt__AddAudioEncoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__AddAudioSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioSourceConfiguration(struct soap*, _trt__AddAudioSourceConfiguration *trt__AddAudioSourceConfiguration, _trt__AddAudioSourceConfigurationResponse &trt__AddAudioSourceConfigurationResponse){ printf("__trt__AddAudioSourceConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__AddPTZConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddPTZConfiguration(struct soap*, _trt__AddPTZConfiguration *trt__AddPTZConfiguration, _trt__AddPTZConfigurationResponse &trt__AddPTZConfigurationResponse){ printf("__trt__AddPTZConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__AddVideoAnalyticsConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddVideoAnalyticsConfiguration(struct soap*, _trt__AddVideoAnalyticsConfiguration *trt__AddVideoAnalyticsConfiguration, _trt__AddVideoAnalyticsConfigurationResponse &trt__AddVideoAnalyticsConfigurationResponse){ printf("__trt__AddVideoAnalyticsConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__AddMetadataConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddMetadataConfiguration(struct soap*, _trt__AddMetadataConfiguration *trt__AddMetadataConfiguration, _trt__AddMetadataConfigurationResponse &trt__AddMetadataConfigurationResponse){ printf("__trt__AddMetadataConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__AddAudioOutputConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioOutputConfiguration(struct soap*, _trt__AddAudioOutputConfiguration *trt__AddAudioOutputConfiguration, _trt__AddAudioOutputConfigurationResponse &trt__AddAudioOutputConfigurationResponse){ printf("__trt__AddAudioOutputConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__AddAudioDecoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__AddAudioDecoderConfiguration(struct soap*, _trt__AddAudioDecoderConfiguration *trt__AddAudioDecoderConfiguration, _trt__AddAudioDecoderConfigurationResponse &trt__AddAudioDecoderConfigurationResponse){ printf("__trt__AddAudioDecoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemoveVideoEncoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoEncoderConfiguration(struct soap*, _trt__RemoveVideoEncoderConfiguration *trt__RemoveVideoEncoderConfiguration, _trt__RemoveVideoEncoderConfigurationResponse &trt__RemoveVideoEncoderConfigurationResponse){ printf("__trt__RemoveVideoEncoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemoveVideoSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoSourceConfiguration(struct soap*, _trt__RemoveVideoSourceConfiguration *trt__RemoveVideoSourceConfiguration, _trt__RemoveVideoSourceConfigurationResponse &trt__RemoveVideoSourceConfigurationResponse){ printf("__trt__RemoveVideoSourceConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemoveAudioEncoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioEncoderConfiguration(struct soap*, _trt__RemoveAudioEncoderConfiguration *trt__RemoveAudioEncoderConfiguration, _trt__RemoveAudioEncoderConfigurationResponse &trt__RemoveAudioEncoderConfigurationResponse){ printf("__trt__RemoveAudioEncoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemoveAudioSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioSourceConfiguration(struct soap*, _trt__RemoveAudioSourceConfiguration *trt__RemoveAudioSourceConfiguration, _trt__RemoveAudioSourceConfigurationResponse &trt__RemoveAudioSourceConfigurationResponse){ printf("__trt__RemoveAudioSourceConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemovePTZConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemovePTZConfiguration(struct soap*, _trt__RemovePTZConfiguration *trt__RemovePTZConfiguration, _trt__RemovePTZConfigurationResponse &trt__RemovePTZConfigurationResponse){ printf("__trt__RemovePTZConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemoveVideoAnalyticsConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveVideoAnalyticsConfiguration(struct soap*, _trt__RemoveVideoAnalyticsConfiguration *trt__RemoveVideoAnalyticsConfiguration, _trt__RemoveVideoAnalyticsConfigurationResponse &trt__RemoveVideoAnalyticsConfigurationResponse){ printf("__trt__RemoveVideoAnalyticsConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemoveMetadataConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveMetadataConfiguration(struct soap*, _trt__RemoveMetadataConfiguration *trt__RemoveMetadataConfiguration, _trt__RemoveMetadataConfigurationResponse &trt__RemoveMetadataConfigurationResponse){ printf("__trt__RemoveMetadataConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemoveAudioOutputConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioOutputConfiguration(struct soap*, _trt__RemoveAudioOutputConfiguration *trt__RemoveAudioOutputConfiguration, _trt__RemoveAudioOutputConfigurationResponse &trt__RemoveAudioOutputConfigurationResponse){ printf("__trt__RemoveAudioOutputConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__RemoveAudioDecoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__RemoveAudioDecoderConfiguration(struct soap*, _trt__RemoveAudioDecoderConfiguration *trt__RemoveAudioDecoderConfiguration, _trt__RemoveAudioDecoderConfigurationResponse &trt__RemoveAudioDecoderConfigurationResponse){ printf("__trt__RemoveAudioDecoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__DeleteProfile' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__DeleteProfile(struct soap*, _trt__DeleteProfile *trt__DeleteProfile, _trt__DeleteProfileResponse &trt__DeleteProfileResponse){ printf("__trt__DeleteProfile\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioSourceConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurations(struct soap*, _trt__GetAudioSourceConfigurations *trt__GetAudioSourceConfigurations, _trt__GetAudioSourceConfigurationsResponse &trt__GetAudioSourceConfigurationsResponse){ printf("__trt__GetAudioSourceConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioEncoderConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurations(struct soap*, _trt__GetAudioEncoderConfigurations *trt__GetAudioEncoderConfigurations, _trt__GetAudioEncoderConfigurationsResponse &trt__GetAudioEncoderConfigurationsResponse){ printf("__trt__GetAudioEncoderConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetVideoAnalyticsConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfigurations(struct soap*, _trt__GetVideoAnalyticsConfigurations *trt__GetVideoAnalyticsConfigurations, _trt__GetVideoAnalyticsConfigurationsResponse &trt__GetVideoAnalyticsConfigurationsResponse){ printf("__trt__GetVideoAnalyticsConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetMetadataConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurations(struct soap*, _trt__GetMetadataConfigurations *trt__GetMetadataConfigurations, _trt__GetMetadataConfigurationsResponse &trt__GetMetadataConfigurationsResponse){ printf("__trt__GetMetadataConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioOutputConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurations(struct soap*, _trt__GetAudioOutputConfigurations *trt__GetAudioOutputConfigurations, _trt__GetAudioOutputConfigurationsResponse &trt__GetAudioOutputConfigurationsResponse){ printf("__trt__GetAudioOutputConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioDecoderConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurations(struct soap*, _trt__GetAudioDecoderConfigurations *trt__GetAudioDecoderConfigurations, _trt__GetAudioDecoderConfigurationsResponse &trt__GetAudioDecoderConfigurationsResponse){ printf("__trt__GetAudioDecoderConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetVideoSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfiguration(struct soap*, _trt__GetVideoSourceConfiguration *trt__GetVideoSourceConfiguration, _trt__GetVideoSourceConfigurationResponse &trt__GetVideoSourceConfigurationResponse){ printf("__trt__GetVideoSourceConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetVideoEncoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfiguration(struct soap*, _trt__GetVideoEncoderConfiguration *trt__GetVideoEncoderConfiguration, _trt__GetVideoEncoderConfigurationResponse &trt__GetVideoEncoderConfigurationResponse){ printf("__trt__GetVideoEncoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfiguration(struct soap*, _trt__GetAudioSourceConfiguration *trt__GetAudioSourceConfiguration, _trt__GetAudioSourceConfigurationResponse &trt__GetAudioSourceConfigurationResponse){ printf("__trt__GetAudioSourceConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioEncoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfiguration(struct soap*, _trt__GetAudioEncoderConfiguration *trt__GetAudioEncoderConfiguration, _trt__GetAudioEncoderConfigurationResponse &trt__GetAudioEncoderConfigurationResponse){ printf("__trt__GetAudioEncoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetVideoAnalyticsConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoAnalyticsConfiguration(struct soap*, _trt__GetVideoAnalyticsConfiguration *trt__GetVideoAnalyticsConfiguration, _trt__GetVideoAnalyticsConfigurationResponse &trt__GetVideoAnalyticsConfigurationResponse){ printf("__trt__GetVideoAnalyticsConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetMetadataConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfiguration(struct soap*, _trt__GetMetadataConfiguration *trt__GetMetadataConfiguration, _trt__GetMetadataConfigurationResponse &trt__GetMetadataConfigurationResponse){ printf("__trt__GetMetadataConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioOutputConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfiguration(struct soap*, _trt__GetAudioOutputConfiguration *trt__GetAudioOutputConfiguration, _trt__GetAudioOutputConfigurationResponse &trt__GetAudioOutputConfigurationResponse){ printf("__trt__GetAudioOutputConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioDecoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfiguration(struct soap*, _trt__GetAudioDecoderConfiguration *trt__GetAudioDecoderConfiguration, _trt__GetAudioDecoderConfigurationResponse &trt__GetAudioDecoderConfigurationResponse){ printf("__trt__GetAudioDecoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetCompatibleVideoEncoderConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoEncoderConfigurations(struct soap*, _trt__GetCompatibleVideoEncoderConfigurations *trt__GetCompatibleVideoEncoderConfigurations, _trt__GetCompatibleVideoEncoderConfigurationsResponse &trt__GetCompatibleVideoEncoderConfigurationsResponse){ printf("__trt__GetCompatibleVideoEncoderConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetCompatibleVideoSourceConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoSourceConfigurations(struct soap*, _trt__GetCompatibleVideoSourceConfigurations *trt__GetCompatibleVideoSourceConfigurations, _trt__GetCompatibleVideoSourceConfigurationsResponse &trt__GetCompatibleVideoSourceConfigurationsResponse){ printf("__trt__GetCompatibleVideoSourceConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetCompatibleAudioEncoderConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioEncoderConfigurations(struct soap*, _trt__GetCompatibleAudioEncoderConfigurations *trt__GetCompatibleAudioEncoderConfigurations, _trt__GetCompatibleAudioEncoderConfigurationsResponse &trt__GetCompatibleAudioEncoderConfigurationsResponse){ printf("__trt__GetCompatibleAudioEncoderConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetCompatibleAudioSourceConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioSourceConfigurations(struct soap*, _trt__GetCompatibleAudioSourceConfigurations *trt__GetCompatibleAudioSourceConfigurations, _trt__GetCompatibleAudioSourceConfigurationsResponse &trt__GetCompatibleAudioSourceConfigurationsResponse){ printf("__trt__GetCompatibleAudioSourceConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetCompatibleVideoAnalyticsConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleVideoAnalyticsConfigurations(struct soap*, _trt__GetCompatibleVideoAnalyticsConfigurations *trt__GetCompatibleVideoAnalyticsConfigurations, _trt__GetCompatibleVideoAnalyticsConfigurationsResponse &trt__GetCompatibleVideoAnalyticsConfigurationsResponse){ printf("__trt__GetCompatibleVideoAnalyticsConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetCompatibleMetadataConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleMetadataConfigurations(struct soap*, _trt__GetCompatibleMetadataConfigurations *trt__GetCompatibleMetadataConfigurations, _trt__GetCompatibleMetadataConfigurationsResponse &trt__GetCompatibleMetadataConfigurationsResponse){ printf("__trt__GetCompatibleMetadataConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetCompatibleAudioOutputConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioOutputConfigurations(struct soap*, _trt__GetCompatibleAudioOutputConfigurations *trt__GetCompatibleAudioOutputConfigurations, _trt__GetCompatibleAudioOutputConfigurationsResponse &trt__GetCompatibleAudioOutputConfigurationsResponse){ printf("__trt__GetCompatibleAudioOutputConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__GetCompatibleAudioDecoderConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetCompatibleAudioDecoderConfigurations(struct soap*, _trt__GetCompatibleAudioDecoderConfigurations *trt__GetCompatibleAudioDecoderConfigurations, _trt__GetCompatibleAudioDecoderConfigurationsResponse &trt__GetCompatibleAudioDecoderConfigurationsResponse){ printf("__trt__GetCompatibleAudioDecoderConfigurations\n"); return SOAP_OK; }
/** Web service operation '__trt__SetVideoSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoSourceConfiguration(struct soap*, _trt__SetVideoSourceConfiguration *trt__SetVideoSourceConfiguration, _trt__SetVideoSourceConfigurationResponse &trt__SetVideoSourceConfigurationResponse){ printf("__trt__SetVideoSourceConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__SetVideoEncoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoEncoderConfiguration(struct soap*, _trt__SetVideoEncoderConfiguration *trt__SetVideoEncoderConfiguration, _trt__SetVideoEncoderConfigurationResponse &trt__SetVideoEncoderConfigurationResponse){ printf("__trt__SetVideoEncoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__SetAudioSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioSourceConfiguration(struct soap*, _trt__SetAudioSourceConfiguration *trt__SetAudioSourceConfiguration, _trt__SetAudioSourceConfigurationResponse &trt__SetAudioSourceConfigurationResponse){ printf("__trt__SetAudioSourceConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__SetAudioEncoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioEncoderConfiguration(struct soap*, _trt__SetAudioEncoderConfiguration *trt__SetAudioEncoderConfiguration, _trt__SetAudioEncoderConfigurationResponse &trt__SetAudioEncoderConfigurationResponse){ printf("__trt__SetAudioEncoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__SetVideoAnalyticsConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoAnalyticsConfiguration(struct soap*, _trt__SetVideoAnalyticsConfiguration *trt__SetVideoAnalyticsConfiguration, _trt__SetVideoAnalyticsConfigurationResponse &trt__SetVideoAnalyticsConfigurationResponse){ printf("__trt__SetVideoAnalyticsConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__SetMetadataConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetMetadataConfiguration(struct soap*, _trt__SetMetadataConfiguration *trt__SetMetadataConfiguration, _trt__SetMetadataConfigurationResponse &trt__SetMetadataConfigurationResponse){ printf("__trt__SetMetadataConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__SetAudioOutputConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioOutputConfiguration(struct soap*, _trt__SetAudioOutputConfiguration *trt__SetAudioOutputConfiguration, _trt__SetAudioOutputConfigurationResponse &trt__SetAudioOutputConfigurationResponse){ printf("__trt__SetAudioOutputConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__SetAudioDecoderConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetAudioDecoderConfiguration(struct soap*, _trt__SetAudioDecoderConfiguration *trt__SetAudioDecoderConfiguration, _trt__SetAudioDecoderConfigurationResponse &trt__SetAudioDecoderConfigurationResponse){ printf("__trt__SetAudioDecoderConfiguration\n"); return SOAP_OK; }
/** Web service operation '__trt__GetVideoSourceConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceConfigurationOptions(struct soap*, _trt__GetVideoSourceConfigurationOptions *trt__GetVideoSourceConfigurationOptions, _trt__GetVideoSourceConfigurationOptionsResponse &trt__GetVideoSourceConfigurationOptionsResponse){ printf("__trt__GetVideoSourceConfigurationOptions\n"); return SOAP_OK; }
/** Web service operation '__trt__GetVideoEncoderConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoEncoderConfigurationOptions(struct soap*, _trt__GetVideoEncoderConfigurationOptions *trt__GetVideoEncoderConfigurationOptions, _trt__GetVideoEncoderConfigurationOptionsResponse &trt__GetVideoEncoderConfigurationOptionsResponse){ printf("__trt__GetVideoEncoderConfigurationOptions\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioSourceConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioSourceConfigurationOptions(struct soap*, _trt__GetAudioSourceConfigurationOptions *trt__GetAudioSourceConfigurationOptions, _trt__GetAudioSourceConfigurationOptionsResponse &trt__GetAudioSourceConfigurationOptionsResponse){ printf("__trt__GetAudioSourceConfigurationOptions\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioEncoderConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioEncoderConfigurationOptions(struct soap*, _trt__GetAudioEncoderConfigurationOptions *trt__GetAudioEncoderConfigurationOptions, _trt__GetAudioEncoderConfigurationOptionsResponse &trt__GetAudioEncoderConfigurationOptionsResponse){ printf("__trt__GetAudioEncoderConfigurationOptions\n"); return SOAP_OK; }
/** Web service operation '__trt__GetMetadataConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetMetadataConfigurationOptions(struct soap*, _trt__GetMetadataConfigurationOptions *trt__GetMetadataConfigurationOptions, _trt__GetMetadataConfigurationOptionsResponse &trt__GetMetadataConfigurationOptionsResponse){ printf("__trt__GetMetadataConfigurationOptions\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioOutputConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioOutputConfigurationOptions(struct soap*, _trt__GetAudioOutputConfigurationOptions *trt__GetAudioOutputConfigurationOptions, _trt__GetAudioOutputConfigurationOptionsResponse &trt__GetAudioOutputConfigurationOptionsResponse){ printf("__trt__GetAudioOutputConfigurationOptions\n"); return SOAP_OK; }
/** Web service operation '__trt__GetAudioDecoderConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetAudioDecoderConfigurationOptions(struct soap*, _trt__GetAudioDecoderConfigurationOptions *trt__GetAudioDecoderConfigurationOptions, _trt__GetAudioDecoderConfigurationOptionsResponse &trt__GetAudioDecoderConfigurationOptionsResponse){ printf("__trt__GetAudioDecoderConfigurationOptions\n"); return SOAP_OK; }
/** Web service operation '__trt__GetGuaranteedNumberOfVideoEncoderInstances' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetGuaranteedNumberOfVideoEncoderInstances(struct soap*, _trt__GetGuaranteedNumberOfVideoEncoderInstances *trt__GetGuaranteedNumberOfVideoEncoderInstances, _trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse &trt__GetGuaranteedNumberOfVideoEncoderInstancesResponse){ printf("__trt__GetGuaranteedNumberOfVideoEncoderInstances\n"); return SOAP_OK; }
/** Web service operation '__trt__StartMulticastStreaming' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__StartMulticastStreaming(struct soap*, _trt__StartMulticastStreaming *trt__StartMulticastStreaming, _trt__StartMulticastStreamingResponse &trt__StartMulticastStreamingResponse){ printf("__trt__StartMulticastStreaming\n"); return SOAP_OK; }
/** Web service operation '__trt__StopMulticastStreaming' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__StopMulticastStreaming(struct soap*, _trt__StopMulticastStreaming *trt__StopMulticastStreaming, _trt__StopMulticastStreamingResponse &trt__StopMulticastStreamingResponse){ printf("__trt__StopMulticastStreaming\n"); return SOAP_OK; }
/** Web service operation '__trt__SetSynchronizationPoint' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetSynchronizationPoint(struct soap*, _trt__SetSynchronizationPoint *trt__SetSynchronizationPoint, _trt__SetSynchronizationPointResponse &trt__SetSynchronizationPointResponse){ printf("__trt__SetSynchronizationPoint\n"); return SOAP_OK; }
/** Web service operation '__trt__GetSnapshotUri' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetSnapshotUri(struct soap*, _trt__GetSnapshotUri *trt__GetSnapshotUri, _trt__GetSnapshotUriResponse &trt__GetSnapshotUriResponse){ printf("__trt__GetSnapshotUri\n"); return SOAP_OK; }
/** Web service operation '__trt__GetVideoSourceModes' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetVideoSourceModes(struct soap*, _trt__GetVideoSourceModes *trt__GetVideoSourceModes, _trt__GetVideoSourceModesResponse &trt__GetVideoSourceModesResponse){ printf("__trt__GetVideoSourceModes\n"); return SOAP_OK; }
/** Web service operation '__trt__SetVideoSourceMode' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetVideoSourceMode(struct soap*, _trt__SetVideoSourceMode *trt__SetVideoSourceMode, _trt__SetVideoSourceModeResponse &trt__SetVideoSourceModeResponse){ printf("__trt__SetVideoSourceMode\n"); return SOAP_OK; }
/** Web service operation '__trt__GetOSDs' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSDs(struct soap*, _trt__GetOSDs *trt__GetOSDs, _trt__GetOSDsResponse &trt__GetOSDsResponse){ printf("__trt__GetOSDs\n"); return SOAP_OK; }
/** Web service operation '__trt__GetOSD' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSD(struct soap*, _trt__GetOSD *trt__GetOSD, _trt__GetOSDResponse &trt__GetOSDResponse){ printf("__trt__GetOSD\n"); return SOAP_OK; }
/** Web service operation '__trt__GetOSDOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__GetOSDOptions(struct soap*, _trt__GetOSDOptions *trt__GetOSDOptions, _trt__GetOSDOptionsResponse &trt__GetOSDOptionsResponse){ printf("__trt__GetOSDOptions\n"); return SOAP_OK; }
/** Web service operation '__trt__SetOSD' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__SetOSD(struct soap*, _trt__SetOSD *trt__SetOSD, _trt__SetOSDResponse &trt__SetOSDResponse){ printf("__trt__SetOSD\n"); return SOAP_OK; }
/** Web service operation '__trt__CreateOSD' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__CreateOSD(struct soap*, _trt__CreateOSD *trt__CreateOSD, _trt__CreateOSDResponse &trt__CreateOSDResponse){ printf("__trt__CreateOSD\n"); return SOAP_OK; }
/** Web service operation '__trt__DeleteOSD' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __trt__DeleteOSD(struct soap*, _trt__DeleteOSD *trt__DeleteOSD, _trt__DeleteOSDResponse &trt__DeleteOSDResponse){ printf("__trt__DeleteOSD\n"); return SOAP_OK; }
