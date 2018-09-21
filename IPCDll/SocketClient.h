#pragma once
#include <afxsock.h>

#define SocketBuffer	1024

class CSocketClient : public CSocket
{
protected:
	virtual void OnReceive(int nErrorCode);
};