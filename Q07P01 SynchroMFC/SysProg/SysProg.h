#pragma once

#include "resource.h"
#include <afxmt.h>

inline void DoWrite()
{
	cout << endl;
}

template <class T, typename... Args> inline void DoWrite(T& value, Args... args)
{
	cout << value << " ";
	DoWrite(args...);
}

CCriticalSection gCS;
template <typename... Args> inline void SafeWrite(Args... args)
{
	CSingleLock sl(&gCS, TRUE);
	DoWrite(args...);
}

class MyClass
{
public:
	MyClass()
	{
		SafeWrite("MyClass::MyClass()");
	}
	~MyClass()
	{
		SafeWrite("MyClass::~MyClass()");
	}
};
