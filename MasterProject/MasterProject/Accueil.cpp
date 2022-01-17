// Accueil.cpp : implementation file
//

#include "stdafx.h"
#include "MasterProject.h"
#include "Accueil.h"
#include "afxdialogex.h"


// Accueil dialog

IMPLEMENT_DYNAMIC(Accueil, CDialogEx)

Accueil::Accueil(CWnd* pParent /*=NULL*/)
	: CDialogEx(Accueil::IDD, pParent)
{
	m_left = AfxGetApp()->LoadIcon(IDI_ICON23);
	m_right	= AfxGetApp()->LoadIcon(IDI_ICON24);
	Create(IDD_HOME, pParent);

}

Accueil::~Accueil()
{
}

void Accueil::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LEFT, left);
	DDX_Control(pDX, IDC_RIGHT, right);
}


BEGIN_MESSAGE_MAP(Accueil, CDialogEx)
END_MESSAGE_MAP()

BOOL Accueil::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	GetDlgItem(IDC_SLIDES)->GetWindowRect(rc);
	ScreenToClient(&rc);
	first = new FirstSlide(this);
	first->MoveWindow(rc);

	left.SetIcon(m_left);
	right.SetIcon(m_right);

	return TRUE;
}
