// Client.cpp : implementation file
//

#include "stdafx.h"
#include "MasterProject.h"
#include "Client.h"
#include "afxdialogex.h"



IMPLEMENT_DYNAMIC(Client, CDialogEx)

Client::Client(CWnd* pParent /*=NULL*/)
	: CDialogEx(Client::IDD, pParent)
{
	m_add = AfxGetApp()->LoadIcon(IDI_ICON22);
	m_del	= AfxGetApp()->LoadIcon(IDI_ICON26);
	m_up = AfxGetApp()->LoadIcon(IDI_ICON28);
	m_app = AfxGetApp()->LoadIcon(IDI_ICON29);
	m_delA = AfxGetApp()->LoadIcon(IDI_ICON27);
	Create(ClientView, pParent);
}

Client::~Client()
{
}

void Client::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CLIENT_RECH, ClientsR);
	DDX_Control(pDX, IDC_NOM, ClientN);
	DDX_Control(pDX, IDC_PRENOM, ClientP);
	DDX_Control(pDX, IDC_LOCALITE, ClientL);
	DDX_Control(pDX, IDC_CLIENTS_LIST, ClientsList);
	DDX_Control(pDX, IDC_NOM_U, ClientNomU);
	DDX_Control(pDX, IDC_PRENOM_U, ClientPU);
	DDX_Control(pDX, IDC_LOCALITE_U, ClientLU);
	DDX_Control(pDX, IDC_AjouterClient, CAdd);
	DDX_Control(pDX, IDC_CLIENT_SUPP, del);
	DDX_Control(pDX, IDC_CLIENTS_SUPP, delA);
	DDX_Control(pDX, IDC_CLIENT_UPDATE, up);
	DDX_Control(pDX, IDC_APP, app);
}


BEGIN_MESSAGE_MAP(Client, CDialogEx)
	ON_EN_CHANGE(IDC_CLIENT_RECH, &Client::OnEnChangeClientRech)
	ON_EN_CHANGE(IDC_NOM, &Client::OnEnChangeNom)
	ON_BN_CLICKED(IDC_CLIENT_SUPP, &Client::OnBnClickedClientSupp)
	ON_BN_CLICKED(IDC_CLIENT_UPDATE, &Client::OnBnClickedClientUpdate)
	ON_BN_CLICKED(IDC_APP, &Client::OnBnClickedApp)
	ON_BN_CLICKED(IDC_AjouterClient, &Client::OnBnClickedAjouterclient)
	ON_BN_CLICKED(IDC_CLIENTS_SUPP, &Client::OnBnClickedClientsSupp)
END_MESSAGE_MAP()


// Client message handlers


BOOL Client::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CAdd.SetIcon(m_add);
	del.SetIcon(m_del);
	delA.SetIcon(m_delA);
	app.SetIcon(m_app);
	up.SetIcon(m_up);

	ClientsList.InsertColumn(0,L"N°",LVCFMT_CENTER,25,-1);
	ClientsList.InsertColumn(1,L"Nom",LVCFMT_CENTER,90,-1);
	ClientsList.InsertColumn(2,L"Prénom",LVCFMT_CENTER,90,-1);
	ClientsList.InsertColumn(3,L"Localité",LVCFMT_CENTER,150,-1);
	fill();

	ClientId = L"-1";

	ClientsR.SetCueBanner(L"Rechercher");
	ClientN.SetCueBanner(L"Nom");
	ClientP.SetCueBanner(L"Prénom");
	ClientL.SetCueBanner(L"Localité");

	GetDlgItem(IDC_NOM_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PRENOM_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LOCALITE_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);


	GetDlgItem(IDC_CLIENT_SUPP)->EnableWindow(FALSE);			
	GetDlgItem(IDC_CLIENT_UPDATE)->EnableWindow(FALSE);
	GetDlgItem(IDC_AjouterClient)->EnableWindow(FALSE);

	GetDlgItem(IDC_NOM_U)->EnableWindow(FALSE);
	GetDlgItem(IDC_PRENOM_U)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOCALITE_U)->EnableWindow(FALSE);
	return TRUE;
}

void Client::fill(){
	
	CDaoDatabase db;
	CDaoRecordset recset(&db);
	ClientsList.DeleteAllItems();
	COleVariant	var;
	var.ChangeType(VT_BSTR, NULL);
	CString lpszFile=L"GestionContratsV2.mdb";
	db.Open(lpszFile); 
	CString SqlCmd=L"SELECT * FROM CLIENTS order by 1 desc";
	recset.Open(AFX_DAO_USE_DEFAULT_TYPE,SqlCmd,NULL);
	CString V_no, V_nom, V_prenom, V_localite;	
	while(!recset.IsEOF())
	{
		int i = 0;
		recset.GetFieldValue(L"no_client", var);
		V_no.Format(L"%d",(LPCWSTR)var.pbstrVal);
					
		recset.GetFieldValue(L"nom", var);		
		V_nom = (LPCWSTR)var.pbstrVal;

		recset.GetFieldValue(L"prenom", var);
		V_prenom = (LPCWSTR)var.pbstrVal;

		recset.GetFieldValue(L"localite", var);
		V_localite = (LPCWSTR)var.pbstrVal;

		ClientsList.InsertItem(i,V_no,0);
		ClientsList.SetItemText(i,1,V_nom);		
		ClientsList.SetItemText(i,2,V_prenom);
		ClientsList.SetItemText(i,3,V_localite);
		i++;
		recset.MoveNext();
	}
	recset.Close();
	db.Close();
	ListView_SetExtendedListViewStyle( ClientsList,LVS_EX_GRIDLINES);
}

void Client::OnEnChangeClientRech()
{
	CString var;	
	int i=0;
	for(i=0;i<ClientsList.GetItemCount();i++){
		GetDlgItemText(IDC_CLIENT_RECH,var);
		if(var != L""){
			if(contains(ClientsList.GetItemText(i,0),var) || contains(ClientsList.GetItemText(i,1),var) || contains(ClientsList.GetItemText(i,2),var) || contains(ClientsList.GetItemText(i,3),var)){
				GetDlgItem(IDC_NO_VAL)->SetWindowText(ClientsList.GetItemText(i,0));
				GetDlgItem(IDC_NOM_VAL)->SetWindowText(ClientsList.GetItemText(i,1));
				GetDlgItem(IDC_PRENOM_VAL)->SetWindowText(ClientsList.GetItemText(i,2));
				GetDlgItem(IDC_LOCALITE_VAL)->SetWindowText(ClientsList.GetItemText(i,3));

				GetDlgItem(IDC_NOM_U)->EnableWindow();
				GetDlgItem(IDC_PRENOM_U)->EnableWindow();
				GetDlgItem(IDC_LOCALITE_U)->EnableWindow();

				GetDlgItem(IDC_NOM_U)->SetWindowText(ClientsList.GetItemText(i,1));
				GetDlgItem(IDC_PRENOM_U)->SetWindowText(ClientsList.GetItemText(i,2));
				GetDlgItem(IDC_LOCALITE_U)->SetWindowText(ClientsList.GetItemText(i,3));

				GetDlgItem(IDC_CLIENT_SUPP)->EnableWindow();
				GetDlgItem(IDC_CLIENT_UPDATE)->EnableWindow();
				ClientId = ClientsList.GetItemText(i,0);
				break;
			}else{
				GetDlgItem(IDC_NO_VAL)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_NOM_VAL)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_PRENOM_VAL)->SetWindowText(L"Aucun client");
				GetDlgItem(IDC_LOCALITE_VAL)->SetWindowText(L"Aucun client");

				GetDlgItem(IDC_NOM_U)->SetWindowText(L"");
				GetDlgItem(IDC_PRENOM_U)->SetWindowText(L"");
				GetDlgItem(IDC_LOCALITE_U)->SetWindowText(L"");

				GetDlgItem(IDC_NOM_U)->EnableWindow(FALSE);
				GetDlgItem(IDC_PRENOM_U)->EnableWindow(FALSE);
				GetDlgItem(IDC_LOCALITE_U)->EnableWindow(FALSE);

				GetDlgItem(IDC_CLIENT_SUPP)->EnableWindow(FALSE);			
				GetDlgItem(IDC_CLIENT_UPDATE)->EnableWindow(FALSE);

				ClientId = L"-1";
			}
		}else{
			
			GetDlgItem(IDC_NO_VAL)->SetWindowText(L"");
			GetDlgItem(IDC_NOM_VAL)->SetWindowText(L"");
			GetDlgItem(IDC_PRENOM_VAL)->SetWindowText(L"");
			GetDlgItem(IDC_LOCALITE_VAL)->SetWindowText(L"");

			GetDlgItem(IDC_NOM_U)->SetWindowText(L"");
			GetDlgItem(IDC_PRENOM_U)->SetWindowText(L"");
			GetDlgItem(IDC_LOCALITE_U)->SetWindowText(L"");

			GetDlgItem(IDC_NOM_U)->EnableWindow(FALSE);
			GetDlgItem(IDC_PRENOM_U)->EnableWindow(FALSE);
			GetDlgItem(IDC_LOCALITE_U)->EnableWindow(FALSE);

			GetDlgItem(IDC_CLIENT_SUPP)->EnableWindow(FALSE);
			GetDlgItem(IDC_CLIENT_UPDATE)->EnableWindow(FALSE);

			ClientId = L"-1";
		}
	}	
}


void Client::OnEnChangeNom()
{
	if(pasvide())
		GetDlgItem(IDC_AjouterClient)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_AjouterClient)->EnableWindow(FALSE);
}


void Client::OnBnClickedClientSupp()
{
	CDaoDatabase db1;
	CDaoRecordset recset1(&db1);
	CString lpszFile=L"GestionContratsV2.mdb";
	db1.Open(lpszFile);
		
	CString SqlCmd2=L"DELETE FROM CONTRATS WHERE NO_CLIENT = "+ClientId+";";
	db1.Execute(SqlCmd2);

	CString SqlCmd1=L"DELETE FROM CLIENTS WHERE NO_CLIENT = "+ClientId+";";
	db1.Execute(SqlCmd1);

	db1.Close();
	recset1.Close();
	GetDlgItem(IDC_CLIENT_RECH)->SetWindowText(L"");
	fill();
	AfxMessageBox(L"Le client a été supprimé \navec succès !",MB_ICONINFORMATION|MB_OK);
}


void Client::OnBnClickedClientUpdate()
{
	GetDlgItem(IDC_NOM_VAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PRENOM_VAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LOCALITE_VAL)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_CLIENT_UPDATE)->ShowWindow(SW_HIDE);

	GetDlgItem(IDC_NOM_U)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PRENOM_U)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LOCALITE_U)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_APP)->ShowWindow(SW_SHOW);
}


void Client::OnBnClickedApp()
{
	CDaoDatabase db2;
	CDaoRecordset recset2(&db2);
	CString V_no, V_nom,V_prenom, V_localite;	
	GetDlgItemText(IDC_NO_VAL, V_no);
	GetDlgItemText(IDC_NOM_U, V_nom);
	GetDlgItemText(IDC_PRENOM_U	, V_prenom);
	GetDlgItemText(IDC_LOCALITE_U, V_localite);
	CString lpszFile=L"GestionContratsV2.mdb";
	db2.Open(lpszFile);
	CString SqlCmd=L"UPDATE CLIENTS SET nom = '"+V_nom+"', prenom = '"+V_prenom+"', localite = '"+V_localite+"' WHERE NO_CLIENT = "+V_no+";";
	db2.Execute(SqlCmd);
	db2.Close();
	recset2.Close();
	GetDlgItem(IDC_CLIENT_RECH)->SetWindowText(L"");
	GetDlgItem(IDC_NOM_VAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_PRENOM_VAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_LOCALITE_VAL)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_CLIENT_UPDATE)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_NOM_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_PRENOM_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_LOCALITE_U)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_APP)->ShowWindow(SW_HIDE);
	fill();
	AfxMessageBox(L"Les informations du client "+V_nom+" "+V_prenom+" \n a été mis à jour avec succès !",MB_ICONINFORMATION|MB_OK);
}


void Client::OnBnClickedAjouterclient()
{
	CDaoDatabase db3;
	CDaoRecordset recset3(&db3);
	CString V_no, V_nom,V_prenom, V_localite;
		
	//GetDlgItemText(IDC_NUM		, V_no);
	GetDlgItemText(IDC_NOM		, V_nom);
	GetDlgItemText(IDC_PRENOM	, V_prenom);
	GetDlgItemText(IDC_LOCALITE	, V_localite);

	CString lpszFile=L"GestionContratsV2.mdb";
	
	db3.Open(lpszFile);

	CString SqlCmd=L"INSERT INTO CLIENTS(NOM, PRENOM, LOCALITE) VALUES ('"+V_nom+"', '"+V_prenom+"', '"+V_localite+"');";
	
	db3.Execute(SqlCmd);
	
	db3.Close();
	recset3.Close();

	//GetDlgItem(IDC_NUM)->SetWindowText(L"");
	GetDlgItem(IDC_NOM)->SetWindowText(L"");
	GetDlgItem(IDC_PRENOM)->SetWindowText(L"");
	GetDlgItem(IDC_LOCALITE)->SetWindowText(L"");

	AfxMessageBox(L"Le client "+V_nom+" "+V_prenom+" a été ajouté avec succès !",MB_ICONINFORMATION|MB_OK);

	fill();
}

bool Client::contains(CString mystring,CString arg){
	bool yes = true;
	int i;
	for(i=0;i<arg.GetLength() && yes;i++){
		if(mystring[i] != arg[i])
			return false;
	}
	return true;
}
bool Client::pasvide(){
	CString var0,var1,var2,var3;
	//GetDlgItemText(IDC_NUM,var0);
	GetDlgItemText(IDC_NOM,var1);
	GetDlgItemText(IDC_PRENOM,var2);
	GetDlgItemText(IDC_LOCALITE,var3);

	if(var1 == "" || var2 == "" || var3 == "")
		return false;
	else if(var1 != "" && var2 != "" && var3 != "")
		return true;

	return true;
}


void Client::OnBnClickedClientsSupp()
{
	// TODO: Add your control notification handler code here
}
