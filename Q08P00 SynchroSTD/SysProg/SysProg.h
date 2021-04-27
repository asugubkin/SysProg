#pragma once

#include "resource.h"
#include <afxmt.h>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>

inline void DoWrite()
{
	cout << endl;
}

template <class T, typename... Args> inline void DoWrite(T& value, Args... args)
{
	cout << value << " ";
	DoWrite(args...);
}

mutex m;
template <typename... Args> inline void SafeWrite(Args... args)
{
	lock_guard<mutex> lg(m);
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
