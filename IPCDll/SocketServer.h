#pragma once

class CSocketServer : public CSocket
{
public:
	CSocketServer();
	~CSocketServer();
protected:
	virtual void OnAccept(int nErrorCode);
public:
	CPtrArray m_arrSocketClient;
};


class CSockThread : public CWinThread
{
public:
	CSockThread();
	~CSockThread();

	BOOL InitInstance();

	SOCKET m_hConnected;

protected:
	CSocketClient m_sConnected;

private:
	
};