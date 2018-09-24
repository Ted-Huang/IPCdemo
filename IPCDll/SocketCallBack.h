#pragma once
#include "stdafx.h"
#include "DLLconst.h"

class SOCKET_CALLBACK
{
public:

	virtual void OnSocketCallBack(SocketEventType eType, CString strMsg) = NULL;
};