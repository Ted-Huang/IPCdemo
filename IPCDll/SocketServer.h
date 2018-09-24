#pragma once
#include "SocketClient.h"
#include "DLLconst.h"
#include "SocketCallBack.h"



class IPCDLL_API CSocketServer : public CSocket
{
public:
	CSocketServer(SOCKET_CALLBACK* pCallback);
	~CSocketServer();
protected:
	virtual void OnAccept(int nErrorCode);
public:
	CPtrArray m_arrSocketClient;
	SOCKET_CALLBACK* m_pCallBack;
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