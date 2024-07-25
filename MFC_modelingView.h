
// MFC_modelingView.h : interface of the CMFCmodelingView class
//

#pragma once

#include "DialogHist.h"
class CMFCmodelingView : public CView
{
protected: // create from serialization only
	CMFCmodelingView() noexcept;
	DECLARE_DYNCREATE(CMFCmodelingView)

// Attributes
public:
	CMFCmodelingDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	

protected:

// Implementation
public:
	virtual ~CMFCmodelingView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void DrawHistogramm(CDC* pDC, Distribution& d0, HupergeomSampleGenerator* s);
	void Draw_p_value_distribution_func(CDC* pDC, pValue& p_s);
	void Draw_power(CDC* pDC, const int* DifferentSizes, const double* power);


protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:

};

#ifndef _DEBUG  // debug version in MFC_modelingView.cpp
inline CMFCmodelingDoc* CMFCmodelingView::GetDocument() const
   { return reinterpret_cast<CMFCmodelingDoc*>(m_pDocument); }
#endif

