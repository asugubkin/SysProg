// MailSlotServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

using namespace std;

void LaunchClient()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	CreateProcess(NULL, (LPSTR)"MailSlotClient.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

int main()
{
	//
	// \\.\mailslot\<slotname>
	//
	HANDLE hMail = CreateMailslot("\\\\.\\mailslot\\myslot", 0, MAILSLOT_WAIT_FOREVER, NULL);
	for (int i = 0; i < 3; ++i)
	{
		LaunchClient();
	}
	while (true)
	{
		DWORD msgSize,dwRead;
		GetMailslotInfo(hMail, NULL, &msgSize, NULL, NULL);
		if (msgSize == MAILSLOT_NO_MESSAGE)
		{
			Sleep(100);
			continue;
		}
		char* pBuff = new char[msgSize];
		ReadFile(hMail, pBuff, msgSize, &dwRead, NULL);
		cout << pBuff << endl;

		if (!lstrcmp(pBuff, "quit"))
		{
			delete[] pBuff;
			break;
		}
		delete[] pBuff;
	}
	CloseHandle(hMail);
}
