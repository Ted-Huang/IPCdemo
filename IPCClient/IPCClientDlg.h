
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
	afx_msg LRESULT OnIPCMsg(WPARAM wp, LPARAM lp);
	afx_msg void OnBtnClick(UINT nID);
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void InitSocket();
	void InitCtrl();
	void Finalize();

private:
	CSocketClient* m_pSocketClient;
	CButton* m_pBtnSendMsg;
	CButton* m_pBtnSharedMem;
	CButton* m_pBtnClear;
	CListBox* m_pLbDebugString;
	HANDLE m_hMapFile;
	LPVOID m_pBuf;
	enum{
		UI_POS_ITEM_BEGIN = 100,	//太小會遇到ID重複的狀況
		//BTN
		UI_POS_BTN_BEGIN,
		UI_POS_BTN_SENDMSG,
		UI_POS_BTN_SHAREDMEMORY,
		UI_POS_BTN_CLEAR,
		UI_POS_BTN_END,
		//LIST BOX
		UI_POS_LB_BEGIN,
		UI_POS_LB_DEBUGSTRING,
		UI_POS_LB_END,
	};
};
