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

static CCriticalSection cs;
template <typename... Args> inline void SafeWrite(Args... args)
{
	cs.Lock();
	DoWrite(args...);
	cs.Unlock();
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
