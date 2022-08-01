#pragma once

#pragma once
#include <math.h>

#include <gl\gl.h>
#include <gl\glu.h>
#include "SceneGeome.h"
#include "Resource.h"
#include "SceneTexture.h"
#include "SceneOperate.h"
#include "SceneParamDlg.h"
#include "ClientCapture.h"
#include "AVICapture.h"
#include "SceneVideoDlg.h"

class CSceneVideoDlg;
#define SCENE_VIEW_PACE 20
// CGLEnableView 视图

class AFX_EXT_CLASS CGLEnableView : public CView
{
	DECLARE_DYNCREATE(CGLEnableView)

protected:
	CGLEnableView();           // 动态创建所使用的受保护的构造函数
	virtual ~CGLEnableView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnDrawGL();
public:
	virtual void SetViewMode();
	virtual void DrawSelCoord();
	virtual void DrawAxis(float rate = 1.0);
	virtual void DrawGrid(float range = 2.0);
	virtual void DrawCube(float mEdge = 1.0);
	virtual void DrawText( int nSize = 10 );
	//显示点云文件点个数、关键点个数、文件名等基本信息
	virtual void DrawText2(int nSize = 10);
	virtual int IsCoordinSel(CPoint point);
	virtual void DrawText(float x,float y,float z,int ftsz,CString str,BOOL bCn = FALSE);
	float DistanceOfTwoPoints(CPoint p1, CPoint p2);
	float DistanceOfTwoPoints(ScenePoint3D p1, ScenePoint3D p2);
	BOOL GetScenePlanePt(CPoint point,SCENEPOINT3D& p,int nPlane);
	BOOL GetDragScenePt(CPoint pMD,CPoint point, SCENEPOINT3D& p, int nType);
	void GetScreenPt(SCENEPOINT3D p, CPoint& point);
	void ViewTo(SCENEPOINT3D pAim);
	void DrawScene();
	BOOL SetLightsParams( int nLight, GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat position[4] );
	BOOL SetLightsStatus( int nLight, BOOL bEnable );
	void OutputBmpFile();
	void OutputBmpFile( CString mPath );
	void AVIFileCapture();
	void VideoOutput();
	void OutputAviFile();
	void OutputBmpSequ();

	bool CalcuPtToMatrix(float& x, float& y, float& z, CMatrix4x4 m);
	bool OperatePt(float& x, float& y, float& z);
	bool OperatePt(SCENEPOINT3D& p);
	bool BoxSelect(CPoint pLT, CPoint pRB, Expoint3D pts[], int sel[], int cnt, float unit);
	bool BoxSelect(CPoint pLT, CPoint pRB, CArray<Expoint3D,Expoint3D> &pts, CArray<int,int> &sel, float unit);//2018.9.7
	void GetScenePt( CPoint pt, SCENEPOINT3D& p );
	void DrawSelectBox();
	void GetOperateMatrix( float m[16] );
	void SetViewBasic();//把视口设置到原点位置，2021.1.22
public:
	BOOL m_bGradualBackgroud;		//渐变背景
	BOOL m_bShowText;
	BOOL m_bShowAxis;
	BOOL m_bShowGridXY;             //网格XY
	BOOL m_bShowGridYZ;             //网格YZ
	BOOL m_bShowGridZX;             //网格ZX
	BOOL m_bShowCube;               //视图盒
	BOOL m_bShowSelCoord;			//选择坐标系
	BOOL m_bFixedSelCoord;			//固定大小的选择坐标系
	bool m_bShowSelBox;				//显示框选框
	SCENEPOINT3D mCurSelPt;
	float m_CoordScale;
	float m_CoordRate;
	int m_nSelType;					//选择状态
	int m_nSelObject;				//选择的对象，用于在LButtonDown和MouseMove之间的对应
	int	m_nViewType;                //视图类型
	int	m_nSceneOperateType;        //视图场景操作类型
	int	m_nObjectOperateType;       //视图对象操作类型
	SCENEPOINT3D SceneAngle;        //视图场景旋转角度
	SCENEPOINT3D ScenePos;          //视图场景平移位置
	SCENEPOINT3D SceneRate;         //视图场景缩放比例
	CDC* m_pDC;						//Windows设备描述表
	float  SceneZoom;               //视图比例系数
	float  SceneDepth;              //视图区深度
	float m_FloorRange;         
	SCENEPOINT3D view_base_point;   //鼠标按下基点GL坐标系
	CPoint ptSelBox[4];				//框选的4点

	BOOL m_bRightMenu;
	HGLRC m_hRC;					// OpenGL渲染描述表
	CRect m_ClientRect;				// 客户区的大小
	float m_dAspectRatio;			// 窗口的比例
	HPALETTE	m_hPalette;			//调色板
	CPoint m_pointMouseDown;
	int m_uSceneUnit;				//3 m, 2 dm, 1 cm, 0 mm
	float m_unitScene;				//1000 m, 100 dm, 10 cm, 1 mm
	int m_nShowMode;				//显示模式0，不显示，1点，2线，3面，4贴图
	ExColor3f m_clrBack1;
	ExColor3f m_clrBack2;
	int nSizeText;
	HFONT hFontA, hFontW, hOldFont;
	//Capture
	CClientCapture  CapturedImage;       //定义位图输出
	bool m_bRecording;
	CAVICapture *m_pMovieCapture;

	//System Light zuiduo 8 Lights
	GLfloat light_ambient[8][4]; 
	GLfloat light_position[8][4];
	GLfloat light_diffuse[8][4];
	GLfloat light_specular[8][4];
	BOOL m_bLightEnable[8];
	BOOL m_bLighting;
	CString mSqenPath;					//序列名称
	//Operate
	CSceneOperate mOperate;
	CSceneVideoDlg* mpSceneVideoDlg;
	CString strCurPointNum;//当前点个数
	CString strSkelPointNum;//骨架点个数
	CString strCurPCFileName;//当前点云文件名
private:
	//Capture
	bool BeginMovieCapture(CString filename,int width, int height,float framerate);
	void InitMovieCapture(CAVICapture* mc);
	void RecordBegin();
	void RecordPause();
	void RecordEnd();

	BOOL bSetupPixelFormat();
	BOOL InitializeOpenGL(CDC* pDC);
	void SetLogicalPalette(void);
	void DrawBackground();
	CSceneTexture mTexture;
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
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
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
	afx_msg void OnRviewmenuOrtho();
	afx_msg void OnUpdateRviewmenuOrtho(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuPersp();
	afx_msg void OnUpdateRviewmenuPersp(CCmdUI *pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnRviewmenuAxis();
	afx_msg void OnUpdateRviewmenuAxis(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuCube();
	afx_msg void OnUpdateRviewmenuCube(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuGridxy();
	afx_msg void OnUpdateRviewmenuGridxy(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuGridyz();
	afx_msg void OnUpdateRviewmenuGridyz(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuGridzx();
	afx_msg void OnUpdateRviewmenuGridzx(CCmdUI *pCmdUI);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRviewmenuText();
	afx_msg void OnUpdateRviewmenuText(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuProperty();
	afx_msg void OnRviewmenuLight();
	afx_msg void OnUpdateRviewmenuLight(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuReset();
	afx_msg void OnRviewmenuSwmdpoint();
	afx_msg void OnRviewmenuSwmdline();
	afx_msg void OnUpdateRviewmenuSwmdpoint(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRviewmenuSwmdline(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuSwmdpoly();
	afx_msg void OnUpdateRviewmenuSwmdpoly(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuSwmdrander();
	afx_msg void OnUpdateRviewmenuSwmdrander(CCmdUI *pCmdUI);
	afx_msg void OnDestroy();
	afx_msg void OnRviewmenuOpertra();
	afx_msg void OnUpdateRviewmenuOpertra(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuOperrot();
	afx_msg void OnUpdateRviewmenuOperrot(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuOpersca();
	afx_msg void OnUpdateRviewmenuOpersca(CCmdUI *pCmdUI);
	afx_msg void OnRviewmenuOpersel();
	afx_msg void OnUpdateRviewmenuOpersel(CCmdUI *pCmdUI);
};


