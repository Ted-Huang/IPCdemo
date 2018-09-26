
// ServerDlg.h : ���Y��
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

// CServerDlg ��ܤ��
class CServerDlg : public CDialogEx
{
// �غc
public:
	CServerDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	~CServerDlg();

// ��ܤ�����
	enum { IDD = IDD_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
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
