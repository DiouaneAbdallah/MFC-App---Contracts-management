
// MasterProjectDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Client.h"
#include "Entreprise.h"
#include "Poste.h"
#include "Contrat.h"
#include "Accueil.h"
#include "afxbutton.h"

class CMasterProjectDlg : public CDialogEx
{
public:
	CMasterProjectDlg(CWnd* pParent = NULL);
	CListCtrl m_list;
	CRect rc;
	bool m_bFirstInit;       
	bool contains(CString mystring,CString arg);
	enum { IDD = IDD_MASTERPROJECT_DIALOG };

protected:
	HICON m_hIcon;
	HICON m_home;	
	HICON m_clientsIcon;
	HICON m_exit;
	HICON m_db;
	HICON m_info;
	CFont m_font;
	CFont m_font2;

	virtual void DoDataExchange(CDataExchange* pDX);	
private:
	Client*		client;
	Entreprise* entreprise;
	Poste*		poste;
	Contrat*	contrat;
	Accueil*	home;
	BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	CSplitButton Clients_button;
	afx_msg void OnClientsAjouter();
	afx_msg void OnClickedBd();
	afx_msg void OnClickedQuitter();
	afx_msg void OnBnClickedSplit1();
	afx_msg void OnBnClickedMfcbutton3();
	CStatic d;
	afx_msg void OnBnClickedMfcbutton4();
	afx_msg void OnBnClickedMfcbutton1();
	afx_msg void OnBnClickedMfcbutton2();
	CButton Exit;
	CButton accueil;
	CButton dbS;
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedButton2();
	CButton about;
	CMFCButton clientB;
	CMFCButton entB;
	CMFCButton posteB;
	CMFCButton contratB;
	afx_msg void OnBnClickedAccueil();
};
