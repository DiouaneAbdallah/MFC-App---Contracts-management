#pragma once


// Fen1 dialog

class Fen1 : public CDialogEx
{
	DECLARE_DYNAMIC(Fen1)

public:
	Fen1(CWnd* pParent = NULL);   // standard constructor
	virtual ~Fen1();

// Dialog Data
	enum { IDD = IDD_FORMVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
