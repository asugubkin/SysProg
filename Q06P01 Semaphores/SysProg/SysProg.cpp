// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "SysProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hSemaphore;

void MyThread(int id)
{
	SafeWrite("Thread", id, "start");

	WaitForSingleObject(hSemaphore, INFINITE);
	SafeWrite("Thread", id, "semaphore capture");
	Sleep(3000);
	ReleaseSemaphore(hSemaphore, 1, NULL);
	SafeWrite("Thread", id, "semaphore release");

	SafeWrite("Thread", id, "end");
}

void start()
{
	hSemaphore = CreateSemaphore(NULL, 1, 3, NULL);
	const int nThreads = 10;
	for (int i = 0; i < nThreads; ++i)
	{
		thread t(MyThread, i);
		t.detach();
	}
	SafeWrite("Threads created");
	int n;
	cin >> n;
	ReleaseSemaphore(hSemaphore, n, NULL);
	_getch();

	CloseHandle(hSemaphore);
}

// The one and only application object

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
			start();
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
