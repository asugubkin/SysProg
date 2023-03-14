// L01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "framework.h"
#include "L01.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

string GetLastErrorString(DWORD ErrorID = 0)
{
    if (!ErrorID)
        ErrorID = GetLastError();
    if (!ErrorID)
        return string();

    LPSTR pBuff = nullptr;
    size_t size = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        NULL, ErrorID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&pBuff, 0, NULL);
    string s(pBuff, size);
    LocalFree(pBuff);

    return s;
}


// The one and only application object

CWinApp theApp;


HANDLE hEvents[100];
DWORD WINAPI MyThread(LPVOID lpParameter)
{
    int i = int(lpParameter);
    cout << i;
    cout << endl;
    
    WaitForSingleObject(hEvents[i], INFINITE);

    cout << "thread " << i << "done" << endl;


    return 0;
}

struct header
{
    int addr;
    int size;
};

string mapreceive(header& h)
{
    HANDLE hFile = CreateFile("filemap.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, 0);
    
    HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(header), "MyMap");
    LPVOID buff = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(header));
    h = *((header*)buff);
    UnmapViewOfFile(buff);
    CloseHandle(hFileMap);

    int n = h.size + sizeof(header);
    hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, n, "MyMap");
    buff = MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, n);
 //   cout << GetLastErrorString();
    string s((char*) buff + sizeof(header), h.size);

    UnmapViewOfFile(buff);
    CloseHandle(hFileMap);
    return s;
}

HANDLE mapsend(int addr, const char* str)
{
    header h = { addr, strlen(str) + 1 };
    HANDLE hFile = CreateFile("filemap.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, 0);
    HANDLE hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, h.size+sizeof(header), "MyMap");
    char* buff = (char*)MapViewOfFile(hFileMap, FILE_MAP_ALL_ACCESS, 0, 0, h.size + sizeof(header));

    memcpy(buff, &h, sizeof(header));
    memcpy(buff + sizeof(header), str, h.size);


    UnmapViewOfFile(buff);
    return hFileMap;
//    CloseHandle(hFileMap);
    CloseHandle(hFile);
}

void start()
{
    HANDLE hFile = CreateFile("file.dat", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE| FILE_SHARE_READ, NULL, OPEN_ALWAYS, 0, 0);
//    SetFilePointer
    int i = 12;
    DWORD dwDone;
    WriteFile(hFile, &i, sizeof(i), &dwDone, NULL);
    cout << dwDone << endl;
    CloseHandle(hFile);
    HANDLE hMap = mapsend(3, "13245");

    header h;
    string s = mapreceive(h);
    cout << s << " " << h.size << " " << h.addr << endl;
    CloseHandle(hMap);
    //    VirtualAlloc
}

void start1()
{
    int i;
    for (i = 0; i < 10; ++i)
    {
        hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
        CreateThread(NULL, 0, MyThread, (LPVOID)i, 0, NULL);
    }

    HANDLE hStartEvent = CreateEvent(NULL, FALSE, FALSE, "StartEvent");
    HANDLE hStopEvent = CreateEvent(NULL, FALSE, FALSE, "StopEvent");
    HANDLE hConfirmEvent = CreateEvent(NULL, FALSE, FALSE, "ConfirmEvent");
    HANDLE hControlEvents[2] = {hStartEvent, hStopEvent};
    while (i)
    {
        int n = WaitForMultipleObjects(2, hControlEvents, FALSE, INFINITE) - WAIT_OBJECT_0;
        switch (n)
        {
            case 0:
                hEvents[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
                CreateThread(NULL, 0, MyThread, (LPVOID)i, 0, NULL);
                SetEvent(hConfirmEvent);
                i++;
                break;
            case 1:
                SetEvent(hEvents[--i]);
                SetEvent(hConfirmEvent);
                break;
        }
    }
    SetEvent(hConfirmEvent);
    int n;
    cin >> n;
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
