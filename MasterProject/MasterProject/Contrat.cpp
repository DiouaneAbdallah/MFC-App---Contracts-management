// Contrat.cpp : implementation file
//

#include "stdafx.h"
#include "MasterProject.h"
#include "Contrat.h"
#include "afxdialogex.h"
#include <time.h>



// Contrat dialog

IMPLEMENT_DYNAMIC(Contrat, CDialogEx)

Contrat::Contrat(CWnd* pParent /*=NULL*/)
	: CDialogEx(Contrat::IDD, pParent)
{
	Create(IDD_Contrat, pParent);
}

Contrat::~Contrat()
{
}

void Contrat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, 1111, cclientstatic);
	DDX_Control(pDX, IDC_LIST1, m_listcontrat);
	//DDX_Control(pDX, IDC_COMBOBOXEX2, cclientscombo);
	//DDX_Control(pDX, IDC_COMBOBOXEX3, cpostescombo);
	DDX_Control(pDX, IDC_COMBO1, cpostescombo);
	DDX_Control(pDX, IDC_COMBO2, cclientscombo);
	//  DDX_Control(pDX, IDC_testo, ctesto);
	//  DDX_Control(pDX, IDC_client, m_clientim);
	DDX_Control(pDX, IDC_COMBO3, ccontratscombo);
}


BEGIN_MESSAGE_MAP(Contrat, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &Contrat::OnBnClickedButton1)
	ON_CBN_EDITCHANGE(IDC_COMBO2, &Contrat::OnEditchangeCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO2, &Contrat::OnCbnSelchangeCombo2)
	ON_CBN_EDITUPDATE(IDC_COMBO2, &Contrat::OnEditupdateCombo2)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Contrat::OnSelchangeCombo1)
	ON_CBN_EDITCHANGE(IDC_COMBO1, &Contrat::OnEditchangeCombo1)
	ON_CBN_EDITUPDATE(IDC_COMBO1, &Contrat::OnEditupdateCombo1)
	ON_EN_CHANGE(IDC_EDIT2, &Contrat::OnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &Contrat::OnChangeEdit3)
	ON_CBN_SELCHANGE(IDC_COMBO3, &Contrat::OnCbnSelchangeCombo3)
	ON_BN_CLICKED(IDC_BUTTON2, &Contrat::OnBnClickedButton2)
END_MESSAGE_MAP()


// Contrat message handlers


BOOL Contrat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	//HICON a = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//cclientstatic.SetIcon(a);
	HICON hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	cclientstatic.SetIcon(hIcon);
	//GetDlgItem(1111)->SetIcon(hIcon,0);
	refreshClients();
	refreshPostes();
	refreshContrats();
	//RefreshList();
	m_listcontrat.InsertColumn(0,L"N°",LVCFMT_CENTER,25,-1);
	m_listcontrat.InsertColumn(1,L"Employé",LVCFMT_CENTER,115,-1);
	m_listcontrat.InsertColumn(2,L"Poste",LVCFMT_CENTER,155,-1);
	m_listcontrat.InsertColumn(3,L"Entreprise",LVCFMT_CENTER,115,-1);
	m_listcontrat.InsertColumn(4,L"Date d'Emploi",LVCFMT_CENTER,85,-1);
	
	ListView_SetExtendedListViewStyle( m_listcontrat,LVS_EX_GRIDLINES);

	RefreshList();

	cpostescombo.SetCueBanner(L"Poste");
	cclientscombo.SetCueBanner(L"Client");
	ccontratscombo.SetCueBanner(L"Contrat");
	

	
	return TRUE;
}

void Contrat::RefreshList()
{
	CDaoDatabase db;
	CDaoRecordset recset(&db);

	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString v_no_Contrat,v_Nom,v_Prenom,v_entreprise,v_Titre,v_date;
	m_listcontrat.DeleteAllItems(); // Clear List
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB


	CString SqlCmd=L"SELECT CLIENTS.Nom, CLIENTS.Prenom, CONTRATS.date_contrat, CONTRATS.no_Contrat, ENTREPRISES.nom, POSTES.Titre FROM ENTREPRISES INNER JOIN (POSTES INNER JOIN (CLIENTS INNER JOIN CONTRATS ON CLIENTS.no_Client = CONTRATS.no_Client) ON POSTES.no_Poste = CONTRATS.no_Poste) ON ENTREPRISES.no_Entreprise = POSTES.no_Entreprise order by CONTRATS.no_Contrat desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);

	COleDateTime vor;
	
	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;
		
		recset.GetFieldValue(L"no_Contrat",var);
		v_no_Contrat.Format(L"%d",(LPCWSTR)var.pbstrVal);
		m_listcontrat.InsertItem(i,v_no_Contrat,0);
		
		recset.GetFieldValue(L"Prenom",var);
		v_Prenom = (LPCWSTR)var.pbstrVal;
		recset.GetFieldValue(L"CLIENTS.Nom",var);
		v_Nom = v_Prenom + L" " + (LPCWSTR)var.pbstrVal;
		m_listcontrat.SetItemText(i,1,v_Nom);
		
		recset.GetFieldValue(L"Titre",var);
		v_Titre = (LPCWSTR)var.pbstrVal;
		m_listcontrat.SetItemText(i,2,v_Titre);
		
		recset.GetFieldValue(L"ENTREPRISES.Nom",var);
		v_entreprise = (LPCWSTR)var.pbstrVal;
		m_listcontrat.SetItemText(i,3,v_entreprise);
		
		vor = recset.GetFieldValue(L"date_contrat");

		DATE date_contrat = var.date;

		v_date = vor.Format(L"%d/%m/%Y");
		m_listcontrat.SetItemText(i,4,v_date);
		
		i++;

		recset.MoveNext();
	}

	recset.Close();

	db.Close();
}

void Contrat::refreshClients(){
	CDaoDatabase db;
	CDaoRecordset recset(&db);

	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	cclientscombo.ResetContent();
	CString v_nom_prenom,v_no_Client;
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT distinct CLIENTS.* FROM CLIENTS LEFT OUTER JOIN CONTRATS ON CLIENTS.no_Client=CONTRATS.no_Client where CONTRATS.no_Client is null order by CLIENTS.no_Client desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);

	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;

		recset.GetFieldValue(L"no_Client",var);
		v_no_Client.Format(L"%d",(LPCWSTR)var.pbstrVal);
		recset.GetFieldValue(L"Nom",var);
		v_nom_prenom = (LPCWSTR)var.pbstrVal;
		recset.GetFieldValue(L"Prenom",var);
		v_nom_prenom = v_nom_prenom + L" " +(LPCWSTR)var.pbstrVal;
		CString v_Client = v_no_Client + L" : " + v_nom_prenom;
		cclientscombo.InsertString(i,v_Client);
		//AfxMessageBox(v_Poste);
		i++;
		recset.MoveNext();
	}
	
	recset.Close();
	db.Close();
}

void Contrat::refreshPostes(){
	CDaoDatabase db;
	CDaoRecordset recset(&db);

	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	cpostescombo.ResetContent();
	CString v_Titre,v_no_Poste;
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT distinct POSTES.* FROM POSTES LEFT OUTER JOIN CONTRATS ON POSTES.no_Poste=CONTRATS.no_Poste where CONTRATS.no_Poste is null order by POSTES.no_Poste desc";
	
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	
	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;

		recset.GetFieldValue(L"no_Poste",var);
		v_no_Poste.Format(L"%d",(LPCWSTR)var.pbstrVal);
		recset.GetFieldValue(L"Titre",var);
		v_Titre = (LPCWSTR)var.pbstrVal;
		CString v_Poste = v_no_Poste + L" : " + v_Titre;
		cpostescombo.InsertString(i,v_Poste);
		i++;
		recset.MoveNext();
	}
	
	recset.Close();
	db.Close();
}

void Contrat::refreshContrats(){
	CDaoDatabase db;
	CDaoRecordset recset(&db);

	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString v_no_Contrat;
	ccontratscombo.ResetContent();
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT * from CONTRATS order by 1 desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	
	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;

		recset.GetFieldValue(L"no_Contrat",var);
		v_no_Contrat.Format(L"%d",(LPCWSTR)var.pbstrVal);
		ccontratscombo.InsertString(i,v_no_Contrat);
		i++;
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
}

void Contrat::OnBnClickedButton1()
{	
	CDaoDatabase db;
	CDaoRecordset recset(&db);

	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString v_no_Client,v_no_Poste;
	GetDlgItemText(IDC_EDIT2,v_no_Poste);
	GetDlgItemText(IDC_EDIT3,v_no_Client);
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"INSERT INTO CONTRATS(no_Client,no_Poste,date_contrat) VALUES("+v_no_Client+","+v_no_Poste+",DATE());";
	db.Execute(SqlCmd);
	
	recset.Close();
	db.Close();

	RefreshList();
	refreshClients();
	refreshPostes();
	refreshContrats();
	GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);

	GetDlgItem(IDC_TITRE)->SetWindowText(L"");
	GetDlgItem(IDC_ENTREPRISE)->SetWindowText(L"");
	GetDlgItem(IDC_SALAIRE)->SetWindowText(L"");

	GetDlgItem(IDC_NOM)->SetWindowText(L"");
	GetDlgItem(IDC_PRENOM)->SetWindowText(L"");
	GetDlgItem(IDC_LOCALITE)->SetWindowText(L"");
}

void Contrat::OnEditchangeCombo2()
{
	CString var,item,a;
	int i;
	for(i=0;i<cclientscombo.GetCount();i++){
		cclientscombo.GetLBText(i,item);
		GetDlgItemText(IDC_COMBO2,var);
		
		if(var != L""){
			if(contains(item,var) || contains(item.Mid(4),var)){
				GetDlgItem(IDC_COMBO2)->SetWindowText(item);
				int pos = 0;
				CString v_no_client = item.Tokenize(_T(" "), pos);
				CDaoDatabase db;
				CDaoRecordset recset(&db);

				COleVariant var;  // Start Variables
				var.ChangeType(VT_BSTR, NULL);
				CString v_Nom,v_Prenom,v_Localite;
				CString lpszFile=L"GestionContratsV2.mdb";
				db.Open(lpszFile); // Open Clients.MDB
				CString SqlCmd=L"SELECT * FROM CLIENTS where no_Client = "+v_no_client;
				recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
				recset.GetFieldValue(L"Nom",var);
				v_Nom = (LPCWSTR)var.pbstrVal;
				recset.GetFieldValue(L"Prenom",var);
				v_Prenom = (LPCWSTR)var.pbstrVal;
				recset.GetFieldValue(L"Localite",var);
				v_Localite = (LPCWSTR)var.pbstrVal;
					
				recset.Close();
				db.Close();

				GetDlgItem(IDC_NOM)->SetWindowText(v_Nom);
				GetDlgItem(IDC_PRENOM)->SetWindowText(v_Prenom);
				GetDlgItem(IDC_LOCALITE)->SetWindowText(v_Localite);
				SetDlgItemText(IDC_EDIT3,v_no_client);
				
				break;
			}
		}
	}	
}

bool Contrat::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}

void Contrat::OnCbnSelchangeCombo2()
{
	CString item;
	cclientscombo.GetLBText(cclientscombo.GetCurSel(), item);
		
	int pos = 0;
	CString v_no_client = item.Tokenize(_T(" "), pos);
					
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString v_Nom,v_Prenom,v_Localite;
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT * FROM CLIENTS where no_Client = "+v_no_client;
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	recset.GetFieldValue(L"Nom",var);
	v_Nom = (LPCWSTR)var.pbstrVal;
	recset.GetFieldValue(L"Prenom",var);
	v_Prenom = (LPCWSTR)var.pbstrVal;
	recset.GetFieldValue(L"Localite",var);
	v_Localite = (LPCWSTR)var.pbstrVal;
					
	recset.Close();
	db.Close();

	GetDlgItem(IDC_NOM)->SetWindowText(v_Nom);
	GetDlgItem(IDC_PRENOM)->SetWindowText(v_Prenom);
	GetDlgItem(IDC_LOCALITE)->SetWindowText(v_Localite);
	SetDlgItemText(IDC_EDIT3,v_no_client);


	

}

void Contrat::OnEditupdateCombo2()
{
	UpdateData(TRUE);
}

void Contrat::OnSelchangeCombo1()
{
	CString item;
	cpostescombo.GetLBText(cpostescombo.GetCurSel(), item);

	int pos = 0;
	CString v_no_poste = item.Tokenize(_T(" "), pos);
				
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString v_Titre,v_no_Entreprise,v_Salaire;
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT * FROM POSTES where no_Poste = "+v_no_poste;
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	recset.GetFieldValue(L"Titre",var);
	v_Titre = (LPCWSTR)var.pbstrVal;
	recset.GetFieldValue(L"Salaire",var);
	v_Salaire.Format(L"%.2f",var.fltVal);
	recset.GetFieldValue(L"no_Entreprise",var);
	v_no_Entreprise.Format(L"%d",(LPCWSTR)var.pbstrVal);
	recset.Close();
	SqlCmd=L"SELECT nom FROM ENTREPRISES where no_Entreprise = "+v_no_Entreprise;
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	recset.GetFieldValue(L"nom",var);
	CString v_Entreprise = (LPCWSTR)var.pbstrVal;
	recset.Close();
	db.Close();

	GetDlgItem(IDC_TITRE)->SetWindowText(v_Titre);
	GetDlgItem(IDC_ENTREPRISE)->SetWindowText(v_Entreprise);
	GetDlgItem(IDC_SALAIRE)->SetWindowText(v_Salaire);
	SetDlgItemText(IDC_EDIT2,v_no_poste);
}

void Contrat::OnEditchangeCombo1()
{
	CString var,item,a;
	int i;
	for(i=0;i<cpostescombo.GetCount();i++){
		cpostescombo.GetLBText(i,item);
		GetDlgItemText(IDC_COMBO1,var);
		if(var != L""){
			if(contains(item,var) || contains(item.Mid(4),var)){
				GetDlgItem(IDC_COMBO1)->SetWindowText(item);
				int pos = 0;
				CString v_no_poste = item.Tokenize(_T(" "), pos);
				
				CDaoDatabase db;
				CDaoRecordset recset(&db);
				COleVariant var;  // Start Variables
				var.ChangeType(VT_BSTR, NULL);
				CString v_Titre,v_no_Entreprise,v_Salaire;
				CString lpszFile=L"GestionContratsV2.mdb";
				db.Open(lpszFile); // Open Clients.MDB
				CString SqlCmd=L"SELECT * FROM POSTES where no_Poste = "+v_no_poste;
				recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
				recset.GetFieldValue(L"Titre",var);
				v_Titre = (LPCWSTR)var.pbstrVal;
				recset.GetFieldValue(L"Salaire",var);
				v_Salaire.Format(L"%.2f",var.fltVal);
				recset.GetFieldValue(L"no_Entreprise",var);
				v_no_Entreprise.Format(L"%d",(LPCWSTR)var.pbstrVal);
				recset.Close();
				SqlCmd=L"SELECT nom FROM ENTREPRISES where no_Entreprise = "+v_no_Entreprise;
				recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
				recset.GetFieldValue(L"nom",var);
				CString v_Entreprise = (LPCWSTR)var.pbstrVal;
				recset.Close();
				db.Close();

				GetDlgItem(IDC_TITRE)->SetWindowText(v_Titre);
				GetDlgItem(IDC_ENTREPRISE)->SetWindowText(v_Entreprise);
				GetDlgItem(IDC_SALAIRE)->SetWindowText(v_Salaire);
				SetDlgItemText(IDC_EDIT2,v_no_poste);
				break;
			}
		}
	}	
}

void Contrat::OnEditupdateCombo1()
{
	UpdateData(TRUE);
}

void Contrat::OnChangeEdit2()
{
	CString var = L"";
	GetDlgItemText(IDC_EDIT3,var);
	if(var!=L"")
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);

}

void Contrat::OnChangeEdit3()
{
	CString var = L"";
	GetDlgItemText(IDC_EDIT2,var);
	if(var!=L"")
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
}

void Contrat::OnCbnSelchangeCombo3()
{

	GetDlgItem(IDC_BUTTON2)->EnableWindow(TRUE);
	//GetDlgItem(IDC_COMBO3)->SetWindowTextW(L"");
	
}

void Contrat::OnBnClickedButton2()
{
	ccontratscombo.SetWindowText(L"");

	CDaoDatabase db;
	CDaoRecordset recset(&db);

	CString v_no_Contrat;
	//GetDlgItemText(IDC_COMBO3,v_no_Contrat);
	ccontratscombo.GetLBText(ccontratscombo.GetCurSel(), v_no_Contrat);
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile);
	CString SqlCmd=L"DELETE FROM CONTRATS WHERE no_Contrat = "+v_no_Contrat;
	db.Execute(SqlCmd);

	recset.Close();
	db.Close();

	ccontratscombo.SetCueBanner(L"Contrat supprimé!");
	
	RefreshList();
	refreshContrats();
	refreshClients();
	refreshPostes();

	GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
}
