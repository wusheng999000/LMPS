// RunningLogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "RunningLogDlg.h"
#include "afxdialogex.h"


// CRunningLogDlg �Ի���

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


// CRunningLogDlg ��Ϣ�������


BOOL CRunningLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_RunningLogList.AddString(L"The system is being initialized...");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
