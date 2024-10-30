#pragma once

#include "KeyValues.h"

bool CGlobal_KeyValues::LoadFromBuffer(KeyValues* pKval, const char* const szName, const char* const szBuff, void* pSys, const char* const szPath)
{
	static const DWORD dwLoadFromBuffer = U::Pattern.Find("client.dll", "55 8B EC 83 EC 34 57 8B 7D 0C 89 4D FC 85 FF 75 09");
	XASSERT(dwLoadFromBuffer == 0x0);

	if (!dwLoadFromBuffer)
		return false;

	return reinterpret_cast<int(__thiscall*)(KeyValues*, char const*, const char*, void*, const char*)>(dwLoadFromBuffer)(pKval, szName, szBuff, pSys, szPath);
}

KeyValues* CGlobal_KeyValues::Init(KeyValues* pKval, const char* const szName)
{
	static const DWORD dwKeyValsInit = U::Pattern.Find("client.dll", "55 8B EC 33 C0 56 8B F1 C7 06");
	XASSERT(dwKeyValsInit == 0x0);

	if (!dwKeyValsInit)
		return nullptr;

	return reinterpret_cast<KeyValues * (__thiscall*)(KeyValues*, const char*)>(dwKeyValsInit)(pKval, szName);
}