
// LocalLoopDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "LocalLoop.h"
#include "LocalLoopDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLocalLoopDlg dialog



CLocalLoopDlg::CLocalLoopDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOCALLOOP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLocalLoopDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
}

BEGIN_MESSAGE_MAP(CLocalLoopDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT, &CLocalLoopDlg::OnEnChangeEdit)
	ON_BN_CLICKED(ID_START, &CLocalLoopDlg::OnBnClickedStart)
	ON_BN_CLICKED(ID_STOP, &CLocalLoopDlg::OnBnClickedStop)
END_MESSAGE_MAP()


// CLocalLoopDlg message handlers

BOOL CLocalLoopDlg::OnInitDialog()
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

void CLocalLoopDlg::OnPaint()
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
HCURSOR CLocalLoopDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLocalLoopDlg::OnEnChangeEdit()
{
	CString s;
	m_Edit.GetWindowText(s);
	SetWindowText(CTime::GetCurrentTime().Format("%T") + " " + s);
}

void WaitIdle()
{
	MSG msg;
	while (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		AfxGetApp()->PumpMessage();
	}
}

void CLocalLoopDlg::OnBnClickedStart()
{
	m_bCanRun = true;
	for (int i = 0; i < 1000; i++)
	{
		WaitIdle();
		DoSomething(i);
		if (!m_bCanRun)
			break;
	}
	m_bCanRun = false;
}

void CLocalLoopDlg::OnBnClickedStop()
{
	m_bCanRun = false;
}

void CLocalLoopDlg::DoSomething(int i)
{
	Sleep(5);
	m_Progress.SetPos(i);
	OnEnChangeEdit();
}
