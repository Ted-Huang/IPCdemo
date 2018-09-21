#pragma once

#ifdef IPCDLL__EXPORTS
#define IPCDLL__API  __declspec(dllexport) 
#else
#define IPCDLL__API  __declspec(dllimport) 
#endif

class CUtility
{
public:
	IPCDLL__API static CString GetIP();
};
