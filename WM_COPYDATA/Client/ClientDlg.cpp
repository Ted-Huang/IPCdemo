
// ClientDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CClientDlg 對話方塊

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


// CClientDlg 訊息處理常式

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO:  在此加入額外的初始設定
	if (AfxSocketInit() == FALSE)
		return FALSE;

	m_pSocket = new CSocketClient();
	if (!m_pSocket->Create())
		return FALSE;

	m_pSocket->Connect(_T("192.168.8.245"), 9999);

	m_nHBTimerID = this->SetTimer(1, 2000, NULL);
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
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