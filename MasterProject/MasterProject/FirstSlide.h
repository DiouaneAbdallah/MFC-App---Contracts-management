#pragma once


// FirstSlide dialog

class FirstSlide : public CDialogEx
{
	DECLARE_DYNAMIC(FirstSlide)

public:
	FirstSlide(CWnd* pParent = NULL);   // standard constructor
	virtual ~FirstSlide();

// Dialog Data
	enum { IDD = IDD_FIRST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
