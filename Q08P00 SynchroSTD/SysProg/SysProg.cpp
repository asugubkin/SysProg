// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "SysProg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

mutex evMutex1;
condition_variable cv1;

shared_mutex evMutex2;
condition_variable_any cv2;

void MyThread1(int id)
{
	SafeWrite("Thread", id, "start");
	unique_lock<mutex> ul(evMutex1);
	cv1.wait(ul, [id] {SafeWrite("cv1 wait completed", id); return true; });

	SafeWrite("Thread", id, "cv capture");
	Sleep(1000);
	SafeWrite("Thread", id, "end");

//	cv1.notify_one();
}

void MyThread2(int id)
{
	SafeWrite("Thread", id, "start");
	shared_lock<shared_mutex> ul(evMutex2);
	cv2.wait(ul);

	SafeWrite("Thread", id, "cv capture");
	Sleep(1000);
	SafeWrite("Thread", id, "end");
}

void start1()
{
	const int nThreads = 10;
	for (int i = 0; i < nThreads; ++i)
	{
		thread t(MyThread1, i);
		t.detach();
	}
	SafeWrite("Threads created");
	_getch();
	cv1.notify_all();
	_getch();
}

void start2()
{
	const int nThreads = 10;
	for (int i = 0; i < nThreads; ++i)
	{
		thread t(MyThread2, i);
		t.detach();
	}
	SafeWrite("Threads created");
	_getch();
	cv2.notify_all();
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
			start2();
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
