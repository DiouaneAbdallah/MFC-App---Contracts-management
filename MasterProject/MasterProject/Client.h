#pragma once
#include "afxwin.h"
#include "afxbutton.h"


// Client dialog

class Client : public CDialogEx
{
	DECLARE_DYNAMIC(Client)

public:
	Client(CWnd* pParent = NULL);   // standard constructor
	virtual ~Client();

// Dialog Data
	enum { IDD = ClientView };
	bool contains(CString mystring,CString arg);
	bool pasvide();
	void fill();
	HICON m_add;
	HICON m_del;
	HICON m_up;
	HICON m_app;
	HICON m_delA;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString ClientId;
	CListCtrl ClientsList;

	CEdit ClientsR;
	afx_msg void OnEnChangeClientRech();
	afx_msg void OnEnChangeNom();
	afx_msg void OnBnClickedClientSupp();
	afx_msg void OnBnClickedClientUpdate();
	afx_msg void OnBnClickedApp();
	afx_msg void OnBnClickedAjouterclient();
	CEdit ClientN;
	CEdit ClientP;
	CEdit ClientL;
	CEdit ClientNomU;
	CEdit ClientPU;
	CEdit ClientLU;
	afx_msg void OnBnClickedClientsSupp();
	CButton CAdd;
	CButton del;
	CButton delA;
	CButton up;
	CButton app;
};
