// SocketClient.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "SocketClient.h"
#include "../SocketServer/Sockets.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


void Client()
{
	AfxSocketInit();
	CSocket s;
	s.Create();
	if (!s.Connect("127.0.0.1", 12345))
	{
		cout << "Socket connect error" << endl;
		_getch();
		return;
	}

	while (true)
	{
		string str;
		cin >> str;
		SendString(s, str);
		if (str == "quit")
		{
			break;
		}
		cout << ReceiveCString(s) << endl;
	}

}

CWinApp theApp;

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: code your application's behavior here.
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			Client();
		}
	}
	else
	{
		// TODO: change error code to suit your needs
		wprintf(L"Fatal Error: GetModuleHandle failed\n");
		nRetCode = 1;
	}

	return nRetCode;
}
