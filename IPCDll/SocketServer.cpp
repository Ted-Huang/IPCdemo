#include "stdafx.h"
#include <afxsock.h>
#include "SocketClient.h"
#include "SocketServer.h"

CSocketServer::CSocketServer()
{
	m_arrSocketClient.RemoveAll();
}

CSocketServer::~CSocketServer()
{
	for (int index = 0; index < m_arrSocketClient.GetSize(); index++)
	{
		CSockThread* pThread = (CSockThread*)m_arrSocketClient.GetAt(index);;
		if (pThread)
		{
			delete pThread;
			pThread = NULL;
		}
	}
	m_arrSocketClient.RemoveAll();
}

void CSocketServer::OnAccept(int nErrorCode)
{
	CSocketClient* pSession = new CSocketClient();
	if (!Accept(*pSession))
	{
		TRACE(_T("Cannot Accept Connection"));
	}

	CString strIP;
	UINT nPort;
	pSession->GetPeerName(strIP, nPort);
	TRACE(_T("Accept IP: %s Port: %d"), strIP, nPort);

	// Start the other thread.
	CSockThread* pSockThread = (CSockThread*)AfxBeginThread(RUNTIME_CLASS(CSockThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	if (!pSockThread)
		return;

	pSockThread->m_hConnected = pSession->m_hSocket;

	m_arrSocketClient.Add(pSockThread);
	pSockThread->ResumeThread();
}

IMPLEMENT_DYNCREATE(CSockThread, CWinThread)
CSockThread::CSockThread()
{
}

CSockThread::~CSockThread()
{
	//disconnect?
	CSocketClient* pSession = (CSocketClient*)CSocket::FromHandle(m_hConnected);
	delete pSession;
	pSession = NULL;
}

BOOL CSockThread::InitInstance()
{

	return TRUE;
}