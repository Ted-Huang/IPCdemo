
// IPCdemoDlg.h : ���Y��
//

#pragma once


class CSocketServer;
class CIPCdemoDlg : public CDialogEx
{
// �غc
public:
	CIPCdemoDlg(CWnd* pParent = NULL);	// �зǫغc�禡
	~CIPCdemoDlg();
// ��ܤ�����
	enum { IDD = IDD_IPCDEMO_DIALOG };

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
	afx_msg void OnBtnClick(UINT nID);
	afx_msg LRESULT OnIPCMsg(WPARAM wp, LPARAM lp);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void InitSocket();
	void InitCtrl();
	void Finalize();
	void HandleSharedMemory(LPARAM lp);
private:
	CSocketServer* m_pSocketServer;
	CButton* m_pBtnSendMsg;
	CButton* m_pBtnClear;
	CButton* m_pBtnSharedMem;
	CEdit* m_EdSharedMem;
	CListBox* m_pLbDebugString;
	CListBox* m_pLbSMString;
	HANDLE m_hMapFile;
	LPVOID m_pBuf;
	enum{
		UI_POS_ITEM_BEGIN = 100,	//�Ӥp�|�J��ID���ƪ����p
		//BTN
		UI_POS_BTN_BEGIN,
		UI_POS_BTN_SENDMSG,
		UI_POS_BTN_SHAREDMEMORY,
		UI_POS_BTN_CLEAR,
		UI_POS_BTN_END,
		//LIST BOX
		UI_POS_LB_BEGIN,
		UI_POS_LB_DEBUGSTRING,
		UI_POS_LB_SMSTRING,
		UI_POS_LB_END,
		//EDIT
		UI_POS_ED_BEGIN,
		UI_POS_ED_SHAREDMEMORY,
		UI_POS_ED_END,
		UI_POS_ITEM_END
	};
};
