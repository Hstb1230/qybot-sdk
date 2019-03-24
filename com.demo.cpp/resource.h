//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ 生成的包含文件。
// 供 com.demo.cpp.rc 使用
//
#define IDR_JSON1                       101

// Next default values for new objects
// 
#ifdef APSTUDIO_INVOKED
#ifndef APSTUDIO_READONLY_SYMBOLS
#define _APS_NEXT_RESOURCE_VALUE        102
#define _APS_NEXT_COMMAND_VALUE         40001
#define _APS_NEXT_CONTROL_VALUE         1001
#define _APS_NEXT_SYMED_VALUE           101
#endif
#endif

/*
	以下都是获取资源文件方法
	带W的是Unicode下用的
	LPCSTR是传入普通字符串时调用
	LPCWSTR是传入宽字符串时调用
	GetResourceFileData是四个函数都会调用的后续函数
*/
const char * GetResourceFileW(LPCSTR lpType, int lpName);

const char * GetResourceFileW(LPCWSTR lpType, int lpName);

const char * GetResourceFileA(LPCWSTR lpType, int lpName);

const char * GetResourceFileA(LPCSTR lpType, int lpName);

const char * GetResourceFileData(HMODULE hModule, HRSRC hRsrc);

#ifdef UNICODE
#define GetResourceFile  GetResourceFileW
#else
#define GetResourceFile  GetResourceFileA
#endif // !UNICODE
