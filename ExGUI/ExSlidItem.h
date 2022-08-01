#pragma once

#define WM_USER_SLID_UPDATE WM_USER+1001

// CExSlidItem

class CExSlidItem : public CStatic
{
	DECLARE_DYNAMIC(CExSlidItem)

public:
	CExSlidItem();
	virtual ~CExSlidItem();
	CExSlidItem(int nOdr, float mVal, float mRef, float mMin, float mMax, BOOL bEdit);
	void SetItem(int nOdr, float mVal, float mRef, float mMin, float mMax, BOOL bEdit);
	void UpdateParent(int nCur);
public:
	int nOrder;
	float mValue;
	float mReference;
	float mMinimum;
	float mMaximum;
	BOOL bEditable;
	BOOL m_bSlider;
	CRect rectItem;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);
};


