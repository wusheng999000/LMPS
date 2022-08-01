// PlantCAD.h : PlantCAD 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号


// CPlantCADApp:
// 有关此类的实现，请参阅 PlantCAD.cpp
//

class CPlantCADApp : public CWinApp
{
public:
	CPlantCADApp();
	long mTime;
public:
	CView* m_pViews[2];
	UINT m_nCurrentView;//当前视口
	// 重写
public:
	virtual BOOL InitInstance();
	CString GetRootPath();
	void InitInstanceWS();
	CView* SwitchView( UINT nIndex );
	// 实现
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	//afx_msg void OnViewCanopyRender();
	//afx_msg void OnViewCommonRender();
	afx_msg void OnViewCanopyRender();
};

extern CPlantCADApp theApp;