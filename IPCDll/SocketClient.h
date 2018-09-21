#pragma once
#include <afxsock.h>
#include "DLLconst.h"


class CSocketClient : public CSocket
{
protected:
	virtual void OnReceive(int nErrorCode);
};