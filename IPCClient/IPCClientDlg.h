
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
	DECLARE_MESSAGE_MAP()

private:
	void Init();
	void Finalize();

private:
	CSocketClient* m_pSocketClient;
};
