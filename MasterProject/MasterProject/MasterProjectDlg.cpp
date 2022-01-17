
// MasterProjectDlg.cpp : implementation file
//

#include "stdafx.h"
#include <iostream>
#include "MasterProject.h"
#include "MasterProjectDlg.h"
#include "afxdialogex.h"
#include "Client.h"
#include "Poste.h"
#include "Contrat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;

CDaoDatabase db;
CDaoRecordset recset(&db);

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClientsAjouter();
	afx_msg void OnStnClickedStatic12();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_COMMAND(ID_CLIENTS_AJOUTER, &CAboutDlg::OnClientsAjouter)
END_MESSAGE_MAP()

CMasterProjectDlg::CMasterProjectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMasterProjectDlg::IDD, pParent)	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON16);
	m_home	= AfxGetApp()->LoadIcon(IDI_ICON17);
	m_exit = AfxGetApp()->LoadIcon(IDI_ICON19);
	m_db = AfxGetApp()->LoadIcon(IDI_ICON20);
	m_info = AfxGetApp()->LoadIcon(IDI_ICON21);
}

void CMasterProjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Quitter, Exit);
	DDX_Control(pDX, IDC_ACCUEIL, accueil);
	DDX_Control(pDX, IDC_BD, dbS);
	DDX_Control(pDX, IDC_ABOUT, about);
	DDX_Control(pDX, IDC_MFCBUTTON1, clientB);
	DDX_Control(pDX, IDC_MFCBUTTON2, entB);
	DDX_Control(pDX, IDC_MFCBUTTON3, posteB);
	DDX_Control(pDX, IDC_MFCBUTTON4, contratB);
}

BEGIN_MESSAGE_MAP(CMasterProjectDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_CLIENTS_AJOUTER, &CMasterProjectDlg::OnClientsAjouter)
	ON_BN_CLICKED(IDC_BD, &CMasterProjectDlg::OnClickedBd)
	ON_BN_CLICKED(IDC_Quitter, &CMasterProjectDlg::OnClickedQuitter)
	ON_BN_CLICKED(IDC_MFCBUTTON3, &CMasterProjectDlg::OnBnClickedMfcbutton3)
	ON_BN_CLICKED(IDC_MFCBUTTON4, &CMasterProjectDlg::OnBnClickedMfcbutton4)
	ON_BN_CLICKED(IDC_MFCBUTTON1, &CMasterProjectDlg::OnBnClickedMfcbutton1)
	ON_BN_CLICKED(IDC_MFCBUTTON2, &CMasterProjectDlg::OnBnClickedMfcbutton2)
	ON_BN_CLICKED(IDC_ABOUT, &CMasterProjectDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDC_BUTTON2, &CMasterProjectDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_ACCUEIL, &CMasterProjectDlg::OnBnClickedAccueil)
END_MESSAGE_MAP()

BOOL CMasterProjectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
				
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
	ScreenToClient(&rc);
	home = new Accueil(this);
	home->MoveWindow(rc);

	m_font.CreatePointFont(100, L"Work Sans SemiBold");
	m_font2.CreatePointFont(90, L"Work Sans SemiBold");

	Exit.SetFont(&m_font);
	accueil.SetFont(&m_font);
	dbS.SetFont(&m_font);
	about.SetFont(&m_font);
	clientB.SetFont(&m_font2);
	entB.SetFont(&m_font2);
	posteB.SetFont(&m_font2);
	contratB.SetFont(&m_font2);


	Exit.SetIcon(m_exit);
	accueil.SetIcon(m_home);
	dbS.SetIcon(m_db);
	about.SetIcon(m_info);

	poste		= NULL;
	contrat		= NULL;
	client		= NULL;
	entreprise	= NULL;
	//home		= NULL;

	return TRUE;
}


void CMasterProjectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CMasterProjectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CMasterProjectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlg::OnClientsAjouter()
{

}

void CMasterProjectDlg::OnClickedQuitter()
{
	OnOK();
}

void CMasterProjectDlg::OnClientsAjouter()
{

}

void CMasterProjectDlg::OnClickedBd()
{
	CString lpszFile =L"GestionContratsV2.mdb";
	db.Create(lpszFile);
	//db.Open(lpszFile);	

	CString creation_table_qualification=L"CREATE TABLE QUALIFICATIONS(no_Qualification AUTOINCREMENT PRIMARY KEY,designation VARCHAR(100));";
	CString creation_table_entreprise=L"CREATE TABLE ENTREPRISES(no_Entreprise AUTOINCREMENT PRIMARY KEY,nom VARCHAR(30), Localite VARCHAR(30));";
	CString creation_table_postes=L"CREATE TABLE POSTES(no_Poste AUTOINCREMENT PRIMARY KEY,Titre VARCHAR(30),no_Entreprise INTEGER,salaire real,FOREIGN KEY (no_Entreprise) REFERENCES ENTREPRISES(no_Entreprise));";
	CString creation_table_contrats=L"CREATE TABLE CONTRATS(no_Contrat AUTOINCREMENT PRIMARY KEY,no_Client INTEGER,no_Poste INTEGER,date_contrat DATE,FOREIGN KEY (no_Poste) REFERENCES POSTES(no_Poste),FOREIGN KEY (no_Client) REFERENCES CLIENTS(no_Client));";
	CString creation_table_posseder=L"CREATE TABLE POSSEDER(no_Poste INTEGER,no_Qualification INTEGER,FOREIGN KEY (no_Qualification) REFERENCES QUALIFICATIONS(no_Qualification),FOREIGN KEY (no_Poste) REFERENCES POSTES(no_Poste));";
	CString creation_table_directeurs=L"CREATE TABLE DIRECTEURS(no_directeur AUTOINCREMENT PRIMARY KEY,no_entreprise INTEGER, Nom VARCHAR(30), Prenom VARCHAR(30),FOREIGN KEY (no_entreprise) REFERENCES ENTREPRISES(no_entreprise));";
	CString creation_table_clients=L"CREATE TABLE CLIENTS(no_Client AUTOINCREMENT PRIMARY KEY, Nom VARCHAR(30), Prenom VARCHAR(30), Localite VARCHAR(30));";

	db.Execute(creation_table_qualification);
	db.Execute(creation_table_entreprise);
	db.Execute(creation_table_postes);
	db.Execute(creation_table_posseder);
	db.Execute(creation_table_clients);
	db.Execute(creation_table_directeurs);
	db.Execute(creation_table_contrats);
	db.Close(); 
   
}

void CMasterProjectDlg::OnBnClickedSplit1()
{
}

bool CMasterProjectDlg::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}

void CMasterProjectDlg::OnBnClickedMfcbutton1()
{
	if(home != NULL){
		delete(home);
		home = NULL;
	}
	if(contrat != NULL){
		delete(contrat);
		contrat = NULL;
	}
	if(poste != NULL){
		delete(poste);
		poste = NULL;
	}
	if(entreprise != NULL){
		delete(entreprise);
		entreprise = NULL;
	}
	if(client == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		client = new Client(this);
		client->MoveWindow(rc);
	}
}

void CMasterProjectDlg::OnBnClickedMfcbutton2()
{
	if(home != NULL){
		delete(home);
		home = NULL;
	}
	if(client != NULL){
		delete(client);
		client = NULL;
	}
	if(poste != NULL){
		delete(poste);
		poste = NULL;
	}
	if(contrat != NULL){
		delete(contrat);
		contrat = NULL;
	}
	if(entreprise == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		entreprise = new Entreprise(this);
		entreprise->MoveWindow(rc);
	}
}

void CMasterProjectDlg::OnBnClickedMfcbutton3()
{
	if(home != NULL){
		delete(home);
		home = NULL;
	}
	if(client != NULL){
		delete(client);
		client = NULL;
	}
	if(contrat != NULL){
		delete(contrat);
		contrat = NULL;
	}
	if(entreprise != NULL){
		delete(entreprise);
		entreprise = NULL;
	}
	if(poste == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		poste = new Poste(this);
		poste->MoveWindow(rc);
	}
}

void CMasterProjectDlg::OnBnClickedMfcbutton4()
{
	if(home != NULL){
		delete(home);
		home = NULL;
	}
	if(client != NULL){
		delete(client);
		client = NULL;
	}
	if(poste != NULL){
		delete(poste);
		poste = NULL;
	}
	if(entreprise != NULL){
		delete(entreprise);
		entreprise = NULL;
	}
	if(contrat == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		contrat = new Contrat(this);
		contrat->MoveWindow(rc);
	}
}




void CMasterProjectDlg::OnBnClickedAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CMasterProjectDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
}


void CAboutDlg::OnStnClickedStatic12()
{
	// TODO: Add your control notification handler code here
}


void CMasterProjectDlg::OnBnClickedAccueil()
{
	if(contrat != NULL){
		delete(contrat);
		contrat = NULL;
	}
	if(client != NULL){
		delete(client);
		client = NULL;
	}
	if(poste != NULL){
		delete(poste);
		poste = NULL;
	}
	if(entreprise != NULL){
		delete(entreprise);
		entreprise = NULL;
	}
	if(home == NULL){
		GetDlgItem(IDC_STATIC)->GetWindowRect(rc);
		ScreenToClient(&rc);
		home = new Accueil(this);
		home->MoveWindow(rc);
	}
}
