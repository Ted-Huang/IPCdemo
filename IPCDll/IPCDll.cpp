// IPCDll.cpp : �w�q�D���x���ε{�����i�J�I�C
//

#include "stdafx.h"
#include "IPCDll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �Ȧ����@�����ε{������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��l�� MFC �é󥢱ѮɦC�L���~
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  �t�X�z���ݭn�ܧ���~�X
			_tprintf(_T("�Y�����~:  MFC ��l�ƥ���\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  �b�����g���ε{���欰���{���X�C
		}
	}
	else
	{
		// TODO:  �t�X�z���ݭn�ܧ���~�X
		_tprintf(_T("�Y�����~:  GetModuleHandle ����\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
