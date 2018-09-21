
// IPCClientDlg.h : 標頭檔
//

#pragma once


// CIPCClientDlg 對話方塊
class CSocketClient;
class CIPCClientDlg : public CDialogEx
{
// 建構
public:
	CIPCClientDlg(CWnd* pParent = NULL);	// 標準建構函式
	~CIPCClientDlg();
// 對話方塊資料
	enum { IDD = IDD_IPCCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void Finalize();

private:
	CSocketClient* m_pSocketClient;
};
