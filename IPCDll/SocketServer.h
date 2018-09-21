#pragma once
#include "SocketClient.h"
#include "DLLconst.h"

class IPCDLL_API CSocketServer : public CSocket
{
public:
	CSocketServer();
	~CSocketServer();
protected:
	virtual void OnAccept(int nErrorCode);
public:
	CPtrArray m_arrSocketClient;
};

class IPCDLL_API CSockThread : public CWinThread
{
	DECLARE_DYNCREATE(CSockThread)
public:
	CSockThread();
	~CSockThread();

	virtual BOOL InitInstance();

	SOCKET m_hConnected;

protected:
};