// SharedConsole.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include "../SharedDLL/SharedDLL.h"

int main()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	CreateProcess(NULL, (LPSTR)"SharedDialog.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);

	while (true)
	{
		std::cin >> GetSharedString();
		if (ghWnd)
		{
			SetForegroundWindow(ghWnd);
		}
	}
}
