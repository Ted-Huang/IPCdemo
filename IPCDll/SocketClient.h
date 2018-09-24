#pragma once
#include <afxsock.h>
#include "DLLconst.h"
#include "SocketCallBack.h"

class IPCDLL_API CSocketClient : public CSocket
{
public:
	CSocketClient(SOCKET_CALLBACK* pCallback);
	~CSocketClient();
protected:
	virtual void OnReceive(int nErrorCode);
private:
	SOCKET_CALLBACK* m_pCallBack;
};