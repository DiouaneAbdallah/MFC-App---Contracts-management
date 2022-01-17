// Poste.cpp : implementation file
//

#include "stdafx.h"
#include <conio.h>
#include <string>
#include <iostream>
#include "MasterProject.h"
#include "Poste.h"
#include "afxdialogex.h"
#include <time.h> 
#include <windows.h>

// Poste dialog

IMPLEMENT_DYNAMIC(Poste, CDialogEx)

Poste::Poste(CWnd* pParent /*=NULL*/)
	: CDialogEx(Poste::IDD, pParent)
{
	m_add = AfxGetApp()->LoadIcon(IDI_ICON33);
	m_del	= AfxGetApp()->LoadIcon(IDI_ICON34);
	m_up = AfxGetApp()->LoadIcon(IDI_ICON35);
	m_app = AfxGetApp()->LoadIcon(IDI_ICON29);
	m_delA = AfxGetApp()->LoadIcon(IDI_ICON27);
	Create(IDD_FORMVIEW1, pParent);
}

Poste::~Poste()
{
}

void Poste::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list1);
	DDX_Control(pDX, IDC_EDIT5, csalaire);
	DDX_Control(pDX, IDC_EDIT1, crechercher);
	DDX_Control(pDX, IDC_EDIT3, ctitre);
	DDX_Control(pDX, IDC_COMBO1, centreprise);
	DDX_Control(pDX, IDC_MFCVSLISTBOX1, cqualifiications);
	DDX_Control(pDX, IDC_BUTTON4, mettreajour);
	DDX_Control(pDX, IDC_MFCVSLISTBOX2, cquallist);
	DDX_Control(pDX, IDC_COMBOentreprise, centrepriselist);
	DDX_Control(pDX, IDC_BUTTON3, delA);
	DDX_Control(pDX, IDC_BUTTON2, del);
	DDX_Control(pDX, IDC_BUTTON1, add);
}

BEGIN_MESSAGE_MAP(Poste, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &Poste::OnEnChangeEdit1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &Poste::OnDeltaposSpin1)
	ON_EN_CHANGE(IDC_EDIT3, &Poste::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT5, &Poste::OnEnChangeEdit5)
	ON_CBN_SELCHANGE(IDC_COMBO1, &Poste::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON2, &Poste::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &Poste::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &Poste::OnBnClickedButton3)
	ON_CBN_EDITCHANGE(IDC_COMBO1, &Poste::OnEditchangeCombo1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON4, &Poste::OnBnClickedButton4)
	ON_CBN_SELCHANGE(IDC_COMBOentreprise, &Poste::OnCbnSelchangeComboentreprise)
	ON_CBN_EDITCHANGE(IDC_COMBOentreprise, &Poste::OnEditchangeComboentreprise)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &Poste::OnLvnItemchangedList1)
	ON_STN_CLICKED(1024, &Poste::OnStnClicked1024)
	ON_STN_CLICKED(3111, &Poste::OnStnClicked3111)
	ON_STN_CLICKED(1111, &Poste::OnStnClicked1111)
END_MESSAGE_MAP()

void Poste::OnEnChangeEdit1()
{
	CString var;	
	int i=0;
	for(i=0;i<m_list1.GetItemCount();i++){
		GetDlgItemText(IDC_EDIT1,var);
		if(var != L""){
			if(contains(m_list1.GetItemText(i,0),var) || contains(m_list1.GetItemText(i,1),var) || contains(m_list1.GetItemText(i,2),var)){
				GetDlgItem(1111)->SetWindowText(m_list1.GetItemText(i,0));
				GetDlgItem(2111)->SetWindowText(m_list1.GetItemText(i,1));
				GetDlgItem(3111)->SetWindowText(m_list1.GetItemText(i,2));
				GetDlgItem(4111)->SetWindowText(m_list1.GetItemText(i,3));

				CDaoDatabase db;
				CDaoRecordset recset(&db);
				COleVariant qual;  // Start Variables
				qual.ChangeType(VT_BSTR, NULL);
				CString v_qualification,tmp;
				CString lpszFile=L"GestionContratsV2.mdb";
				db.Open(lpszFile); // Open Clients.MDB
				CString SqlCmd=L"SELECT designation FROM QUALIFICATIONS inner join POSSEDER on QUALIFICATIONS.no_qualification = POSSEDER.no_qualification where POSSEDER.no_Poste = " + m_list1.GetItemText(i,0);
				recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);

				while(!recset.IsEOF()) // Do until EOF
				{
					recset.GetFieldValue(L"designation",qual);
					v_qualification = (LPCWSTR)qual.pbstrVal;
					GetDlgItem(5111)->GetWindowTextW(tmp);
					if( tmp == L"Aucun poste" )
						tmp = L"";
					else{
						tmp = tmp + L"\n";
					}
					GetDlgItem(5111)->SetWindowText(tmp + v_qualification  + L"\n");
					recset.MoveNext();
				}
				recset.Close();
				db.Close();

				GetDlgItem(IDC_BUTTON4)->EnableWindow();
				GetDlgItem(IDC_BUTTON2)->EnableWindow();
				break;
			}else{
				GetDlgItem(1111)->SetWindowText(L"Aucun poste");
				GetDlgItem(2111)->SetWindowText(L"Aucun poste");
				GetDlgItem(3111)->SetWindowText(L"Aucun poste");
				GetDlgItem(4111)->SetWindowText(L"Aucun poste");
				GetDlgItem(5111)->SetWindowText(L"Aucun poste");
				GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
			}
		}else{
			GetDlgItem(1111)->SetWindowText(L"");
			GetDlgItem(2111)->SetWindowText(L"");
			GetDlgItem(3111)->SetWindowText(L"");
			GetDlgItem(4111)->SetWindowText(L"");
			GetDlgItem(5111)->SetWindowText(L"");
			GetDlgItem(IDC_BUTTON2)->EnableWindow(FALSE);
		}
	}	
}

bool Poste::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}

BOOL Poste::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	add.SetIcon(m_add);
	del.SetIcon(m_del);
	delA.SetIcon(m_delA);
	mettreajour.SetIcon(m_up);

	m_list1.InsertColumn(0,L"N°",LVCFMT_LEFT,20,-1);
	m_list1.InsertColumn(1,L"Titre",LVCFMT_LEFT,140,-1);
	m_list1.InsertColumn(2,L"Entreprise",LVCFMT_LEFT,100,-1);
	m_list1.InsertColumn(3,L"Salaire",LVCFMT_LEFT,60,-1);

	ListView_SetExtendedListViewStyle( m_list1,LVS_EX_GRIDLINES);

	csalaire.SetCueBanner(L"Salaire");
	crechercher.SetCueBanner(L"Rechercher");
	ctitre.SetCueBanner(L"Titre de poste");
	centreprise.SetCueBanner(L"Entreprise");
	cqualifiications.SetWindowTextW(L"Qualifications");
	cquallist.SetWindowTextW(L"Qualifications");
	refreshEntreprise();
	RefreshList();
	GetDlgItem(8888)->GetWindowRect(rc);
	ScreenToClient(&rc);
	return TRUE;
}

void Poste::refreshEntreprise(){
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;
	var.ChangeType(VT_BSTR, NULL);
	CString v_nom,v_no_Entreprise;
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile);
	CString SqlCmd=L"SELECT * FROM ENTREPRISES order by 1 desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	while(!recset.IsEOF())
	{
		int i = 0;
		recset.GetFieldValue(L"no_Entreprise",var);
		v_no_Entreprise.Format(L"%d",(LPCWSTR)var.pbstrVal);
		recset.GetFieldValue(L"nom",var);
		v_nom = (LPCWSTR)var.pbstrVal;
		CString v_Entreprise = v_no_Entreprise + L" : " + v_nom;
		centreprise.InsertString(i,v_Entreprise);
		centrepriselist.InsertString(i,v_Entreprise);
		i++;
		recset.MoveNext();
	}	
	recset.Close();
	db.Close();
}

void Poste::RefreshList()
{
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	COleVariant var;  // Start Variables
	var.ChangeType(VT_BSTR, NULL);
	CString v_no_Poste,v_Titre,v_no_Entreprise,v_salaire,v_no_Qualification; // End Variables
	m_list1.DeleteAllItems(); // Clear List
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT no_Poste,Titre,Nom,salaire FROM POSTES INNER JOIN ENTREPRISES ON POSTES.no_Entreprise=ENTREPRISES.no_Entreprise order by 1 desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	while(!recset.IsEOF()) // Do until EOF
	{
		int i = 0;	
		recset.GetFieldValue(L"no_Poste",var);
		v_no_Poste.Format(L"%d",(LPCWSTR)var.pbstrVal);
		m_list1.InsertItem(i,v_no_Poste,0);
		recset.GetFieldValue(L"Titre",var);
		v_Titre = (LPCWSTR)var.pbstrVal;
		m_list1.SetItemText(i,1,v_Titre);	
		recset.GetFieldValue(L"Nom",var);		
		v_no_Entreprise = (LPCWSTR)var.pbstrVal;
		m_list1.SetItemText(i,2,v_no_Entreprise);		
		recset.GetFieldValue(L"salaire",var);
		v_salaire.Format(L"%.2f",var.fltVal);
		m_list1.SetItemText(i,3,v_salaire);
		i++;		
		recset.MoveNext();
	}	
	recset.Close();
	db.Close();
}

void Poste::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	double sal;
	CString salaire;
	GetDlgItemText(IDC_EDIT5,salaire);
	sal = _tstof(salaire);
	double resolution = 0.5;
	if (pNMUpDown->iDelta == 1)
		sal = sal - resolution;
	else
		sal = sal + resolution;
	salaire.Format(L"%g", sal);
	SetDlgItemText(IDC_EDIT5,salaire);
	*pResult = 0 ;
}

void Poste::OnEnChangeEdit3()
{
	CString var1,var2,var3,item;
	GetDlgItemText(IDC_EDIT3,var1);
	GetDlgItemText(IDC_EDIT5,var2);
	int i;
	GetDlgItemText(IDC_COMBO1,var3);
	bool exist = false;
	for(i=0;i<centreprise.GetCount() && !exist;i++){
		centreprise.GetLBText(i,item);
		if(var3 == item)
			exist = true;
	}
	if(var1 == "" || var2 == "" || var3 == "")
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	else if(var1 != "" && var2 != "" && exist)
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
}

void Poste::OnEnChangeEdit5()
{
	CString var1,var2,var3,item;
	GetDlgItemText(IDC_EDIT3,var1);
	GetDlgItemText(IDC_EDIT5,var2);
	int i;
	GetDlgItemText(IDC_COMBO1,var3);
	bool exist = false;
	for(i=0;i<centreprise.GetCount() && !exist;i++){
		centreprise.GetLBText(i,item);
		if(var3 == item)
			exist = true;
	}
	if(var1 == "" || var2 == "" || var3 == "")
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
	else if(var1 != "" && var2 != "" && exist)
		GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
	
}

void Poste::OnCbnSelchangeCombo1()
{

}

void Poste::OnBnClickedButton2()
{
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CString v_no_Poste;
	GetDlgItemText(1111,v_no_Poste);
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile);

	CString SqlCmd1=L"DELETE FROM CONTRATS WHERE no_Poste = "+v_no_Poste;
	db.Execute(SqlCmd1);

	CString SqlCmd2=L"DELETE FROM POSSEDER WHERE no_Poste = "+v_no_Poste;
	db.Execute(SqlCmd2);

	CString SqlCmd3=L"DELETE FROM POSTES WHERE no_Poste = "+v_no_Poste;
	db.Execute(SqlCmd3);

	GetDlgItem(1111)->SetWindowText(L"");
	GetDlgItem(2111)->SetWindowText(L"");
	GetDlgItem(3111)->SetWindowText(L"");
	GetDlgItem(4111)->SetWindowText(L"");
	GetDlgItem(IDC_EDIT1)->SetWindowText(L"");
	RefreshList();
		
	AfxMessageBox(L"Le poste a été supprimé \navec succès !",MB_ICONINFORMATION|MB_OK);

	recset.Close();
	db.Close();
}

void Poste::OnBnClickedButton1()
{
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CDaoRecordset recsetq(&db);
	CString v_Titre,v_no_Entreprise,v_salaire,v_no_Qualification;
	GetDlgItemText(IDC_EDIT3,v_Titre);
	GetDlgItemText(IDC_EDIT5,v_salaire);
	GetDlgItemText(IDC_COMBO1,v_no_Entreprise);
	v_no_Entreprise = v_no_Entreprise[0]; // gotta figure this out
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"SELECT * FROM POSTES";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	recset.AddNew();
	recset.SetFieldValue(L"Titre",(LPCWSTR)v_Titre);
	recset.SetFieldValue(L"no_Entreprise",(LPCTSTR)v_no_Entreprise);
	recset.SetFieldValue(L"salaire",(LPCWSTR)v_salaire);
	recset.Update();
	recset.Close();
	RefreshList();

	AfxMessageBox(L"Le poste a été creé avec succès !",MB_ICONINFORMATION|MB_OK);

	int i;
	CString v_designation;
	CString Sqlcmdq=L"SELECT * FROM QUALIFICATIONS";	
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,Sqlcmdq,NULL);
	for(i=0;i<cqualifiications.GetCount();i++){
		v_designation = cqualifiications.GetItemText(i);	
		recset.AddNew();
		recset.SetFieldValue(L"designation",(LPCWSTR)v_designation);
		recset.Update();
	}
	recset.Close();
	CString Sqlcmdp = L"SELECT no_Poste FROM POSTES where Titre = '" + v_Titre +"'";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,Sqlcmdp,NULL);
	CString v_no_Poste;
	COleVariant var;
	var.ChangeType(VT_BSTR, NULL);
	recset.GetFieldValue(L"no_Poste",var);
	v_no_Poste.Format(L"%d",(LPCWSTR)var.pbstrVal);
	recset.Close();
	CString Sqlcmd1=L"SELECT * FROM POSSEDER";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,Sqlcmd1,NULL);
	CString Sqlcmdqq;
	for(i=0;i<cqualifiications.GetCount();i++){
		Sqlcmdqq.Format(L"SELECT * FROM QUALIFICATIONS where designation = '%s'",cqualifiications.GetItemText(i));
		recsetq.Open(AFX_DAO_USE_DEFAULT_TYPE,Sqlcmdqq,NULL);
		recsetq.GetFieldValue(L"no_Qualification",var);
		v_no_Qualification.Format(L"%d",(LPCWSTR)var.pbstrVal);
		recset.AddNew();
		recset.SetFieldValue(L"no_Poste",(LPCWSTR)v_no_Poste);
		recset.SetFieldValue(L"no_Qualification",(LPCWSTR)v_no_Qualification);
		recset.Update();
		recsetq.Close();
	}
	recset.Close();
	db.Close();
	GetDlgItem(9902)->ShowWindow(SW_SHOW);
}

void Poste::OnBnClickedButton3()
{
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); // Open Clients.MDB
	CString SqlCmd=L"DELETE FROM POSTES";
	db.Execute(SqlCmd);
	RefreshList();
	recset.Close();
	db.Close();
}

void Poste::OnEditchangeCombo1()
{
	CString var,item,a;
	int i=0;
	GetDlgItem(9901)->ShowWindow(SW_HIDE);
	GetDlgItem(9900)->ShowWindow(SW_HIDE);
	GetDlgItem(9902)->ShowWindow(SW_HIDE);
	for(i=0;i<centreprise.GetCount();i++){
		centreprise.GetLBText(i,item);
		GetDlgItemText(IDC_COMBO1,var);
		GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		if(var != L""){
			if(contains(item,var)  || contains(item.Mid(4),var)){
				GetDlgItem(9901)->ShowWindow(SW_HIDE);
				GetDlgItem(9900)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_COMBO1)->SetWindowText(item);
				GetDlgItem(IDC_BUTTON1)->EnableWindow(TRUE);
				break;
			}else{
				GetDlgItem(9900)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
			}
		}else{
			GetDlgItem(9901)->ShowWindow(SW_SHOW);
			GetDlgItem(IDC_BUTTON1)->EnableWindow(FALSE);
		}
	}	
}

void Poste::OnPaint()
{
	CPaintDC dc(this);
}

void Poste::OnBnClickedButton4()
{
	CString boutontitre;
	mettreajour.GetWindowTextW(boutontitre);
	if(boutontitre == L"Mettre à Jour"){
		mettreajour.SetIcon(m_app);

		GetDlgItem(2111)->ShowWindow(SW_HIDE);
		GetDlgItem(3111)->ShowWindow(SW_HIDE);
		GetDlgItem(4111)->ShowWindow(SW_HIDE);
		GetDlgItem(5111)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_EDIT6)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_EDITsalaire)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_COMBOentreprise)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_MFCVSLISTBOX2)->ShowWindow(SW_SHOW);
		
		mettreajour.SetWindowTextW(L"Appliquer");
		CString var;
		GetDlgItemText(2111,var);
		GetDlgItem(IDC_EDIT6)->SetWindowTextW(var);
		GetDlgItemText(3111,var);
		GetDlgItem(IDC_COMBOentreprise)->SetWindowTextW(var);
		GetDlgItemText(4111,var);
		GetDlgItem(IDC_EDITsalaire)->SetWindowTextW(var);
		OnEditchangeComboentreprise();
		GetDlgItemText(5111,var);
		int nTokenPos = 0;
		CString strToken = var.Tokenize(_T("\n"), nTokenPos);
		while (!strToken.IsEmpty()){
			cquallist.AddItem(strToken);
			strToken = var.Tokenize(_T("\n"), nTokenPos);
		}
	}else{
		mettreajour.SetIcon(m_up);

		CDaoDatabase db;
		CDaoRecordset recset(&db);

		CString v_no_Poste,v_Titre,v_no_Entreprise,v_salaire,v_no_Qualification;
		GetDlgItemText(1111,v_no_Poste);
		GetDlgItemText(IDC_EDIT6,v_Titre);
		GetDlgItemText(IDC_EDITsalaire,v_salaire);
		GetDlgItemText(IDC_COMBOentreprise,v_no_Entreprise);
		
		v_no_Entreprise = v_no_Entreprise[0]; // gotta figure this out
		CString lpszFile=L"GestionContratsV2.mdb";
		db.Open(lpszFile);
		CString SqlCmd = L"UPDATE POSTES SET Titre = '"+v_Titre+"', no_Entreprise = "+v_no_Entreprise+", salaire = "+v_salaire+" where no_Poste = "+v_no_Poste+";";
		db.Execute(SqlCmd);
		recset.Close();
		db.Close();
			
		AfxMessageBox(L"Les informations du poste a été mis à jour avec succès !",MB_ICONINFORMATION|MB_OK);

		RefreshList();
		GetDlgItem(2111)->ShowWindow(SW_SHOW);
		GetDlgItem(3111)->ShowWindow(SW_SHOW);
		GetDlgItem(4111)->ShowWindow(SW_SHOW);
		GetDlgItem(5111)->ShowWindow(SW_SHOW);

		GetDlgItem(IDC_EDIT6)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_EDITsalaire)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_COMBOentreprise)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_MFCVSLISTBOX2)->ShowWindow(SW_HIDE);
		OnEnChangeEdit1();
		mettreajour.SetWindowTextW(L"Mettre à Jour");
	}
}

void Poste::OnCbnSelchangeComboentreprise()
{
	// TODO: Add your control notification handler code here
}


void Poste::OnEditchangeComboentreprise()
{
	CString var,item,a;
	int i=0;

	for(i=0;i<centrepriselist.GetCount();i++){
		centrepriselist.GetLBText(i,item);
		GetDlgItemText(IDC_COMBOentreprise,var);
		if(var != L""){
			if(contains(item,var)  || contains(item.Mid(4),var)){
				GetDlgItem(IDC_COMBOentreprise)->SetWindowText(item);
				break;
			}
		}	
	}
}

void Poste::OnLbnSelchangeList2()
{
	// TODO: Add your control notification handler code here
}


void Poste::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void Poste::OnStnClicked1024()
{
	// TODO: Add your control notification handler code here
}


void Poste::OnStnClicked3111()
{
	// TODO: Add your control notification handler code here
}


void Poste::OnStnClicked1111()
{
	// TODO: Add your control notification handler code here
}
