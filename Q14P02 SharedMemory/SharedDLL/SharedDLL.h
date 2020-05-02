#pragma once

#ifdef SHAREDDLL_EXPORTS
#define SHAREDEXP dllexport
#else
#define SHAREDEXP dllimport
#endif

extern __declspec(SHAREDEXP) HWND ghWnd;
__declspec(SHAREDEXP) char* GetSharedString();