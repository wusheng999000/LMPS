#pragma once
#include "afxcmn.h"
#include "afxwin.h"
// CTextureDlg 对话框
#define WM_TEXTUER_OPERATE WM_USER + 202

#ifndef SCENE_MAX_TEXTURE
#define SCENE_MAX_TEXTURE 10
#endif

class CTextureDlg : public CDialog
{
	DECLARE_DYNAMIC(CTextureDlg)
	void SetTextures(CString mPath[]);
public:
	CTextureDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTextureDlg();
	CExListCtrl mTextureList;
	CEdit		mTexturePath;
	CButton		mTextureBrowse;
	CString		texPath[SCENE_MAX_TEXTURE];
// 对话框数据
	enum { IDD = IDD_TEXTURE_DLG };
protected:
	BOOL m_bCtrlCreated;
//	CExToolBar	mTextureToolBar;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString GetSysPath();

	afx_msg void OnBnClickedTextureBrowse();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnItemchangedTextureList(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTextureAddNew();
//	afx_msg void OnTextureDelete();
//	afx_msg void OnTextureGenerate();
};
