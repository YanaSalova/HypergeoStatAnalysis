#pragma once


// DialogHist dialog

class DialogHist : public CDialog
{
	DECLARE_DYNAMIC(DialogHist)

public:
	DialogHist(CWnd* pParent = nullptr);   // standard constructor
	virtual ~DialogHist();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnEnKillfocusW0();
	afx_msg void OnEnKillfocusB0();
	afx_msg void OnEnKillfocusR0();

	afx_msg void OnEnKillfocusW1();
	afx_msg void OnEnKillfocusB1();
	afx_msg void OnEnKillfocusR1();

	afx_msg void OnEnKillfocusPvalSize();
	
	afx_msg void OnEnKillfocusSampleSize();
	afx_msg void OnEnKillfocusalpha();

	int m_n;
	int m_W0;
	int m_B0;
	int m_R0;
	int m_W1;
	int m_B1;
	int m_R1;
	int m_Npval;
	double m_alpha;
	int m_method;

	
	afx_msg void OnBnClickedOk();
};
