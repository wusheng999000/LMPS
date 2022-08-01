#pragma once
#include "afxcmn.h"


// CSliderDlg 对话框

class CSliderDlg : public CDialog
{
	DECLARE_DYNAMIC(CSliderDlg)

public:
	CSliderDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSliderDlg();

// 对话框数据
	enum { IDD = IDD_SLIDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int nMaxFrame;
	int nMinFrame;
	int nCurFrame;
	int nSpeed;
	CSliderCtrl mSlider;
};
