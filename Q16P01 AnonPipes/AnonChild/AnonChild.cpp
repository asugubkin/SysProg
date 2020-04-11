// AnonChild.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

int main()
{
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	const int MAXLEN = 1024;

	while (true)
	{
		DWORD dwRead;
		char buff[MAXLEN+1];

		if (!ReadFile(hIn, buff, MAXLEN, &dwRead, nullptr) || !dwRead)
			break;

		buff[min(MAXLEN, dwRead)] = 0;
		cout << "child: " << buff << endl;
	}
}
