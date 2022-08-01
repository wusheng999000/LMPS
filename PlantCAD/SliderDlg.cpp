// SliderDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "SliderDlg.h"


// CSliderDlg �Ի���

IMPLEMENT_DYNAMIC(CSliderDlg, CDialog)

CSliderDlg::CSliderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSliderDlg::IDD, pParent)
	, nMaxFrame(0)
	, nMinFrame(0)
	, nCurFrame(0)
	, nSpeed(0)
{

}

CSliderDlg::~CSliderDlg()
{
}

void CSliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MAXFRAME, nMaxFrame);
	DDX_Text(pDX, IDC_MINFRAME, nMinFrame);
	DDX_Text(pDX, IDC_CURFRAME, nCurFrame);
	DDX_CBIndex(pDX, IDC_PLAY_SPEED, nSpeed);
	DDX_Control(pDX, IDC_FRAME_SLIDER, mSlider);
}


BEGIN_MESSAGE_MAP(CSliderDlg, CDialog)
END_MESSAGE_MAP()


// CSliderDlg ��Ϣ�������
