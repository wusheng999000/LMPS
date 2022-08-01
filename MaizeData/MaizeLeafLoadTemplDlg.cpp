// MaizeLeafLoadTemplDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MaizeLeafLoadTemplDlg.h"


// CMaizeDataLeafLoadTemplDlg �Ի���

IMPLEMENT_DYNAMIC(CMaizeLeafLoadTemplDlg, CDialog)

CMaizeLeafLoadTemplDlg::CMaizeLeafLoadTemplDlg( CWnd* pParent /*=NULL*/)
	: CDialog(CMaizeLeafLoadTemplDlg::IDD, pParent)
	, m_nDeform(0)
{
	m_sVar = _T("");
}

CMaizeLeafLoadTemplDlg::~CMaizeLeafLoadTemplDlg()
{
}

void CMaizeLeafLoadTemplDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MAIZELEAF_LOADTEMPL_LIST, m_List);
	DDX_Radio(pDX, IDC_MAIZELEAF_LOADTEMPL_DEFORM, m_nDeform);
}


BEGIN_MESSAGE_MAP(CMaizeLeafLoadTemplDlg, CDialog)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMaizeLeafLoadTemplDlg ��Ϣ�������

BOOL CMaizeLeafLoadTemplDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_List.SetExtendedStyle( LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP );
	m_List.SetItemHeight(18);
	m_List.InsertColumn(0,_T("���"),LVCFMT_LEFT,30);
	m_List.InsertColumn(1,_T("Ʒ��"),LVCFMT_LEFT,80);
	m_List.InsertColumn(2,_T("���"),LVCFMT_LEFT,50);
	m_List.InsertColumn(3,_T("ģ����"),LVCFMT_LEFT,60);

	//���ݿ�
	LoadTemplListFromDB();

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

bool CMaizeLeafLoadTemplDlg::LoadTemplListFromDB(void)
{
	CODBCRecordset rsTempl(&dbCrop);
	CString sql;
	sql.Format(_T("select ����, Ʒ��, ���, Ҷ��, Ҷ�� from MaizeTemplList where Ʒ�� = '%s'"),m_sVar);
	//����Ӧ�����򿪲�ѯ�����
	rsTempl.Open(sql);
	if(rsTempl.IsEOF()) return false;
	CArray<int,int> nCnt;
	//����б�
	m_List.DeleteAllItems();
	//д������ݿ�������Ϣ
	int i = 0, n = 0;
	CString strTempl,strVal;
	bool bSuc = false;
	while (!rsTempl.IsEOF()) {
		strVal = rsTempl.GetString(2);
		bSuc = false;
		for( i = 0; i < m_List.GetItemCount(); i++ )
		{
			if(bSuc)break;
			if(m_List.GetItemText( i, 2) == strVal )
			{//����
				strTempl = m_List.GetItemText(i, 3);
				n = _wtoi(strTempl) + 1;
				strTempl.Format(_T("%d"),n);
				m_List.SetItemText(i,3,strTempl);
				bSuc = true;
				continue;
			}
		}
		if(!bSuc)
		{//������
			n = m_List.GetItemCount();
			strTempl.Format(_T("%d"),n+1);
			m_List.InsertItem(n,strTempl);
			m_List.SetItemText(n,1,m_sVar);
			m_List.SetItemText(n,2,strVal);
			m_List.SetItemText(n,3,_T("1"));
		}
		rsTempl.MoveNext();
	}
	//�رս����
	rsTempl.Close();
	return true;
}

void CMaizeLeafLoadTemplDlg::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	CString dbPath = GetSysPath() + _T("/DataBase/CropData.mdb");
	if( GetFileAttributes(dbPath) != -1 )
	{
		GetDatabaseConnection(dbPath,&dbCrop);
	}
	//���ӻ������ݿ�
	CDialog::PreSubclassWindow();
}

CString CMaizeLeafLoadTemplDlg::GetSysPath()
{//��ȡϵͳĿ¼��Exe��Image��Database���ϼ�
	CString strPath;
	TCHAR exeFullPath[500]; //
	GetModuleFileName(NULL,exeFullPath,500);//�õ�����ģ�����ƣ�ȫ·��
	strPath = exeFullPath;
	int i = 0, j = 0, k = 0, n = strPath.GetLength();
	for( i = 0; i < n; i++ )
	{
		if( strPath.GetAt(i) == '\\' )
			strPath.SetAt(i,'/');
	}
	for( i = n-1; i >= 0; i-- )
	{
		j++;
		if( strPath.GetAt(i) == '/' )
			k++;
		if( k == 2 )
		{
			strPath = strPath.Left(n-j);
			return strPath;
		}
	}
	return _T("");
}

void CMaizeLeafLoadTemplDlg::GetDatabaseConnection(CString& dbname, CDatabase *db)
{
	//��ʼ�����ݿ���󣬽������ݿ�����
	try{
		CString cs;
		cs = _T("Driver={Microsoft Access Driver (*.mdb)};Dbq=") + dbname;
		db->OpenEx(cs.GetBuffer(0));
	}
	catch (CDBException cdbe) {
		AfxMessageBox(_T("�޷����û����ݿ�!"));
	}
}

BOOL CMaizeLeafLoadTemplDlg::ReleaseConnection(CDatabase* db)
{
	//������ݿ�����Ǵ򿪵ģ���ر����ݿ����
	if(db->IsOpen())
	{
		db->Close();
	}
	return 1;
}


void CMaizeLeafLoadTemplDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: �ڴ˴������Ϣ����������
	ReleaseConnection(&dbCrop);
}

void CMaizeLeafLoadTemplDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	if( m_List.GetItemCount() == 0 )
	{
		m_sPlant = _T("1");
	}
	else
	{
		if( m_List.GetCurSel() == -1 )
			m_sPlant = m_List.GetItemText(0,2);
		else
		{
			int n = m_List.GetCurSel();
			m_sPlant = m_List.GetItemText(n,2);
		}
	}
	CDialog::OnOK();
}
