// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "SysProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CRITICAL_SECTION gcs;
HANDLE hMutex;

void f(int id)
{
	MyClass o;
//  ExitThread(id*100);
//  _endthreadex(id * 100);
}

void MyThread(int id)
{
	for (int i = 0; i<10; ++i)
	{
//		EnterCriticalSection(&gcs);
		WaitForSingleObject(hMutex, INFINITE);

		SafeWrite("Thread ", id);
//		LeaveCriticalSection(&gcs);
		ReleaseMutex(hMutex);
		Sleep(100);
	}
	f(id);
	SafeWrite("After f()");
//  return id*10;
}

void start()
{
//	InitializeCriticalSection(&gcs);
	hMutex = CreateMutex(NULL, FALSE, NULL);
	const int nThreads = 10;
	HANDLE hThreads[nThreads];
	for (int i = 0; i < nThreads; ++i)
	{
//	  hThreads[i] = CreateThread(NULL, 0, MyThread, (LPVOID)i, 0, NULL);
//	  hThreads[i] = (HANDLE)_beginthreadex(NULL, 0, MyThread, (LPVOID)i, 0, NULL);
//	  hThreads[i] = AfxBeginThread(MyThread, (LPVOID)i)->m_hThread;
		thread t(MyThread, i);
		hThreads[i] = t.native_handle();
		t.detach();
	}
	SafeWrite("Threads created");
	WaitForMultipleObjects(nThreads, hThreads, TRUE, INFINITE);
	SafeWrite("Threads done");
	/*
	for (int i = 0; i < nThreads, ++i)
	{
		DWORD dwCode;
		GetExitCodeThread(hThreads[i], &dwCode);
		SafeWrite(dwCode);
//	  CloseHandle(hThreads[i]);
	}
	*/
	_getch();
//	DeleteCriticalSection(&gcs);
	CloseHandle(hMutex);
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
