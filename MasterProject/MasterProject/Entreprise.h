#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// Entreprise dialog

class Entreprise : public CDialogEx
{
	DECLARE_DYNAMIC(Entreprise)

public:
	Entreprise(CWnd* pParent = NULL);   // standard constructor
	virtual ~Entreprise();

// Dialog Data
	enum { IDD = EntView };
	bool contains(CString mystring,CString arg);
	bool pasvideEnt();
	bool pasvideDir();
	void fill();
	void SetOptions();
	HICON m_add;
	HICON m_del;
	HICON m_up;
	HICON m_app;
	HICON m_delA;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl EntsList;
	CString EntId;
	CEdit EntNom;
	CEdit EntLoc;
	CEdit DirNom;
	CEdit DirPre;
	CComboBox DirEnt;
	CEdit EntrepriseR;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEntr();
	afx_msg void OnEnChangeEntNom();
	afx_msg void OnEnChangeDirPre();
	afx_msg void OnBnClickedEntSupp();
	afx_msg void OnBnClickedEntAjout();
	afx_msg void OnBnClickedDirAjout();
	afx_msg void OnBnClickedEntUpda();
	afx_msg void OnBnClickedApp();
	CButton up;
	CButton del;
	CButton delA;
	CButton app;
	afx_msg void OnStnClickedDirVal();
	afx_msg void OnLvnItemchangedEntList(NMHDR *pNMHDR, LRESULT *pResult);
};
