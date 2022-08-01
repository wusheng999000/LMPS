#pragma once
#include "afxwin.h"


// CRunningLogDlg 对话框

class CRunningLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRunningLogDlg)

public:
	CRunningLogDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRunningLogDlg();

// 对话框数据
	enum { IDD = IDD_RunningLogDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_RunningLogList;
	virtual BOOL OnInitDialog();
};
