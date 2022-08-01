// PlantCADView.cpp : CPlantCADView 类的实现
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "MainFrm.h"
#include "PlantCADDoc.h"
#include "PlantCADView.h"
#include<algorithm>
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

GLfloat mat_ambient[]={0.8,0.8,0.0,1.0};
GLfloat mat_diffuse[]={0.0,0.0,0.0,1.0};
GLfloat mat_specular[]={0.6,0.6,0.6,1.0};
GLfloat mat_emission[]={0.0,0.4,0.0,1.0};
GLfloat mat_shininess = 10.0;
// CPlantCADView

IMPLEMENT_DYNCREATE(CPlantCADView, CGLEnableView) //CView)

BEGIN_MESSAGE_MAP(CPlantCADView, CGLEnableView)//CView)
	// 标准打印命令
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDC_OUTPUT_BMPFILE, &CPlantCADView::OnOutputBmpFile)
	ON_WM_KEYUP()
	ON_WM_DROPFILES()
	ON_COMMAND(ID_VIEWBASE, &CPlantCADView::OnViewbase)
END_MESSAGE_MAP()

// CPlantCADView 构造/析构

CPlantCADView::CPlantCADView()
{
	// TODO: 在此处添加构造代码
	m_bShowText = FALSE;

}

CPlantCADView::~CPlantCADView()
{
}

BOOL CPlantCADView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPlantCADView 绘制
/*
void CPlantCADView::OnDraw(CDC* pDC)
{
CPlantCADDoc* pDoc = GetDocument();
ASSERT_VALID(pDoc);
if (!pDoc)
return;

CGLEnableView::OnDraw(pDC);
// TODO: 在此处为本机数据添加绘制代码
}
*/
// CPlantCADView 打印

BOOL CPlantCADView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlantCADView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlantCADView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlantCADView 诊断

#ifdef _DEBUG
void CPlantCADView::AssertValid() const
{
	CView::AssertValid();
}

void CPlantCADView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlantCADDoc* CPlantCADView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlantCADDoc)));
	return (CPlantCADDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlantCADView 消息处理程序

void CPlantCADView::OnDrawGL()
{
	CGLEnableView::OnDrawGL();
	CPlantCADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LESS);   
	glEnable(GL_DEPTH_TEST);  
	
	SetLights();
	if( m_bLighting && m_nShowMode > 2 )
	{
		glEnable(GL_LIGHTING);
	}
	else
	{
		glDisable(GL_LIGHTING);
	}

	glEnable(GL_COLOR_MATERIAL);
	//
	glColor3f(0.0f,0.5f,0.6f);

	pDoc->Draw(m_unitScene, m_nShowMode);
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_LIGHTING);
	//
}


void CPlantCADView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	OnDraw(pDC);
}

void CPlantCADView::SetLights()
{
	CPlantCADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_bLightFixed) return;
	int i = 0;
	for( i = 0; i < 8; i++ )
	{
		if( pDoc->m_bLightEnable[i] )
		{
			SetLightsParams(i,pDoc->light_ambient[i],pDoc->light_diffuse[i],pDoc->light_specular[i],pDoc->light_position[i]);
			SetLightsStatus( i, TRUE );
		}
		else
		{
			SetLightsStatus( i, FALSE );
		}
	}
	pDoc->m_bLightFixed = TRUE;
}

int CPlantCADView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CGLEnableView::OnCreate(lpCreateStruct) == -1)
		return -1;
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,mat_ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,mat_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,mat_specular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS, mat_shininess);
	//	glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,mat_emission);
	//	glColorMaterial(GL_FRONT_AND_BACK,GL_DIFFUSE);
	pDC = GetDC();
	//130105
	CPlantCADDoc* pDoc = GetDocument();
	pDoc->m_hDC = pDC->GetSafeHdc();
	DragAcceptFiles(TRUE);//支持文件拖拽
	//130105
	return 0;
}

void CPlantCADView::OnDestroy()
{
	CGLEnableView::OnDestroy();
	// TODO: 在此处添加消息处理程序代码
	ReleaseDC(pDC);
}

void CPlantCADView::OnLButtonDown(UINT nFlags, CPoint point)
{
	
	CGLEnableView::OnLButtonDown(nFlags, point);
}

void CPlantCADView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture();
	CPlantCADDoc* pDoc = GetDocument();
	CGLEnableView::OnLButtonUp(nFlags, point);
	
}

void CPlantCADView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture();
	CPlantCADDoc* pDoc = GetDocument();
	
	CGLEnableView::OnRButtonUp(nFlags, point);
}
void CPlantCADView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ReleaseCapture();
	CPlantCADDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if(pDoc->m_uMouseOperate == pDoc->OPERATE_DRAW)
	{

		//pDoc->Invalidate();
	}
	else
	{ 
	    CGLEnableView::OnRButtonDown(nFlags, point);
	}
}

void CPlantCADView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPlantCADDoc* pDoc = GetDocument();
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	ASSERT_VALID(pDoc);
	//
	if (pDoc->m_uMouseOperate == pDoc->OPERATE_DRAW)
	{
		return;
	}
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);	
	CGLEnableView::OnMouseMove(nFlags, point);

	
}

void CPlantCADView::OnOutputBmpFile()
{
	OutputBmpFile();
}



void CPlantCADView::Stick3leaves_bmpOutput(CString strPath)
{
	
}



void CPlantCADView::OnInitialUpdate()
{
	CGLEnableView::OnInitialUpdate();
	CMainFrame *pMainWnd=(CMainFrame*)AfxGetMainWnd();
    //pMainWnd->mPlantCADView=this;
}


void CPlantCADView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPlantCADDoc* pDoc = GetDocument();
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	ASSERT_VALID(pDoc);

	
	CGLEnableView::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CPlantCADView::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CString strPath;
	UINT nFileNum = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0); // 拖拽文件个数  
	TCHAR strFileName[MAX_PATH]; //定义一个缓冲区，接收文件名字
	for (int i = 0; i < nFileNum; i++)  //支持同时拖拽多个文件
	{
		DragQueryFile(hDropInfo, i, strFileName, MAX_PATH);//获得拖曳的文件名  
		//m_vetFileNames.push_back(strFileName); //m_vetFileNames是一个文档类中的成员变量,std::vector<CString> 保存文件名 
	}
	DragFinish(hDropInfo);      //释放hDrop ，销毁系统为存储拖拽文件的文件名所开辟的内存块
	CPlantCADDoc* pDoc = GetDocument();
	CMainFrame* pMain = (CMainFrame*)AfxGetMainWnd();
	ASSERT_VALID(pDoc);
	//pDoc->ReadFileByDropFiles(strFileName);
	Invalidate(TRUE);//让窗口无效，重绘
	
	CGLEnableView::OnDropFiles(hDropInfo);
}


void CPlantCADView::OnViewbase()
{
	SetViewBasic();
	Invalidate(TRUE);//让窗口无效，重绘
	//CPlantCADDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//pDoc->Invalidate();
}


//线段1：p1p2,线段2：p3p4,交点IntersectP
BOOL CPlantCADView::LineIntersect(Expoint3D p1, Expoint3D p2, Expoint3D p3, Expoint3D p4, Expoint3D& IntersectP)
{
	float x1, x2, x3, x4, y1, y2, y3, y4;
	x1 = p1.x;
	x2 = p2.x;
	x3 = p3.x;
	x4 = p4.x;
	y1 = p1.y;
	y2 = p2.y;
	y3 = p3.y;
	y4 = p4.y;
	//判断两条直线是否平行
	float fK1 = (y1 - y2) / (x1 - x2);
	float fK2 = (y3 - y4) / (x3 - x4);
	if (fabs(fK2 - fK1) < 0.000001)
	{
		return false;
	}
	IntersectP.x = ((x2 - x1) * (x3 - x4) * (y3 - y1) - x3 * (x2 - x1) * (y3 - y4) + x1 * (y2 - y1) * (x3 - x4)) / ((y2 - y1) * (x3 - x4) - (x2 - x1) * (y3 - y4));
	//IntersectP.x = ((x1 - x2) * (x3 * y4 - x4 * y3) - (x3 - x4) * (x1 * y2 - x2 * y1)) / ((x3 - x4) * (y1 - y2) - (x1 - x2) * (y3 - y4));
	//IntersectP.y = ((y1 - y2) * (x3 * y4 - x4 * y3) - (x1 * y2 - x2 * y1) * (y3 - y4)) / ((y1 - y2) * (x3 - x4) - (x1 - x2) * (y3 - y4));
	IntersectP.y = ((y2 - y1) * (y3 - y4) * (x3 - x1) - y3 * (y2 - y1) * (x3 - x4) + y1 * (x2 - x1) * (y3 - y4)) / ((y2 - y1) * (y3 - y4) - (y2 - y1) * (x3 - x4));
	//判断直线的交点
	/*
	float fMinX, fMaxX, fMinY, fMaxY;
	if (x1 < x2)
	{
		fMinX = x1;
		fMaxX = x2;
	}
	else
	{ 
		fMinX = x2;
		fMaxX = x1;
	}

	if (y1 < y2)
	{
		fMinY = y1;
		fMaxY = y2;
	}
	else
	{
		fMinY = y2;
		fMaxY = y1;
	}
	*/
	if (min(p1.x, p2.x) <= IntersectP.x && IntersectP.x <= max(p1.x, p2.x) && min(p1.y, p2.y) <= IntersectP.y && IntersectP.y <= max(p1.y, p2.y))
	{
		if (min(p3.x, p4.x) <= IntersectP.x && IntersectP.x <= max(p3.x, p4.x) && min(p3.y, p4.y) <= IntersectP.y && IntersectP.y <= max(p3.y, p4.y))
		{
			return true;
		}
	}
	/*	
	
	if ((IntersectP.x > fMinX) && (IntersectP.x < fMaxX))
	{
		if ((IntersectP.y > fMinY) && (IntersectP.y < fMaxY))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
	*/
	return FALSE;
}


//判断两线段相交
//https://www.cnblogs.com/tuyang1129/p/9390376.html
//https://blog.csdn.net/zhouzi2018/article/details/81871875
BOOL CPlantCADView::LineIntersect(Expoint3D p1, Expoint3D p2, Expoint3D p3, Expoint3D p4)
{
	Expoint3D p12, p34;
	p12 = p1 - p2;
	p34 = p3 - p4;
	if (p12 * p34 == 0)
	{
		//两线段平行
		return false;
	}
	else
	{
		float num1, num2, num3, num4;
		//num1 = (p1 - p2) * (p1 - p3);
		p12 = p1 - p2;
		p34 = p1 - p3;
		num1 = p12.VecCross(p34);
		//num2 = (p1 - p2) * (p1 - p4);
		p12 = p1 - p2;
		p34 = p1 - p4;
		num2 = p12.VecCross(p34);
		//num3 = (p1 - p3) * (p3 - p4);
		p12 = p1 - p3;
		p34 = p3 - p4;
		num3 = p12.VecCross(p34);
		//num4 = (p2 - p3) * (p3 - p4);
		p12 = p2 - p3;
		p34 = p3 - p4;
		num4 = p12.VecCross(p34);
		if ((num1*num2 < 0 && num3*num4 <= 0) || (num1*num2 <= 0 && num3*num4 < 0))
		{//等于0表示成180度角
			return  true;
		}	
	}
	return false;
}

//点云转化为屏幕坐标
void CPlantCADView::GetALLpcScreenPt(CArray<CPoint, CPoint>&  mPcPreList)
{
	
}

//点云转化为屏幕坐标
void CPlantCADView::GetALLpcScreenPt2(float fMinX,float fMaxX,float fMinY,float fMaxY,CArray<ExEdge, ExEdge>& mPolyEdgeList)
{
	
}