// ProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "ProgressDlg.h"


// CProgressDlg �Ի���

IMPLEMENT_DYNAMIC(CProgressDlg, CDialog)

CProgressDlg::CProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressDlg::IDD, pParent)
{

}

CProgressDlg::~CProgressDlg()
{
}

void CProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESSDLG_PROG, mProg);
}


BEGIN_MESSAGE_MAP(CProgressDlg, CDialog)
END_MESSAGE_MAP()


// CProgressDlg ��Ϣ�������
