// SysProg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <stdexcept>
#include <conio.h>
#include <windows.h>
using namespace std;

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

void Error()
{
	HANDLE hFile = CreateFile("file.dat", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		cout << GetLastErrorString() << endl;
	}
	CloseHandle(hFile);
}

class MyClass
{
public:
	MyClass() { cout << "MyClass::MyClass()" << endl; }
	~MyClass() { cout << "MyClass::~MyClass()" << endl; }
};

int n;

int f()
{
	MyClass o;
	cout << 1 / n << endl;
	return n;
}

void Exception1()
{
	__try
	{
//		MyClass o;
		if (f())
			__leave;
	}
	__finally
	{
		if (AbnormalTermination())
		{
			cout << "something wrong" << endl;
		}
		else
		{
			cout << "ok" << endl;
		}
	}
	cout << "SEH done" << endl;
}

DWORD GetFilter(DWORD exCode)
{
	if (exCode == EXCEPTION_INT_DIVIDE_BY_ZERO)
	{
		n = 1;
		return EXCEPTION_CONTINUE_EXECUTION;
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

void Exception2()
{
	__try
	{
		__try
		{
			if (f())
				__leave;
		}
//		__except (EXCEPTION_EXECUTE_HANDLER)
//		__except ((GetExceptionCode() == EXCEPTION_INT_DIVIDE_BY_ZERO)? EXCEPTION_EXECUTE_HANDLER:EXCEPTION_CONTINUE_SEARCH)
		__except(GetFilter(GetExceptionCode()))
		{
			cout << "exception handled" << endl;
		}
	}
	__finally
	{
		if (AbnormalTermination())
		{
			cout << "something wrong" << endl;
		}
		else
		{
			cout << "ok" << endl;
		}
	}
	cout << "SEH done" << endl;
}

void SETranslator(unsigned int exCode, EXCEPTION_POINTERS*)
{
	throw runtime_error("Exception: " + to_string(exCode));
}

void Exception3()
{
	_set_se_translator(SETranslator);
	try
	{
		MyClass o;
		if (f())
			return;
	}
	catch (runtime_error& ex)
	{
		cout << ex.what() << endl;
	}
}
	
int main()
{
	Error();
	cin >> n;
//	Exception1();
//	Exception2();
	Exception3();

	_getch();
}

