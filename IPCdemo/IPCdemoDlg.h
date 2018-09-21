
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
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void InitCtrl();
	void Finalize();

private:
	CSocketServer* m_pSocketServer;
	CButton* m_pBtnSendMsg;
	enum{
		UI_POS_ITEM_BEGIN = 100,	//�Ӥp�|�J��ID���ƪ����p
		UI_POS_BTN_SENDMSG,
		UI_POS_BTN_SHAREDMEMORY
	};
};
