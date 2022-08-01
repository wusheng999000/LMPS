// MainFrm.h : CMainFrame 类的接口
//


#pragma once

#include "stdafx.h"
#include "PropertyDlg.h"
#include "TextureDlg.h"
#include "PropertiesBar.h"
#include "ProgressDlg.h"
#include "RunningLogDlg.h"
//#include "PlantCADView.h"
//#include "PlantCADRenderView.h"
#define ID_PROP_DOCKBAR 10234
#define ID_TIMECTRL_BAR 10235
#define ID_PROP_DOCKBAR_2 10236
#define IDC_WND_PROGBAR  10237
#define IDC_WND_TOPOTREE 10238

class CMainFrame : public CAutoHideFrame //CTestHideFrame //CFrameWnd //CAutoHideFrame
{

protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

	// 属性
public:
	CPropertiesBar	m_wndDockPageBar;
	CEdit			m_wndEdit;
	CPtrList        m_dlgList;
	CExTreeCtrl		m_wndTopoTree;
	CPropertyDlg	m_PropertyDlg;
	CPropertiesBar	m_wndTimeCtrlBar;
	CExSliderBar	m_TimeSliderBar;
	CTextureDlg		m_TextureDlg;
	CRunningLogDlg m_RunningLogDlg;

	//Progress
	CProgressDlg m_wndProgBar;
	BOOL m_bProgDlgCreated;
	BOOL m_bLeafShapeDlgCreated;
	int m_iProPointCloud;
	CLeafVienDlg mLeafVienDlg;
	//	CProgressCtrl m_StatusProgBar;
public:
	//CPlantCADView* mPlantCADView ;
	//CPlantCADRenderView* mPlantCADRenderView;

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	void ChangeDialogBars( int nType = 0 );
	void DockControlBarLeftOf(CExToolBar* Bar,CExToolBar* LeftOf); 
	void DockControlBarLeftOf(CToolBar* Bar,CToolBar* LeftOf); 
	void ResetDialogBars( void );
	void RefreshTexture();
	void RefreshTimer();

public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected: 
	CStatusBar  m_wndStatusBar;
	CExToolBar  mSceneToolBar;
	CExToolBar	mOperateToolBar;
	CExToolBar	mMaizeorganleafToolBar;
	CExToolBar	mMaizeorganearToolBar;
	CExToolBar	mMaizeorganrootToolBar;
	CExToolBar	mMaizeplantToolBar;
	CExToolBar	mMaizecolonyToolBar;

	
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnTreeLClicked(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnPointCloudViewInvalidate(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnPointCloudLoadModel(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnMaizeLeafTemplInput(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnSliderPosChange(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnTextureOperate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPropertyOperate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnCanopyOperate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMaizeLeafTemplCtrlOperate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPointCloudDlgCtrlProcessing(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPointCloudOperUndo(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTest();
	afx_msg LRESULT OnVisualizationParamUpdate(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnViewColonyToolbar();
	afx_msg void OnUpdateViewColonyToolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewOperateToolbar();
	afx_msg void OnUpdateViewOperateToolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewLeafToolbar();
	afx_msg void OnUpdateViewLeafToolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewEarToolbar();
	afx_msg void OnUpdateViewEarToolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewRootToolbar();
	afx_msg void OnUpdateViewRootToolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewPlantToolbar();
	afx_msg void OnUpdateViewPlantToolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewSceneToolbar();
	afx_msg void OnUpdateViewSceneToolbar(CCmdUI *pCmdUI);
	afx_msg void OnViewTreeCtrlpane();
	afx_msg void OnUpdateViewTreeCtrlpane(CCmdUI *pCmdUI);
	afx_msg void OnViewPropCtrlpane();
	afx_msg void OnUpdateViewPropCtrlpane(CCmdUI *pCmdUI);
	afx_msg void OnViewTextureCtrlpane();
	afx_msg void OnUpdateViewTextureCtrlpane(CCmdUI *pCmdUI);
	afx_msg void OnViewTemplCtrlpane();
	afx_msg void OnUpdateViewTemplCtrlpane(CCmdUI *pCmdUI);
	afx_msg void OnViewCanopyCtrlpane();
	afx_msg void OnUpdateViewCanopyCtrlpane(CCmdUI *pCmdUI);
	afx_msg void OnSystemHelp();
	afx_msg void OnCalcuTest3();
	//void OnViewRender(UINT nCmdID);
	//void OnUpdateViewRenderUI(CCmdUI* pCmdUI);
	afx_msg void OnUpmodel();
	afx_msg void OnDataMS();
};


