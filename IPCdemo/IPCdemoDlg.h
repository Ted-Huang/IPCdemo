
// IPCdemoDlg.h : 標頭檔
//

#pragma once


class CSocketServer;
class CIPCdemoDlg : public CDialogEx
{
// 建構
public:
	CIPCdemoDlg(CWnd* pParent = NULL);	// 標準建構函式
	~CIPCdemoDlg();
// 對話方塊資料
	enum { IDD = IDD_IPCDEMO_DIALOG };

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
	CSocketServer* m_pSocketServer;
};
