#pragma once
#include "afxtempl.h"
// CExListCtrl
class AFX_EXT_CLASS CExListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CExListCtrl)

public:
	CExListCtrl();
	virtual ~CExListCtrl();
	int GetCurSel();
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
protected:
	CImageList LargeImage;
	CArray<CString,CString> path;
	int nImageWidth,nImageHeight;
public:
	BOOL SetImagePath(int nImage, CString strPath);
	void SetImageRange(int nx, int ny);
	CString GetImagePath(int nImage);
protected:
	virtual void PreSubclassWindow();
};


