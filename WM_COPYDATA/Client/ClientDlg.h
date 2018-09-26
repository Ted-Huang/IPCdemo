
// ClientDlg.h : ���Y��
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


// CClientDlg ��ܤ��
class CClientDlg : public CDialogEx
{
// �غc
public:
	CClientDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	~CClientDlg();
// ��ܤ�����
	enum { IDD = IDD_CLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
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
