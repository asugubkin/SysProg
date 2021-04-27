
// AnonDlgDlg.h : header file
//

#pragma once


// CAnonDlg dialog
class CAnonDlg : public CDialogEx
{
// Construction
public:
	CAnonDlg(CWnd* pParent = nullptr);	// standard constructor
	~CAnonDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANONDLG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HANDLE hRead, hWrite;

	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_Text;
};
