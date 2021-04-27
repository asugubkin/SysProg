// PipesServer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <iostream>
#include <thread>
#include "Pipes.h"


void LaunchClient()
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	CreateProcess(NULL, (LPSTR)"PipesClient.exe", NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void ProcessClient(HANDLE hPipe)
{
	static int i = 0;
	while (true)
	{
		string s = GetString(hPipe);
		cout << s << endl;
		if (s == "quit")
		{
			break;
		}
		SendInt(hPipe, ++i);
	}
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
}

int main()
{
	for (int i = 0; i < 3; ++i)
	{
		LaunchClient();
	}

	while (true)
	{
		HANDLE hPipe = CreateNamedPipe("\\\\.\\pipe\\MyPipe", 
			PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, 
			1024, 1024, 0, NULL);
		ConnectNamedPipe(hPipe, NULL);
		thread t(ProcessClient, hPipe);
		t.detach();
	}
}
