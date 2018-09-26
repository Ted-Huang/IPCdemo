
// ServerDlg.h : 標頭檔
//
#include <afxsock.h>
#pragma once
class CTest
{
public:
	CTest();
	~CTest();
	int m_n1;
	char m_str[80];
};

#define WM_TESTSENDMSG_MSG			WM_APP + 1

#define WM_TESTWPARAM				WM_USER + 1 
#define WM_TESTWPARAMCSTRING		WM_USER + 2 

class CListenSocket: public CSocket
{
protected:
	virtual void OnAccept(int nErrorCode);
public :
	CPtrArray m_arrSocketClient;
};

class CSessionSocket : public CSocket
{
protected:
	virtual void OnReceive(int nErrorCode);
};

// CServerDlg 對話方塊
class CServerDlg : public CDialogEx
{
// 建構
public:
	CServerDlg(CWnd* pParent = NULL);	// 標準建構函式
	~CServerDlg();

// 對話方塊資料
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

private:
	CTest* m_pTest;
	HANDLE m_hMapFile;
	CListenSocket* m_pSocket;
	int m_nHBTimerID;
private:
	
};
