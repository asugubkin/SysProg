
// IdleView.h : interface of the CIdleView class
//

#pragma once


class CIdleView : public CFormView
{
protected: // create from serialization only
	CIdleView() noexcept;
	DECLARE_DYNCREATE(CIdleView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_IDLE_FORM };
#endif

// Attributes
public:
	CIdleDoc* GetDocument() const;

// Operations
public:
	bool OnIdle();


// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CIdleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int m_I;
	int m_bCanRun = false;

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_Edit;
	CProgressCtrl m_Progress;
	afx_msg void OnEnChangeEdit();
	void DoSomething();
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
};

#ifndef _DEBUG  // debug version in IdleView.cpp
inline CIdleDoc* CIdleView::GetDocument() const
   { return reinterpret_cast<CIdleDoc*>(m_pDocument); }
#endif

