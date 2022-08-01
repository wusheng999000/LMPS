// PropertiesBar.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "PropertiesBar.h"


// CPropertiesBar

//IMPLEMENT_DYNAMIC(CPropertiesBar, CDockPageBar)

CPropertiesBar::CPropertiesBar()
{

}

CPropertiesBar::~CPropertiesBar()
{
}


BEGIN_MESSAGE_MAP(CPropertiesBar, CDockPageBar)
		ON_WM_CREATE()
END_MESSAGE_MAP()



// CPropertiesBar ��Ϣ�������
int CPropertiesBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDockPageBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}

CObject* CPropertiesBar::AddPage(CRuntimeClass *pClass, UINT nIDTemplate, LPCTSTR sText, UINT IconID)
{
	CDialog *pDlg = (CDialog*)pClass->CreateObject();
	if(pDlg != NULL)
	{
		if(pDlg->Create(nIDTemplate,this))
		{
			if(AddPage(pDlg, sText, IconID))
				return pDlg;
			else{
				delete pDlg;
				return NULL;
			}
		}
	}

	return NULL;
}


