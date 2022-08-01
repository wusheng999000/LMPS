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
// CGLEnableView ��ͼ

class AFX_EXT_CLASS CGLEnableView : public CView
{
	DECLARE_DYNCREATE(CGLEnableView)

protected:
	CGLEnableView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CGLEnableView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnDrawGL();
public:
	virtual void SetViewMode();
	virtual void DrawSelCoord();
	virtual void DrawAxis(float rate = 1.0);
	virtual void DrawGrid(float range = 2.0);
	virtual void DrawCube(float mEdge = 1.0);
	virtual void DrawText( int nSize = 10 );
	//��ʾ�����ļ���������ؼ���������ļ����Ȼ�����Ϣ
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
	void SetViewBasic();//���ӿ����õ�ԭ��λ�ã�2021.1.22
public:
	BOOL m_bGradualBackgroud;		//���䱳��
	BOOL m_bShowText;
	BOOL m_bShowAxis;
	BOOL m_bShowGridXY;             //����XY
	BOOL m_bShowGridYZ;             //����YZ
	BOOL m_bShowGridZX;             //����ZX
	BOOL m_bShowCube;               //��ͼ��
	BOOL m_bShowSelCoord;			//ѡ������ϵ
	BOOL m_bFixedSelCoord;			//�̶���С��ѡ������ϵ
	bool m_bShowSelBox;				//��ʾ��ѡ��
	SCENEPOINT3D mCurSelPt;
	float m_CoordScale;
	float m_CoordRate;
	int m_nSelType;					//ѡ��״̬
	int m_nSelObject;				//ѡ��Ķ���������LButtonDown��MouseMove֮��Ķ�Ӧ
	int	m_nViewType;                //��ͼ����
	int	m_nSceneOperateType;        //��ͼ������������
	int	m_nObjectOperateType;       //��ͼ�����������
	SCENEPOINT3D SceneAngle;        //��ͼ������ת�Ƕ�
	SCENEPOINT3D ScenePos;          //��ͼ����ƽ��λ��
	SCENEPOINT3D SceneRate;         //��ͼ�������ű���
	CDC* m_pDC;						//Windows�豸������
	float  SceneZoom;               //��ͼ����ϵ��
	float  SceneDepth;              //��ͼ�����
	float m_FloorRange;         
	SCENEPOINT3D view_base_point;   //��갴�»���GL����ϵ
	CPoint ptSelBox[4];				//��ѡ��4��

	BOOL m_bRightMenu;
	HGLRC m_hRC;					// OpenGL��Ⱦ������
	CRect m_ClientRect;				// �ͻ����Ĵ�С
	float m_dAspectRatio;			// ���ڵı���
	HPALETTE	m_hPalette;			//��ɫ��
	CPoint m_pointMouseDown;
	int m_uSceneUnit;				//3 m, 2 dm, 1 cm, 0 mm
	float m_unitScene;				//1000 m, 100 dm, 10 cm, 1 mm
	int m_nShowMode;				//��ʾģʽ0������ʾ��1�㣬2�ߣ�3�棬4��ͼ
	ExColor3f m_clrBack1;
	ExColor3f m_clrBack2;
	int nSizeText;
	HFONT hFontA, hFontW, hOldFont;
	//Capture
	CClientCapture  CapturedImage;       //����λͼ���
	bool m_bRecording;
	CAVICapture *m_pMovieCapture;

	//System Light zuiduo 8 Lights
	GLfloat light_ambient[8][4]; 
	GLfloat light_position[8][4];
	GLfloat light_diffuse[8][4];
	GLfloat light_specular[8][4];
	BOOL m_bLightEnable[8];
	BOOL m_bLighting;
	CString mSqenPath;					//��������
	//Operate
	CSceneOperate mOperate;
	CSceneVideoDlg* mpSceneVideoDlg;
	CString strCurPointNum;//��ǰ�����
	CString strSkelPointNum;//�Ǽܵ����
	CString strCurPCFileName;//��ǰ�����ļ���
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


