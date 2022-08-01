#pragma once
#include "afxwin.h"
#include "Resource.h"
#include "stdafx.h"
// CSceneParamDlg �Ի���

class CSceneParamDlg : public CDialog
{
	DECLARE_DYNAMIC(CSceneParamDlg)

public:
	CSceneParamDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSceneParamDlg();

// �Ի�������
	enum { IDD = IDD_SCENE_PARAM_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_nSceneParamUnit;
	float m_fSceneParamRange;
	float m_fSceneParamRule;
	BOOL m_bSceneParamGradual;
	CExColorPicker m_btnSceneParamClr1;
	CExColorPicker m_btnSceneParamClr2;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedSceneparamGradual();
};
