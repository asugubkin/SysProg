
// SharedDialogDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "SharedDialog.h"
#include "SharedDialogDlg.h"
#include "afxdialogex.h"
#include "../SharedDLL/SharedDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSharedDialogDlg dialog


CSharedDialogDlg::CSharedDialogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHAREDDIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSharedDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
}

BEGIN_MESSAGE_MAP(CSharedDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CSharedDialogDlg message handlers

BOOL CSharedDialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	ghWnd = m_hWnd;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSharedDialogDlg::OnPaint()
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

HCURSOR CSharedDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSharedDialogDlg::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CDialogEx::OnActivate(nState, pWndOther, bMinimized);
	if (nState == WA_ACTIVE)
	{
		m_Edit.SetWindowText(GetSharedString());
	}
}
