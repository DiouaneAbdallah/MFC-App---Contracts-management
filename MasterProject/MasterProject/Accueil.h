#pragma once
#include "afxwin.h"
#include "FirstSlide.h"

// Accueil dialog

class Accueil : public CDialogEx
{
	DECLARE_DYNAMIC(Accueil)

public:
	Accueil(CWnd* pParent = NULL);   // standard constructor
	virtual ~Accueil();

// Dialog Data
	enum { IDD = IDD_HOME };
	HICON m_left;
	HICON m_right;	
	CRect rc;
	FirstSlide* first;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CButton left;
	CButton right;
	virtual BOOL OnInitDialog();
};
