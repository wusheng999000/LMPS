// PlantCAD.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "MainFrm.h"
#include "SplashWnd.h"
#include "PlantCADDoc.h"
#include "PlantCADView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlantCADApp

BEGIN_MESSAGE_MAP(CPlantCADApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CPlantCADApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	//ON_COMMAND(ID_VIEW_CANOPY_RENDER, &CPlantCADApp::OnViewCanopyRender)
	//ON_COMMAND(ID_VIEW_COMMON_RENDER, &CPlantCADApp::OnViewCommonRender)
	ON_COMMAND(ID_VIEW_CANOPY_RENDER, &CPlantCADApp::OnViewCanopyRender)
END_MESSAGE_MAP()


// CPlantCADApp 构造

CPlantCADApp::CPlantCADApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	//mPlantCADView = NULL ;
	//mPlantCADRenderView = NULL ;
	m_nCurrentView = 0;
}


// 唯一的一个 CPlantCADApp 对象

CPlantCADApp theApp;


// CPlantCADApp 初始化

BOOL CPlantCADApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("jj"));
	LoadStdProfileSettings(4);  // 加载标准 INI 文件选项(包括 MRU)
	// 注册应用程序的文档模板。文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPlantCADDoc),
		RUNTIME_CLASS(CMainFrame),       // 主 SDI 框架窗口
		RUNTIME_CLASS(CPlantCADView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// 分析标准外壳命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	
	//time_t time; 
	time_t rawtime;
    struct tm *ptminfo;
    time(&rawtime);
    ptminfo = localtime(&rawtime);
	int iYear = ptminfo->tm_year + 1900;
	int iMom = ptminfo->tm_mon + 1;
	//if((iYear > 2020) && (iMom > 9))
	if(iYear > 2024)
	{
		return FALSE;
	}


	if (!ProcessShellCommand(cmdInfo))
		return FALSE;


	m_pMainWnd->ShowWindow(SW_SHOWMAXIMIZED);

	m_pMainWnd->SetWindowText(_T("Leaf midrib phenotype system (LMPS)"));
	m_pMainWnd->UpdateWindow();
	m_pViews[0] = ((CFrameWnd*)m_pMainWnd)->GetActiveView();

	InitInstanceWS();

	//	m_pMainWnd->DragAcceptFiles();
	CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
	CSplashWnd::ShowSplashScreen(NULL);
	return TRUE;
}


// 获得程序执行根路径
CString CPlantCADApp::GetRootPath()
{
	WCHAR m_cRootModuleDirectory[256];// 程序路径
	GetModuleFileName(0, m_cRootModuleDirectory, 255);
	CString strFullPath(m_cRootModuleDirectory);
	int nPos = strFullPath.ReverseFind(_T('\\'));
	if (nPos == 0)
	{
		strFullPath = CString("");
	}
	else
	{
		strFullPath = strFullPath.Left(nPos + 1);
	}
	/*nPos = strFullPath.ReverseFind(_T('\\'));
	if(nPos == 0)
	{
	strFullPath = CString("");
	}
	else
	{
	strFullPath = strFullPath.Left(nPos);
	}*/
	return strFullPath;
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CPlantCADApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPlantCADApp 消息处理程序

/*
void CPlantCADApp::OnViewCanopyRender()
{
	 // TODO: Add your command handler code here
     UINT temp = ::GetWindowLong(mPlantCADRenderView->m_hWnd, GWL_ID);
     ::SetWindowLong(mPlantCADRenderView->m_hWnd, GWL_ID, ::GetWindowLong(mPlantCADView->m_hWnd, GWL_ID));
     ::SetWindowLong(mPlantCADView->m_hWnd, GWL_ID, temp);
 
     mPlantCADView->ShowWindow(SW_HIDE);
     mPlantCADRenderView->ShowWindow(SW_SHOW);      
 
     ((CFrameWnd*)m_pMainWnd)->SetActiveView(mPlantCADRenderView); 
     ((CFrameWnd*) m_pMainWnd)->RecalcLayout();
     mPlantCADRenderView->Invalidate();
}


void CPlantCADApp::OnViewCommonRender()
{
	  // TODO: Add your command handler code here
      UINT temp = ::GetWindowLong(mPlantCADRenderView->m_hWnd, GWL_ID);
      ::SetWindowLong(mPlantCADRenderView->m_hWnd, GWL_ID, ::GetWindowLong(mPlantCADView->m_hWnd, GWL_ID));
      ::SetWindowLong(mPlantCADView->m_hWnd, GWL_ID, temp);
 
      mPlantCADRenderView->ShowWindow(SW_HIDE);
      mPlantCADView->ShowWindow(SW_SHOW);
            
      ((CFrameWnd*)m_pMainWnd)->SetActiveView(mPlantCADView); 
      ((CFrameWnd*) m_pMainWnd)->RecalcLayout();
      mPlantCADView->Invalidate();
}
*/
void CPlantCADApp::InitInstanceWS()
{ 
	/*CMainFrame *pMainWnd=(CMainFrame*)AfxGetMainWnd();
    m_pViews[1] = (CPlantCADRenderView*)new CPlantCADRenderView;
    CDocument* pCurrentDoc = ((CFrameWnd*)m_pMainWnd)->GetActiveDocument();
    // 初始化创建上下文相关指针
    CCreateContext newContext;
    newContext.m_pNewViewClass = NULL;
    newContext.m_pNewDocTemplate = NULL;
    newContext.m_pLastView = NULL;
    newContext.m_pCurrentFrame = NULL;
    newContext.m_pCurrentDoc = pCurrentDoc;
    // 最初激活视的ID为AFX_IDW_PANE_FIRST，对新创建的视图增加这个值，注意对CSplitterWnd不能这样使用
    UINT viewID[2];
    viewID[1] = AFX_IDW_PANE_FIRST + 1;
    CRect rect(0, 0, 0, 0);
    // 创建新的视图，创建的视图在应用中永久存在，直到应用程序退出，应用程序会自动删除新创建的视图
     m_pViews[1]->Create(NULL, NULL,
    (AFX_WS_DEFAULT_VIEW&~WS_VISIBLE),
    // AFX_WS_DEFAULT_VIEW代表(WS_BORDER | WS_VISIBLE | WS_CHILD)
    rect, m_pMainWnd, viewID[1], &newContext);
    //}
    // 当文档模板创建视图的时候，会自动发送WM_INITIALUPDATE消息，因此对于我们自己创建的视图，需要人工发送这条消息
   // ((CForm2＊)m_pViews[1])－>OnInitialUpdate();
    ((CPlantCADRenderView*)m_pViews[1])->OnInitialUpdate();
	*/
}
CView* CPlantCADApp::SwitchView(UINT nIndex)
{
	//ASSERT( nIndex >=0 ＆＆ nIndex < NUMVIEWS );
    CView* pNewView = m_pViews[nIndex];
    CView* pActiveView =((CFrameWnd*) m_pMainWnd)->GetActiveView();
    if (!pActiveView ) // 当前没有激活的视图
        return NULL;
    if(pNewView == pActiveView ) // 当前视图和需要切换的视图相同
        return pActiveView;
    // 交换视图的窗口ID，使RecalcLayout()可以工作
    UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
    ::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(pNewView->m_hWnd, GWL_ID));
    ::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp);
    // 显示新的视图，隐藏前一个视图
    pActiveView->ShowWindow(SW_HIDE);
    pNewView->ShowWindow(SW_SHOW);
    ((CFrameWnd*) m_pMainWnd)->SetActiveView(pNewView);
    ((CFrameWnd*) m_pMainWnd)->RecalcLayout();
    pNewView->Invalidate();
        return pActiveView;
}

void CPlantCADApp::OnViewCanopyRender()
{
	
	if(m_nCurrentView == 0)
	{
		m_nCurrentView = 1;
	}
	else
	{
		m_nCurrentView = 0;
	}
	SwitchView(m_nCurrentView);
}
