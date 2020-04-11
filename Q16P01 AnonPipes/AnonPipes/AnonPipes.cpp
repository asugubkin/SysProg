// AnonPipes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
using namespace std;

int main()
{
	HANDLE hRead, hWrite;
	SECURITY_ATTRIBUTES sa = {0};
	sa.bInheritHandle = TRUE;
	BOOL bRes = CreatePipe(&hRead, &hWrite, &sa, 0);

	STARTUPINFO si = {0};
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hRead;
	si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	si.hStdError = GetStdHandle(STD_ERROR_HANDLE);

//	SetStdHandle(STD_OUTPUT_HANDLE, hWrite);

	PROCESS_INFORMATION pi;

	CreateProcess(NULL, (LPSTR)"AnonChild.exe", &sa, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

	string s;
	while (true)
	{
		cin >> s;
		DWORD dwWrite;
		WriteFile(hWrite, s.c_str(), s.length(), &dwWrite, nullptr);
	}

	CloseHandle(hRead);
	CloseHandle(hWrite);

}

