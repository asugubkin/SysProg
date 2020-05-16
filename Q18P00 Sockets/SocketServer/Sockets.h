#pragma once

#include <afxsock.h>

inline string ReceiveString(CSocket& s)
{
	int nLength;
	s.Receive(&nLength, sizeof(int));
	vector <char> v(nLength);
	s.Receive(&v[0], nLength);
	return string(&v[0], nLength);
}

inline void SendString(CSocket& s, const string& str)
{
	int nLength = str.length();
	s.Send(&nLength, sizeof(int));
	s.Send(str.c_str(), nLength);
}

inline CString ReceiveCString(CSocket& s)
{
	CString str;
	CSocketFile f(&s);
	CArchive ar(&f, CArchive::load);
	ar >> str;
	return str;
}

inline void SendCString(CSocket& s, const CString& str)
{
	CSocketFile f(&s);
	CArchive ar(&f, CArchive::store);
	ar << str;
}
