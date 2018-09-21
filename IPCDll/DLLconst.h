#pragma once


#ifdef IPCDLL__EXPORTS
#define IPCDLL_API  __declspec(dllexport) 
#else
#define IPCDLL_API  __declspec(dllimport) 
#endif

#define SocketBuffer	1024
#define SocketPort		9999	//À³¨Ó¦Ûini
#define HeartBeatID		1