// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "SysProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

shared_mutex evMutex;
condition_variable_any cv;

void MyThread(int id)
{
	SafeWrite("Thread", id, "start");
	shared_lock<shared_mutex> ul(evMutex);
	cv.wait(ul);

	SafeWrite("Thread", id, "cv capture");
	Sleep(1000);
	SafeWrite("Thread", id, "end");
}

void start()
{
	const int nThreads = 10;
	for (int i = 0; i < nThreads; ++i)
	{
		thread t(MyThread, i);
		t.detach();
	}
	SafeWrite("Threads created");
	_getch();
	cv.notify_all();
	_getch();
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
