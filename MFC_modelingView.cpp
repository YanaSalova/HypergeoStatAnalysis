// MFC_modelingView.cpp : implementation of the CMFCmodelingView class
//
#include "Resource.h"
#include "pch.h"
#include <cmath>
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFC_modeling.h"
#endif

#include "MFC_modelingDoc.h"
#include "MFC_modelingView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCmodelingView

IMPLEMENT_DYNCREATE(CMFCmodelingView, CView)

BEGIN_MESSAGE_MAP(CMFCmodelingView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	
END_MESSAGE_MAP()

// CMFCmodelingView construction/destruction

CMFCmodelingView::CMFCmodelingView() noexcept
{
	// TODO: add construction code here

}

CMFCmodelingView::~CMFCmodelingView()
{
}

BOOL CMFCmodelingView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


void CMFCmodelingView::DrawHistogramm(CDC* pDC, 
	                                  Distribution& d0, 
	                                  HupergeomSampleGenerator* s)
{
	// Получаем размеры области окна просмотра
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width(),
		height = rect.Height();

	 //Создаем перо для рисования графиков
	CPen pen;
	pen.CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);


	// Рисуем оси гистограммы
	pDC->MoveTo(width / 10 - 5, 2 * height / 15 + 5);
	pDC->LineTo(width / 10, 2 * height / 15);
	pDC->MoveTo(width / 10 + 5, 2 * height / 15 + 5);
	pDC->LineTo(width / 10, 2 * height / 15);

	pDC->LineTo(width / 10, 9. * height / 10);
	pDC->LineTo(14 * width / 15, 9 * height / 10);
	pDC->LineTo(14 * width / 15 - 5, 9 * height / 10 + 5);
	pDC->MoveTo(14 * width / 15, 9 * height / 10);
	pDC->LineTo(14 * width / 15 - 5, 9 * height / 10 - 5);

	// Восстанавливаем предыдущее перо
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();

	pDC->SetViewportOrg(width / 10, 9 * height / 10);


	int* obs_freq = s->fill_observe_freq();
	double* theor_freq = d0.GetTheoretical_prob();

	int N = s->Get_sample_size();
	int size = s->GetDist().Get_removed() + 1;
	int size_theor = d0.Get_removed() + 1;


	Chi2Histogram h(d0, s);
	h.Chi2();

	// Находим максимальное и минимальное значение частот
	int max = 0, min = s->Get_sample_size();
	for (int i = 0; i < size; ++i)
	{
		if (obs_freq[i] > max) max = obs_freq[i];
		if (obs_freq[i] < min) min = obs_freq[i];
	}
	for (int i = 0; i < size_theor; ++i) 
	{
		if (N * theor_freq[i] > max) max = N * theor_freq[i];
		if (N * theor_freq[i] < min) min = N * theor_freq[i];
	}

	// Создаем шрифт для подписей
	CFont font;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWeight = 800;
	font.CreateFontIndirect(&lf);
	CFont* def_font = pDC->SelectObject(&font);

	// Рисуем подписи осей
	CString str;
	str.Format(L"%d", max);
	pDC->TextOut(-20 - str.GetLength() * 10, -2 * height / 3 - 10, str);
	pDC->MoveTo(-5, -2 * height / 3);
	pDC->LineTo(5, -2 * height / 3);
	str.Format(L"%d", min);
	pDC->TextOut(-20 - str.GetLength() * 10, -2 * height / 3. * static_cast<double>(min) / max - 10, str);
	pDC->MoveTo(-5, -2 * height / 3. * static_cast<double>(min) / max);
	pDC->LineTo(5, -2 * height / 3. * static_cast<double>(min) / max);


	// Создаем кисти для заливки гистограммы
	CBrush brush1, brush2;
	brush1.CreateSolidBrush(RGB(247, 7, 223));
	brush2.CreateSolidBrush(RGB(55, 7, 247));

	int denom_size = max(size, size_theor);

	CBrush* pOldBrush = pDC->SelectObject(&brush1);
	for (int i = 0; i < max(size, size_theor); ++i)
	{
		double obs = 0, theor = 0;
		if (i < min(size, size_theor))
		{
			obs = obs_freq[i];
			theor = theor_freq[i] * N;
		}
		if (i >= size)
		{
			obs = 0;
			theor = static_cast<double>(theor_freq[i] * N);
		}
		if (i >= size_theor) 
		{
			obs = static_cast<double>(obs_freq[i]);
			theor = 0;
		}
		str.Format(L"%d", i);
		pDC->SelectObject(&brush2);
		pDC->Rectangle(10. * width * i / (13 * denom_size) + width / (10. * denom_size),
			                             -2 * height / 3. * theor / max, 
			                              10 * width * (i + 1.) / (13 * denom_size), 0);
		pDC->SelectObject(&brush1);
		pDC->Rectangle(10. * width * i / (13 * denom_size) + width / (5. * denom_size),
			           -2 * height / 3. * obs / max, 
			           10 * width * (i + 1.) / (13 * denom_size) - width / (10. * denom_size), 0);
		pDC->TextOut((10 * width * (2 * i + 1.) / (13 * denom_size) + width / (10. * denom_size)) 
		 / 2 - 6 * str.GetLength(), 10, str);
	}



	pDC->SelectObject(&brush2);
	pDC->Rectangle(6 * width / 10, -3 * height / 4, 6 * width / 10 + 35, -3 * height / 4 + 35);
	pDC->TextOut(6 * width / 10 + 35, -3 * height / 4, L" - Theoretical frequencies");
	pDC->SelectObject(&brush1);
	pDC->Rectangle(6 * width / 10, -3 * height / 4 + 45, 6 * width / 10 + 35, -3 * height / 4 + 75);
	pDC->TextOut(6 * width / 10 + 35, -3 * height / 4 + 45, L" - Observed frequences");

	CString strSampleSize;
	strSampleSize.Format(L"Sample size = %d", s->Get_sample_size());
	pDC->SetTextColor(RGB(255, 0, 250));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 95, strSampleSize);

	CString strP5;
	strP5.Format(L"H0: White = %d", d0.Geta());
	pDC->SetTextColor(RGB(253, 0, 252));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 135, strP5);

	CString strP0;
	strP0.Format(L"       Black = %d", d0.Getb());
	pDC->SetTextColor(RGB(253, 0, 252));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 175, strP0);

	CString strP1;
	strP1.Format(L"       Removed = %d", d0.Get_removed());
	pDC->SetTextColor(RGB(253, 0, 252));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 215, strP1);

	//////////////////////////////////////
	CString strP2;
	strP2.Format(L"H1: White = %d", s->GetDist().Geta());
	pDC->SetTextColor(RGB(253, 0, 252));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 255, strP2);

	CString strP3;
	strP3.Format(L"       Black = %d", s->GetDist().Getb());
	pDC->SetTextColor(RGB(253, 0, 252));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 295, strP3);

	CString strP4;
	strP4.Format(L"       Removed = %d", s->GetDist().Get_removed());
	pDC->SetTextColor(RGB(253, 0, 252));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 335, strP4);

	CString strDf;
	strDf.Format(L"df = %d", h.Getdf());
	pDC->SetTextColor(RGB(254, 0, 251));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 375, strDf);


	if (h.Getchi2() == -1)
	{
		CString strChiStat;
		strChiStat.Format(L"Chi2 = \inf");
		pDC->SetTextColor(RGB(251, 0, 254));
		pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 415, strChiStat);
	}
	else
	{	
		CString strChiStat;
		strChiStat.Format(L"Chi2 = %f", h.Getchi2());
		pDC->SetTextColor(RGB(251, 0, 254));
		pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 415, strChiStat);
	}


	CString strPValue;
	strPValue.Format(L"P-value = %f", h.Getpvalue());
	pDC->SetTextColor(RGB(250, 0, 255));
	pDC->TextOut(6 * width / 10 + 35, -2 * height / 3 + 455, strPValue);


	// Восстанавливаем предыдущую кисть и шрифт
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(def_font);

	delete[] obs_freq;
}


void CMFCmodelingView::Draw_p_value_distribution_func(CDC* pDC, pValue& PV)
{
	CRect rect;
	GetClientRect(&rect);
	int width = rect.Width(),
		height = rect.Height();

	double* pValueArr = PV.GetDistributionArray();

	CPen pen;
	pen.CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	pDC->TextOut(width / 4, height / 17, L"P-value distribution of the hypergeometric distribution");
	pDC->TextOut(width / 4, height / 12, L"The empirical distribution is pink, the theoretical distribution is black.");
	pDC->MoveTo(100, height / 1.1);
	pDC->LineTo(width / 1.3, height / 1.1);
	pDC->MoveTo(width / 1.3, height / 1.1);
	pDC->LineTo(width / 1.3 - 15, height / 1.1 + 15);
	pDC->MoveTo(width / 1.3, height / 1.1);
	pDC->LineTo(width / 1.3 - 15, height / 1.1 - 15);
	pDC->TextOut(width / 1.3 + 10, height / 1.1, L"alpha");


	pDC->MoveTo(100, height / 1.1);
	pDC->LineTo(100, height / 13);
	pDC->MoveTo(100, height / 13);
	pDC->LineTo(115, height / 13 + 15);
	pDC->MoveTo(100, height / 13);
	pDC->LineTo(85, height / 13 + 15);
	pDC->TextOut(90, height / 13 - 25, L"P(pvalue < alpha)");
	pDC->TextOut(100, height / 1.09, L"0");


	int x = 100;
	double y = height / 1.1;
	double delta = (width / 1.3 - 100) / 21;
	int x2 = 100;
	int y2 = height / 1.1;
	int delta2 = (height / 1.1 - height / 13) / 21;

	for (int j = 1; j < 21; j++)
	{
		pDC->MoveTo(x2 - 10, y2 - j * delta2);
		pDC->LineTo(x2 + 10, y - j * delta2);
		pDC->TextOut(x2 - 50, y2 - (j + 1) * delta2 + 20, std::to_wstring(5 * (double(j)) / 100).c_str());

		pDC->MoveTo(x + j * delta, y - 10);
		pDC->LineTo(x + j * delta, y + 10);
		pDC->TextOut(x + (j + 1) * delta - 60, y + 20, std::to_wstring(5 * (double(j)) / 100).c_str());

		pDC->MoveTo(x + (j - 1) * delta, y2 - (j - 1) * delta2);
		pDC->LineTo(x + j * delta, y - j * delta2);

	}

	pen.DeleteObject();
	pen.CreatePen(PS_SOLID, 3, RGB(214, 45, 147));
	CPen* pOldPen_new = pDC->SelectObject(&pen);
	pDC->MoveTo(x, y2);
	pDC->LineTo(x + delta, (y2 - (pValueArr[0] / 0.05) * delta2));

	for (int j = 1; j < 19; ++j) 
	{
		pDC->MoveTo(x + j * delta, (y2 - (pValueArr[j - 1] / (0.05 * j)) * j * delta2));
		pDC->LineTo(x + (j + 1) * delta, (y2 - (pValueArr[j] / (0.05 * (j + 1))) * (j + 1) * delta2));
	}

	pDC->MoveTo(x + 19 * delta, (y2 - (pValueArr[18] / (0.05 * 19)) * 19 * delta2));
	pDC->LineTo(x + 20 * delta, y2 - 20 * delta2);


}

void CMFCmodelingView::Draw_power(CDC* pDC, const int* DifferentSizes, const double* power)
{

	CRect rc;
	GetClientRect(&rc);
	double height = rc.Height();
	double width = rc.Width();

	CPen pen;
	pen.CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&pen);

	
	int x_tick = 100;
	pDC->MoveTo(100, height / 1.1);
	pDC->LineTo(width / 1.3, height / 1.1);
	pDC->MoveTo(width / 1.3, height / 1.1);
	pDC->LineTo(width / 1.3 - 15, height / 1.1 + 15);
	pDC->MoveTo(width / 1.3, height / 1.1);
	pDC->LineTo(width / 1.3 - 15, height / 1.1 - 15);
	pDC->TextOut(width / 1.3 + 10, height / 1.1, L"sample size");
	pDC->TextOut(90, height / 13 - 35, L"beta");

	pDC->MoveTo(100, height / 1.1);//y
	pDC->LineTo(100, height / 13);
	pDC->MoveTo(100, height / 13);
	pDC->LineTo(115, height / 13 + 15);
	pDC->MoveTo(100, height / 13);
	pDC->LineTo(85, height / 13 + 15);
	////////////////////////////

	double xInterval = (width / 1.3 - x_tick) / (11);
	double minY = height / 13;
	double maxY = height / 1.1;
	int prevXPixel{};
	double prevYPixel{};

	for (int i = 0; i < 10; ++i)
	{
		//Подписываем значения на оси X
		CString strX;
		strX.Format(_T("%d"), DifferentSizes[i]);

		int xPixel = static_cast<int>(x_tick + (i+1) * xInterval);
		pDC->MoveTo(xPixel, static_cast<int>(maxY) - 10);
		pDC->LineTo(xPixel, static_cast<int>(maxY) + 10);
		pDC->TextOutW(xPixel, static_cast<int>(maxY), strX);


		//Подписываем значения на оси Y
		CString strY;
		strY.Format(_T("%.3f"), power[i]);

		double yPixel = maxY - power[i] * (maxY - minY);
		pDC->MoveTo(x_tick - 10, yPixel);
		pDC->LineTo(x_tick + 10, yPixel);
		pDC->TextOutW(100, static_cast<int>(yPixel), strY);



	//	 Рисуем точку
		pDC->Ellipse(xPixel - 3, static_cast<int>(yPixel) - 3, 
			         xPixel + 3, static_cast<int>(yPixel) + 3);

	//	 Соединяем точки линиями
		if (!i) 
		{
			prevXPixel = xPixel;
			prevYPixel = yPixel;
		}
		if (i > 0) 
		{
			prevXPixel = static_cast<int>(x_tick + i * xInterval);
			double prevYPixel = maxY - power[i-1] * (maxY - minY);
			pDC->MoveTo(prevXPixel, static_cast<int>(prevYPixel));
			pDC->LineTo(xPixel, static_cast<int>(yPixel));
			prevXPixel = xPixel;
			prevYPixel = yPixel;
		}

	}


}

// CMFCmodelingView drawing

void CMFCmodelingView::OnDraw(CDC* pDC)
{
 
        CMFCmodelingDoc* pDoc = GetDocument();
        ASSERT_VALID(pDoc);
        if (!pDoc)
            return;

		Distribution& d0(pDoc->getD0());
		HupergeomSampleGenerator* s(pDoc->getSample());
		pValue& PV(pDoc->getPV());

		const double* power = pDoc->GetPower();
		const int* DifferentSizes = pDoc->GetDifferentSizes();


		int view = pDoc->get_view();

		switch (view)
		{
		case 1:
			DrawHistogramm(pDC, d0, s);
			break;
		case 2:
			Draw_p_value_distribution_func(pDC, PV);
			break;
		case 3:
			Draw_power(pDC, DifferentSizes, power);
			break;
		}
}
	



void CMFCmodelingView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCmodelingView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCmodelingView diagnostics

#ifdef _DEBUG
void CMFCmodelingView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCmodelingView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCmodelingDoc* CMFCmodelingView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCmodelingDoc)));
	return (CMFCmodelingDoc*)m_pDocument;
}
#endif //_DEBUG



// CMFCmodelingView message handlers
