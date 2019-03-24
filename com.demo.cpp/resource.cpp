#include "stdafx.h"
#include "resource.h"

/* 取DLL自身句柄 */
HMODULE GetSelfModuleHandle()
{
	MEMORY_BASIC_INFORMATION mbi;
	return ((::VirtualQuery(GetSelfModuleHandle, &mbi, sizeof(mbi)) != 0) ? (HMODULE)mbi.AllocationBase : NULL);
}

/* LPCWSTR转LPCSTR */
LPCSTR w2c(LPCWSTR wText)
{
	DWORD dwNum = WideCharToMultiByte(CP_ACP, NULL, wText, -1, NULL, 0, NULL, FALSE);//把第五个参数设成NULL的到宽字符串的长度包括结尾符
	LPSTR psText = NULL;
	psText = new char[dwNum];
	if(!psText)
	{
		delete[] psText;
		psText = NULL;
	}
	WideCharToMultiByte(CP_ACP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	LPCSTR pscTest = psText;
	//delete[] psText;
	return pscTest;
}

/* LPCSTR转LPCWSTR */
LPCWSTR c2w(LPCSTR sText)
{
	DWORD dwNum = MultiByteToWideChar(CP_ACP, 0, sText, -1, NULL, 0);//把第五个参数设成NULL的到宽字符串的长度包括结尾符

	LPWSTR pwText = NULL;
	pwText = new wchar_t[dwNum];
	if(!pwText)
	{
		delete[] pwText;
		pwText = NULL;
	}
	unsigned nLen = MultiByteToWideChar(CP_ACP, 0, sText, -1, pwText, dwNum + 10);
	if(nLen >= 0)
	{
		pwText[nLen] = 0;
	}
	return pwText;
}

const char * GetResourceFileW(LPCSTR lpType, int lpName)
{
	return GetResourceFileW(c2w(lpType), lpName);
}

const char * GetResourceFileW(LPCWSTR lpType, int lpName)
{
	//取DLL自身句柄
	HMODULE hModule = GetSelfModuleHandle();
	//读取资源包文件
	HRSRC hRsrc = FindResourceW(hModule, MAKEINTRESOURCEW(lpName), lpType);
	return GetResourceFileData(hModule, hRsrc);
}

const char * GetResourceFileA(LPCWSTR lpType, int lpName) {
	return GetResourceFileA(w2c(lpType), lpName);
}

const char * GetResourceFileA(LPCSTR lpType, int lpName) {
	//取DLL自身句柄
	HMODULE hModule = GetSelfModuleHandle();
	//读取资源包文件
	HRSRC hRsrc = FindResourceA(hModule, MAKEINTRESOURCEA(lpName), lpType);
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
