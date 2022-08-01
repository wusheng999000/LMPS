#pragma once

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
#include "resource.h"

#define GLTABLE_VIEW_PACE 20
// CExGLTable ��ͼ

class AFX_EXT_CLASS CExGLTable : public CView
{
	DECLARE_DYNCREATE(CExGLTable)
public:
	void AddPointItem(float x,float y,float z,float r,float g,float b);
	void AddLineItem(float x1,float y1,float z1,float x2,float y2,float z2,float r,float g,float b);
	void AddTriangleItem(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float r,float g,float b);
	void AddQuadItem(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4,float r,float g,float b);
	void RemoveAllItems();          //ɾ������Ԫ��
	void SetScene(float px,float py,float pz,float ax,float ay,float az,float rx,float ry,float rz);

private:
	struct point3D{
		point3D(float mx=0,float my=0,float mz=0){x=mx;y=my;z=mz;}
		~point3D(){};
		float x,y,z;
	};
	struct color3f{
		color3f(float mr=0,float mg=0,float mb=0){r=mr;g=mg;b=mb;}
		~color3f(){};
		float r,g,b;
	};
	point3D SceneAngle;             //��ͼ������ת�Ƕ�
	point3D ScenePos;               //��ͼ����ƽ��λ��
	point3D SceneRate;
	float  SceneZoom;              //��ͼ����ϵ��
	float  SceneDepth;             //��ͼ�����
	BOOL	m_bShowAxis;
	int m_nViewOperateType;
	BOOL m_bShowGrid;
	BOOL m_bRightMenu;
	int	m_nViewType;                //��ͼ����

	CDC* m_pDC;						// Windows�豸������
	HGLRC m_hRC;					// OpenGL��Ⱦ������
	CRect m_ClientRect;				// �ͻ����Ĵ�С
	float m_dAspectRatio;			// ���ڵı���
	HPALETTE	m_hPalette;			//��ɫ��
	CPoint m_pointMouseDown;

	CArray<point3D,point3D> mpts;
	CArray<point3D,point3D> mlns;
	CArray<point3D,point3D> mtgs;
	CArray<point3D,point3D> mqds;
	CArray<color3f,color3f> cpts;
	CArray<color3f,color3f> clns;
	CArray<color3f,color3f> ctgs;
	CArray<color3f,color3f> cqds;

	virtual void OnDrawGL();
	BOOL bSetupPixelFormat();
	BOOL InitializeOpenGL(CDC* pDC);
	void SetLogicalPalette(void);
	void SetViewMode();
	void DrawAxis(float rule);
	void DrawGrid(float range = 2.0);
	void DrawItems();
	void DrawScene();
	void ViewTo(point3D pAim);
protected:
	CExGLTable();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CExGLTable();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnRviewmenuOrtho();
	afx_msg void OnUpdateRviewmenuOrtho(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuPersp();
	afx_msg void OnUpdateRviewmenuPersp(CCmdUI *pCmdUI);

	afx_msg void OnRviewmenuFront();
	afx_msg void OnRviewmenuBack();
	afx_msg void OnRviewmenuLeft();
	afx_msg void OnRviewmenuRight();
	afx_msg void OnRviewmenuTop();
	afx_msg void OnRviewmenuBottom();

	afx_msg void OnRviewmenuTrans();
	afx_msg void OnRviewmenuRotxy();
	afx_msg void OnRviewmenuRotyz();
	afx_msg void OnRviewmenuRotzx();
	afx_msg void OnRviewmenuScale();

	afx_msg void OnRviewmenuAxis();
	afx_msg void OnUpdateRviewmenuAxis(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuGrid();
	afx_msg void OnUpdateRviewmenuGrid(CCmdUI *pCmdUI);
};


