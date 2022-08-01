// RunningLogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "RunningLogDlg.h"
#include "afxdialogex.h"


// CRunningLogDlg 对话框

IMPLEMENT_DYNAMIC(CRunningLogDlg, CDialogEx)

CRunningLogDlg::CRunningLogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRunningLogDlg::IDD, pParent)
{

}

CRunningLogDlg::~CRunningLogDlg()
{
}

void CRunningLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_RunningLogList);
}


BEGIN_MESSAGE_MAP(CRunningLogDlg, CDialogEx)
END_MESSAGE_MAP()


// CRunningLogDlg 消息处理程序


BOOL CRunningLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_RunningLogList.AddString(L"The system is being initialized...");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
