// L01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "L01.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HANDLE hEvents[10];

HANDLE hEvent;
HANDLE hEventConfirm;
HANDLE hMutex;

CRITICAL_SECTION cs;

DWORD WINAPI MyThread(LPVOID lpParam)
{
    int i = (int)lpParam;
//    EnterCriticalSection(&cs);
    WaitForSingleObject(hMutex, INFINITE);
    std::cout << i << endl;
//    LeaveCriticalSection(&cs);
    ReleaseMutex(hMutex);


//    WaitForSingleObject(hEvents[i], INFINITE);
    WaitForSingleObject(hEvent, INFINITE);

    std::cout << i << " done" << endl;
    CloseHandle(hEvents[i]);
    SetEvent(hEventConfirm);

    return 0;
}

void start()
{
    InitializeCriticalSection(&cs);
    hEvent = CreateEvent(NULL, FALSE, FALSE, "StartEvent");
    hMutex = CreateMutex(NULL, FALSE, NULL);
    hEventConfirm = CreateEvent(NULL, FALSE, FALSE, "ConfirmEvent");
    int i;
    for (i = 0; i < 10; ++i)
    {
        hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        CreateThread(NULL, 0, MyThread, (LPVOID)i, 0, NULL);
    }

    for (int j = 0; j < 10; ++j)
    {
        std::cin >> i;
        SetEvent(hEvents[j]);
        SetEvent(hEvent);
    }
    std::cin >> i;
    DeleteCriticalSection(&cs);
    CloseHandle(hEvent);
    CloseHandle(hEventConfirm);
    CloseHandle(hMutex);
}

void start0()
{
    SECURITY_ATTRIBUTES sa = {0};
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    sa.bInheritHandle = TRUE;


    HANDLE hMutex1 = CreateMutex(&sa, TRUE, "MyMutex");
    HANDLE hMutex2 = CreateMutex(&sa, TRUE, "MyMutex");

    int i;
    std::cin >> i;

    if (CreateProcess(NULL, (LPSTR)"notepad", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi))
    {
        DWORD code;
        GetExitCodeProcess(pi.hProcess, &code);
        std::cout << "notepad closed " << code << std::endl;

        std::cin >> i;
        TerminateProcess(pi.hProcess, 12345);

        WaitForSingleObject(pi.hProcess, INFINITE);
        GetExitCodeProcess(pi.hProcess, &code);
        std::cout << "notepad closed " << code << std::endl;

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    std::cin >> i;

}

CWinApp theApp;

using namespace std;

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
