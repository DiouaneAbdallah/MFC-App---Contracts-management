// Entreprise.cpp : implementation file
//

#include "stdafx.h"
#include "MasterProject.h"
#include "Entreprise.h"
#include "afxdialogex.h"

CDaoDatabase db1;
CDaoRecordset recset1(&db1);

IMPLEMENT_DYNAMIC(Entreprise, CDialogEx)

Entreprise::Entreprise(CWnd* pParent /*=NULL*/)
	: CDialogEx(Entreprise::IDD, pParent)
{	
	m_add	= AfxGetApp()->LoadIcon(IDI_ICON30);
	m_del	= AfxGetApp()->LoadIcon(IDI_ICON31);
	m_delA	= AfxGetApp()->LoadIcon(IDI_ICON27);
	m_up	= AfxGetApp()->LoadIcon(IDI_ICON32);
	m_app	= AfxGetApp()->LoadIcon(IDI_ICON29);
	Create(EntView, pParent);
}

Entreprise::~Entreprise()
{
}

void Entreprise::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ENT_LIST, EntsList);
	DDX_Control(pDX, IDC_ENT_NOM, EntNom);
	DDX_Control(pDX, IDC_ENT_LOC, EntLoc);
	DDX_Control(pDX, IDC_DIR_NOM, DirNom);
	DDX_Control(pDX, IDC_DIR_PRE, DirPre);
	DDX_Control(pDX, IDC_DIR_ENT, DirEnt);
	DDX_Control(pDX, IDC_ENTR, EntrepriseR);
	DDX_Control(pDX, IDC_ENT_UPDA, up);
	DDX_Control(pDX, IDC_ENT_SUPP, del);
	DDX_Control(pDX, IDC_ENTS_SUPP, delA);
	DDX_Control(pDX, IDC_APP, app);
}


BEGIN_MESSAGE_MAP(Entreprise, CDialogEx)
	ON_EN_CHANGE(IDC_ENTR, &Entreprise::OnEnChangeEntr)
	ON_EN_CHANGE(IDC_ENT_NOM, &Entreprise::OnEnChangeEntNom)
	ON_EN_CHANGE(IDC_DIR_PRE, &Entreprise::OnEnChangeDirPre)
	ON_BN_CLICKED(IDC_ENT_SUPP, &Entreprise::OnBnClickedEntSupp)
	ON_BN_CLICKED(IDC_ENT_AJOUT, &Entreprise::OnBnClickedEntAjout)
	ON_BN_CLICKED(IDC_DIR_AJOUT, &Entreprise::OnBnClickedDirAjout)
	ON_BN_CLICKED(IDC_ENT_UPDA, &Entreprise::OnBnClickedEntUpda)
	ON_BN_CLICKED(IDC_APP, &Entreprise::OnBnClickedApp)
	ON_STN_CLICKED(IDC_DIR_VAL, &Entreprise::OnStnClickedDirVal)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_ENT_LIST, &Entreprise::OnLvnItemchangedEntList)
END_MESSAGE_MAP()


void Entreprise::SetOptions(){
	CComboBox *ComboEnt=(CComboBox*)GetDlgItem(IDC_DIR_ENT);

	ComboEnt->ResetContent();
	COleVariant	var;
	var.ChangeType(VT_BSTR, NULL);
	CString lpszFile=L"GestionContratsV2.mdb";
	db1.Open(lpszFile); 
	CString SqlCmd=L"SELECT NO_ENTREPRISE,NOM FROM ENTREPRISES";
	recset1.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	CString V_no, V_nom;	
	while(!recset1.IsEOF())
	{
		recset1.GetFieldValue(0, var);
		V_no.Format(L"%d",(LPCWSTR)var.pbstrVal);
		recset1.GetFieldValue(1, var);
		V_nom = (LPCWSTR)var.pbstrVal;

		ComboEnt->AddString(V_no+L" : "+V_nom);
		recset1.MoveNext();
	}
	recset1.Close();
	db1.Close();
}

void Entreprise::fill(){
	EntsList.DeleteAllItems();
	COleVariant	var;
	var.ChangeType(VT_BSTR, NULL);
	CString lpszFile=L"GestionContratsV2.mdb";
	db1.Open(lpszFile); 
	CString SqlCmd=L"SELECT ENTREPRISES.NO_ENTREPRISE, ENTREPRISES.NOM, ENTREPRISES.LOCALITE, IIF(IsNull(DIRECTEURS.NOM), '', DIRECTEURS.NOM), IIF(IsNull(DIRECTEURS.PRENOM), '', DIRECTEURS.PRENOM) FROM ENTREPRISES LEFT JOIN DIRECTEURS ON ENTREPRISES.NO_ENTREPRISE = DIRECTEURS.NO_ENTREPRISE order by 1 desc";
	recset1.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	CString V_no, V_nom, V_localite, V_dir, V_pre;
	while(!recset1.IsEOF())
	{
		int i = 0;
		recset1.GetFieldValue(0, var);
		V_no.Format(L"%d",(LPCWSTR)var.pbstrVal);
					
		recset1.GetFieldValue(1, var);		
		V_nom = (LPCWSTR)var.pbstrVal;

		recset1.GetFieldValue(2, var);
		V_localite = (LPCWSTR)var.pbstrVal;

		recset1.GetFieldValue(3, var);
		V_dir = (LPCWSTR)var.pbstrVal;

		recset1.GetFieldValue(4, var);
		V_pre = (LPCWSTR)var.pbstrVal;

		EntsList.InsertItem(i,V_no,0);
		EntsList.SetItemText(i,1,V_nom);		
		EntsList.SetItemText(i,2,V_localite);
		EntsList.SetItemText(i,3,V_dir+L" "+V_pre);
		i++;
		recset1.MoveNext();
	}
	recset1.Close();
	db1.Close();
	ListView_SetExtendedListViewStyle(EntsList,LVS_EX_GRIDLINES);
	SetOptions();
}


BOOL Entreprise::OnInitDialog()
{
	CDialogEx::OnInitDialog();
		
	//add.SetIcon(m_add);
	del.SetIcon(m_del);
	delA.SetIcon(m_delA);
	app.SetIcon(m_app);
	up.SetIcon(m_up);

	EntsList.InsertColumn(0,L"N°",LVCFMT_CENTER,20,-1);
	EntsList.InsertColumn(1,L"Nom",LVCFMT_CENTER,100,-1);
	EntsList.InsertColumn(2,L"Localité",LVCFMT_CENTER,115,-1);
	EntsList.InsertColumn(3,L"Directeur",LVCFMT_CENTER,120,-1);
	fill();

	EntId = L"-1";

	EntrepriseR.SetCueBanner(L"Rechercher");
	EntNom.SetCueBanner(L"Nom");
	EntLoc.SetCueBanner(L"Localité");
	DirNom.SetCueBanner(L"Nom");
	DirPre.SetCueBanner(L"Prénom");
	DirEnt.SetCueBanner(L"Entreprise");

	GetDlgItem(IDC_NOM_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LOC_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_ENT_AJOUT)->EnableWindow(FALSE);			
	GetDlgItem(IDC_DIR_AJOUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENT_SUPP)->EnableWindow(FALSE);
	GetDlgItem(IDC_ENT_UPDA)->EnableWindow(FALSE);

	GetDlgItem(IDC_NOM_U)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOC_U)->EnableWindow(FALSE);

	return TRUE;
}

bool Entreprise::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}

bool Entreprise::pasvideEnt(){
	CString var1,var2;
	GetDlgItemText(IDC_ENT_NOM,var1);
	GetDlgItemText(IDC_ENT_LOC,var2);

	if(var1 == "" || var2 == "")
		return false;
	else if(var1 != "" && var2 != "")
		return true;

	return true;
}
bool Entreprise::pasvideDir(){
	CString var1,var2,var3;
	GetDlgItemText(IDC_DIR_NOM,var1);
	GetDlgItemText(IDC_DIR_PRE,var2);
	
	CComboBox *ComboEnt=(CComboBox*)GetDlgItem(IDC_DIR_ENT);
	ComboEnt->GetLBText(0, var3);

	int nTokenPos = 0;
	CString strToken = var3.Tokenize(_T("+"), nTokenPos);

	if(var1 == "" || var2 == "" || strToken == "")
		return false;
	else if(var1 != "" && var2 != "" && strToken != "")
		return true;

	return true;
}

void Entreprise::OnEnChangeEntr()
{
	CString var;	
	int i=0;
	for(i=0;i<EntsList.GetItemCount();i++){
		GetDlgItemText(IDC_ENTR,var);
		if(var != L""){
			if(contains(EntsList.GetItemText(i,0),var) || contains(EntsList.GetItemText(i,1),var) || contains(EntsList.GetItemText(i,2),var) || contains(EntsList.GetItemText(i,3),var)){
				GetDlgItem(IDC_NUM_VAL)->SetWindowText(EntsList.GetItemText(i,0));
				GetDlgItem(IDC_NOM_VAL)->SetWindowText(EntsList.GetItemText(i,1));
				GetDlgItem(IDC_LOC_VAL)->SetWindowText(EntsList.GetItemText(i,2));
				GetDlgItem(IDC_DIR_VAL)->SetWindowText(EntsList.GetItemText(i,3));

				GetDlgItem(IDC_NOM_U)->EnableWindow();
				GetDlgItem(IDC_LOC_U)->EnableWindow();

				GetDlgItem(IDC_NOM_U)->SetWindowText(EntsList.GetItemText(i,1));
				GetDlgItem(IDC_LOC_U)->SetWindowText(EntsList.GetItemText(i,2));

				GetDlgItem(IDC_ENT_SUPP)->EnableWindow();
				GetDlgItem(IDC_ENT_UPDA)->EnableWindow();
				EntId = EntsList.GetItemText(i,0);
				break;
			}else{			
				GetDlgItem(IDC_NUM_VAL)->SetWindowText(L"Aucune entreprise");
				GetDlgItem(IDC_NOM_VAL)->SetWindowText(L"Aucune entreprise");
				GetDlgItem(IDC_LOC_VAL)->SetWindowText(L"Aucune entreprise");
				GetDlgItem(IDC_DIR_VAL)->SetWindowText(L"Aucune entreprise");

				GetDlgItem(IDC_NOM_U)->SetWindowText(L"");
				GetDlgItem(IDC_LOC_U)->SetWindowText(L"");

				GetDlgItem(IDC_NOM_U)->EnableWindow(FALSE);
				GetDlgItem(IDC_LOC_U)->EnableWindow(FALSE);

				GetDlgItem(IDC_ENT_SUPP)->EnableWindow(FALSE);			
				GetDlgItem(IDC_ENT_UPDA)->EnableWindow(FALSE);

				EntId = L"-1";
			}
		}else{		
			GetDlgItem(IDC_NUM_VAL)->SetWindowText(L"");	
			GetDlgItem(IDC_NOM_VAL)->SetWindowText(L"");
			GetDlgItem(IDC_LOC_VAL)->SetWindowText(L"");
			GetDlgItem(IDC_DIR_VAL)->SetWindowText(L"");

			GetDlgItem(IDC_NOM_U)->SetWindowText(L"");
			GetDlgItem(IDC_LOC_U)->SetWindowText(L"");

			GetDlgItem(IDC_NOM_U)->EnableWindow(FALSE);
			GetDlgItem(IDC_LOC_U)->EnableWindow(FALSE);

			GetDlgItem(IDC_ENT_SUPP)->EnableWindow(FALSE);
			GetDlgItem(IDC_ENT_UPDA)->EnableWindow(FALSE);

			EntId = L"-1";
		}
	}
}

void Entreprise::OnEnChangeEntNom()
{
	if(pasvideEnt())
		GetDlgItem(IDC_ENT_AJOUT)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_ENT_AJOUT)->EnableWindow(FALSE);
}

void Entreprise::OnEnChangeDirPre()
{
	if(pasvideDir())
		GetDlgItem(IDC_DIR_AJOUT)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_DIR_AJOUT)->EnableWindow(FALSE);
}

void Entreprise::OnBnClickedEntSupp()
{
	CString lpszFile=L"GestionContratsV2.mdb";
	db1.Open(lpszFile);
		
	CString SqlCmd1=L"DELETE FROM DIRECTEURS WHERE NO_ENTREPRISE = "+EntId+";";
	db1.Execute(SqlCmd1);

	CString SqlCmd2=L"DELETE FROM ENTREPRISES WHERE NO_ENTREPRISE = "+EntId+";";
	db1.Execute(SqlCmd2);

	db1.Close();
	recset1.Close();
	GetDlgItem(IDC_ENTR)->SetWindowText(L"");
	fill();
	AfxMessageBox(L"L'entreprise a été supprimé \navec succès !",MB_ICONINFORMATION|MB_OK);
}

void Entreprise::OnBnClickedEntAjout()
{
	CString V_no, V_nom, V_localite;	
	GetDlgItemText(IDC_ENT_NOM	, V_nom);
	GetDlgItemText(IDC_ENT_LOC	, V_localite);

	CString lpszFile=L"GestionContratsV2.mdb";
	
	db1.Open(lpszFile);

	CString SqlCmd=L"INSERT INTO ENTREPRISES(NOM, LOCALITE) VALUES ('"+V_nom+"', '"+V_localite+"');";
	
	db1.Execute(SqlCmd);
	
	db1.Close();
	recset1.Close();

	GetDlgItem(IDC_ENT_NOM)->SetWindowText(L"");
	GetDlgItem(IDC_ENT_LOC)->SetWindowText(L"");

	AfxMessageBox(L"L'entreprise "+V_nom+" a été ajoutée avec succès !",MB_ICONINFORMATION|MB_OK);

	fill();
}


void Entreprise::OnBnClickedDirAjout()
{
	CString V_nom, V_prenom, V_ent;
		
	GetDlgItemText(IDC_DIR_NOM	, V_nom);
	GetDlgItemText(IDC_DIR_PRE	, V_prenom);


	CComboBox *ComboEnt=(CComboBox*)GetDlgItem(IDC_DIR_ENT);
	ComboEnt->GetLBText(ComboEnt->GetCurSel(), V_ent);

	int nTokenPos = 0;
	CString ent = V_ent.Tokenize(_T(" : "), nTokenPos);

	CString lpszFile=L"GestionContratsV2.mdb";
	
	db1.Open(lpszFile);

	CString SqlCmd=L"INSERT INTO DIRECTEURS(NO_ENTREPRISE, NOM, PRENOM) VALUES ("+ent+",'"+V_nom+"', '"+V_prenom+"');";
	
	db1.Execute(SqlCmd);
	
	db1.Close();
	recset1.Close();

	GetDlgItem(IDC_DIR_NOM)->SetWindowText(L"");
	GetDlgItem(IDC_DIR_PRE)->SetWindowText(L"");
	GetDlgItem(IDC_DIR_ENT)->SetWindowText(L"");

	AfxMessageBox(L"Le directeur "+V_nom+" a été ajouté \navec succès !",MB_ICONINFORMATION|MB_OK);

	fill();
}




void Entreprise::OnBnClickedEntUpda()
{
	GetDlgItem(IDC_NOM_VAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LOC_VAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_ENT_UPDA)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_NOM_U)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LOC_U)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_APP)->ShowWindow(SW_SHOW);
}




void Entreprise::OnBnClickedApp()
{
	CString V_no, V_nom,V_prenom, V_localite;	
	GetDlgItemText(IDC_NUM_VAL, V_no);
	GetDlgItemText(IDC_NOM_U, V_nom);
	GetDlgItemText(IDC_LOC_U, V_localite);
	CString lpszFile=L"GestionContratsV2.mdb";
	db1.Open(lpszFile);
	CString SqlCmd=L"UPDATE ENTREPRISES SET nom = '"+V_nom+"', localite = '"+V_localite+"' WHERE NO_ENTREPRISE = "+V_no+";";
	db1.Execute(SqlCmd);
	db1.Close();
	recset1.Close();
	GetDlgItem(IDC_ENTR)->SetWindowText(L"");

	GetDlgItem(IDC_NOM_VAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LOC_VAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_ENT_UPDA)->ShowWindow(SW_SHOW);

	GetDlgItem(IDC_NOM_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LOC_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);
	fill();
	AfxMessageBox(L"Les informations de l'entreprise "+V_nom+" \na été mis à jour avec succès !",MB_ICONINFORMATION|MB_OK);
}


void Entreprise::OnStnClickedDirVal()
{
	// TODO: Add your control notification handler code here
}


void Entreprise::OnLvnItemchangedEntList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
