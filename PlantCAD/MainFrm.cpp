// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "MainFrm.h"
#include "PlantCADDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame
IMPLEMENT_DYNCREATE(CMainFrame, CAutoHideFrame)

BEGIN_MESSAGE_MAP(CMainFrame, CAutoHideFrame)
	ON_WM_CREATE()
	ON_MESSAGE(WM_SLIDERPOS_CHANGE, OnSliderPosChange)
	ON_MESSAGE(WM_PROPERTY_OPERATE, OnPropertyOperate)
	ON_MESSAGE(WM_TREECTRL_CHANGE, OnTreeLClicked)
	ON_MESSAGE(WM_POINTCLOUD_CHANGE, OnPointCloudViewInvalidate)
	ON_MESSAGE(WM_POINTCLOUD_OPERUNDO, OnPointCloudOperUndo)
	ON_MESSAGE(WM_POINTCLOUD_LOADMODEL, OnPointCloudLoadModel)
	ON_MESSAGE(WM_TEXTUER_OPERATE, OnTextureOperate)
//	ON_COMMAND(ID_BUTTONTEST,OnTest)
	ON_WM_SIZE()
	ON_COMMAND(ID_VIEW_COLONY_TOOLBAR, &CMainFrame::OnViewColonyToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COLONY_TOOLBAR, &CMainFrame::OnUpdateViewColonyToolbar)
	ON_COMMAND(ID_VIEW_OPERATE_TOOLBAR, &CMainFrame::OnViewOperateToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_OPERATE_TOOLBAR, &CMainFrame::OnUpdateViewOperateToolbar)
	ON_COMMAND(ID_VIEW_LEAF_TOOLBAR, &CMainFrame::OnViewLeafToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_LEAF_TOOLBAR, &CMainFrame::OnUpdateViewLeafToolbar)
	ON_COMMAND(ID_VIEW_EAR_TOOLBAR, &CMainFrame::OnViewEarToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EAR_TOOLBAR, &CMainFrame::OnUpdateViewEarToolbar)
	ON_COMMAND(ID_VIEW_ROOT_TOOLBAR, &CMainFrame::OnViewRootToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_ROOT_TOOLBAR, &CMainFrame::OnUpdateViewRootToolbar)
	ON_COMMAND(ID_VIEW_PLANT_TOOLBAR, &CMainFrame::OnViewPlantToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PLANT_TOOLBAR, &CMainFrame::OnUpdateViewPlantToolbar)
	ON_COMMAND(ID_VIEW_SCENE_TOOLBAR, &CMainFrame::OnViewSceneToolbar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_SCENE_TOOLBAR, &CMainFrame::OnUpdateViewSceneToolbar)
	ON_COMMAND(ID_VIEW_TREE_CTRLPANE, &CMainFrame::OnViewTreeCtrlpane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TREE_CTRLPANE, &CMainFrame::OnUpdateViewTreeCtrlpane)
	ON_COMMAND(ID_VIEW_PROP_CTRLPANE, &CMainFrame::OnViewPropCtrlpane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROP_CTRLPANE, &CMainFrame::OnUpdateViewPropCtrlpane)
	ON_COMMAND(ID_VIEW_TEXTURE_CTRLPANE, &CMainFrame::OnViewTextureCtrlpane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TEXTURE_CTRLPANE, &CMainFrame::OnUpdateViewTextureCtrlpane)
	ON_COMMAND(ID_VIEW_TEMPL_CTRLPANE, &CMainFrame::OnViewTemplCtrlpane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TEMPL_CTRLPANE, &CMainFrame::OnUpdateViewTemplCtrlpane)
	ON_COMMAND(ID_VIEW_CANOPY_CTRLPANE, &CMainFrame::OnViewCanopyCtrlpane)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CANOPY_CTRLPANE, &CMainFrame::OnUpdateViewCanopyCtrlpane)
	ON_COMMAND(IDC_SYSTEM_HELP, &CMainFrame::OnSystemHelp)
	ON_COMMAND(IDC_CALCU_TEST3, &CMainFrame::OnCalcuTest3)
	//ON_COMMAND_RANGE(ID_VIEW_CANOPY_RENDER, ID_VIEW_COMMON_RENDER, OnViewRender)
	//ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_CANOPY_RENDER, ID_VIEW_COMMON_RENDER, OnUpdateViewRenderUI)
	ON_COMMAND(ID_UpModel, &CMainFrame::OnUpmodel)
//	ON_MESSAGE(WM_VISUALDLL_PARAM_CHANGE, OnVisualizationParamUpdate)//苗腾添加
ON_COMMAND(ID_DataMS, &CMainFrame::OnDataMS)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame 构造/析构

CMainFrame::CMainFrame()
{
	// TODO: 在此添加成员初始化代码
	m_bProgDlgCreated = FALSE;
	m_bLeafShapeDlgCreated = FALSE;
	//mPlantCADView = NULL ;
	//mPlantCADRenderView = NULL ;
	m_iProPointCloud = 2;
	//m_pDataMSDlg = NULL;
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	//DockingBar 1
	if (!m_wndDockPageBar.Create(_T("DockPageBar"), this, CSize(340,360),TRUE,ID_PROP_DOCKBAR))
	{
		TRACE0("Failed to create DockPageBar.\n");
		return -1;
	}
	m_wndDockPageBar.SetBarStyle(m_wndDockPageBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_ALIGN_ANY| CBRS_SIZE_DYNAMIC);
	m_wndDockPageBar.EnableDocking (CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndDockPageBar, AFX_IDW_DOCKBAR_RIGHT);

	if (!m_wndTopoTree.Create(WS_CHILD|WS_VISIBLE|TVS_HASLINES|TVS_HASBUTTONS|TVS_LINESATROOT,
		CRect(0, 0, 0, 0), this, IDC_WND_TOPOTREE))
	{
		TRACE0("Failed to create instant bar child\n");
		return -1;
	}
	mLeafVienDlg.Create(IDD_LeafVienDlg, this);
	m_wndDockPageBar.AddPage(&mLeafVienDlg, _T("LeafVien"), IDI_PreProcess);
	/*	if (!m_wndEdit.Create(WS_CHILD|WS_VISIBLE|
	ES_MULTILINE|ES_WANTRETURN|ES_AUTOVSCROLL,
	CRect(0,0,0,0), this, 123))
	return -1;	
	*/
	//m_PropertyDlg.Create(IDD_PROPERTY_DLG,this);
	//m_TextureDlg.Create(IDD_TEXTURE_DLG,this);
	//m_PointCloudProCtrlDlg.Create(IDD_PointClodProDlg,this);
	//m_MaizePointCloudDlg.Create(IDD_MaizePointCloudDlg,this);
	//m_KinectPointCloudDlg.Create(IDD_KINECT_PCDlg,this);
	//m_KinectCollectDlg.Create(IDD_KinectCollectDlg,this);
	//The new created dialog by m_wndDockPageBar.AddPage will be released by Mainframe 
	//m_wndDockPageBar.AddPage(&m_wndTopoTree,_T("结构"),IDI_STRUCTURE);
	//m_dlgList.AddTail(m_wndDockPageBar.AddPage(RUNTIME_CLASS(CCtrlPaneDlg), IDD_CTRLPANE_DLG, _T("Search"), IDI_ICON2));
	//m_wndDockPageBar.AddPage(&m_PropertyDlg,_T("属性"),IDI_PROPERTY);

	//Scene ToolBar
	mSceneToolBar.SetBkGrdBmp(_T("..\\Images\\bkvs2.bmp"), 30);
	mSceneToolBar.CreateEx(this, TBSTYLE_BUTTON, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	mSceneToolBar.LoadToolBar(IDR_TOOLBAR_SCENE);
	mSceneToolBar.LoadBitmaps(24, IDB_TOOLBAR_SCENE_NORMAL, IDB_TOOLBAR_SCENE_NORMAL, IDB_TOOLBAR_SCENE_NORMAL);
	mSceneToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&mSceneToolBar);
	mSceneToolBar.ShowWindow(SW_SHOW);

	//Operate ToolBar
	mOperateToolBar.SetBkGrdBmp(_T("..\\Images\\bkvs2.bmp"), 30);
	mOperateToolBar.CreateEx(this, TBSTYLE_BUTTON, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	mOperateToolBar.LoadToolBar(IDR_TOOLBAR_OPERATE);
	mOperateToolBar.LoadBitmaps(24, IDB_TOOLBAR_OPERATE_NORMAL, IDB_TOOLBAR_OPERATE_NORMAL, IDB_TOOLBAR_OPERATE_NORMAL);
	mOperateToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&mOperateToolBar);
	DockControlBarLeftOf(&mOperateToolBar,&mSceneToolBar);
	mOperateToolBar.ShowWindow(SW_SHOW);

	
	//TimerCtrlBar
	if (!m_wndTimeCtrlBar.Create(_T("TimeCtrlBar"), this, CSize(480,54),TRUE,ID_TIMECTRL_BAR))
	{
		TRACE0("Failed to create DockPageBar.\n");
		return -1;
	}
	m_wndTimeCtrlBar.SetBarStyle(m_wndTimeCtrlBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY |CBRS_ALIGN_ANY| CBRS_SIZE_DYNAMIC);
	m_wndTimeCtrlBar.EnableDocking (CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndTimeCtrlBar, AFX_IDW_DOCKBAR_BOTTOM);

	//m_TimeSliderBar.Create(IDD_EXSLIDERBAR,this);
	//m_wndTimeCtrlBar.AddPage(&m_TimeSliderBar,_T("时间轴控制"),IDI_TEMPLATE);

	m_RunningLogDlg.Create(IDD_RunningLogDlg,this);
	m_wndTimeCtrlBar.AddPage(&m_RunningLogDlg,_T("运行时提示"),IDI_TEMPLATE);
	//Progress
	m_wndProgBar.Create(IDD_MAIN_PROGRESS_DLG,this);
	m_wndProgBar.ShowWindow(SW_HIDE);
	m_bProgDlgCreated = TRUE;
	CRect rcFrm,rcProg;
	GetClientRect(&rcFrm);
	m_wndProgBar.GetClientRect(&rcProg);
	rcFrm.left = (rcFrm.Width()-rcProg.Width())/2;
	rcFrm.top = (rcFrm.Height()-rcProg.Height())/2;
	rcFrm.right = rcFrm.left + rcProg.Width();
	rcFrm.bottom = rcFrm.top + rcProg.Height();
	m_wndProgBar.MoveWindow(rcFrm);


	//直接创建在状态条上
	//	CRect rectStatus;
	//	m_wndStatusBar.GetClientRect(&rectStatus);
	//	rectStatus.left+=40;
	//	rectStatus.right-=100;
	//	m_StatusProgBar.Create(WS_VISIBLE|WS_CHILD,rectStatus/*CRect(20,2,400,18)*/,&m_wndStatusBar,1);
	//	m_StatusProgBar.SetRange(1,100);
	//	m_StatusProgBar.SetPos(60);
	//	m_StatusProgBar.ShowWindow(SW_SHOW);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CAutoHideFrame::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	//	cs.style|=WS_CLIPSIBLINGS|WS_CLIPCHILDREN;

	//	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
	//		 | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE | WS_SYSMENU;
	//cs.cx = 220;
	//cs.cy = 150;
	return TRUE;
}


// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


LRESULT CMainFrame::OnSliderPosChange(WPARAM wParam,LPARAM lParam)
{

	return 0;
}

LRESULT CMainFrame::OnPropertyOperate(WPARAM wParam,LPARAM lParam)
{
	if( wParam != IDD_PROPERTY_DLG )return 0;
	CPlantCADDoc* pDoc = (CPlantCADDoc*)GetActiveDocument();
	
	return 0;
}

LRESULT CMainFrame::OnTreeLClicked(WPARAM wParam,LPARAM lParam)
{
	if( wParam != IDC_WND_TOPOTREE )return 0;

	return 0;
}

LRESULT CMainFrame::OnPointCloudViewInvalidate(WPARAM wParam,LPARAM lParam)
{
	///if( wParam != IDI_MultiViewPointCloud )return 0;
	CPlantCADDoc* pDoc = (CPlantCADDoc*)GetActiveDocument();
	CString strParam((TCHAR*)lParam);
	CString strTemp;
	//字符串的构成：点云点个数：关键点个数：文件名
	int ipos = strParam.FindOneOf(L":");
	strTemp = strParam.Left(ipos);
	pDoc->m_nCurPointNum = _ttoi(strTemp);//当前点个数
	strParam = strParam.Right(strParam.GetLength()-ipos-1);

	ipos = strParam.FindOneOf(L":");
	strTemp = strParam.Left(ipos);
	pDoc->m_nSkelPointNum = _ttoi(strTemp);//当前点个数
	pDoc->m_strCurPCFileName = strParam.Right(strParam.GetLength() - ipos - 1);//当前点个数

	pDoc->Invalidate();
	return 0;
}

LRESULT CMainFrame::OnPointCloudLoadModel(WPARAM wParam,LPARAM lParam)
{
	///if( wParam != IDI_MultiViewPointCloud )return 0;
	CPlantCADDoc* pDoc = (CPlantCADDoc*)GetActiveDocument();
	return 0;
}

//接收骨架处理的回滚操作
LRESULT CMainFrame::OnPointCloudOperUndo(WPARAM wParam, LPARAM lParam)
{
	CPlantCADDoc* pDoc = (CPlantCADDoc*)GetActiveDocument();
	CString strParam((TCHAR*)lParam);

	
	return 0;
}

LRESULT CMainFrame::OnTextureOperate(WPARAM wParam,LPARAM lParam)
{
	if( wParam != IDD_TEXTURE_DLG )return 0;
	CPlantCADDoc* pDoc = (CPlantCADDoc*)GetActiveDocument();
	if( lParam >= 0 )
	{
		if( lParam < SCENE_MAX_TEXTURE )
		{
			pDoc->texPath[lParam] = m_TextureDlg.texPath[lParam];
			pDoc->m_bTextureGenerated = FALSE;
			pDoc->Invalidate();
		}
	}
	return 0;
}

LRESULT CMainFrame::OnMaizeLeafTemplCtrlOperate(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

LRESULT CMainFrame::OnPointCloudDlgCtrlProcessing(WPARAM wParam,LPARAM lParam)
{
	
	return 0;
}

LRESULT CMainFrame::OnCanopyOperate(WPARAM wParam,LPARAM lParam)
{
	return 0;
}

void CMainFrame::OnTest()
{
	//	CTextureDlg dlg;
	//	dlg.DoModal();
}

void CMainFrame::ChangeDialogBars( int nType )
{
	CPropertiesBar* pProp;
	POSITION pos;
	int nItemIndex = 0;
	CPageItem *pItem;
	int n = 0;
	switch(nType)
	{
	case 0:		//PropList
		
		if((mLeafVienDlg.GetParent())->GetRuntimeClass() == (RUNTIME_CLASS(CPropertiesBar)))
		{
			m_iProPointCloud = 1; 
			pProp = (CPropertiesBar*)(mLeafVienDlg.GetParent());
			if(!pProp->IsWindowVisible())
			{
				//设置显示
				pProp->ShowWindow(SW_SHOW);
				//设置当前页面
				for(pos = pProp->m_PageList.GetHeadPosition(); pos != NULL; nItemIndex++ )
				{
					pItem = (CPageItem*)pProp->m_PageList.GetNext(pos);
					if(pItem->m_sText == _T("LeafVien"))
					{
						pProp->SetActivePage(nItemIndex);
					}
				}
				//如果是AutoHide状态
				if( pProp->m_pAutoHideBar != NULL )
				{
					//现在要做的是确定要Dock的HideItem
					//pProp->m_pAutoHideBar->Dock(_T("控制"));
					pProp->m_pAutoHideBar->RemoveItem(_T("LeafVien"));
				}
			}
			else
			{
				for(pos = pProp->m_PageList.GetHeadPosition(); pos != NULL; nItemIndex++ )
				{
					pItem = (CPageItem*)pProp->m_PageList.GetNext(pos);
					if(pItem->m_sText == _T("LeafVien"))
					{
						pProp->SetActivePage(nItemIndex);
					}
				}
			}
		}
		//			else if((m_CtrlPaneDlg.GetParent())->GetRuntimeClass() == (RUNTIME_CLASS(CAHFloatWnd)))
		else if((mLeafVienDlg.GetParent())->GetRuntimeClass() == (RUNTIME_CLASS(CAHFloatWnd)))
		{
			//				((CAHFloatWnd*)m_CtrlPaneDlg.GetParent())->OnStudClick();
			((CAHFloatWnd*)mLeafVienDlg.GetParent())->OnStudClick();
		}
		break;
	
	default:
		break;
	}
	RecalcLayout();//重新显示 
}

void CMainFrame::ResetDialogBars( void )
{
	//重置DialogBar
}

void CMainFrame::DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf) 
{ //设置工具条并列停靠在同一条边上 
	CRect rect; //矩形区域定义 
	DWORD dw; 
	UINT n=0; 
	RecalcLayout();//重新显示 
	LeftOf->GetWindowRect(&rect); 
	rect.OffsetRect(1,0);//设置偏移值以停靠在同一边上 
	dw=LeftOf->GetBarStyle(); 
	n=(dw&CBRS_ALIGN_TOP)?AFX_IDW_DOCKBAR_TOP:n; 
	n=(dw&CBRS_ALIGN_BOTTOM&&n==0)?AFX_IDW_DOCKBAR_BOTTOM:n; 
	n=(dw&CBRS_ALIGN_LEFT&&n==0)?AFX_IDW_DOCKBAR_LEFT:n; 
	n=(dw&CBRS_ALIGN_RIGHT&&n==0)?AFX_IDW_DOCKBAR_RIGHT:n; 
	DockControlBar(Bar,n,&rect); 
}

void CMainFrame::DockControlBarLeftOf(CExToolBar* Bar,CExToolBar* LeftOf) 
{ //设置工具条并列停靠在同一条边上 
	CRect rect; //矩形区域定义 
	DWORD dw; 
	UINT n=0; 
	RecalcLayout();//重新显示 
	LeftOf->GetWindowRect(&rect); 
	rect.OffsetRect(1,0);//设置偏移值以停靠在同一边上 
	dw=LeftOf->GetBarStyle(); 
	n=(dw&CBRS_ALIGN_TOP)?AFX_IDW_DOCKBAR_TOP:n; 
	n=(dw&CBRS_ALIGN_BOTTOM&&n==0)?AFX_IDW_DOCKBAR_BOTTOM:n; 
	n=(dw&CBRS_ALIGN_LEFT&&n==0)?AFX_IDW_DOCKBAR_LEFT:n; 
	n=(dw&CBRS_ALIGN_RIGHT&&n==0)?AFX_IDW_DOCKBAR_RIGHT:n; 
	DockControlBar(Bar,n,&rect); 
} 

LRESULT CMainFrame::OnMaizeLeafTemplInput(WPARAM wParam,LPARAM lParam)
{
	//模板对象对话框中的 载入模板 操作所发消息，因为不确定如何向Doc发消息
	if( wParam != 101 )return 0;
	CPlantCADDoc* pDoc = (CPlantCADDoc*)GetActiveDocument();
	pDoc->Invalidate();
	//操作面板 //更新显示
	return 0;
}

void CMainFrame::RefreshTexture()
{	//纹理
	CPlantCADDoc* pDoc = (CPlantCADDoc*)GetActiveDocument();
	m_TextureDlg.SetTextures(pDoc->texPath);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CAutoHideFrame::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_bProgDlgCreated )
	{
		CRect rcFrm,rcProg;
		GetClientRect(&rcFrm);
		ClientToScreen(rcFrm);
		m_wndProgBar.GetClientRect(&rcProg);
		rcFrm.left = rcFrm.left + (rcFrm.Width()-rcProg.Width())/2;
		rcFrm.top = rcFrm.top + (rcFrm.Height()-rcProg.Height())/2;
		rcFrm.right = rcFrm.left + rcProg.Width();
		rcFrm.bottom = rcFrm.top + rcProg.Height();
		m_wndProgBar.MoveWindow(rcFrm);
	}
}

void CMainFrame::OnViewColonyToolbar()
{
	// TODO: 在此添加命令处理程序代码
	if( mMaizecolonyToolBar.GetStyle() & WS_VISIBLE )
		mMaizecolonyToolBar.ShowWindow(SW_HIDE);
	else
	{
		mMaizecolonyToolBar.ShowWindow(SW_SHOW);
		DockControlBarLeftOf(&mMaizecolonyToolBar,&mMaizeorganrootToolBar);
	}
}

void CMainFrame::OnUpdateViewColonyToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bShow = FALSE;
	if( mMaizecolonyToolBar.GetStyle() & WS_VISIBLE )
		m_bShow = TRUE;
	else
		m_bShow = FALSE;
	pCmdUI->SetCheck(m_bShow);
}

void CMainFrame::OnViewOperateToolbar()
{
	// TODO: 在此添加命令处理程序代码
	if( mOperateToolBar.GetStyle() & WS_VISIBLE )
		mOperateToolBar.ShowWindow(SW_HIDE);
	else
		mOperateToolBar.ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdateViewOperateToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bShow = FALSE;
	if( mOperateToolBar.GetStyle() & WS_VISIBLE )
		m_bShow = TRUE;
	else
		m_bShow = FALSE;
	pCmdUI->SetCheck(m_bShow);
}

void CMainFrame::OnViewLeafToolbar()
{
	// TODO: 在此添加命令处理程序代码
	if( mMaizeorganleafToolBar.GetStyle() & WS_VISIBLE )
		mMaizeorganleafToolBar.ShowWindow(SW_HIDE);
	else
		mMaizeorganleafToolBar.ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdateViewLeafToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bShow = FALSE;
	if( mMaizeorganleafToolBar.GetStyle() & WS_VISIBLE )
		m_bShow = TRUE;
	else
		m_bShow = FALSE;
	pCmdUI->SetCheck(m_bShow);
}

void CMainFrame::OnViewEarToolbar()
{
	// TODO: 在此添加命令处理程序代码
	if( mMaizeorganearToolBar.GetStyle() & WS_VISIBLE )
		mMaizeorganearToolBar.ShowWindow(SW_HIDE);
	else
		mMaizeorganearToolBar.ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdateViewEarToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bShow = FALSE;
	if( mMaizeorganearToolBar.GetStyle() & WS_VISIBLE )
		m_bShow = TRUE;
	else
		m_bShow = FALSE;
	pCmdUI->SetCheck(m_bShow);
}

void CMainFrame::OnViewRootToolbar()
{
	// TODO: 在此添加命令处理程序代码
	if( mMaizeorganrootToolBar.GetStyle() & WS_VISIBLE )
		mMaizeorganrootToolBar.ShowWindow(SW_HIDE);
	else
		mMaizeorganrootToolBar.ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdateViewRootToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bShow = FALSE;
	if( mMaizeorganrootToolBar.GetStyle() & WS_VISIBLE )
		m_bShow = TRUE;
	else
		m_bShow = FALSE;
	pCmdUI->SetCheck(m_bShow);
}

void CMainFrame::OnViewPlantToolbar()
{
	// TODO: 在此添加命令处理程序代码
	if( mMaizeplantToolBar.GetStyle() & WS_VISIBLE )
	{
		mMaizeplantToolBar.ShowWindow(SW_HIDE);
	}
	else
	{
		mMaizeplantToolBar.ShowWindow(SW_SHOW);
		DockControlBarLeftOf(&mMaizeplantToolBar,&mSceneToolBar);
	}
}

void CMainFrame::OnUpdateViewPlantToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bShow = FALSE;
	if( mMaizeplantToolBar.GetStyle() & WS_VISIBLE )
		m_bShow = TRUE;
	else
		m_bShow = FALSE;
	pCmdUI->SetCheck(m_bShow);
}

void CMainFrame::OnViewSceneToolbar()
{
	// TODO: 在此添加命令处理程序代码
	if( mSceneToolBar.GetStyle() & WS_VISIBLE )
		mSceneToolBar.ShowWindow(SW_HIDE);
	else
		mSceneToolBar.ShowWindow(SW_SHOW);
}

void CMainFrame::OnUpdateViewSceneToolbar(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bShow = FALSE;
	if( mSceneToolBar.GetStyle() & WS_VISIBLE )
		m_bShow = TRUE;
	else
		m_bShow = FALSE;
	pCmdUI->SetCheck(m_bShow);
}

void CMainFrame::RefreshTimer()
{
	CPlantCADDoc* pDoc = (CPlantCADDoc*)GetActiveDocument();
	
}

/////////////////////////////////////////////////////////////////////////////
//////////////////           控制调显示/隐藏控制					/////////
/////////////////////////////////////////////////////////////////////////////

void CMainFrame::OnViewTreeCtrlpane()
{
	// TODO: 在此添加命令处理程序代码
	ChangeDialogBars(0);
}

void CMainFrame::OnUpdateViewTreeCtrlpane(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnViewPropCtrlpane()
{
	// TODO: 在此添加命令处理程序代码
	ChangeDialogBars(1);
}

void CMainFrame::OnUpdateViewPropCtrlpane(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnViewTextureCtrlpane()
{
	// TODO: 在此添加命令处理程序代码
	ChangeDialogBars(2);
}

void CMainFrame::OnUpdateViewTextureCtrlpane(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnViewTemplCtrlpane()
{
	// TODO: 在此添加命令处理程序代码
	ChangeDialogBars(3);
}

void CMainFrame::OnUpdateViewTemplCtrlpane(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnViewCanopyCtrlpane()
{
	// TODO: 在此添加命令处理程序代码
	ChangeDialogBars(9);
}

void CMainFrame::OnUpdateViewCanopyCtrlpane(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
}

void CMainFrame::OnSystemHelp()
{
	// TODO: 在此添加命令处理程序代码
	::HtmlHelp(GetSafeHwnd(),_T("PlantCAD-Maize.chm"),HH_DISPLAY_TOC,NULL);
}


void CMainFrame::OnCalcuTest3()
{
}
/*
void CMainFrame::OnViewRender(UINT nCmdID)
{
	if (nCmdID == m_nCurrentView)
		return;  // already selected
	CView* pOldActiveView = GetActiveView();
	if(mPlantCADRenderView==NULL)
    {
		CCreateContext context;
        context.m_pCurrentDoc=pOldActiveView->GetDocument();
        mPlantCADRenderView=new CPlantCADRenderView;
        mPlantCADRenderView->Create(NULL,NULL,WS_BORDER|WS_CHILD,CFrameWnd::rectDefault,this,IDV_NEW_VIEW_ID,&context);
        mPlantCADRenderView->OnInitialUpdate();  //IDV_NEW_VIEW_ID是这个视图的ID，这个值可以是常数，如 1，或者在资源视图的String Table中设置，如设为:IDV_NEW_VIEW_ID;
     }
	//CView* pOldActiveView = GetActiveView();
	//	::SetWindowLong(pOldActiveView->m_hWnd, GWL_ID, m_nCurrentView);
	CRuntimeClass* pNewViewClass;
	switch (nCmdID)
	{
		case ID_VIEW_CANOPY_RENDER:
             mPlantCADRenderView->ShowWindow(SW_SHOW);
             mPlantCADView->ShowWindow(SW_HIDE);
			 SetActiveView(mPlantCADRenderView);
             RecalcLayout();
			 break;
		case ID_VIEW_COMMON_RENDER:
			 SetActiveView(mPlantCADView);
             mPlantCADView->ShowWindow(SW_SHOW);
             mPlantCADRenderView->ShowWindow(SW_HIDE);
             RecalcLayout();
			 break;
		default:
			ASSERT(0);
			return;
	}
	m_nCurrentView = nCmdID;
	/*
	// create the new view
	CCreateContext context;
	context.m_pNewViewClass = pNewViewClass;
	context.m_pCurrentDoc = GetActiveDocument();
	CView* pNewView = STATIC_DOWNCAST(CView, CreateView(&context));
	if (pNewView != NULL)
	{
		// the new view is there, but invisible and not active...
		pNewView->ShowWindow(SW_SHOW);
		pNewView->OnInitialUpdate();
		SetActiveView(pNewView);
		RecalcLayout();
		m_nCurrentView = nCmdID;

		// finally destroy the old view...
		pOldActiveView->DestroyWindow();
	}
	*/
/*	
}

void CMainFrame::OnUpdateViewRenderUI(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(pCmdUI->m_nID == m_nCurrentView);
}*/


void CMainFrame::OnUpmodel()
{

}

LRESULT CMainFrame::OnVisualizationParamUpdate(WPARAM wParam, LPARAM lParam)
{
	//if( wParam != IDD_DLG_VISUALPARAM )return 0;
	((CPlantCADApp*)AfxGetApp())->m_pViews[1]->Invalidate(NULL);
	//((CPlantCADRenderView*)GetActiveView())->Invalidate(NULL);
	return 0;
}


void CMainFrame::OnDataMS()
{
	//CDataMSDlg m_DataMSDlg;
	//m_DataMSDlg.DoModal();
	/*
	if (NULL == m_pDataMSDlg)
	{
		// 创建非模态对话框实例   
		m_pDataMSDlg = new CDataMSDlg();
		m_pDataMSDlg->Create(IDD_DataMS, this);
		
		// 显示非模态对话框   
	    m_pDataMSDlg->ShowWindow(SW_SHOW);
		//m_pDataMSDlg->LoadTitle(); 
		//m_pDataMSDlg->Invalidate();
		//m_pDataMSDlg->UpdataData();
	}
	*/
}
