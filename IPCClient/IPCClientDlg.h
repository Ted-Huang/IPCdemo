
// IPCClientDlg.h : ���Y��
//

#pragma once


// CIPCClientDlg ��ܤ��
class CSocketClient;
class CIPCClientDlg : public CDialogEx
{
// �غc
public:
	CIPCClientDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	~CIPCClientDlg();
// ��ܤ�����
	enum { IDD = IDD_IPCCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �䴩


// �{���X��@
protected:
	HICON m_hIcon;

	// ���ͪ��T�������禡
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
	void OnInitSocket();
	void OnSocketSend();
	void InitCtrl();
	void Finalize();
	void HandleSharedMemory(LPARAM lp);

private:
	CSocketClient* m_pSocketClient;
	CButton* m_pBtnSendMsg;
	CButton* m_pBtnSharedMem;
	CButton* m_pBtnClear;
	CButton* m_pBtnConnect;
	CButton* m_pBtnSendSocket;
	CListBox* m_pLbDebugString;
	CListBox* m_pLbSMString;
	CListBox* m_pLbSocketString;
	CEdit* m_EdSharedMem;
	CEdit* m_EdServerIP;
	CEdit* m_EdServerPort;
	CEdit* m_EdSocketMsg;
	HANDLE m_hMapFile;
	LPVOID m_pBuf;
	enum{
		UI_POS_ITEM_BEGIN = 100,	//�Ӥp�|�J��ID���ƪ����p
		//BTN
		UI_POS_BTN_BEGIN,
		UI_POS_BTN_SENDMSG,
		UI_POS_BTN_SHAREDMEMORY,
		UI_POS_BTN_CLEAR,
		UI_POS_BTN_CONNECT,
		UI_POS_BTN_SOCKETSEND,
		UI_POS_BTN_END,
		//LIST BOX
		UI_POS_LB_BEGIN,
		UI_POS_LB_DEBUGSTRING,
		UI_POS_LB_SMSTRING,
		UI_POS_LB_SOCKETSTRING,
		UI_POS_LB_END,
		//EDIT
		UI_POS_ED_BEGIN,
		UI_POS_ED_SHAREDMEMORY,
		UI_POS_ED_SERVERIP,
		UI_POS_ED_SERVERPORT,
		UI_POS_ED_SOCKETMSG,
		UI_POS_ED_END,
		UI_POS_ITEM_END
	};
};

