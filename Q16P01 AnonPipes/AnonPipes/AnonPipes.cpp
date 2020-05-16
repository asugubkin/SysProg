// AnonPipes.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <io.h>
#include <fcntl.h>

int main()
{
	HANDLE hRead, hWrite;
	SECURITY_ATTRIBUTES sa = { sizeof(sa), NULL, TRUE };
	CreatePipe(&hRead, &hWrite, &sa, 0);
	SetHandleInformation(hWrite, HANDLE_FLAG_INHERIT, 0);

	STARTUPINFO si = {0};
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdInput = hRead;
	si.hStdOutput = 0;
	si.hStdError = 0;

//	SetStdHandle(STD_OUTPUT_HANDLE, hWrite);

	int fd = _open_osfhandle(intptr_t(hWrite), _O_TEXT);
	FILE* fp = _fdopen(fd, "w");
	setvbuf(fp, NULL, _IONBF, 0);
	_dup2(_fileno(fp), _fileno(stdout));

	PROCESS_INFORMATION pi;
	CreateProcess(NULL, (LPSTR)"AnonChild.exe", &sa, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	string s;
	while (true)
	{
		cin >> s;
		cout << s;
	}

	CloseHandle(hRead);
	CloseHandle(hWrite);
}

