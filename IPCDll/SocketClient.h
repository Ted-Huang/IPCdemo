#pragma once
#include <afxsock.h>
#include "DLLconst.h"


class IPCDLL_API CSocketClient : public CSocket
{
protected:
	virtual void OnReceive(int nErrorCode);
};