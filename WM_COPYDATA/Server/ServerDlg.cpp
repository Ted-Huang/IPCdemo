
// ServerDlg.cpp : ��@��
//

#include "stdafx.h"
#include "Server.h"
#include "ServerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _SOCKET_PORT	9999
// �� App About �ϥ� CAboutDlg ��ܤ��

void CListenSocket::OnAccept(int nErrorCode)
{
	CString strIP;
	UINT port;
	CSessionSocket* sConnected = new CSessionSocket();
	if (Accept(*sConnected))
	{
		CString strIP;
		UINT port;
		sConnected->GetPeerName(strIP, port);
		m_arrSocketClient.Add(sConnected);
	}
	else
	{
		AfxMessageBox(_T("Cannot Accept Connection"));
	}
}

void CSessionSocket::OnReceive(int nErrorCode)
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
	CAsyncSocket::OnReceive(nErrorCode);
}


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


// CServerDlg ��ܤ��



CServerDlg::CServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CServerDlg::~CServerDlg()
{
	if (m_pSocket)
	{
		delete m_pSocket;
		m_pSocket = NULL;
	}
	KillTimer(m_nHBTimerID);
}

void CServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, &CServerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CServerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CServerDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CServerDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CServerDlg �T���B�z�`��

BOOL CServerDlg::OnInitDialog()
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
	m_pTest = new CTest();
	if (AfxSocketInit() == FALSE)
		return FALSE;

	m_pSocket = new CListenSocket();
	if (!m_pSocket->Create(_SOCKET_PORT, SOCK_STREAM, _T("192.168.8.245")))
		return FALSE;

	if (!m_pSocket->Listen())
		return FALSE ;

	m_nHBTimerID = this->SetTimer(1, 2000, NULL);

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

//
//void CServerDlg::GetIP()
//{
//	int i;
//
//	/* Variables used by GetIpAddrTable */
//	PMIB_IPADDRTABLE pIPAddrTable;
//	DWORD dwSize = 0;
//	DWORD dwRetVal = 0;
//	IN_ADDR IPAddr;
//
//	/* Variables used to return error message */
//	LPVOID lpMsgBuf;
//
//	// Before calling AddIPAddress we use GetIpAddrTable to get
//	// an adapter to which we can add the IP.
//	pIPAddrTable = (MIB_IPADDRTABLE *) malloc (sizeof(MIB_IPADDRTABLE));
//
//	if (pIPAddrTable) {
//		// Make an initial call to GetIpAddrTable to get the
//		// necessary size into the dwSize variable
//		if (GetIpAddrTable(pIPAddrTable, &dwSize, 0) ==
//			ERROR_INSUFFICIENT_BUFFER) {
//			free(pIPAddrTable);
//			pIPAddrTable = (MIB_IPADDRTABLE *) malloc (dwSize);
//
//		}
//		if (pIPAddrTable == NULL) {
//			printf("Memory allocation failed for GetIpAddrTable\n");
//			exit(1);
//		}
//	}
//	// Make a second call to GetIpAddrTable to get the
//	// actual data we want
//	if ((dwRetVal = GetIpAddrTable(pIPAddrTable, &dwSize, 0)) != NO_ERROR) {
//		printf("GetIpAddrTable failed with error %d\n", dwRetVal);
//		if (FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dwRetVal, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),       // Default language
//			(LPTSTR)& lpMsgBuf, 0, NULL)) {
//			printf("\tError: %s", lpMsgBuf);
//			LocalFree(lpMsgBuf);
//		}
//		//exit(1);
//	}
//
//	printf("\tNum Entries: %ld\n", pIPAddrTable->dwNumEntries);
//	for (i = 0; i < (int)pIPAddrTable->dwNumEntries; i++) {
//		printf("\n\tInterface Index[%d]:\t%ld\n", i, pIPAddrTable->table[i].dwIndex);
//		IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[i].dwAddr;
//		printf("\tIP Address[%d]:     \t%s\n", i, inet_ntoa(IPAddr));
//		IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[i].dwMask;
//		printf("\tSubnet Mask[%d]:    \t%s\n", i, inet_ntoa(IPAddr));
//		IPAddr.S_un.S_addr = (u_long)pIPAddrTable->table[i].dwBCastAddr;
//		printf("\tBroadCast[%d]:      \t%s (%ld%)\n", i, inet_ntoa(IPAddr), pIPAddrTable->table[i].dwBCastAddr);
//		printf("\tReassembly size[%d]:\t%ld\n", i, pIPAddrTable->table[i].dwReasmSize);
//		printf("\tType and State[%d]:", i);
//		if (pIPAddrTable->table[i].wType & MIB_IPADDR_PRIMARY)
//			printf("\tPrimary IP Address");
//		if (pIPAddrTable->table[i].wType & MIB_IPADDR_DYNAMIC)
//			printf("\tDynamic IP Address");
//		if (pIPAddrTable->table[i].wType & MIB_IPADDR_DISCONNECTED)
//			printf("\tAddress is on disconnected interface");
//		if (pIPAddrTable->table[i].wType & MIB_IPADDR_DELETED)
//			printf("\tAddress is being deleted");
//		if (pIPAddrTable->table[i].wType & MIB_IPADDR_TRANSIENT)
//			printf("\tTransient address");
//		printf("\n");
//	}
//
//	if (pIPAddrTable) {
//		free(pIPAddrTable);
//		pIPAddrTable = NULL;
//	}
//
//
//	//if (pIPAddrTable)
//	//	return pIPAddrTable[0];
//}

CTest::CTest()
{
	m_n1 = 0;
	strcpy_s(m_str, "now 0");
}

CTest::~CTest()
{
}

void CServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServerDlg::OnPaint()
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
HCURSOR CServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CServerDlg::OnBnClickedButton1() // WM_COPYDATA
{
	HWND hwnd = ::FindWindow(NULL, _T("Client"));
	if (!hwnd)
		return;

	COPYDATASTRUCT cds;

	cds.cbData = sizeof(CTest);
	cds.lpData = m_pTest;
	//WM_COPYDATA �@�w�n��sendmsg
	LRESULT lRtn = ::SendMessage(hwnd, WM_COPYDATA, (WPARAM)GetSafeHwnd(), (LPARAM)&cds);
	if (!lRtn)
	{
		DWORD dw = GetLastError();
		CString strError;
		strError.Format(_T("error %d"), dw);
		AfxMessageBox(strError);
		return;
	}

	//change value
	m_pTest->m_n1++;
	CString str;
	str.Format(_T("now %d"), m_pTest->m_n1);
	strcpy_s(m_pTest->m_str, CStringA(str).GetString());
	TRACE(m_pTest->m_str);
}

#define BUF_SIZE 100

void CServerDlg::OnBnClickedButton2()
{
	HWND hwnd = ::FindWindow(NULL, _T("Client"));
	if (!hwnd)
		return;

	::PostMessage(hwnd, WM_TESTSENDMSG_MSG, WM_TESTWPARAM, (LPARAM)10); //lparam

	
	

}


void CServerDlg::OnBnClickedButton3()
{
	
	LPCTSTR pBuf;
	m_hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		_T("MySharedMemory"));                 // name of mapping object

	if (m_hMapFile == NULL)
	{
		CString strError;
		strError.Format(_T("CreateFileMapping error %d"), GetLastError());
		AfxMessageBox(strError);
		return ;
	}
	pBuf = (LPTSTR)MapViewOfFile(m_hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		CString strError;
		strError.Format(_T("MapViewOfFile error %d"), GetLastError());
		AfxMessageBox(strError);

		CloseHandle(m_hMapFile);

		return ;
	}
	CopyMemory((PVOID)pBuf, m_pTest, sizeof(CTest));

	//change value
	m_pTest->m_n1++;
	CString str;
	str.Format(_T("now %d"), m_pTest->m_n1);
	strcpy_s(m_pTest->m_str, CStringA(str).GetString());

	AfxMessageBox(_T("Memory send!"));
}


void CServerDlg::OnBnClickedButton4()
{
	// TODO:  �b���[�J����i���B�z�`���{���X
	if (m_hMapFile)
	{
		CloseHandle(m_hMapFile);
		m_hMapFile = NULL;
	}
}

void CServerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (m_nHBTimerID == nIDEvent)
	{
		if (!m_pSocket){
			CDialog::OnTimer(nIDEvent);
			return;
		}

		for (int index = 0; index < m_pSocket->m_arrSocketClient.GetSize(); index++)
		{
			CSocket* pSocket = (CSocket*)m_pSocket->m_arrSocketClient.GetAt(index);
			if (!pSocket)
			{
				CDialog::OnTimer(nIDEvent);
				return;
			}

			CString strMsg(_T("HeartBeat!"));
			int i = strMsg.GetLength();
			pSocket->Send(strMsg, strMsg.GetLength() * sizeof(TCHAR));
		}

	}
	CDialog::OnTimer(nIDEvent);
}