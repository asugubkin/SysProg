// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

HANDLE hRead, hWrite;

void Init()
{
	SECURITY_ATTRIBUTES sa = { 0 };
	sa.bInheritHandle = TRUE;
	BOOL bRes = CreatePipe(&hRead, &hWrite, &sa, 0);

	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hRead;
//	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	PROCESS_INFORMATION pi;

	CreateProcess(NULL, (LPSTR)"AnonChild.exe", &sa, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
}

void Cleanup()
{
	CloseHandle(hRead);
	CloseHandle(hWrite);
}

#include <iostream>

extern "C" _declspec(dllexport) void __stdcall Send(const char* pStr)
{
	DWORD dwWrite;
	WriteFile(hWrite, pStr, strlen(pStr), &dwWrite, nullptr);
}


BOOL APIENTRY DllMain( HMODULE hModule,
					   DWORD  ul_reason_for_call,
					   LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		Init();
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		Cleanup();
		break;
	}
	return TRUE;
}

