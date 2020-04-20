
// LocalLoopDlg.h : header file
//

#pragma once


// CLocalLoopDlg dialog
class CLocalLoopDlg : public CDialogEx
{
// Construction
public:
	CLocalLoopDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOCALLOOP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	bool m_bCanRun = false;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_Progress;
	CEdit m_Edit;
	afx_msg void OnEnChangeEdit();
	void DoSomething(int i);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
};
