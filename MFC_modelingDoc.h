
// MFC_modelingDoc.h : interface of the CMFCmodelingDoc class
//


#pragma once
#include "HupergeomSampleGenerator.h"
#include "Bernilli_Method.h"
#include "Reverse_f_method.h"
#include "DialogHist.h"
#include "Chi2Histogram.h"
#include "Pvalue.h"

class CMFCmodelingDoc : public CDocument
{
protected: // create from serialization only
	CMFCmodelingDoc() noexcept;
	DECLARE_DYNCREATE(CMFCmodelingDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CMFCmodelingDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

protected:

	DialogHist d;
	HupergeomSampleGenerator* s;
	Distribution d0;
	Distribution d1;
	Chi2Histogram h;
	pValue	PV;
	int choice_method;
	int view = 0;
	double power[10];
	int DifferentSizes[10];

public:
	const double* GetPower() const;

	const int* GetDifferentSizes() const;

	HupergeomSampleGenerator* getSample();
	Distribution& getD0();
	Chi2Histogram& getChi2();
	pValue& getPV();
	int get_view();
	afx_msg void OnModelHistogramm();
	afx_msg void OnModelSettings();
	afx_msg void OnModelpValue();
	afx_msg void OnModelPower();
	void setParams();
};
