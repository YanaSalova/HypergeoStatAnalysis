// DialogHist.cpp : implementation file
//

#include "pch.h"
#include "MFC_modeling.h"
#include "DialogHist.h"
#include "afxdialogex.h"


// DialogHist dialog

IMPLEMENT_DYNAMIC(DialogHist, CDialog)

DialogHist::DialogHist(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent),
	 m_n(0),
	 m_W0(0),
	 m_B0(0),
	 m_R0(0),
	 m_W1(0),
	 m_B1(0),
	 m_R1(0),
	 m_Npval(0),
	 m_alpha(0),
	 m_method(0)
{

}

DialogHist::~DialogHist()
{
}

void DialogHist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SampleSize, m_n);
	DDX_Text(pDX, IDC_W0, m_W0);
	DDX_Text(pDX, IDC_B0, m_B0);
	DDX_Text(pDX, IDC_R0, m_R0);
	DDX_Text(pDX, IDC_W1, m_W1);
	DDX_Text(pDX, IDC_B1, m_B1);
	DDX_Text(pDX, IDC_R1, m_R1);
	DDX_Text(pDX, IDC_PvalSize, m_Npval);


	DDX_Radio(pDX, IDC_BER, m_method);
	DDX_Text(pDX, IDC_alpha, m_alpha);
}


BEGIN_MESSAGE_MAP(DialogHist, CDialog)
	//ON_BN_CLICKED(IDC_BER, &DialogHist::OnBnClickedMethod)
	//ON_BN_CLICKED(IDC_REVERSE, &DialogHist::OnBnClickedReverse)

	//ON_EN_KILLFOCUS(IDC_W0, &DialogHist::OnEnKillfocusW0)
	//ON_EN_KILLFOCUS(IDC_B0, &DialogHist::OnEnKillfocusB0)
	ON_EN_KILLFOCUS(IDC_R0, &DialogHist::OnEnKillfocusR0)

	//ON_EN_KILLFOCUS(IDC_W1, &DialogHist::OnEnKillfocusW1)
	//ON_EN_KILLFOCUS(IDC_B1, &DialogHist::OnEnKillfocusB1)
	ON_EN_KILLFOCUS(IDC_R1, &DialogHist::OnEnKillfocusR1)

	ON_EN_KILLFOCUS(IDC_PvalSize, &DialogHist::OnEnKillfocusPvalSize)
	ON_EN_KILLFOCUS(IDC_SampleSize, &DialogHist::OnEnKillfocusSampleSize)
	ON_EN_KILLFOCUS(IDC_alpha, &DialogHist::OnEnKillfocusalpha)
	
END_MESSAGE_MAP()


// DialogHist message handlers


void DialogHist::OnEnKillfocusR0()
{
	UpdateData(1);
	if (m_R0 > m_W0||m_R0>m_B0 )
		AfxMessageBox(L"Attention: (removed <= white) & (removed <= black)");
}


void DialogHist::OnEnKillfocusR1()
{
	UpdateData(1);
	if (m_R1 > m_W1 || m_R1 > m_B1)
		AfxMessageBox(L"Attention: (removed <= white) & (removed <= black)");
}

void DialogHist::OnEnKillfocusPvalSize()
{
	UpdateData(1);
	if (m_Npval < 0) AfxMessageBox(L"Pvalue sample size > 0");
}


void DialogHist::OnEnKillfocusSampleSize()
{
	UpdateData(1);
	if (m_n < 0) AfxMessageBox(L"Must be > 0");

}

void DialogHist::OnEnKillfocusalpha()
{
	UpdateData(1);
	if (m_alpha <= 0 || m_alpha >= 1) AfxMessageBox(L"0 < alpha < 1");
}

