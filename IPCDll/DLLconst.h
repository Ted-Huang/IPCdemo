#pragma once


#ifdef IPCDLL__EXPORTS
#define IPCDLL_API  __declspec(dllexport) 
#else
#define IPCDLL_API  __declspec(dllimport) 
#endif


// socket 
#define SocketBuffer	1024
#define SocketPort		9999	//À³¨Ó¦Ûini
#define HeartBeatID		1

// shared memory
#define SM_BUF_SIZE		1024
#define SM_NAME			_T("Global\\SM_IPC")