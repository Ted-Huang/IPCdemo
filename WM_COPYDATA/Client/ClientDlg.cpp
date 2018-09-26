
// ClientDlg.cpp : ��@��
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientDlg ��ܤ��

void CSocketClient::OnReceive(int nErrorCode)
{
	char *pBuf = new char[1024];
	memset(pBuf, 0, 1024);
	
	int iLen;
	iLen = Receive(pBuf, 1024);
	if (iLen == SOCKET_ERROR)
	{
		TRACE(_T("Could not Receive"));
	}
	else
	{
		pBuf[iLen] = NULL;
		CString strData;
		strData.Format(_T("%s"), pBuf);
		TRACE(_T("Received :%s %s \n"), strData, pBuf);
		delete pBuf;
	}
}

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClientDlg::~CClientDlg()
{
	if (m_pSocket)
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}
	KillTimer(m_nHBTimerID);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_MESSAGE(WM_TESTSENDMSG_MSG, &OnMessageTest)
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON1, &CClientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CClientDlg �T���B�z�`��

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO:  �b���[�J�B�~����l�]�w
	if (AfxSocketInit() == FALSE)
		return FALSE;

	m_pSocket = new CSocketClient();
	if (!m_pSocket->Create())
		return FALSE;

	m_pSocket->Connect(_T("192.168.8.245"), 9999);

	m_nHBTimerID = this->SetTimer(1, 2000, NULL);
	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CClientDlg::OnPaint()
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CClientDlg::OnMessageTest(WPARAM wp, LPARAM lp)
{
	switch (wp)
	{
	case WM_TESTWPARAM:
	{
		//CTest* pTest = (CTest*)lp; //send pointer though sendmessage is not possible

		CString str;
		str.Format(_T("int : %d \n"), lp);
		TRACE(str);
		break;
	}
	case WM_TESTWPARAMCSTRING:
	{
		break;
	}
	default:
		break;
	}
	return 1;
}

BOOL CClientDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	HWND hwnd = ::FindWindow(NULL, _T("Server"));
	if (!hwnd || !pWnd || !pCopyDataStruct)
		return 0;

	if (hwnd == pWnd->m_hWnd)
	{
		CTest* pTest = (CTest*)pCopyDataStruct->lpData;
		if (!pTest)
			return 0;
		CString str;
		str.Format(_T("OnCopyData  int : %d str: %s \n"), pTest->m_n1, CString(pTest->m_str));
		TRACE(str);
		AfxMessageBox(str);
	}

	return 1;
}

#define BUF_SIZE 100

void CClientDlg::OnBnClickedButton1()
{
	HANDLE hMapFile;
	LPCTSTR pBuf;

	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		FALSE,                 // do not inherit the name
		_T("MySharedMemory"));               // name of mapping object

	if (hMapFile == NULL)
	{
		CString strError;
		strError.Format(_T("OpenFileMapping error %d"), GetLastError());
		AfxMessageBox(strError);
		return ;
	}

	pBuf = (LPTSTR)MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		CString strError;
		strError.Format(_T("MapViewOfFile error %d"), GetLastError());
		AfxMessageBox(strError);

		CloseHandle(hMapFile);

		return;
	}
	CTest* p = (CTest*)pBuf;
	CString str;
	str.Format(_T("int %d str %s "), p->m_n1, CString(p->m_str));
	TRACE(str);
	TRACE(_T("\n"));
	AfxMessageBox(str);

	UnmapViewOfFile(pBuf);

	CloseHandle(hMapFile);

}

void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nHBTimerID == nIDEvent)
	{
		if (m_pSocket)
		{
			CString strMsg(_T("HeartBeat From Client"));
			int i = strMsg.GetLength();
			m_pSocket->Send(strMsg, strMsg.GetLength() * sizeof(TCHAR));
		}
	}
}