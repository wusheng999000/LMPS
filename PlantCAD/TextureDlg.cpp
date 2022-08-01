// TextureDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "TextureDlg.h"


// CTextureDlg 对话框

IMPLEMENT_DYNAMIC(CTextureDlg, CDialog)

CTextureDlg::CTextureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTextureDlg::IDD, pParent)
{
	m_bCtrlCreated = FALSE;
}

CTextureDlg::~CTextureDlg()
{
}

void CTextureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TEXTURE_LIST, mTextureList);
	DDX_Control(pDX, IDC_TEXTURE_PATH, mTexturePath);
	DDX_Control(pDX, IDC_TEXTURE_BROWSE, mTextureBrowse);
	m_bCtrlCreated = TRUE;
}


BEGIN_MESSAGE_MAP(CTextureDlg, CDialog)
	ON_BN_CLICKED(IDC_TEXTURE_BROWSE, &CTextureDlg::OnBnClickedTextureBrowse)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_TEXTURE_LIST, &CTextureDlg::OnLvnItemchangedTextureList)
//	ON_COMMAND(IDC_TEXTURE_ADDNEW, &CTextureDlg::OnTextureAddNew)
//	ON_COMMAND(IDC_TEXTURE_DELETE, &CTextureDlg::OnTextureDelete)
//	ON_COMMAND(IDC_TEXTURE_GENERATE, &CTextureDlg::OnTextureGenerate)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CTextureDlg 消息处理程序

void CTextureDlg::OnBnClickedTextureBrowse()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strVal;
	mTexturePath.GetWindowTextW(strVal);
	CFileDialog dlg(TRUE,_T("*.bmp"),NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		_T("bmp files(*.bmp)|*.bmp|"));
	if(dlg.DoModal()==IDOK)
	{
		CString mPath = dlg.GetPathName();
		mTexturePath.SetWindowText(mPath);
		UpdateData(FALSE);
		int nk = mTextureList.GetCurSel();
		if( nk >= 0 && nk < SCENE_MAX_TEXTURE)
		{
			mTextureList.SetImagePath(nk,mPath);
			//Path
			texPath[nk] = mPath;
			AfxGetMainWnd()->SendMessage(WM_TEXTUER_OPERATE, IDD_TEXTURE_DLG, nk);
		}
	}
}

void CTextureDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_bCtrlCreated)
	{
		CRect rc,rcRect1,rcRect2,rcRect3;
		GetClientRect(&rc);
		//Edit
		rcRect1 = rc;
		rcRect1.top = 0;
		rcRect1.bottom = 20;
		rcRect1.right -= 40;
		//Button
		rcRect2 = rcRect1;
		rcRect2.left = rcRect1.right + 2;
		rcRect2.right = rc.right - 2;
		//ListCtrl
		rcRect3 = rc;
		rcRect3.top = 22;
		//
//		CRect rcRect4;
//		mTextureToolBar.GetWindowRect(&rcRect4);
//		ScreenToClient(rcRect4);
//		rcRect4.right = rc.right;
//		mTextureToolBar.MoveWindow(rcRect4);
		mTexturePath.MoveWindow(rcRect1);
		mTextureBrowse.MoveWindow(rcRect2);
		mTextureList.MoveWindow(rcRect3);
		mTextureList.Arrange(0);
	}
}

BOOL CTextureDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//ToolBar
//	mTextureToolBar.SetBkGrdBmp(_T("..\\Images\\bkvs2.bmp"), 28);
//	mTextureToolBar.CreateEx(this, TBSTYLE_BUTTON, WS_CHILD | WS_VISIBLE | CBRS_TOP );
//	mTextureToolBar.LoadToolBar(IDR_TOOLBAR_TEXTURE);
//	mTextureToolBar.LoadBitmaps(20, IDB_BITMAP_TEXTURE_TOOLBAR_NORMAL, IDB_BITMAP_TEXTURE_TOOLBAR_NORMAL, IDB_BITMAP_TEXTURE_TOOLBAR_NORMAL);
//	mTextureToolBar.SetButtonStyle(0,TBBS_CHECKBOX);
	
/*	CRect	rcClientOld; // Old Client Rect
	CRect	rcClientNew; // New Client Rect with Tollbar Added
	GetClientRect(rcClientOld); // Retrive the Old Client WindowSize
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0,reposQuery,rcClientNew);
	CPoint ptOffset(rcClientNew.left-rcClientOld.left,
			rcClientNew.top-rcClientOld.top);

	CRect	rcChild;
	CWnd*	pwndChild = GetWindow(GW_CHILD);  //Handle to the Dialog Controls
	while(pwndChild) // Cycle through all child controls
	{
		pwndChild->GetWindowRect(rcChild); //  Get the child control RECT
		ScreenToClient(rcChild); 
		rcChild.OffsetRect(ptOffset); // Changes the Child Rect by the values of the claculated offset
		pwndChild->MoveWindow(rcChild,FALSE); // Move the Child Control
		pwndChild = pwndChild->GetNextWindow();
	}
	CRect	rcWindow;
	GetWindowRect(rcWindow); // Get the RECT of the Dialog
	rcWindow.right += rcClientOld.Width() - rcClientNew.Width(); // Increase width to new Client Width
	rcWindow.bottom += rcClientOld.Height() - rcClientNew.Height(); // Increase height to new Client Height
	MoveWindow(rcWindow,FALSE); // Redraw Window
	// Now we REALLY Redraw the Toolbar
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,0);
*/
	//List
	mTextureList.SetImageRange(64,64);
	texPath[0] = GetSysPath() + _T("/Images/stalk.bmp");
	texPath[1] = GetSysPath() + _T("/Images/sheath.bmp");
	texPath[2] = GetSysPath() + _T("/Images/leaf.bmp");
	texPath[3] = GetSysPath() + _T("/Images/bract.bmp");
	texPath[4] = GetSysPath() + _T("/Images/land.bmp");
	texPath[5] = GetSysPath() + _T("/Images/sensor.bmp");
	texPath[6] = _T("");
	texPath[7] = _T("");
	texPath[8] = _T("");
	texPath[9] = _T("");
	SetTextures(texPath);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

CString CTextureDlg::GetSysPath()
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

void CTextureDlg::OnLvnItemchangedTextureList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	int n = mTextureList.GetCurSel();
	int nCnt = mTextureList.GetItemCount();
	if( n < 0 || n >= nCnt )return;
	CString strVal;
	strVal = mTextureList.GetImagePath(n);
	mTexturePath.SetWindowText(strVal);
	UpdateData(FALSE);
}
/*
void CTextureDlg::OnTextureAddNew()
{
	AfxGetMainWnd()->SendMessage(WM_TEXTUER_OPERATE, IDD_TEXTURE_DLG, -2);
}

void CTextureDlg::OnTextureDelete()
{
	AfxGetMainWnd()->SendMessage(WM_TEXTUER_OPERATE, IDD_TEXTURE_DLG, -3);
}

void CTextureDlg::OnTextureGenerate()
{
	AfxGetMainWnd()->SendMessage(WM_TEXTUER_OPERATE, IDD_TEXTURE_DLG, -4);
}
*/
void CTextureDlg::SetTextures(CString mPath[])
{
	int i = 0;
	//Clear
	mTextureList.DeleteAllItems();
	LVITEM lvi;
	CString strItem;
	for ( i = 0; i < SCENE_MAX_TEXTURE; i++ )
	{
		//设置第一列
		lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
		strItem.Format(_T("纹理%d"), i+1);
		lvi.iItem = i;
		lvi.iSubItem = 0;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		lvi.iImage = i;
		mTextureList.InsertItem(&lvi);
		
		//设置第二列(子列)：
		strItem.Format(_T("第%d行"), i);
		lvi.iSubItem =1;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		mTextureList.SetItem(&lvi);
		
		//设置第三列(子列)
		strItem.Format(_T("第%d行"), i);
		lvi.iSubItem =2;
		lvi.pszText = (LPTSTR)(LPCTSTR)(strItem);
		mTextureList.SetItem(&lvi);
		//Image
		mTextureList.SetImagePath(i,mPath[i]);
	}
}
