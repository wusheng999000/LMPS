#pragma once

#define WM_TREECTRL_CHANGE WM_USER + 1006			//
// CExTreeCtrl
#include <afxcmn.h>  

class AFX_EXT_CLASS CExTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CExTreeCtrl)

public:
	CExTreeCtrl();
	virtual ~CExTreeCtrl();
	void ExpandAllItems(BOOL bExpand = TRUE );
	void ExpandBranch( HTREEITEM hItem,BOOL bExpand = TRUE );
	BOOL SetItemState( HTREEITEM hItem, UINT nState, UINT nStateMask, BOOL bSearch=TRUE);
	BOOL m_bShowCheckBox;
	void ShowCheckBox(BOOL mbShow = TRUE );
	void SetAllItemState(UINT uState, BOOL bFlag = TRUE);
	void SetAllItemCheck(BOOL bCheck = TRUE);
	void SetCheckItem(HTREEITEM hItem, BOOL bCheck = TRUE);
private:
	CImageList m_imgState;
	void TravelSiblingAndParent(HTREEITEM hItem, int nState);
	void TravelChild(HTREEITEM hItem,int nState);
	HTREEITEM m_hOldTreeItem,m_hCurTreeItem;
	
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
protected:
	virtual void PreSubclassWindow();
public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};


