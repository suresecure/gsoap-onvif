�Ӱٶ���������gsoap�����������ѹ http://pan.baidu.com/s/1pLUvtmr
���ɸ���wsdd10��onvif�ӿ��ļ�
1. gsoap_onvif_complier_win32_01
2. add #import "wsdd10.h" in the onvif.h
3. �޸�gsoap/import/wsa5.h��ע�͵�SOAP_ENV_Fault�������������wsa.h�еĶ����ظ���(��һ���ڵ�ǰĿ¼���Ѿ���ɣ�����Ӧ�����Լ��)
4. gsoap_onvif_complier_win32_02
5. ��DeviceBinding.nsmap�޸�Ϊnsmap.cpp�����޸�����
//{"wsa5", "http://www.w3.org/2005/08/addressing", "http://schemas.xmlsoap.org/ws/2004/08/addressing", NULL},
{"wsa5", "http://www.w3.org/2005/08/addressing", NULL, NULL},
����ֻ��������wsa5����wsa5ƥ��
6. �޸�soapStub.h�ļ���ע�͵�
#define SOAP_WSA_2005
��һ�У�ʹ��wsaapi.hʹ��wsa2004���������ᱨ����Ϊimport����wsdd10��ʹ�õ���wsa2004


���ɵ�����wsdd10�ӿ�
gsoap_wsdd10_win32.bat
�����Ժ��޸�namespace�ļ�
���ɵ������ռ��ļ���������޸ģ�����discovery�޷��ɹ�������ǳ��ؼ�
 {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
 {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
��������Ҫ�޸�Ϊ��
 {"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope"�� "http://schemas.xmlsoap.org/soap/envelope/", NULL},
 {"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/",NULL},
ǰ��һ��д����Ȼ�ڽ���ʱû�����⣬�����ڷ���ʱ��ʹ��ǰ��������ռ����֣�����C#����onvif device manager�޷����ա�
ͬʱ���û��device�����ռ䣬����Ҫ�ټ�һ��
 {"tds", "http://www.onvif.org/ver10/device/wsdl", NULL, NULL},
