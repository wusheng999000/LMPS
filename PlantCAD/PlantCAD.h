// PlantCAD.h : PlantCAD Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CPlantCADApp:
// �йش����ʵ�֣������ PlantCAD.cpp
//

class CPlantCADApp : public CWinApp
{
public:
	CPlantCADApp();
	long mTime;
public:
	CView* m_pViews[2];
	UINT m_nCurrentView;//��ǰ�ӿ�
	// ��д
public:
	virtual BOOL InitInstance();
	CString GetRootPath();
	void InitInstanceWS();
	CView* SwitchView( UINT nIndex );
	// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	//afx_msg void OnViewCanopyRender();
	//afx_msg void OnViewCommonRender();
	afx_msg void OnViewCanopyRender();
};

extern CPlantCADApp theApp;