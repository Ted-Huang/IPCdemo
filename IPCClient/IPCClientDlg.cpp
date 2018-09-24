
// IPCClientDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "IPCClient.h"
#include "SocketClient.h"
#include "Utility.h"
#include "IPCClientDlg.h"
#include "afxdialogex.h"
#include "Msg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIPCClientDlg 對話方塊

CIPCClientDlg::CIPCClientDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIPCClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CIPCClientDlg::~CIPCClientDlg()
{
	Finalize();
}

void CIPCClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIPCClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, UI_POS_BTN_BEGIN, UI_POS_BTN_END, &OnBtnClick)
	ON_MESSAGE(WM_IPC_MSG, &OnIPCMsg)
END_MESSAGE_MAP()


// CIPCClientDlg 訊息處理常式

BOOL CIPCClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO:  在此加入額外的初始設定
	Init();
	InitCtrl();
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CIPCClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CIPCClientDlg::OnPaint()
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
HCURSOR CIPCClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CIPCClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (HeartBeatID == nIDEvent)
	{
		if (m_pSocketClient)
		{
			CString strMsg(_T("HeartBeat From Client"));
			m_pSocketClient->Send(strMsg, strMsg.GetLength() * sizeof(TCHAR));
		}
	}
}

void CIPCClientDlg::InitSocket()
{
	//set ip
	CString strIP, strDlgCaption;
	if (!CUtility::GetIP(strIP))
		strIP = "";
	GetWindowText(strDlgCaption);
	strDlgCaption += _T("  Client IP : ") + strIP;
	SetWindowText(strDlgCaption);

	//set socket
	if (!m_pSocketClient && strIP.GetLength() > 0){

		if (!AfxSocketInit())
			return;

		m_pSocketClient = new CSocketClient();
		if (!m_pSocketClient->Create())
			return;

		if (!m_pSocketClient->Connect(strIP, SocketPort))
			return;

		this->SetTimer(HeartBeatID, 2000, NULL);
	}
}

void CIPCClientDlg::Init()
{
	InitSocket();


	m_hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		SM_BUF_SIZE,                // maximum object size (low-order DWORD)
		SM_NAME);                 // name of mapping object

	if (m_hMapFile == NULL)
	{
		CString strError;
		strError.Format(_T("CreateFileMapping error %d"), GetLastError());
		AfxMessageBox(strError);
		return;
	}
	m_pBuf = MapViewOfFile(m_hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		SM_BUF_SIZE);

	if (m_pBuf == NULL)
	{
		CString strError;
		strError.Format(_T("MapViewOfFile error %d"), GetLastError());
		AfxMessageBox(strError);

		CloseHandle(m_hMapFile);

		return;
	}
}

void CIPCClientDlg::InitCtrl()
{
	POINT ptBase = { 0, 0 };
	POINT ptSize = { 0, 0 };

	ptBase = { 10, 10 };
	ptSize = { 120, 30 };
	m_pBtnSendMsg = new CButton();
	m_pBtnSendMsg->Create(_T("SendMsg"), WS_CHILD | WS_VISIBLE, CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_BTN_SENDMSG);

	ptBase = { 10, 50 };
	ptSize = { 120, 30 };
	m_pBtnClear = new CButton();
	m_pBtnClear->Create(_T("Clear"), WS_CHILD | WS_VISIBLE, CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_BTN_CLEAR);

	ptBase = { 10, 90 };
	ptSize = { 120, 30 };
	m_pBtnSharedMem = new CButton();
	m_pBtnSharedMem->Create(_T("Shared memory"), WS_CHILD | WS_VISIBLE, CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_BTN_SHAREDMEMORY);

	ptBase = { 250, 10 };
	ptSize = { 200, 70 };
	m_pLbDebugString = new CListBox();
	m_pLbDebugString->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL, CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_LB_DEBUGSTRING);

	ptBase = { 250, 90 };
	ptSize = { 200, 70 };
	m_pLbSMString = new CListBox();
	m_pLbSMString->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL, CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_LB_SMSTRING);

	ptBase = { 150, 90 };
	ptSize = { 80, 30 };
	m_EdSharedMem = new CEdit();
	m_EdSharedMem->Create(WS_CHILD | WS_VISIBLE | WS_BORDER , CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_ED_SHAREDMEMORY);
	
}

void CIPCClientDlg::Finalize()
{
	if (m_pSocketClient){
		delete m_pSocketClient;
		m_pSocketClient = NULL;
	}

	if (m_pBtnSendMsg){
		m_pBtnSendMsg->DestroyWindow();
		delete m_pBtnSendMsg;
		m_pBtnSendMsg = NULL;
	}
	
	if (m_pBtnClear){
		m_pBtnClear->DestroyWindow();
		delete m_pBtnClear;
		m_pBtnClear = NULL;
	}
	if (m_pBtnSharedMem){
		m_pBtnSharedMem->DestroyWindow();
		delete m_pBtnSharedMem;
		m_pBtnSharedMem = NULL;
	}

	if (m_pLbSMString){
		m_pLbSMString->DestroyWindow();
		delete m_pLbSMString;
		m_pLbSMString = NULL;
	}

	if (m_pLbDebugString){
		m_pLbDebugString->DestroyWindow();
		delete m_pLbDebugString;
		m_pLbDebugString = NULL;
	}
	
	if (m_pBuf){
		UnmapViewOfFile(m_pBuf);
		m_pBuf = NULL;
	}

	if (m_hMapFile){
		CloseHandle(m_hMapFile);
		m_hMapFile = NULL;
	}

	if (m_EdSharedMem){
		m_EdSharedMem->DestroyWindow();
		delete m_EdSharedMem;
		m_EdSharedMem = NULL;
	}
}

LRESULT CIPCClientDlg::OnIPCMsg(WPARAM wp, LPARAM lp)
{
	switch (wp)
	{
	case Cmd_Test:
	{
		CString strMsg;
		strMsg.Format(_T("%d"), lp);

		if (!m_pLbDebugString)
			return 0L;
			
			m_pLbDebugString->AddString(strMsg);
			m_pLbDebugString->SetCurSel(m_pLbDebugString->GetCount() - 1);
		break;
	}
	case Cmd_SM_CString:
	{
		HandleSharedMemory(lp);
		break;
	}
	default:
		break;
	}
	return 1L;
}

void CIPCClientDlg::OnBtnClick(UINT nID)
{
	switch (nID)
	{
	case UI_POS_BTN_SENDMSG:
	{
		HWND hwnd = ::FindWindow(_T("CIPCdemoDlg"), NULL);
		if (!hwnd)
			return;

		::PostMessage(hwnd, WM_IPC_MSG, Cmd_Test, (LPARAM)10); //lparam
		break;
	}
	case UI_POS_BTN_CLEAR:
	{
		if (!m_pLbDebugString)
			return;

		m_pLbDebugString->ResetContent();

		if (!m_pLbSMString)
			return;

		m_pLbSMString->ResetContent();
		break;

		break;
	}
	case UI_POS_BTN_SHAREDMEMORY:
	{
		if (!m_hMapFile || !m_pBuf || !m_EdSharedMem)
			return;

		HWND hwnd = ::FindWindow(_T("CIPCdemoDlg"), NULL);
		if (!hwnd)
			return;

		CString strMsg;
		m_EdSharedMem->GetWindowText(strMsg);

		if (strMsg.GetLength() == 0)
			return;
		char* szTemp[MAX_PATH];
		memset(szTemp, 0, MAX_PATH);
		memcpy(szTemp, strMsg.GetBuffer(), strMsg.GetLength() * sizeof(TCHAR));
		TRACE(_T("%d %s"), strMsg.GetLength() * sizeof(TCHAR), szTemp);
		//memcpy(m_pBuf, strMsg.GetBuffer(), strMsg.GetLength() * sizeof(TCHAR));
		memcpy(m_pBuf, szTemp, MAX_PATH);
		::PostMessage(hwnd, WM_IPC_MSG, Cmd_SM_CString, strMsg.GetLength() * sizeof(TCHAR));
		break;
	}
	default:
		break;
	}
}

void CIPCClientDlg::HandleSharedMemory(LPARAM lp)
{
	if (!m_pLbSMString)
		return;

	CString strMsg;
	
	int i2;
	memcpy(&i2, m_pBuf, (int)lp);
	strMsg.Format(_T("%d"), i2);
	m_pLbSMString->AddString(strMsg);
	m_pLbSMString->SetCurSel(m_pLbSMString->GetCount() - 1);
}