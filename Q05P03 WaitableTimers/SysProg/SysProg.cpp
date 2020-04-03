// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "SysProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hTimer;

void MyThread(int id)
{
	SafeWrite("Thread", id, "start");
	WaitForSingleObject(hTimer, INFINITE);
	SafeWrite("Thread", id, "end");
}

void start()
{
	hTimer = CreateWaitableTimer(NULL, FALSE, NULL);
	const int nThreads = 10;
	for (int i = 0; i < nThreads; ++i)
	{
		thread t(MyThread, i);
		t.detach();
	}
	LARGE_INTEGER dTime;
	dTime.QuadPart = -10000*1000;
	SetWaitableTimer(hTimer, &dTime, 1000, NULL, NULL, false);
	SafeWrite("Threads created");
	_getch();


	/*
	FILETIME uTime, fTime;
	SYSTEMTIME sTime = { 0 };
	SystemTimeToFileTime(&sTime, &fTime);
	LocalFileTimeToFileTime(&fTime, &uTime);
	SetWaitableTimer(hTimer, (LARGE_INTEGER*)&uTime, 1000, NULL, NULL, false);
	*/

	CancelWaitableTimer(hTimer);
	CloseHandle(hTimer);
	
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
