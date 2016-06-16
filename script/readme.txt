从百度云盘下载gsoap程序包，并解压 http://pan.baidu.com/s/1pLUvtmr
生成附加wsdd10的onvif接口文件
1. gsoap_onvif_complier_win32_01
2. add #import "wsdd10.h" in the onvif.h
3. 修改gsoap/import/wsa5.h，注释掉SOAP_ENV_Fault函数，否则会与wsa.h中的定义重复。(这一步在当前目录下已经完成，但是应该予以检查)
4. gsoap_onvif_complier_win32_02
5. 将DeviceBinding.nsmap修改为nsmap.cpp，并修改内容
//{"wsa5", "http://www.w3.org/2005/08/addressing", "http://schemas.xmlsoap.org/ws/2004/08/addressing", NULL},
{"wsa5", "http://www.w3.org/2005/08/addressing", NULL, NULL},
这样只有真正的wsa5才与wsa5匹配
6. 修改soapStub.h文件，注释掉
#define SOAP_WSA_2005
这一行，使得wsaapi.h使用wsa2004，否则编译会报错，因为import的是wsdd10，使用的是wsa2004


生成单纯的wsdd10接口
gsoap_wsdd10_win32.bat
生成以后修改namespace文件
生成的命名空间文件必须进行修改，否则discovery无法成功，这个非常关键
 {"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
 {"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
这两项需要修改为：
 {"SOAP-ENV", "http://www.w3.org/2003/05/soap-envelope"， "http://schemas.xmlsoap.org/soap/envelope/", NULL},
 {"SOAP-ENC", "http://www.w3.org/2003/05/soap-encoding", "http://schemas.xmlsoap.org/soap/encoding/",NULL},
前面一种写法虽然在接收时没有问题，但是在发送时会使用前面的命名空间名字，导致C#或是onvif device manager无法接收。
同时如果没有device明明空间，还需要再加一个
 {"tds", "http://www.onvif.org/ver10/device/wsdl", NULL, NULL},
