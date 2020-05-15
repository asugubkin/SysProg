// MailSlotClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
	//
	// \\.\mailslot\<slotname>
	// \\<systemname>\mailslot\<slotname>
	// \\*\mailslot\<slotname>
	// \\<domainname>\mailslot\<slotname>
	//

	HANDLE hMail = CreateFile("\\\\.\\mailslot\\myslot", 
		GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, NULL);
	string s;
	while (1)
	{
		cin >> s;
		if (s == "bye")
			break;
		DWORD dwWrite;
		WriteFile(hMail, s.c_str(), s.length() + 1, &dwWrite, NULL);
	}
	CloseHandle(hMail);
}

