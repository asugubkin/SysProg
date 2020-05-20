// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <Shlobj.h>
#include <VersionHelpers.h>
#include <conio.h>
#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <functional>
using namespace std;

string GetString(function<DWORD WINAPI(DWORD, LPTSTR)> f)
{
	DWORD dwLength = f(0, nullptr);
	vector<char> vBuff(dwLength);
	f(dwLength, &vBuff[0]);
	return string(&vBuff[0], dwLength);
}

string GetString(function<UINT(LPTSTR, UINT)> f)
{
	DWORD dwLength = f(nullptr, 0);
	vector<char> vBuff(dwLength);
	f(&vBuff[0], dwLength);
	return string(&vBuff[0], dwLength);
}

string GetString(function<BOOL(LPTSTR, LPDWORD)> f)
{
	DWORD dwLength = 0;
	f(nullptr, &dwLength);
	vector<char> vBuff(dwLength);
	f(&vBuff[0], &dwLength);
	return string(&vBuff[0], dwLength);
}

string GetFolderPath(int nFolder)
{
	char buff[MAX_PATH];
	SHGetFolderPath(nullptr, nFolder, nullptr, SHGFP_TYPE_CURRENT, buff);
	return string(buff);
}

void ListDir(string sDir, bool bSubDir = true)
{
	WIN32_FIND_DATA fData;
	HANDLE hFind = FindFirstFile((sDir+"\\*.*").c_str(), &fData);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			cout << sDir << "\\" << fData.cFileName;
			if(!(fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
				cout << "\t" << fData.nFileSizeLow;
			cout << endl;
			if (!bSubDir || !lstrcmp(fData.cFileName, ".") || !lstrcmp(fData.cFileName, ".."))
				continue;
			if(fData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				ListDir(sDir+"\\"+ fData.cFileName);
			}
		} while (FindNextFile(hFind, &fData));
		FindClose(hFind);
	}
}

void WatchDir(const char* sDir)
{
	HANDLE hFind = FindFirstChangeNotification(sDir, TRUE, FILE_NOTIFY_CHANGE_FILE_NAME | FILE_NOTIFY_CHANGE_SIZE);

	while (true)
	{
		WaitForSingleObject(hFind, INFINITE);
		ListDir(sDir, false);
		FindNextChangeNotification(hFind);
	}

	FindCloseChangeNotification(hFind);
}

int main()
{
	// OSVERSIONINFOEX vi = { sizeof(OSVERSIONINFOEX) };
	// GetVersionEx((LPOSVERSIONINFO)&vi);

	cout << "IsWindows10OrGreater:\t" << IsWindows10OrGreater() << endl;
	cout << "IsWindows8OrGreater:\t" << IsWindows8OrGreater() << endl<<endl;

	DWORD dwDrives = GetLogicalDrives();
	cout << bitset<32>(dwDrives) << endl << "      ZYXWVUTSRQPONMLKJIHGFEDCBA" << endl << endl;

	cout
		<< GetString(GetLogicalDriveStrings) << endl
		<< GetString(GetWindowsDirectory) << endl
		<< GetString(GetSystemDirectory) << endl
		<< GetString(GetCurrentDirectory) << endl
		<< GetString(GetTempPath) << endl
		<< GetString(GetUserName) << endl
		<< GetString(GetComputerName) << endl
		<< GetFolderPath(CSIDL_PROGRAM_FILES) << endl
		<< GetFolderPath(CSIDL_PROGRAM_FILES_COMMON) << endl
		<< GetFolderPath(CSIDL_SYSTEM) << endl
		<< GetFolderPath(CSIDL_WINDOWS) << endl
		<< GetFolderPath(CSIDL_PERSONAL) << endl
		<< GetFolderPath(CSIDL_APPDATA) << endl
		<< GetFolderPath(CSIDL_LOCAL_APPDATA) << endl
		<< GetFolderPath(CSIDL_COMMON_APPDATA) << endl;

	char buff[MAX_PATH];
	GetTempFileName(GetString(GetTempPath).c_str(), "NCC", 42, buff);
	cout << buff << endl;

	ListDir("..");
	WatchDir(".");

	_getch();
}
