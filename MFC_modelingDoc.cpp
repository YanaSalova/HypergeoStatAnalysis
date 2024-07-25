// MFC_modelingDoc.cpp : implementation of the CMFCmodelingDoc class
//

#include "pch.h"
#include "framework.h"
#include "DialogHist.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_modeling.h"
#endif

#include "MFC_modelingDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCmodelingDoc

IMPLEMENT_DYNCREATE(CMFCmodelingDoc, CDocument)

BEGIN_MESSAGE_MAP(CMFCmodelingDoc, CDocument)

	ON_COMMAND(ID_HISTOGRAMM, &CMFCmodelingDoc::OnModelHistogramm)
	ON_COMMAND(ID_SETTINGS, &CMFCmodelingDoc::OnModelSettings)
	ON_COMMAND(ID_Pvalue, &CMFCmodelingDoc::OnModelpValue)
	ON_COMMAND(ID_POWER, &CMFCmodelingDoc::OnModelPower)

END_MESSAGE_MAP()


// CMFCmodelingDoc construction/destruction

CMFCmodelingDoc::CMFCmodelingDoc() noexcept
{
	d0.Modeling_theoretical_prob();
	d1.Modeling_theoretical_prob();

	s = new Reverse_f_method(100, d1);
	s->Simulate();

	choice_method = 0;

	d.m_method = choice_method;
	d.m_n = s->Get_sample_size();

	d.m_W0 = d0.Geta();
	d.m_W1 = d1.Geta();

	d.m_B0 = d0.Getb();
	d.m_B1 = d1.Getb();

	d.m_R0 = d0.Get_removed();
	d.m_R1 = d1.Get_removed();

	d.m_alpha = PV.GetAlpha();
	d.m_Npval = PV.GetPvaluesize();

	double power[10]{ 0 };
	int DifferentSizes[10]{ 0 };
}

CMFCmodelingDoc::~CMFCmodelingDoc()
{
	delete s;
}

BOOL CMFCmodelingDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

// CMFCmodelingDoc serialization

void CMFCmodelingDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CMFCmodelingDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CMFCmodelingDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCmodelingDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCmodelingDoc diagnostics

#ifdef _DEBUG
void CMFCmodelingDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCmodelingDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


void CMFCmodelingDoc::setParams()
{
	PV.SetPvaluesize(d.m_Npval);
	PV.SetAlpha(d.m_alpha);
	delete s;
	s = nullptr;

	d0.Seta(d.m_W0);
    d1.Seta(d.m_W1);

	d0.Setb(d.m_B0);
	d1.Setb(d.m_B1);

	d0.Set_removed(d.m_R0);
	d1.Set_removed(d.m_R1);

	d0.Modeling_theoretical_prob();
	d1.Modeling_theoretical_prob();

	switch (d.m_method) 
	{
	case 0:
		s = new Bernulli_Method(d.m_n, d1);
		choice_method = 0;
		break;
	default:
		s = new Reverse_f_method(d.m_n, d1);
		choice_method = 1;
		break;
	}

}
void CMFCmodelingDoc::OnModelHistogramm()
{
	setParams();
	s->Simulate();
	view = 1;
	UpdateAllViews(0);
}


void CMFCmodelingDoc::OnModelSettings()
{
	d.m_method = choice_method;
	d.m_n = s->Get_sample_size();

	d.m_W0 = d0.Geta();
	d.m_W1 = d1.Geta();

	d.m_B0 = d0.Getb();
	d.m_B1 = d1.Getb();

	d.m_R0 = d0.Get_removed();
	d.m_R1 = d1.Get_removed();

	d.m_Npval = PV.GetPvaluesize();
	d.m_alpha = PV.GetAlpha();

	if (d.DoModal() == IDOK) 
	{
		setParams();
	}
}

void CMFCmodelingDoc::OnModelpValue()
{
	setParams();
	view = 2;
	PV.SetPvaluesize(d.m_Npval);
	PV.FillPvalueArr(d0, s);
	PV.FillDistributionArray();
	UpdateAllViews(0);
}

void CMFCmodelingDoc::OnModelPower()
{
		setParams();
		view = 3;


		int N = s->Get_sample_size();


		if (N <= 1000) 
		{
			for (int i = 0; i < 10; ++i) 
			{
				DifferentSizes[i] = N + 1000 * i; 
			}
		}
		else if (N < 10000) 
		{
			int LastThree = N % 1000; 

			for (int i = 0; i < 10; ++i) 
			{
				DifferentSizes[i] = 1000 * i + LastThree; 
			}
		}
		else 
		{
			for (int i = 0; i < 10; ++i) 
			{
				DifferentSizes[9 - i] = N - 1000 * i; 
			}
		}

		double* pvalues;

		for (int i = 0; i < 10; ++i)
		{
			s->Set_sample_size(DifferentSizes[i]);
					
			PV.FillPvalueArr(d0, s);
			pvalues = PV.GetPvalueArr();

			double powerCount = 0;
			for (int j = 0; j < PV.GetPvaluesize(); ++j)
			{
				if (pvalues[j] < PV.GetAlpha())
				{
					++powerCount;
				}
			}
			powerCount /= PV.GetPvaluesize();;
			power[i] = powerCount;
		
		}
		

		UpdateAllViews(0);
}

int CMFCmodelingDoc::get_view()
{
	return view;
};


pValue& CMFCmodelingDoc::getPV()
{

	return PV;
}


Distribution& CMFCmodelingDoc::getD0()
{
	return d0;
}

Chi2Histogram& CMFCmodelingDoc::getChi2()
{
	return h;
}

HupergeomSampleGenerator* CMFCmodelingDoc::getSample() 
{
	return s;
}

const double* CMFCmodelingDoc::GetPower() const 
{
	return power;
}

const int* CMFCmodelingDoc::GetDifferentSizes() const 
{
	return DifferentSizes;
}

