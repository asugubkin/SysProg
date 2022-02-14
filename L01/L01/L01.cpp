// L01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "L01.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;

using namespace std;

HANDLE hEvents[10];
DWORD WINAPI MyThread(LPVOID lpParameter)
{
    int i = int(lpParameter);
    cout << i;
    cout << endl;
    
    WaitForSingleObject(hEvents[i], INFINITE);

    cout << "thread " << i << "done" << endl;


    return 0;
}

void start()
{
    int i;
    for (i = 0; i < 10; ++i)
    {
        CreateThread(NULL, 0, MyThread, (LPVOID)i, 0, NULL);
        hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
    }
    int n;
    HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, "StopEvent");
    while (i)
    {
        WaitForSingleObject(hEvent, INFINITE);
        SetEvent(hEvents[--i]);
    }
}

void start0()
{
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

    if (!CreateProcess(
        NULL,
        (LPSTR)"notepad",
        &sa,
        &sa,
        TRUE,
        0,
        NULL,
        NULL,
        &si,
        &pi
    ))
       return;
    
    HANDLE hMutex = CreateMutex(NULL, FALSE, "MyMutex");
//    HANDLE hMutex2 = OpenMutex(0, FALSE, "MyMutex");

    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD dwCode;
    GetExitCodeProcess(pi.hProcess, &dwCode);
    cout << "waiting done: " << dwCode << endl;

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(hMutex);

//    ExitProcess(123);
//    TerminateProcess(pi.hProcess, 12345);
}


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
