#include "stdafx.h"
#include "resource.h"
#include "utils/encodingConvert.h"

/* 取DLL自身句柄 */
HMODULE GetSelfModuleHandle()
{
	MEMORY_BASIC_INFORMATION mbi;
	return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
}

const char * GetResourceFileW(nstring lpType, int lpName)
{
	//取DLL自身句柄
	HMODULE hModule = GetSelfModuleHandle();
	//读取资源包文件
	wstring wlpType(lpType);
	HRSRC hRsrc = FindResourceW(hModule, MAKEINTRESOURCEW(lpName), wlpType.c_str());
	return GetResourceFileData(hModule, hRsrc);
}

const char * GetResourceFileA(nstring lpType, int lpName) {
	//取DLL自身句柄
	HMODULE hModule = GetSelfModuleHandle();
	//读取资源包文件
	string clpType(lpType);
	HRSRC hRsrc = FindResourceA(hModule, MAKEINTRESOURCEA(lpName), clpType.c_str());
	return GetResourceFileData(hModule, hRsrc);
}

const char * GetResourceFileData(HMODULE hModule, HRSRC hRsrc)
{
	if(NULL == hRsrc) return nullptr;
	//获取资源的大小
	DWORD dwSize = SizeofResource(hModule, hRsrc);
	if(0 == dwSize) return nullptr;
	//加载资源
	HGLOBAL hGlobal = LoadResource(hModule, hRsrc);
	if(NULL == hGlobal) return nullptr;
	//锁定资源
	LPVOID pBuffer = LockResource(hGlobal);
	if(NULL == pBuffer) {
		GlobalUnlock(hGlobal);
		return nullptr;
	}
	static char * pChar = nullptr;
	if(pChar) delete[] pChar;
	pChar = new char[dwSize + 1];
	memcpy(pChar, pBuffer, dwSize * sizeof(char));
	GlobalUnlock(hGlobal);
	return pChar;
}
