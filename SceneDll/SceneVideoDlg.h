#pragma once
#include "afxwin.h"
#include "resource.h"
#include "GLEnableView.h"

class CGLEnableView;
// CSceneVideoDlg �Ի���

class CSceneVideoDlg : public CDialog
{
	DECLARE_DYNAMIC(CSceneVideoDlg)

public:
	CSceneVideoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSceneVideoDlg();

// �Ի�������
	enum { IDD = IDD_SCENE_VIDEO_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mVideoPath;
	afx_msg void OnBnClickedScenevideoBrowse();
	CButton mBtnStart;
	bool m_bCapture;
	CGLEnableView* m_pParent;
	
	void SetParent(CGLEnableView* pParent);

	afx_msg void OnBnClickedScenevideoStart();
protected:
	virtual void OnCancel();
public:
	virtual BOOL OnInitDialog();
	int m_nSceneBmp;
	int m_nOrderSqen;
};
