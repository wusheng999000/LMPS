// PlantCADDoc.cpp : CPlantCADDoc 
//
#include "stdafx.h"
#include "PlantCAD.h"
#include "Mainfrm.h"
#include "PlantCADDoc.h"
#include "PlantCADView.h"
#include <locale>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CPlantCADDoc

IMPLEMENT_DYNCREATE(CPlantCADDoc, CDocument)

BEGIN_MESSAGE_MAP(CPlantCADDoc, CDocument)
	//Scene
	ON_COMMAND(ID_SCENE_ORTHO, &CPlantCADDoc::OnSceneOrtho)
	ON_UPDATE_COMMAND_UI(ID_SCENE_ORTHO, &CPlantCADDoc::OnUpdateSceneOrtho)
	ON_COMMAND(ID_SCENE_PERSP, &CPlantCADDoc::OnScenePersp)
	ON_UPDATE_COMMAND_UI(ID_SCENE_PERSP, &CPlantCADDoc::OnUpdateScenePersp)
	ON_COMMAND(ID_SCENE_FRONT, &CPlantCADDoc::OnSceneFront)
	ON_COMMAND(ID_SCENE_BACK, &CPlantCADDoc::OnSceneBack)
	ON_COMMAND(ID_SCENE_LEFT, &CPlantCADDoc::OnSceneLeft)
	ON_COMMAND(ID_SCENE_RIGHT, &CPlantCADDoc::OnSceneRight)
	ON_COMMAND(ID_SCENE_TOP, &CPlantCADDoc::OnSceneTop)
	ON_COMMAND(ID_SCENE_BOTTOM, &CPlantCADDoc::OnSceneBottom)
	ON_COMMAND(ID_SCENE_TRANS, &CPlantCADDoc::OnSceneTrans)
	ON_UPDATE_COMMAND_UI(ID_SCENE_TRANS, &CPlantCADDoc::OnUpdateSceneTrans)
	ON_COMMAND(ID_SCENE_ROTXY, &CPlantCADDoc::OnSceneRotXY)
	ON_UPDATE_COMMAND_UI(ID_SCENE_ROTXY, &CPlantCADDoc::OnUpdateSceneRotXY)
	ON_COMMAND(ID_SCENE_ROTYZ, &CPlantCADDoc::OnSceneRotYZ)
	ON_UPDATE_COMMAND_UI(ID_SCENE_ROTYZ, &CPlantCADDoc::OnUpdateSceneRotYZ)
	ON_COMMAND(ID_SCENE_ROTZX, &CPlantCADDoc::OnSceneRotZX)
	ON_UPDATE_COMMAND_UI(ID_SCENE_ROTZX, &CPlantCADDoc::OnUpdateSceneRotZX)
	ON_COMMAND(ID_SCENE_SCALE, &CPlantCADDoc::OnSceneScale)
	ON_UPDATE_COMMAND_UI(ID_SCENE_SCALE, &CPlantCADDoc::OnUpdateSceneScale)
	ON_COMMAND(ID_SCENE_REPOS, &CPlantCADDoc::OnSceneRepos)
	ON_COMMAND(ID_SCENE_AXIS, &CPlantCADDoc::OnSceneAxis)
	ON_UPDATE_COMMAND_UI(ID_SCENE_AXIS, &CPlantCADDoc::OnUpdateSceneAxis)
	ON_COMMAND(ID_SCENE_GRIDXY, &CPlantCADDoc::OnSceneGridXY)
	ON_UPDATE_COMMAND_UI(ID_SCENE_GRIDXY, &CPlantCADDoc::OnUpdateSceneGridXY)
	ON_COMMAND(ID_SCENE_GRIDYZ, &CPlantCADDoc::OnSceneGridYZ)
	ON_UPDATE_COMMAND_UI(ID_SCENE_GRIDYZ, &CPlantCADDoc::OnUpdateSceneGridYZ)
	ON_COMMAND(ID_SCENE_GRIDZX, &CPlantCADDoc::OnSceneGridZX)
	ON_UPDATE_COMMAND_UI(ID_SCENE_GRIDZX, &CPlantCADDoc::OnUpdateSceneGridZX)
	ON_COMMAND(ID_SCENE_CUBE, &CPlantCADDoc::OnSceneCube)
	ON_UPDATE_COMMAND_UI(ID_SCENE_CUBE, &CPlantCADDoc::OnUpdateSceneCube)
	ON_COMMAND(ID_SCENE_TEXT, &CPlantCADDoc::OnSceneText)
	ON_UPDATE_COMMAND_UI(ID_SCENE_TEXT, &CPlantCADDoc::OnUpdateSceneText)
	ON_COMMAND(ID_SCENE_LIGHT, &CPlantCADDoc::OnSceneLight)
	ON_UPDATE_COMMAND_UI(ID_SCENE_LIGHT, &CPlantCADDoc::OnUpdateSceneLight)
	ON_COMMAND(ID_SCENE_LIGHTPARAM, &CPlantCADDoc::OnSceneLightparam)
	ON_COMMAND(ID_SCENE_POINT, &CPlantCADDoc::OnScenePoint)
	ON_UPDATE_COMMAND_UI(ID_SCENE_POINT, &CPlantCADDoc::OnUpdateScenePoint)
	ON_COMMAND(ID_SCENE_LINE, &CPlantCADDoc::OnSceneLine)
	ON_UPDATE_COMMAND_UI(ID_SCENE_LINE, &CPlantCADDoc::OnUpdateSceneLine)
	ON_COMMAND(ID_SCENE_POLYGON, &CPlantCADDoc::OnScenePolygon)
	ON_UPDATE_COMMAND_UI(ID_SCENE_POLYGON, &CPlantCADDoc::OnUpdateScenePolygon)
	ON_COMMAND(ID_SCENE_RENDER, &CPlantCADDoc::OnSceneRender)
	ON_UPDATE_COMMAND_UI(ID_SCENE_RENDER, &CPlantCADDoc::OnUpdateSceneRender)
	ON_COMMAND(ID_SCENE_PROPERTIES, &CPlantCADDoc::OnSceneProperties)

	//Main
	//Tree & Property

	//Operate
	ON_COMMAND(ID_OPERATE_NORMAL, &CPlantCADDoc::OnOperateNormal)
	ON_UPDATE_COMMAND_UI(ID_OPERATE_NORMAL, &CPlantCADDoc::OnUpdateOperateNormal)
	ON_COMMAND(ID_OPERATE_DRAW, &CPlantCADDoc::OnOperateDraw)
	ON_UPDATE_COMMAND_UI(ID_OPERATE_DRAW, &CPlantCADDoc::OnUpdateOperateDraw)
	ON_COMMAND(ID_OPERATE_PICK, &CPlantCADDoc::OnOperateDrawpick)
	ON_UPDATE_COMMAND_UI(ID_OPERATE_PICK, &CPlantCADDoc::OnUpdateOperateDrawpick)
	ON_COMMAND(ID_OPERATE_MOVE, &CPlantCADDoc::OnOperateMove)
	ON_UPDATE_COMMAND_UI(ID_OPERATE_MOVE, &CPlantCADDoc::OnUpdateOperateMove)
	ON_COMMAND(ID_OPERATE_ROTATE, &CPlantCADDoc::OnOperateRotate)
	ON_UPDATE_COMMAND_UI(ID_OPERATE_ROTATE, &CPlantCADDoc::OnUpdateOperateRotate)
	ON_COMMAND(ID_OPERATE_SCALE, &CPlantCADDoc::OnOperateScale)
	ON_UPDATE_COMMAND_UI(ID_OPERATE_SCALE, &CPlantCADDoc::OnUpdateOperateScale)
	ON_COMMAND(ID_HELP, &CPlantCADDoc::OnHelp)
	ON_COMMAND(ID_LeafVienPh, &CPlantCADDoc::OnLeafvienph)
END_MESSAGE_MAP()


// CPlantCADDoc 构造/析构

CPlantCADDoc::CPlantCADDoc()
{
	// TODO: 在此添加一次性构造代码
	InitSystem();
}

CPlantCADDoc::~CPlantCADDoc()
{
	//	ResetSystem();
	
}

BOOL CPlantCADDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}


// CPlantCADDoc 序列化

void CPlantCADDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CPlantCADDoc 诊断

#ifdef _DEBUG
void CPlantCADDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPlantCADDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPlantCADDoc 命令

//System Scene



void CPlantCADDoc::ResetSystem()
{
	//重置系统
	
	InitSystemLights();
	InitTexturePath();
	Invalidate();
}

void CPlantCADDoc::InitSystem()
{
	InitSystemLights();
	InitTexturePath();
	Invalidate();
}

void CPlantCADDoc::InitSystemLights(void)
{
	for( int i = 0; i < 8; i++ )
	{
		light_ambient[i][0] = 0.5f; 
		light_ambient[i][1] = 0.5f; 
		light_ambient[i][2] = 0.5f; 
		light_ambient[i][3] = 1.0f; 

		light_diffuse[i][0] = 0.5f; 
		light_diffuse[i][1] = 0.5f; 
		light_diffuse[i][2] = 0.5f; 
		light_diffuse[i][3] = 1.0f; 

		light_specular[i][0] = 0.5f; 
		light_specular[i][1] = 0.5f; 
		light_specular[i][2] = 0.5f; 
		light_specular[i][3] = 1.0f; 

		light_position[i][0] = 10000.0f; 
		light_position[i][1] = 10000.0f;  
		light_position[i][2] = 10000.0f;  
		light_position[i][3] = 0.0f;  

		m_bLightEnable[i] = FALSE;
	}
	m_bLightEnable[0] = TRUE;
}

void CPlantCADDoc::OnSceneLightparam()
{
	
}

void CPlantCADDoc::OnSceneLight()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuLight();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneLight(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_bLighting )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneOrtho()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOrtho();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneOrtho(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nViewType == 0 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnScenePersp()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuPersp();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateScenePersp(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nViewType == 1 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneFront()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuFront();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneBack()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuBack();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneLeft()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuLeft();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneRight()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuRight();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneTop()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuTop();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneBottom()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuBottom();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneTrans()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuTrans();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneTrans(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nSceneOperateType == 1 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneRotXY()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuRotxy();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneRotXY(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nSceneOperateType == 2 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneRotYZ()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuRotyz();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneRotYZ(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nSceneOperateType == 3 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneRotZX()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuRotzx();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneRotZX(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nSceneOperateType == 4 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneScale()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuScale();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneScale(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nSceneOperateType == 5 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneProperties()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuProperty();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneRepos()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuReset();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneAxis()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuAxis();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneAxis(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_bShowAxis )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneGridXY()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuGridxy();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneGridXY(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_bShowGridXY )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneGridYZ()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuGridyz();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneGridYZ(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_bShowGridYZ )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneGridZX()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuGridzx();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneGridZX(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_bShowGridZX )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneCube()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuCube();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneCube(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_bShowCube )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneText()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuText();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneText(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_bShowText )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnScenePoint()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuSwmdpoint();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateScenePoint(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nShowMode == 1 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneLine()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuSwmdline();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneLine(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nShowMode == 2 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnScenePolygon()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuSwmdpoly();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateScenePolygon(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nShowMode == 3 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

void CPlantCADDoc::OnSceneRender()
{
	// TODO: 在此添加命令处理程序代码
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuSwmdrander();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneRender(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	BOOL m_bVal = FALSE;
	if(m_nCurView == 0 )
	{
		if( ((CPlantCADView*)GetActiveView())->m_nShowMode == 4 )
			m_bVal = TRUE;
		else
			m_bVal = FALSE;
	}
	pCmdUI->SetCheck(m_bVal);
}

CView* CPlantCADDoc::GetActiveView()
{
	CView* pView = NULL;
	POSITION pos = GetFirstViewPosition();
	while( pos != NULL)
	{
		pView = (CView*)GetNextView(pos);
		if( m_nCurView == 0 && pView->GetRuntimeClass() == RUNTIME_CLASS(CPlantCADView))
		{
			return pView;
		}
	}
	return pView;
}


/////////////////////////////////////////////////////////////
///////// Texture
/////////////////////////////////////////////////////////////

void CPlantCADDoc::GenerateTexture(int nIndex)
{
	;
}

void CPlantCADDoc::InitTexturePath()
{
	texPath[0] = GetSysPath() + _T("/Images/stalk.bmp");
	texPath[1] = GetSysPath() + _T("/Images/sheath.bmp");
	texPath[2] = GetSysPath() + _T("/Images/leaf.bmp");
	texPath[3] = GetSysPath() + _T("/Images/bract.bmp");
	texPath[4] = GetSysPath() + _T("/Images/land.bmp");
	texPath[5] = GetSysPath() + _T("/Images/sensor.bmp");
	texPath[6] = _T("");
	texPath[7] = _T("");
	texPath[8] = _T("");
	texPath[9] = _T("");
}

CString CPlantCADDoc::GetSysPath()
{//获取系统目录，Exe、Image、Database的上级
	CString strPath;
	TCHAR exeFullPath[500]; //
	GetModuleFileName(NULL,exeFullPath,500);//得到程序模块名称，全路径
	strPath = exeFullPath;
	int i = 0, j = 0, k = 0, n = strPath.GetLength();
	for( i = 0; i < n; i++ )
	{
		if( strPath.GetAt(i) == '\\' )
			strPath.SetAt(i,'/');
	}
	for( i = n-1; i >= 0; i-- )
	{
		j++;
		if( strPath.GetAt(i) == '/' )
			k++;
		if( k == 2 )
		{
			strPath = strPath.Left(n-j);
			return strPath;
		}
	}
	return _T("");
}


////////////////////////////////////////////////////////////////
////////Operate
////////////////////////////////////////////////////////////////

void CPlantCADDoc::OnOperateNormal()
{
	// TODO: 在此添加命令处理程序代码
	m_uMouseOperate = OPERATE_NORMAL;
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOpersel();
	}
}

void CPlantCADDoc::OnUpdateOperateNormal(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if( m_uMouseOperate == OPERATE_NORMAL )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateDraw()
{
	// TODO: 在此添加命令处理程序代码
	m_uMouseOperate = OPERATE_DRAW;

	
}

void CPlantCADDoc::OnUpdateOperateDraw(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if( m_uMouseOperate == OPERATE_DRAW )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateDrawpick()
{
	// TODO: 在此添加命令处理程序代码
	m_uMouseOperate = OPERATE_PICK;
}

void CPlantCADDoc::OnUpdateOperateDrawpick(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if(m_uMouseOperate == OPERATE_PICK)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateMove()
{
	// TODO: 在此添加命令处理程序代码
	m_uMouseOperate = OPERATE_MOVE;
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOpertra();
	}
}

void CPlantCADDoc::OnUpdateOperateMove(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if( m_uMouseOperate == OPERATE_MOVE )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateRotate()
{
	// TODO: 在此添加命令处理程序代码
	m_uMouseOperate = OPERATE_ROTATE;
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOperrot();
	}
}

void CPlantCADDoc::OnUpdateOperateRotate(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if( m_uMouseOperate == OPERATE_ROTATE )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateScale()
{
	// TODO: 在此添加命令处理程序代码
	m_uMouseOperate = OPERATE_SCALE;
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOpersca();
	}
}

void CPlantCADDoc::OnUpdateOperateScale(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if( m_uMouseOperate == OPERATE_SCALE )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

/////////////////////////////////////////////////////////////////////




void CPlantCADDoc::Draw( float unit, UINT mode )
{

	mPointCloud.Draw(unit,mode);
	
}



void CPlantCADDoc::Invalidate()
{
	CPlantCADView* pView = (CPlantCADView*)GetActiveView();
	CString str;
	if (pView != NULL)
	{
		str.Format(_T("%d"), m_nCurPointNum);
		pView->strCurPointNum = str;
		str.Format(_T("%d"), m_nSkelPointNum);
		pView->strSkelPointNum = str;
		pView->strCurPCFileName = m_strCurPCFileName;
	}
	
	UpdateAllViews(FALSE);
}



//获取文件夹路径
CString CPlantCADDoc::Loaddirectory()
{
	CString sFolderPath;//模型文件夹路径
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//初始化入口参数bi开始
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;//初始化制定的root目录很不容易，
	bi.pszDisplayName = (LPWSTR)Buffer;//此参数如为NULL则不能显示对话框
	bi.lpszTitle = L"选择数据保存文件夹";
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//包括文件
	bi.ulFlags = BIF_EDITBOX;//包括文件
	bi.lpfn = NULL;
	//初始化入口参数bi结束
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//调用显示选择对话框
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, (LPWSTR)Buffer);
		//取得文件夹路径到Buffer里
		sFolderPath.Format(L"%s", Buffer);
	}
	LPMALLOC lpMalloc;
	if (FAILED(SHGetMalloc(&lpMalloc))) return L"";
	//释放内存
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
	return sFolderPath;
}


void CPlantCADDoc::OnHelp()
{
	//AfxMessageBox("Please click the menu leafvien-leafvienph firstly.");
}

void CPlantCADDoc::OnLeafvienph()
{
	if (m_uOperationType != MAIZEFAROPC)
	{
		m_bOperateChanged = true;
	}
	m_uOperationType = MAIZEFAROPC;
	CMainFrame* pMain = (CMainFrame*)(AfxGetApp()->m_pMainWnd);
	pMain->mLeafVienDlg.SetObject(&mPointCloud);
	pMain->ChangeDialogBars(0);
}
