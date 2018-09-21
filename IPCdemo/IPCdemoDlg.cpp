
// IPCdemoDlg.cpp : ��@��
//

#include "stdafx.h"
#include "IPCdemo.h"
#include "IPCdemoDlg.h"
#include "afxdialogex.h"
#include "Utility.h"
#include "SocketServer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIPCdemoDlg ��ܤ��

CIPCdemoDlg::CIPCdemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIPCdemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CIPCdemoDlg::~CIPCdemoDlg()
{
	Finalize();
}

void CIPCdemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIPCdemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CIPCdemoDlg �T���B�z�`��

BOOL CIPCdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO:  �b���[�J�B�~����l�]�w
	Init();
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CIPCdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CIPCdemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CIPCdemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CIPCdemoDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (HeartBeatID == nIDEvent)
	{
		if (!m_pSocketServer){
			CDialog::OnTimer(nIDEvent);
			return;
		}

		for (int index = 0; index < m_pSocketServer->m_arrSocketClient.GetSize(); index++)
		{
			CSockThread* pThread = (CSockThread*)m_pSocketServer->m_arrSocketClient.GetAt(index);
			if (!pThread)
			{
				CDialog::OnTimer(nIDEvent);
				return;
			}

			CString strMsg(_T("HeartBeat From Server!"));
			if (pThread->m_hConnected && CSocket::FromHandle(pThread->m_hConnected))
				CSocket::FromHandle(pThread->m_hConnected)->Send(strMsg, strMsg.GetLength() * sizeof(TCHAR));
		}

	}
	CDialog::OnTimer(nIDEvent);
}

void CIPCdemoDlg::Init()
{
	//set ip
	CString strIP, strDlgCaption;
	if (!CUtility::GetIP(strIP))
		strIP = "";
	GetWindowText(strDlgCaption);
	strDlgCaption += _T("  Server IP : ") + strIP;
	SetWindowText(strDlgCaption);
	
	//set socket
	if (!m_pSocketServer && strIP.GetLength() > 0){

		if (AfxSocketInit() == FALSE)
			return ;

		m_pSocketServer = new CSocketServer();
		if (!m_pSocketServer->Create(SocketPort, SOCK_STREAM, strIP))
			return ;

		if (!m_pSocketServer->Listen())
			return ;

		this->SetTimer(HeartBeatID, 2000, NULL);
	}
}

void CIPCdemoDlg::Finalize()
{
	if (m_pSocketServer){
		delete m_pSocketServer;
		m_pSocketServer = NULL;
	}
}