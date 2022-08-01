#pragma once

#include <afxtempl.h>
#include "stdafx.h" 
#define IDC_LISTCTRL_EDIT        29902
#define IDC_LISTCTRL_COMBO       29903
#define WM_LISTCTRL_CHANGE WM_USER + 1005

// CExEditList

class AFX_EXT_CLASS CExEditList : public CListCtrl
{
	DECLARE_DYNAMIC(CExEditList)

public:
	CExEditList();
	virtual ~CExEditList();

	void SetItemHeight(UINT nHeight);
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	int InsertItem(int nItem,LPCTSTR lpszItem);
	BOOL SetItemStatus(int nItem ,int nSubItem, int nStatus, CString sContent = _T(""));   //可编辑状态，0不可编辑，1edit，2combo 
	int GetCurSel();
	CString GetItemContent( int nItem ,int nSubItem );
protected:
	void ShowEdit( BOOL bShow,int nItem = 0,int nIndex = 0,CRect rc = CRect(0,0,0,0) );
	void ShowCombo( BOOL bShow,int nItem = 0,int nIndex = 0,CRect rc = CRect(0,0,0,0) );   // Sail 090903Add
	BOOL SetComboItemContent(int nItem ,int nSubItem, CString sContent);

private:
	CEdit		m_edit;
	CComboBox   m_combo;              
	int m_nItem;
	int m_nSub;

	int m_nCntCol;                    //总列数
	int m_nCntRow;                    //总行数
	CArray<int,int> m_nItemStatus;    //可编辑状态，0不可编辑，1edit，2combo 
	CArray<CString,CString> m_sComboContent; //Combo内容
	UINT m_nItemHeight;               //ListItemHeight
protected:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnComboSelectChange();
	afx_msg void OnComboEnd();
	afx_msg void OnEditChange();
	afx_msg void OnEditEnd();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	DECLARE_MESSAGE_MAP()
};


