// CtrlPaneDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "PropertyDlg.h"
#include "MainFrm.h"
#include "PlantCADDoc.h"
// CPropertyDlg 对话框

IMPLEMENT_DYNAMIC(CPropertyDlg, CDialog)

CPropertyDlg::CPropertyDlg(CWnd* pParent /*=NULL*/)
	: CDialog()
{
	m_bCtrlCreated = FALSE;
}

CPropertyDlg::~CPropertyDlg()
{
}

void CPropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CTRLCOMBO_KEYSTATE, m_comboCtrlKeyState);
	DDX_Control(pDX, IDC_CTRLLIST_PROP, m_listCtrlProp);
	DDX_Control(pDX, IDC_CTRLBTN_APPLY, m_btnCtrlApply);
	DDX_Control(pDX, IDC_CTRLBTN_ADDKEY, m_btnCtrlAddkey);
	DDX_Control(pDX, IDC_CTRLBTN_VIEWGLOBAL, m_btnCtrlViewGlobal);
	DDX_Control(pDX, IDC_CTRLEDIT_DESCRIPTION, m_editCtrlDescription);
	DDX_Control(pDX, IDC_CTRLCOMBO_SHOWVIEW, m_comboCtrlShowView);
	m_bCtrlCreated = TRUE;
}


BEGIN_MESSAGE_MAP(CPropertyDlg, CDialog)
	ON_WM_SIZE()
	ON_MESSAGE(WM_PROPLIST_SELCHANGE,OnPropListSelChange)
	ON_MESSAGE(WM_INITDIALOG, OnInitDialog)
	ON_BN_CLICKED(IDC_CTRLBTN_APPLY, &CPropertyDlg::OnBnClickedCtrlbtnApply)
	ON_BN_CLICKED(IDC_CTRLBTN_ADDKEY, &CPropertyDlg::OnBnClickedCtrlbtnAddkey)
	ON_BN_CLICKED(IDC_CTRLBTN_VIEWGLOBAL, &CPropertyDlg::OnBnClickedCtrlbtnViewglobal)
	ON_CBN_SELCHANGE(IDC_CTRLCOMBO_KEYSTATE, &CPropertyDlg::OnCbnSelchangeCtrlcomboKeystate)
END_MESSAGE_MAP()

//LONG CPropertyDlg::OnInitDialog(UINT wParam, LONG lParam)
LRESULT CPropertyDlg::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	BOOL bRet = HandleInitDialog(wParam, lParam);
//	if(!UpdateData(FALSE))
//	{
//		 TRACE0("Warning, Unalbe to init update.\n");
//	}
	// Add Code here
	return bRet;
}

// CPropertyDlg 消息处理程序

void CPropertyDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	if(m_bCtrlCreated)
	{
		int nWidth = 0;
		CRect rc,rcRect1,rcRect2,rcRect3,rcRect4,rcRect5,rcRect6,rcRect7;
		GetClientRect(&rc);
		if( rc.bottom > 600 ) rc.bottom = 600;
		rcRect1 = rc;
		rcRect1.bottom = 14;
		nWidth =  (rc.right - 6) / 3;
		//Buttons
		rcRect3 = rc;
		rcRect3.top = rc.bottom - 54;
		rcRect3.bottom = rc.bottom - 32;
		rcRect3.right = nWidth;
		rcRect4 = rcRect3;
		rcRect4.left = nWidth + 3;
		rcRect4.right = rcRect4.left + nWidth;
		rcRect5 = rcRect3;
		rcRect5.left = rcRect4.right + 3;
		rcRect5.right = rcRect5.left + nWidth;
		//PropList
		rcRect2 = rc;
		rcRect2.top = 30;
		rcRect2.bottom = rc.bottom - 120;
		//Description
		rcRect6 = rc;
		rcRect6.top = rcRect2.bottom + 3;
		rcRect6.bottom = rc.bottom - 60;
		//Combo ShowView
		rcRect7 = rc;
		rcRect7.top = rc.bottom - 24;
		rcRect7.bottom = rc.bottom - 10;
		m_comboCtrlKeyState.MoveWindow(rcRect1);
		m_listCtrlProp.MoveWindow(rcRect2);
		m_btnCtrlApply.MoveWindow(rcRect3);
		m_btnCtrlAddkey.MoveWindow(rcRect4);
		m_btnCtrlViewGlobal.MoveWindow(rcRect5);
		m_editCtrlDescription.MoveWindow(rcRect6);
		m_comboCtrlShowView.MoveWindow(rcRect7);
	}
}

LRESULT CPropertyDlg::OnPropListSelChange(WPARAM wParam,LPARAM lParam)
{
	if( wParam != IDC_CTRLLIST_PROP )return 0;
	CString strTemp = m_listCtrlProp.GetCurItemDescrption();
	m_editCtrlDescription.SetWindowTextW(strTemp);
	return 0;
}

void CPropertyDlg::OnCbnSelchangeCtrlcomboKeystate()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxGetMainWnd()->SendMessage(WM_PROPERTY_OPERATE, IDD_PROPERTY_DLG, 1);
}

void CPropertyDlg::OnBnClickedCtrlbtnApply()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxGetMainWnd()->SendMessage(WM_PROPERTY_OPERATE, IDD_PROPERTY_DLG, 2);
}

void CPropertyDlg::OnBnClickedCtrlbtnAddkey()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxGetMainWnd()->SendMessage(WM_PROPERTY_OPERATE, IDD_PROPERTY_DLG, 3);
}

void CPropertyDlg::OnBnClickedCtrlbtnViewglobal()
{
	// TODO: 在此添加控件通知处理程序代码
	AfxGetMainWnd()->SendMessage(WM_PROPERTY_OPERATE, IDD_PROPERTY_DLG, 4);
}
