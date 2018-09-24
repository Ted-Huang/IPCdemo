#include "stdafx.h"
#include <afxsock.h>
#include "SocketClient.h"

CSocketClient::CSocketClient(SOCKET_CALLBACK* pCallback) : m_pCallBack(pCallback)
{
}

CSocketClient::~CSocketClient()
{

}

void CSocketClient::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);

	char *pBuf = new char[SocketBuffer];
	memset(pBuf, 0, SocketBuffer);

	int nRead;
	nRead = Receive(pBuf, SocketBuffer);
	switch (nRead)
	{
	case 0:
		Close();
		break;
	case SOCKET_ERROR:
		if (GetLastError() != WSAEWOULDBLOCK)
		{
			AfxMessageBox(_T("Error occurred"));
			TRACE(_T("Error occurred"));
			Close();
		}
		break;
	default:
		pBuf[nRead] = _T('\0'); //terminate the string
		CString strData;
		strData.Format(_T("%s"), pBuf);
		TRACE(_T("Received :%s %s \n"), strData, pBuf);

		if (!m_pCallBack)
			return;

		m_pCallBack->OnSocketCallBack($ST_Receive, strData);
		delete pBuf;
	}
}