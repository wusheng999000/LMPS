#pragma once

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <afxtempl.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
// CExCurveCtrl
#define CURVE_SEL_DIS 10.0
#define WM_CURVECTRL_CHANGE WM_USER+1003

class AFX_EXT_CLASS CExCurveCtrl : public CListBox
{
	DECLARE_DYNAMIC(CExCurveCtrl)

public:
	CExCurveCtrl();
	virtual ~CExCurveCtrl();
	void SetCtrlProp(CRect rect,float scale,float mark,int text);
	void Invalidate();
	void InitPoints(CArray<float,float>& mPts);
	void RemoveAllPoints(); 
	void AddRefPoint(float mx,float my);
	int GetCurSel();
	void GetPoints(CArray<float,float>& mPts);
	void GetSpline(CArray<float,float>& mSpln);
	float GetBSplineLength(CArray<float,float>& mPts);
	void GetBSpline(CArray<float,float>& mPts, CArray<float,float>& mSpln);
	void Refresh();
protected:
	CDC* m_pDC;						// Windows设备描述表
	HGLRC m_hRC;					// OpenGL渲染描述表
	CRect m_ClientRect;				// 客户区的大小
	CRect m_SceneRect;
	float m_Scale;
	float m_Scale_I;
	float m_Mark;
	int m_Text;
	float m_Mark_I;
	int m_Text_I;
	int m_nOperate;
	CPoint m_pointMouseDown;
	float mSceneRate;
	HPALETTE	m_hPalette;			//调色板
	GLYPHMETRICSFLOAT agmf[256];
	HFONT hFontA, hFontW, hOldFont;
	COLORREF mSysClr;
	int m_nCurSel;
	float mpRefx,mpRefy;
	BOOL m_bShowRef;
	CArray<float,float> mPoints;  //
	CArray<float,float> mSplins;
	void Chase(CArray<float,float> &a,CArray<float,float> &b,CArray<float,float> &c,CArray<float,float> &d,CArray<float,float> &x);
	void GetBSplineCtrlPts(CArray<float,float> &pMdl,CArray<float,float> &knot,CArray<float,float> &pCtrl);
	void GetBSpline(CArray<float,float> &pt_Ctrl,CArray<float,float> &m_Node,CArray<float,float> &pt_Inter);
	void BSpline(float p[8],float node[8],float u, float* mx, float* my);
	void CalcuBSpline();
	void DrawText(float x,float y,float z,int ftsz,CString str);
	void GetGLToDC(GLdouble gx,GLdouble gy,GLdouble gz,GLdouble* dx,GLdouble* dy,GLdouble* dz);
	void GetDCToGL(GLdouble dx,GLdouble dy,GLdouble dz,GLdouble* gx,GLdouble* gy,GLdouble* gz);
	void DrawPoints();
	void DrawRef();
	void SetRefShow(BOOL m_bShow = TRUE);
	void DrawSplines();
	BOOL bSetupPixelFormat();
	BOOL InitializeOpenGL();
	void SetLogicalPalette(void);
	void SetViewMode();
	void DrawAxis();
	void DrawScene();
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	virtual void OnDraw(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	virtual void PreSubclassWindow();
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};


