
// IPCClient.h : PROJECT_NAME ���ε{�����D�n���Y��
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�� PCH �]�t���ɮ׫e���]�t 'stdafx.h'"
#endif

#include "resource.h"		// �D�n�Ÿ�


// CIPCClientApp: 
// �аѾ\��@�����O�� IPCClient.cpp
//

class CIPCClientApp : public CWinApp
{
public:
	CIPCClientApp();

// �мg
public:
	virtual BOOL InitInstance();

// �{���X��@

	DECLARE_MESSAGE_MAP()
};

extern CIPCClientApp theApp;