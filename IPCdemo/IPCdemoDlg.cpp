
// IPCdemoDlg.cpp : 實作檔
//

#include "stdafx.h"
#include "IPCdemo.h"
#include "IPCdemoDlg.h"
#include "afxdialogex.h"
#include "Utility.h"
#include "SocketServer.h"
#include "Msg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CIPCdemoDlg 對話方塊

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
	ON_CONTROL_RANGE(BN_CLICKED, UI_POS_BTN_BEGIN, UI_POS_BTN_END, &OnBtnClick)
	ON_MESSAGE(WM_IPC_MSG, &OnIPCMsg)
END_MESSAGE_MAP()


// CIPCdemoDlg 訊息處理常式

BOOL CIPCdemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO:  在此加入額外的初始設定
	Init();
	InitCtrl();
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CIPCdemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialogEx::OnSysCommand(nID, lParam);
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CIPCdemoDlg::OnPaint()
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

void CIPCdemoDlg::InitCtrl()
{
	POINT ptBase = { 0, 0 };
	POINT ptSize = { 0, 0 };
	ptBase = { 10, 10 };
	ptSize = { 90, 30 };
	m_pBtnSendMsg = new CButton();
	m_pBtnSendMsg->Create(_T("SendMsg"), WS_CHILD | WS_VISIBLE, CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_BTN_SENDMSG);

	ptBase = { 150, 10 };
	ptSize = { 200, 70 };
	m_pLbDebugString = new CListBox();
	m_pLbDebugString->Create(WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL, CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_LB_DEBUGSTRING);

	ptBase = { 10, 50 };
	ptSize = { 90, 30 };
	m_pBtnClear = new CButton();
	m_pBtnClear->Create(_T("Clear"), WS_CHILD | WS_VISIBLE, CRect(ptBase.x, ptBase.y, ptBase.x + ptSize.x, ptBase.y + ptSize.y), this, UI_POS_BTN_CLEAR);
}

void CIPCdemoDlg::Finalize()
{
	if (m_pSocketServer){
		delete m_pSocketServer;
		m_pSocketServer = NULL;
	}

	if (m_pBtnSendMsg){
		m_pBtnSendMsg->DestroyWindow();
		delete m_pBtnSendMsg;
		m_pBtnSendMsg = NULL;
	}

	if (m_pLbDebugString){
		m_pLbDebugString->DestroyWindow();
		delete m_pLbDebugString;
		m_pLbDebugString = NULL;
	}

	if (m_pBtnClear){
		m_pBtnClear->DestroyWindow();
		delete m_pBtnClear;
		m_pBtnClear = NULL;
	}
}

LRESULT CIPCdemoDlg::OnIPCMsg(WPARAM wp, LPARAM lp)
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
	case Cmd_SharedMemory:
	{
		TRACE(_T("rec!"));
		break;
	}
	default:
		break;
	}
	return 1L;
}


void CIPCdemoDlg::OnBtnClick(UINT nID)
{
	switch (nID)
	{
	case UI_POS_BTN_SENDMSG:
	{
		HWND hwnd = ::FindWindow(_T("CIPCClientDlg"), NULL);
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
		break;
	}
	default:
		break;
	}
}