
// TimerDlg.h : header file
//

#pragma once


// CTimerDlg dialog
class CTimerDlg : public CDialogEx
{
// Construction
public:
	CTimerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	int m_I;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_Progress;
	CEdit m_Edit;
	afx_msg void OnEnChangeEdit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DoSomething();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
};
