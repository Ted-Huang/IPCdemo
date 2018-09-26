
// ClientDlg.h : 標頭檔
//

#pragma once

#include <afxsock.h>

class CTest
{
public:
	CTest();
	int m_n1;
	char m_str[80];
};

class CSocketClient : public CSocket
{
protected:
	virtual void OnReceive(int nErrorCode);
};

#define WM_TESTSENDMSG_MSG			WM_APP + 1
#define WM_TESTWPARAM				WM_USER + 1 
#define WM_TESTWPARAMCSTRING		WM_USER + 2 


// CClientDlg 對話方塊
class CClientDlg : public CDialogEx
{
// 建構
public:
	CClientDlg(CWnd* pParent = NULL);	// 標準建構函式
	~CClientDlg();
// 對話方塊資料
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	void OnTimer(UINT_PTR nIDEvent);
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnMessageTest(WPARAM wp, LPARAM lp);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	afx_msg void OnBnClickedButton1();
	DECLARE_MESSAGE_MAP()
private:
	CSocketClient* m_pSocket;
	int m_nHBTimerID;
};
