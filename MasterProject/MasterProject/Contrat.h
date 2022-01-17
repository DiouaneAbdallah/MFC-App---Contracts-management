#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// Contrat dialog

class Contrat : public CDialogEx
{
	DECLARE_DYNAMIC(Contrat)

public:
	Contrat(CWnd* pParent = NULL);   // standard constructor
	virtual ~Contrat();
	bool contains(CString mystring,CString arg);
	void RefreshList();
	CRect rc;
// Dialog Data
	enum { IDD = IDD_Contrat };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic cclientstatic;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	CListCtrl m_listcontrat;
//	CComboBoxEx cclientscombo;
//	CComboBoxEx cpostescombo;
	void refreshClients();
	void refreshPostes();
	void refreshContrats();
	CComboBox cpostescombo;
	CComboBox cclientscombo;
	afx_msg void OnEditchangeCombo2();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnEditupdateCombo2();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnEditupdateCombo1();
	afx_msg void OnChangeEdit2();
	afx_msg void OnChangeEdit3();
//	CStatic ctesto;
//	afx_msg void OnPaint();
//	CStatic m_clientim;
	CComboBox ccontratscombo;
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnBnClickedButton2();
};
