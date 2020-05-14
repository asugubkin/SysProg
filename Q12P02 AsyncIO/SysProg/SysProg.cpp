// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

int main()
{
	const int nBufSize = 512*123456;
	int* pBuff = new int[nBufSize];
	for (int i = 0; i < nBufSize; i++)
	{
		pBuff[i] = i;
	}
	DWORD dwDone, dwStart, dwEnd;
	HANDLE hFile;

	hFile = CreateFile("file.dat", GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, 0, NULL);

	dwStart = GetTickCount();
	WriteFile(hFile, pBuff, nBufSize*sizeof(int), &dwDone, NULL);
	dwEnd = GetTickCount();
	cout << "WriteFile done: " << dwDone << " " << (dwEnd - dwStart) << endl;

	CloseHandle(hFile);

	hFile = CreateFile("file.dat", 
		GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED | FILE_FLAG_NO_BUFFERING, NULL);
	OVERLAPPED o = { 0 };
	o.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	dwStart = GetTickCount();
	WriteFile(hFile, pBuff, nBufSize * sizeof(int), &dwDone, &o);
	dwEnd = GetTickCount();
	cout << "WriteFile done: " << dwDone << " " << (dwEnd-dwStart) << endl;

	WaitForSingleObject(o.hEvent, INFINITE);
	dwEnd = GetTickCount();
	GetOverlappedResult(hFile, &o, &dwDone, TRUE);
	cout << "done: " << dwDone << " " << (dwEnd - dwStart) << endl;

	CloseHandle(o.hEvent);
	CloseHandle(hFile);

	delete[] pBuff;
	_getch();
}
