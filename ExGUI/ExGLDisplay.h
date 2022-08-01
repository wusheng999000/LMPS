#pragma once

#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
// CExGLDisplay

class AFX_EXT_CLASS CExGLDisplay : public CListBox
{
	DECLARE_DYNAMIC(CExGLDisplay)

public:
	CExGLDisplay();
	virtual ~CExGLDisplay();
	void AddBranchPointItem(float x, float y, float z);
	void AddSkelectPointItem(float x, float y, float z, int iOne, int iTow, int iThree);
	void AddPointItem(float x,float y,float z,float r,float g,float b);
	void AddLineItem(float x1,float y1,float z1,float x2,float y2,float z2,float r,float g,float b);
	void AddTriangleItem(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float r,float g,float b);
	void AddQuadItem(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3,float x4,float y4,float z4,float r,float g,float b);
	void RemoveAllItems();          //删除所有元素
	void SetScene(int ntype,float px,float py,float pz,float ax,float ay,float az,float rx,float ry,float rz);
	void Invalidate();
public:
	bool m_bPointCloud;
	bool m_bSkelect;
	bool m_bBranch;
	int m_iLeafNum;
	bool m_bHaveTassel;
	int m_iLeafNodeNum;
private:
	struct point3D{
		point3D(float mx=0,float my=0,float mz=0, int iPointOne=0,int iPointTow=0,int iPointThree=0){x=mx;y=my;z=mz;}
		~point3D(){};
		float x,y,z;
		int iPointOne, iPointTow, iPointThree;
	};
	struct color3f{
		color3f(float mr=0,float mg=0,float mb=0){r=mr;g=mg;b=mb;}
		~color3f(){};
		float r,g,b;
	};
	point3D SceneAngle;             //视图场景旋转角度
	point3D ScenePos;               //视图场景平移位置
	point3D SceneRate;
	float  SceneZoom;              //视图比例系数
	float  SceneDepth;             //视图区深度
	BOOL	m_bShowAxis;
	int m_nViewOperateType;
	BOOL m_bShowGrid;
	BOOL m_bRightMenu;
	int	m_nViewType;                //视图类型
	int m_nOperate;

	CDC* m_pDC;						// Windows设备描述表
	HGLRC m_hRC;					// OpenGL渲染描述表
	CRect m_ClientRect;				// 客户区的大小
	float m_dAspectRatio;			// 窗口的比例
	HPALETTE	m_hPalette;			//调色板
	CPoint m_pointMouseDown;
	BOOL m_bGLInited;
	CArray<point3D,point3D> mpts;
	CArray<point3D,point3D> mlns;
	CArray<point3D,point3D> mtgs;
	CArray<point3D,point3D> mqds;
	CArray<color3f,color3f> cpts;
	CArray<color3f,color3f> clns;
	CArray<color3f,color3f> ctgs;
	CArray<color3f,color3f> cqds;

	BOOL bSetupPixelFormat();
	BOOL InitializeOpenGL();
	void SetLogicalPalette(void);
	void SetViewMode();
	void DrawAxis(float rule);
	void DrawGrid(float range = 2.0);
	void DrawItems();
	void DrawScene();
	void DrawPointCloud();
	void DrawSkelectData();//画骨架数据			   
	void DrawBranchPointCloud();//画叶片分离点
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnDraw(CDC* pDC);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT /*lpMeasureItemStruct*/);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
protected:
	virtual void PreSubclassWindow();
};


