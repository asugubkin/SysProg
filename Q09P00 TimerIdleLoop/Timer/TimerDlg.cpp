
// TimerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Timer.h"
#include "TimerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTimerDlg dialog



CTimerDlg::CTimerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TIMER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTimerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
}

BEGIN_MESSAGE_MAP(CTimerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT, &CTimerDlg::OnEnChangeEdit)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_START, &CTimerDlg::OnBnClickedStart)
	ON_BN_CLICKED(ID_STOP, &CTimerDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CTimerDlg message handlers

BOOL CTimerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_Progress.SetRange(0, 1000);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTimerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTimerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTimerDlg::OnEnChangeEdit()
{
	CString s;
	m_Edit.GetWindowText(s);
	SetWindowText(CTime::GetCurrentTime().Format("%T") + " " + s);
}

void CTimerDlg::OnBnClickedStart()
{
	KillTimer(0);
	m_I = 0;
	SetTimer(0, 1, NULL);
}

void CTimerDlg::OnBnClickedStop()
{
	KillTimer(0);
}

void CTimerDlg::DoSomething()
{
	Sleep(5);
	m_Progress.SetPos(m_I);
	OnEnChangeEdit();
}

void CTimerDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (++m_I == 1000)
		KillTimer(0);

	DoSomething();

	CDialogEx::OnTimer(nIDEvent);
}
