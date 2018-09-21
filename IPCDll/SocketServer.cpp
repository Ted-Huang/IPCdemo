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
	CSockThread* pSockThread = (CSockThread*)AfxBeginThread(
		RUNTIME_CLASS(CSockThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	if (NULL != pSockThread)
	{
		// Detach the newly accepted socket and save
		// the SOCKET handle in our new thread object.
		// After detaching it, it should no longer be
		// used in the context of this thread.
		pSockThread->m_hConnected = pSession->Detach();
		pSockThread->ResumeThread();
		m_arrSocketClient.Add(pSockThread);
	}
}

CSockThread::CSockThread()
{
	InitInstance();
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
	// Attach the socket object to the socket handle
	// in the context of this thread.
	m_sConnected.Attach(m_hConnected);
	m_hConnected = NULL;

	return TRUE;
}