// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

HANDLE hRead, hWrite;

void Init()
{
	SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
	CreatePipe(&hRead, &hWrite, &sa, 0);
	SetHandleInformation(hWrite, HANDLE_FLAG_INHERIT, 0);

	STARTUPINFO si = { 0 };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hRead;

	PROCESS_INFORMATION pi;
	CreateProcess(NULL, (LPSTR)"AnonChild.exe", &sa, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void Cleanup()
{
	CloseHandle(hRead);
	CloseHandle(hWrite);
}

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

