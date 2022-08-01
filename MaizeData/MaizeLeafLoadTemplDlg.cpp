// MaizeLeafLoadTemplDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MaizeLeafLoadTemplDlg.h"


// CMaizeDataLeafLoadTemplDlg 对话框

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


// CMaizeLeafLoadTemplDlg 消息处理程序

BOOL CMaizeLeafLoadTemplDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.SetExtendedStyle( LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES| LVS_EX_HEADERDRAGDROP );
	m_List.SetItemHeight(18);
	m_List.InsertColumn(0,_T("序号"),LVCFMT_LEFT,30);
	m_List.InsertColumn(1,_T("品种"),LVCFMT_LEFT,80);
	m_List.InsertColumn(2,_T("株号"),LVCFMT_LEFT,50);
	m_List.InsertColumn(3,_T("模板数"),LVCFMT_LEFT,60);

	//数据库
	LoadTemplListFromDB();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

bool CMaizeLeafLoadTemplDlg::LoadTemplListFromDB(void)
{
	CODBCRecordset rsTempl(&dbCrop);
	CString sql;
	sql.Format(_T("select 名称, 品种, 株号, 叶序, 叶龄 from MaizeTemplList where 品种 = '%s'"),m_sVar);
	//用相应的语句打开查询结果集
	rsTempl.Open(sql);
	if(rsTempl.IsEOF()) return false;
	CArray<int,int> nCnt;
	//清空列表
	m_List.DeleteAllItems();
	//写入从数据库读入的信息
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
			{//设置
				strTempl = m_List.GetItemText(i, 3);
				n = _wtoi(strTempl) + 1;
				strTempl.Format(_T("%d"),n);
				m_List.SetItemText(i,3,strTempl);
				bSuc = true;
				continue;
			}
		}
		if(!bSuc)
		{//不存在
			n = m_List.GetItemCount();
			strTempl.Format(_T("%d"),n+1);
			m_List.InsertItem(n,strTempl);
			m_List.SetItemText(n,1,m_sVar);
			m_List.SetItemText(n,2,strVal);
			m_List.SetItemText(n,3,_T("1"));
		}
		rsTempl.MoveNext();
	}
	//关闭结果集
	rsTempl.Close();
	return true;
}

void CMaizeLeafLoadTemplDlg::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	CString dbPath = GetSysPath() + _T("/DataBase/CropData.mdb");
	if( GetFileAttributes(dbPath) != -1 )
	{
		GetDatabaseConnection(dbPath,&dbCrop);
	}
	//连接基础数据库
	CDialog::PreSubclassWindow();
}

CString CMaizeLeafLoadTemplDlg::GetSysPath()
{//获取系统目录，Exe、Image、Database的上级
	CString strPath;
	TCHAR exeFullPath[500]; //
	GetModuleFileName(NULL,exeFullPath,500);//得到程序模块名称，全路径
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
	//初始化数据库对象，进行数据库连接
	try{
		CString cs;
		cs = _T("Driver={Microsoft Access Driver (*.mdb)};Dbq=") + dbname;
		db->OpenEx(cs.GetBuffer(0));
	}
	catch (CDBException cdbe) {
		AfxMessageBox(_T("无法打开用户数据库!"));
	}
}

BOOL CMaizeLeafLoadTemplDlg::ReleaseConnection(CDatabase* db)
{
	//如果数据库对象是打开的，则关闭数据库对象
	if(db->IsOpen())
	{
		db->Close();
	}
	return 1;
}


void CMaizeLeafLoadTemplDlg::OnDestroy()
{
	CDialog::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	ReleaseConnection(&dbCrop);
}

void CMaizeLeafLoadTemplDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
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
