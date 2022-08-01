
#pragma once
#include "afxwin.h"
// CPropertyDlg 对话框

#define WM_PROPERTY_OPERATE WM_USER + 201

class CPropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(CPropertyDlg)

public:
	CPropertyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPropertyDlg();

// 对话框数据
	enum { IDD = IDD_PROPERTY_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bCtrlCreated;
	CComboBox m_comboCtrlKeyState;
	CExPropList m_listCtrlProp;
	CButton m_btnCtrlApply;
	CButton m_btnCtrlAddkey;
	CButton m_btnCtrlViewGlobal;
	CEdit m_editCtrlDescription;
	CComboBox m_comboCtrlShowView;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnPropListSelChange(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnInitDialog(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedCtrlbtnApply();
	afx_msg void OnBnClickedCtrlbtnAddkey();
	afx_msg void OnBnClickedCtrlbtnViewglobal();
	afx_msg void OnCbnSelchangeCtrlcomboKeystate();
};
