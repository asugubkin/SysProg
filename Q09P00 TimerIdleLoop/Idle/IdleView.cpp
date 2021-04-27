
// IdleView.cpp : implementation of the CIdleView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Idle.h"
#endif

#include "IdleDoc.h"
#include "IdleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIdleView

IMPLEMENT_DYNCREATE(CIdleView, CFormView)

BEGIN_MESSAGE_MAP(CIdleView, CFormView)
	ON_EN_CHANGE(IDC_EDIT, &CIdleView::OnEnChangeEdit)
	ON_BN_CLICKED(ID_START, &CIdleView::OnBnClickedStart)
	ON_BN_CLICKED(ID_STOP, &CIdleView::OnBnClickedStop)
END_MESSAGE_MAP()

// CIdleView construction/destruction

CIdleView::CIdleView() noexcept
	: CFormView(IDD_IDLE_FORM)
{
	// TODO: add construction code here

}

CIdleView::~CIdleView()
{
}

void CIdleView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_Edit);
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
}

BOOL CIdleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CIdleView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	m_Progress.SetRange(0, 1000);
}


// CIdleView diagnostics

#ifdef _DEBUG
void CIdleView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIdleView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIdleDoc* CIdleView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIdleDoc)));
	return (CIdleDoc*)m_pDocument;
}
#endif //_DEBUG


// CIdleView message handlers


void CIdleView::OnEnChangeEdit()
{
	CString s;
	m_Edit.GetWindowText(s);
	AfxGetMainWnd()->SetWindowText(CTime::GetCurrentTime().Format("%T") + " " + s);
}

void CIdleView::OnBnClickedStart()
{
	m_I = 0;
	m_bCanRun = true;
}

void CIdleView::OnBnClickedStop()
{
	m_bCanRun = false;
}

void CIdleView::DoSomething()
{
	Sleep(5);
	m_Progress.SetPos(m_I);
	OnEnChangeEdit();
}

bool CIdleView::OnIdle()
{
	if (!m_bCanRun)
		return false;
	if (++m_I == 1000)
		m_bCanRun = false;

	DoSomething();

	return m_bCanRun;
}
