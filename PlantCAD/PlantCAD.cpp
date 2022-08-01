// PlantCAD.cpp : ����Ӧ�ó��������Ϊ��
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
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
	// ��׼��ӡ��������
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinApp::OnFilePrintSetup)
	//ON_COMMAND(ID_VIEW_CANOPY_RENDER, &CPlantCADApp::OnViewCanopyRender)
	//ON_COMMAND(ID_VIEW_COMMON_RENDER, &CPlantCADApp::OnViewCommonRender)
	ON_COMMAND(ID_VIEW_CANOPY_RENDER, &CPlantCADApp::OnViewCanopyRender)
END_MESSAGE_MAP()


// CPlantCADApp ����

CPlantCADApp::CPlantCADApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	//mPlantCADView = NULL ;
	//mPlantCADRenderView = NULL ;
	m_nCurrentView = 0;
}


// Ψһ��һ�� CPlantCADApp ����

CPlantCADApp theApp;


// CPlantCADApp ��ʼ��

BOOL CPlantCADApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	// ��ʼ�� OLE ��
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}
	AfxEnableControlContainer();
	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("jj"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)
	// ע��Ӧ�ó�����ĵ�ģ�塣�ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CPlantCADDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CPlantCADView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// ������׼������DDE�����ļ�������������
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


// ��ó���ִ�и�·��
CString CPlantCADApp::GetRootPath()
{
	WCHAR m_cRootModuleDirectory[256];// ����·��
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
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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

// �������жԻ����Ӧ�ó�������
void CPlantCADApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CPlantCADApp ��Ϣ�������

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
    // ��ʼ���������������ָ��
    CCreateContext newContext;
    newContext.m_pNewViewClass = NULL;
    newContext.m_pNewDocTemplate = NULL;
    newContext.m_pLastView = NULL;
    newContext.m_pCurrentFrame = NULL;
    newContext.m_pCurrentDoc = pCurrentDoc;
    // ��������ӵ�IDΪAFX_IDW_PANE_FIRST�����´�������ͼ�������ֵ��ע���CSplitterWnd��������ʹ��
    UINT viewID[2];
    viewID[1] = AFX_IDW_PANE_FIRST + 1;
    CRect rect(0, 0, 0, 0);
    // �����µ���ͼ����������ͼ��Ӧ�������ô��ڣ�ֱ��Ӧ�ó����˳���Ӧ�ó�����Զ�ɾ���´�������ͼ
     m_pViews[1]->Create(NULL, NULL,
    (AFX_WS_DEFAULT_VIEW&~WS_VISIBLE),
    // AFX_WS_DEFAULT_VIEW����(WS_BORDER | WS_VISIBLE | WS_CHILD)
    rect, m_pMainWnd, viewID[1], &newContext);
    //}
    // ���ĵ�ģ�崴����ͼ��ʱ�򣬻��Զ�����WM_INITIALUPDATE��Ϣ����˶��������Լ���������ͼ����Ҫ�˹�����������Ϣ
   // ((CForm2��)m_pViews[1])��>OnInitialUpdate();
    ((CPlantCADRenderView*)m_pViews[1])->OnInitialUpdate();
	*/
}
CView* CPlantCADApp::SwitchView(UINT nIndex)
{
	//ASSERT( nIndex >=0 ���� nIndex < NUMVIEWS );
    CView* pNewView = m_pViews[nIndex];
    CView* pActiveView =((CFrameWnd*) m_pMainWnd)->GetActiveView();
    if (!pActiveView ) // ��ǰû�м������ͼ
        return NULL;
    if(pNewView == pActiveView ) // ��ǰ��ͼ����Ҫ�л�����ͼ��ͬ
        return pActiveView;
    // ������ͼ�Ĵ���ID��ʹRecalcLayout()���Թ���
    UINT temp = ::GetWindowLong(pActiveView->m_hWnd, GWL_ID);
    ::SetWindowLong(pActiveView->m_hWnd, GWL_ID, ::GetWindowLong(pNewView->m_hWnd, GWL_ID));
    ::SetWindowLong(pNewView->m_hWnd, GWL_ID, temp);
    // ��ʾ�µ���ͼ������ǰһ����ͼ
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
