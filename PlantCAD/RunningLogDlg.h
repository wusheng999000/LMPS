#pragma once
#include "afxwin.h"


// CRunningLogDlg �Ի���

class CRunningLogDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRunningLogDlg)

public:
	CRunningLogDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRunningLogDlg();

// �Ի�������
	enum { IDD = IDD_RunningLogDlg };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_RunningLogList;
	virtual BOOL OnInitDialog();
};
