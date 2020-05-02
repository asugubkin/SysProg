// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "SharedDll.h"

#pragma data_seg("Shared")
__declspec(SHAREDEXP) HWND ghWnd = NULL;
#pragma data_seg()

__declspec(allocate("Shared")) char gsSharedString[1024] = {0};

#pragma comment(linker, "/SECTION:Shared,RWS")

__declspec(SHAREDEXP) char* GetSharedString()
{
	return gsSharedString;
}

BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

