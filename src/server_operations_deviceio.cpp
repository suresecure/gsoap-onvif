#include "soapStub.h"
#include "soapH.h"

#if 0
#ifdef WIN32
#define KKKK
#else
#endif
/** Web service operation '__tmd__GetServiceCapabilities' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetServiceCapabilities(struct soap*, _tmd__GetServiceCapabilities *tmd__GetServiceCapabilities, _tmd__GetServiceCapabilitiesResponse &tmd__GetServiceCapabilitiesResponse){printf("__tmd__GetServiceCapabilities\n");return SOAP_OK;}
/** Web service operation '__tmd__GetRelayOutputOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetRelayOutputOptions(struct soap*, _tmd__GetRelayOutputOptions *tmd__GetRelayOutputOptions, _tmd__GetRelayOutputOptionsResponse &tmd__GetRelayOutputOptionsResponse){printf("__tmd__GetRelayOutputOptions\n");return SOAP_OK;}
/** Web service operation '__tmd__GetAudioSources' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSources(struct soap*, tmd__Get *tmd__GetAudioSources, tmd__GetResponse &tmd__GetAudioSourcesResponse){printf("__tmd__GetAudioSources\n");return SOAP_OK;}
/** Web service operation '__tmd__GetAudioOutputs' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputs(struct soap*, tmd__Get *tmd__GetAudioOutputs, tmd__GetResponse &tmd__GetAudioOutputsResponse){printf("__tmd__GetAudioOutputs\n");return SOAP_OK;}
/** Web service operation '__tmd__GetVideoSources' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSources(struct soap*, tmd__Get *tmd__GetVideoSources, tmd__GetResponse &tmd__GetVideoSourcesResponse){printf("__tmd__GetVideoSources\n");return SOAP_OK;}
/** Web service operation '__tmd__GetVideoOutputs' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputs(struct soap*, _tmd__GetVideoOutputs *tmd__GetVideoOutputs, _tmd__GetVideoOutputsResponse &tmd__GetVideoOutputsResponse){printf("__tmd__GetVideoOutputs\n");return SOAP_OK;}
/** Web service operation '__tmd__GetVideoSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSourceConfiguration(struct soap*, _tmd__GetVideoSourceConfiguration *tmd__GetVideoSourceConfiguration, _tmd__GetVideoSourceConfigurationResponse &tmd__GetVideoSourceConfigurationResponse){printf("__tmd__GetVideoSourceConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__GetVideoOutputConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputConfiguration(struct soap*, _tmd__GetVideoOutputConfiguration *tmd__GetVideoOutputConfiguration, _tmd__GetVideoOutputConfigurationResponse &tmd__GetVideoOutputConfigurationResponse){printf("__tmd__GetVideoOutputConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__GetAudioSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSourceConfiguration(struct soap*, _tmd__GetAudioSourceConfiguration *tmd__GetAudioSourceConfiguration, _tmd__GetAudioSourceConfigurationResponse &tmd__GetAudioSourceConfigurationResponse){printf("__tmd__GetAudioSourceConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__GetAudioOutputConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputConfiguration(struct soap*, _tmd__GetAudioOutputConfiguration *tmd__GetAudioOutputConfiguration, _tmd__GetAudioOutputConfigurationResponse &tmd__GetAudioOutputConfigurationResponse){printf("__tmd__GetAudioOutputConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__SetVideoSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetVideoSourceConfiguration(struct soap*, _tmd__SetVideoSourceConfiguration *tmd__SetVideoSourceConfiguration, _tmd__SetVideoSourceConfigurationResponse &tmd__SetVideoSourceConfigurationResponse){printf("__tmd__SetVideoSourceConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__SetVideoOutputConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetVideoOutputConfiguration(struct soap*, _tmd__SetVideoOutputConfiguration *tmd__SetVideoOutputConfiguration, _tmd__SetVideoOutputConfigurationResponse &tmd__SetVideoOutputConfigurationResponse){printf("__tmd__SetVideoOutputConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__SetAudioSourceConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetAudioSourceConfiguration(struct soap*, _tmd__SetAudioSourceConfiguration *tmd__SetAudioSourceConfiguration, _tmd__SetAudioSourceConfigurationResponse &tmd__SetAudioSourceConfigurationResponse){printf("__tmd__SetAudioSourceConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__SetAudioOutputConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetAudioOutputConfiguration(struct soap*, _tmd__SetAudioOutputConfiguration *tmd__SetAudioOutputConfiguration, _tmd__SetAudioOutputConfigurationResponse &tmd__SetAudioOutputConfigurationResponse){printf("__tmd__SetAudioOutputConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__GetVideoSourceConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoSourceConfigurationOptions(struct soap*, _tmd__GetVideoSourceConfigurationOptions *tmd__GetVideoSourceConfigurationOptions, _tmd__GetVideoSourceConfigurationOptionsResponse &tmd__GetVideoSourceConfigurationOptionsResponse){printf("__tmd__GetVideoSourceConfigurationOptions\n");return SOAP_OK;}
/** Web service operation '__tmd__GetVideoOutputConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetVideoOutputConfigurationOptions(struct soap*, _tmd__GetVideoOutputConfigurationOptions *tmd__GetVideoOutputConfigurationOptions, _tmd__GetVideoOutputConfigurationOptionsResponse &tmd__GetVideoOutputConfigurationOptionsResponse){printf("__tmd__GetVideoOutputConfigurationOptions\n");return SOAP_OK;}
/** Web service operation '__tmd__GetAudioSourceConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioSourceConfigurationOptions(struct soap*, _tmd__GetAudioSourceConfigurationOptions *tmd__GetAudioSourceConfigurationOptions, _tmd__GetAudioSourceConfigurationOptionsResponse &tmd__GetAudioSourceConfigurationOptionsResponse){printf("__tmd__GetAudioSourceConfigurationOptions\n");return SOAP_OK;}
/** Web service operation '__tmd__GetAudioOutputConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetAudioOutputConfigurationOptions(struct soap*, _tmd__GetAudioOutputConfigurationOptions *tmd__GetAudioOutputConfigurationOptions, _tmd__GetAudioOutputConfigurationOptionsResponse &tmd__GetAudioOutputConfigurationOptionsResponse){printf("__tmd__GetAudioOutputConfigurationOptions\n");return SOAP_OK;}
/** Web service operation '__tmd__GetRelayOutputs' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetRelayOutputs(struct soap*, _tds__GetRelayOutputs *tds__GetRelayOutputs, _tds__GetRelayOutputsResponse &tds__GetRelayOutputsResponse){printf("__tmd__GetRelayOutputs\n");return SOAP_OK;}
/** Web service operation '__tmd__SetRelayOutputSettings' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetRelayOutputSettings(struct soap*, _tmd__SetRelayOutputSettings *tmd__SetRelayOutputSettings, _tmd__SetRelayOutputSettingsResponse &tmd__SetRelayOutputSettingsResponse){printf("__tmd__SetRelayOutputSettings\n");return SOAP_OK;}
/** Web service operation '__tmd__SetRelayOutputState' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetRelayOutputState(struct soap*, _tds__SetRelayOutputState *tds__SetRelayOutputState, _tds__SetRelayOutputStateResponse &tds__SetRelayOutputStateResponse){printf("__tmd__SetRelayOutputState\n");return SOAP_OK;}
/** Web service operation '__tmd__GetDigitalInputs' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetDigitalInputs(struct soap*, _tmd__GetDigitalInputs *tmd__GetDigitalInputs, _tmd__GetDigitalInputsResponse &tmd__GetDigitalInputsResponse){printf("__tmd__GetDigitalInputs\n");return SOAP_OK;}
/** Web service operation '__tmd__GetDigitalInputConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetDigitalInputConfigurationOptions(struct soap*, _tmd__GetDigitalInputConfigurationOptions *tmd__GetDigitalInputConfigurationOptions, _tmd__GetDigitalInputConfigurationOptionsResponse &tmd__GetDigitalInputConfigurationOptionsResponse){printf("__tmd__GetDigitalInputConfigurationOptions\n");return SOAP_OK;}
/** Web service operation '__tmd__SetDigitalInputConfigurations' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetDigitalInputConfigurations(struct soap*, _tmd__SetDigitalInputConfigurations *tmd__SetDigitalInputConfigurations, _tmd__SetDigitalInputConfigurationsResponse &tmd__SetDigitalInputConfigurationsResponse){printf("__tmd__SetDigitalInputConfigurations\n");return SOAP_OK;}
/** Web service operation '__tmd__GetSerialPorts' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPorts(struct soap*, _tmd__GetSerialPorts *tmd__GetSerialPorts, _tmd__GetSerialPortsResponse &tmd__GetSerialPortsResponse){printf("__tmd__GetSerialPorts\n");return SOAP_OK;}
/** Web service operation '__tmd__GetSerialPortConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPortConfiguration(struct soap*, _tmd__GetSerialPortConfiguration *tmd__GetSerialPortConfiguration, _tmd__GetSerialPortConfigurationResponse &tmd__GetSerialPortConfigurationResponse){printf("__tmd__GetSerialPortConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__SetSerialPortConfiguration' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SetSerialPortConfiguration(struct soap*, _tmd__SetSerialPortConfiguration *tmd__SetSerialPortConfiguration, _tmd__SetSerialPortConfigurationResponse &tmd__SetSerialPortConfigurationResponse){printf("__tmd__SetSerialPortConfiguration\n");return SOAP_OK;}
/** Web service operation '__tmd__GetSerialPortConfigurationOptions' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__GetSerialPortConfigurationOptions(struct soap*, _tmd__GetSerialPortConfigurationOptions *tmd__GetSerialPortConfigurationOptions, _tmd__GetSerialPortConfigurationOptionsResponse &tmd__GetSerialPortConfigurationOptionsResponse){printf("__tmd__GetSerialPortConfigurationOptions\n");return SOAP_OK;}
/** Web service operation '__tmd__SendReceiveSerialCommand' (returns SOAP_OK or error code) */
SOAP_FMAC5 int SOAP_FMAC6 __tmd__SendReceiveSerialCommand(struct soap*, _tmd__SendReceiveSerialCommand *tmd__SendReceiveSerialCommand, _tmd__SendReceiveSerialCommandResponse &tmd__SendReceiveSerialCommandResponse){printf("__tmd__SendReceiveSerialCommand\n");return SOAP_OK;}
#endif
