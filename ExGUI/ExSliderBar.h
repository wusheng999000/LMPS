#pragma once

#include "Resource.h"
#include "afxcmn.h"
// CExSliderBar 对话框
#define WM_SLIDERPOS_CHANGE WM_USER + 1004

class AFX_EXT_CLASS CExSliderBar : public CDialog
{
	DECLARE_DYNAMIC(CExSliderBar)

public:
	CExSliderBar(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CExSliderBar();

// 对话框数据
	enum { IDD = IDD_EXSLIDERBAR };

	int nFrameCur;
	int nFrameMin;
	int nFrameMax;
	CSliderCtrl mFrameSlider;
	int mPlay;
	int nSpeed;
	int nTimePlay;
	int mPlaySpeed;
	void SetRange( int nMin, int nMax);
	void SetPos( int nPos );
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedFrameTomin();
	afx_msg void OnBnClickedFrameMinus();
	afx_msg void OnBnClickedFrameMplay();
	afx_msg void OnBnClickedFramePause();
	afx_msg void OnBnClickedFramePplay();
	afx_msg void OnBnClickedFramePlus();
	afx_msg void OnBnClickedFrameTomax();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangePlaySpeed();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
