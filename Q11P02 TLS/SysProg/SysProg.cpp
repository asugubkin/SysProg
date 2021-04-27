// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "SysProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

__declspec (thread) int gID = 0;

void f1(int id)
{
	__declspec (thread) static int sID = 0;
	sID = id;
	for (int i = 0; i < 2; ++i)
	{
		SafeWrite("Thread", id, "sID", sID, "gID", gID);
		Sleep(1000);
	}
}

void MyThread1(int id)
{
	SafeWrite("Thread", id, "start");
	gID = id;
	f1(id);
	SafeWrite("Thread", id, "end");
}

DWORD tlsIndex;

void f2()
{
	for (int i = 0; i < 2; ++i)
	{
		SafeWrite("tlsIndex", tlsIndex, "id from TLS", *((int*)TlsGetValue(tlsIndex)));
		Sleep(1000);
	}
}

void MyThread2(int id)
{
	SafeWrite("Thread", id, "start");

	if (!TlsGetValue(tlsIndex))
		TlsSetValue(tlsIndex, new int);
	
	*((int*)TlsGetValue(tlsIndex)) = id;
	f2();
	delete (int*)TlsGetValue(tlsIndex);

	SafeWrite("Thread", id, "end");
}

void start()
{
	tlsIndex = TlsAlloc();
	const int nThreads = 10;
	for (int i = 0; i < nThreads; ++i)
	{
		thread t(MyThread2, i);
		t.detach();
	}
	SafeWrite("Threads created");
	_getch();
	TlsFree(tlsIndex);
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
