#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "afxvslistbox.h"


// Poste dialog

class Poste : public CDialogEx
{
	DECLARE_DYNAMIC(Poste)

public:
	Poste(CWnd* pParent = NULL);
	virtual ~Poste();
	HICON m_add;
	HICON m_del;
	HICON m_up;
	HICON m_app;
	HICON m_delA;

	enum { IDD = IDD_FORMVIEW1 };
	bool contains(CString mystring,CString arg);
	bool pasvide();
	CFont l_font;
	void RefreshList();
	void refreshEntreprise();
	CRect rc;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	CListCtrl m_list1;
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	CEdit csalaire;
	CEdit crechercher;
	CEdit ctitre;
	CComboBox centreprise;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit5();
	afx_msg void OnCbnSelchangeCombo1();
	CVSListBox cqualifiications;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton4();
	CButton mettreajour;
	CVSListBox cquallist;
	CComboBox centrepriselist;
	afx_msg void OnCbnSelchangeComboentreprise();
	afx_msg void OnEditchangeComboentreprise();
	afx_msg void OnLbnSelchangeList2();
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnStnClicked1024();
	afx_msg void OnStnClicked3111();
	CButton delA;
	CButton del;
	CButton add;
	afx_msg void OnStnClicked1111();
};

