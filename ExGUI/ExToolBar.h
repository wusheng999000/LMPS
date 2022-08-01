#pragma once

#include <afxpriv.h>
// CExToolBar

class AFX_EXT_CLASS CExToolBar : public CToolBar
{
	DECLARE_DYNAMIC(CExToolBar)

public:
	CExToolBar();
	virtual ~CExToolBar();
	void SetMessageReceiver(CWnd* pMessageReceiver);
	BOOL LoadBitmaps(int  nBtnWidth, UINT uToolBar, UINT uToolBarHot, UINT uToolBarDisabled);
	BOOL SetTrueColorToolBar(UINT uToolBarType, UINT uToolBar, int  nBtnWidth);
	void SetBkGrdBmp(CString path, int nHeight);
protected:
	DECLARE_MESSAGE_MAP()
	CWnd*	m_pMessageReceiver;
	CBrush	mBrush;
	CBitmap cBmp;
	HBITMAP hBmp;
	int		bkHeight;
	CString bkPath;
	BOOL	m_bBkGrd;
public:
	virtual BOOL CreateEx(CWnd* pParentWnd, DWORD dwCtrlStyle = TBSTYLE_FLAT, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_ALIGN_TOP, CRect rcBorders = CRect(0, 0, 0, 0), UINT nID = AFX_IDW_TOOLBAR);
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
protected:
	virtual void PreSubclassWindow();
};
