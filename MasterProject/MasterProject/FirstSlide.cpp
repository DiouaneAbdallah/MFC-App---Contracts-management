// FirstSlide.cpp : implementation file
//

#include "stdafx.h"
#include "MasterProject.h"
#include "Accueil.h"
#include "FirstSlide.h"
#include "afxdialogex.h"


// FirstSlide dialog

IMPLEMENT_DYNAMIC(FirstSlide, CDialogEx)

FirstSlide::FirstSlide(CWnd* pParent /*=NULL*/)
	: CDialogEx(FirstSlide::IDD, pParent)
{
	Create(IDD_FIRST, pParent);
}

FirstSlide::~FirstSlide()
{
}

void FirstSlide::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(FirstSlide, CDialogEx)
END_MESSAGE_MAP()

