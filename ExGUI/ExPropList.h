#pragma once

#include <afxtempl.h>
#include "ExPropItem.h"
#include "ExColorPicker.h"
#define IDC_PROPLIST_EDIT        29901
#define IDC_PROPLIST_COMBO       29902
#define IDC_PROPLIST_COLOR       29903

#define WM_PROPLIST_SELCHANGE WM_USER+1007

////////////////////////////////////////////////////////////////////////////////
// CExPropList

class AFX_EXT_CLASS CExPropList : public CListBox
{
	DECLARE_DYNAMIC(CExPropList)

public:
	CExPropList();
	virtual ~CExPropList();
	
	BOOL AddPropItem(CString catalog, CString propName, CString curValue, int nItemType, CString cmbItems, CString propDesc = _T(""), BOOL bEnable = TRUE, BOOL bItemShow = TRUE, int nItemOrder = -1);
	BOOL SetPropItem(CString catalog, CString propName, CString curValue, int nItemType, CString cmbItems, CString propDesc = _T(""), BOOL bEnable = TRUE, BOOL bItemShow = TRUE, int nItemOrder = -1);
	BOOL DeletePropItem( CString catalog, CString propName );
	void DeleteAllItem();
	COLORREF GetItemColor(CString catalog, CString propName);
	CString GetItemValue(CString catalog, CString propName);
	CString GetItemDescrption(CString catalog, CString propName);
	CString GetCurItemDescrption();
	CString GetCurItemValue();
	BOOL EnableItem(CString catalog, CString propName, BOOL bEnable = TRUE);
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void CheckColorString(CString& strColor);
protected:
	DECLARE_MESSAGE_MAP()
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void DrawItem(CDC &Dc,int nIndex,CRect &Rect);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	virtual void Invalidate(BOOL bErase = 1);
	virtual void OnDraw(CDC* pDC);

	void ResetContent();
	void ShowEdit(BOOL bShow,int nIndex = 0);
	void ShowCombo(BOOL bShow,int nIndex = 0);  
	void ShowColor(BOOL bShow,int nIndex = 0);
	void KillFocus(int n);
	int GetDataIndex(int nListIndex);
protected:
	int		m_curSel;
	int		m_prevSel;
	int		m_nDivider;
	CBitmap m_bmpCross;
	BOOL	m_bTracking;
	HCURSOR	m_hCursorArrow;
	HCURSOR	m_hCursorSize;
	BOOL	m_bEditShow;
	BOOL	m_bComboShow;
	BOOL	m_bColorShow;
	CEdit	m_edit;
	CComboBox	m_combo; 
	CExColorPicker m_color;
	CArray<CExPropItem,CExPropItem> mList;
	CExPropItem mItem,mCatalog;
	CDC MemDC;
	CBitmap MemBmp;
	int m_nKillFocus;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnPaint();
	afx_msg void OnChangeEdit();
	afx_msg void OnComboSelectChange();
	afx_msg LRESULT OnColorBtnSelOk(WPARAM wParam,LPARAM lParam);
	afx_msg void OnLbnKillfocus();
	afx_msg void OnCbnKillfocusPropListCombo();
	afx_msg void OnEnKillfocusPropListEdit();
protected:
	virtual void PreSubclassWindow();
};


