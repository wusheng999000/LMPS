#pragma once
#include "ExSlidItem.h"

#define IDC_SLIDLIST_EDIT 29905
#define WM_SLIDLIST_CHANGE WM_USER+1002
// CExSlidList

class AFX_EXT_CLASS CExSlidList : public CListCtrl
{
	DECLARE_DYNAMIC(CExSlidList)

public:
	CExSlidList();
	virtual ~CExSlidList();
	void	AddItem(int nOrder, float mVal, float mRef, float mMin, float mMax, BOOL bEditable = TRUE);
	void	SetItemHeight(UINT nHeight);
	int		InsertColumn(int nCol, LPCTSTR lpszColumnHeading,int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	int		InsertItem(int nItem,LPCTSTR lpszItem);
	void	InitColumn(int nWidth1 = 40,int nWidth2 = 50);
	void	DeleteAllItems();
	void	ShowEdit( BOOL bShow,int nItem = 0,CRect rc = CRect(0,0,0,0) );
	void	InvalidateCtrl(void);
	void	InvalidateItem(int nOrder);
	float	GetItemValue(int nItem);
	void	SetItemValue(int nOrder, float mVal, float mRef, float mMin, float mMax, BOOL bEditable);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
public:
//	UINT nID;
	int m_nWidth;
	int m_nWidth1;
	int m_nWidth2;
	int m_nCntItems;
	int m_nItemHeight;
	BOOL m_bColumnInited;
	int m_nCurSel;
	CArray<CExSlidItem*,CExSlidItem*> mData;
	CEdit m_edit;
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnSlidUpdate(WPARAM wParam,LPARAM lParam);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnEditChange();
	afx_msg void OnEditEnd();
};


