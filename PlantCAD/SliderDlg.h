#pragma once
#include "afxcmn.h"


// CSliderDlg �Ի���

class CSliderDlg : public CDialog
{
	DECLARE_DYNAMIC(CSliderDlg)

public:
	CSliderDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSliderDlg();

// �Ի�������
	enum { IDD = IDD_SLIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int nMaxFrame;
	int nMinFrame;
	int nCurFrame;
	int nSpeed;
	CSliderCtrl mSlider;
};
