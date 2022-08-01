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


// CPlantCADDoc ����/����

CPlantCADDoc::CPlantCADDoc()
{
	// TODO: �ڴ����һ���Թ������
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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}


// CPlantCADDoc ���л�

void CPlantCADDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CPlantCADDoc ���

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


// CPlantCADDoc ����

//System Scene



void CPlantCADDoc::ResetSystem()
{
	//����ϵͳ
	
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuLight();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneLight(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOrtho();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneOrtho(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuPersp();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateScenePersp(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuFront();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneBack()
{
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuBack();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneLeft()
{
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuLeft();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneRight()
{
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuRight();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneTop()
{
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuTop();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneBottom()
{
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuBottom();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneTrans()
{
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuTrans();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneTrans(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuRotxy();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneRotXY(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuRotyz();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneRotYZ(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuRotzx();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneRotZX(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuScale();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneScale(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuProperty();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneRepos()
{
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuReset();
	}
	Invalidate();
}

void CPlantCADDoc::OnSceneAxis()
{
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuAxis();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneAxis(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuGridxy();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneGridXY(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuGridyz();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneGridYZ(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuGridzx();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneGridZX(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuCube();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneCube(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuText();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneText(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuSwmdpoint();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateScenePoint(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuSwmdline();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneLine(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuSwmdpoly();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateScenePolygon(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���������������
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuSwmdrander();
	}
	Invalidate();
}

void CPlantCADDoc::OnUpdateSceneRender(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
{//��ȡϵͳĿ¼��Exe��Image��Database���ϼ�
	CString strPath;
	TCHAR exeFullPath[500]; //
	GetModuleFileName(NULL,exeFullPath,500);//�õ�����ģ�����ƣ�ȫ·��
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
	// TODO: �ڴ���������������
	m_uMouseOperate = OPERATE_NORMAL;
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOpersel();
	}
}

void CPlantCADDoc::OnUpdateOperateNormal(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if( m_uMouseOperate == OPERATE_NORMAL )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateDraw()
{
	// TODO: �ڴ���������������
	m_uMouseOperate = OPERATE_DRAW;

	
}

void CPlantCADDoc::OnUpdateOperateDraw(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if( m_uMouseOperate == OPERATE_DRAW )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateDrawpick()
{
	// TODO: �ڴ���������������
	m_uMouseOperate = OPERATE_PICK;
}

void CPlantCADDoc::OnUpdateOperateDrawpick(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if(m_uMouseOperate == OPERATE_PICK)
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateMove()
{
	// TODO: �ڴ���������������
	m_uMouseOperate = OPERATE_MOVE;
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOpertra();
	}
}

void CPlantCADDoc::OnUpdateOperateMove(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if( m_uMouseOperate == OPERATE_MOVE )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateRotate()
{
	// TODO: �ڴ���������������
	m_uMouseOperate = OPERATE_ROTATE;
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOperrot();
	}
}

void CPlantCADDoc::OnUpdateOperateRotate(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if( m_uMouseOperate == OPERATE_ROTATE )
		pCmdUI->SetCheck(TRUE);
	else
		pCmdUI->SetCheck(FALSE);
}

void CPlantCADDoc::OnOperateScale()
{
	// TODO: �ڴ���������������
	m_uMouseOperate = OPERATE_SCALE;
	if(m_nCurView == 0 )
	{
		((CPlantCADView*)GetActiveView())->OnRviewmenuOpersca();
	}
}

void CPlantCADDoc::OnUpdateOperateScale(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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



//��ȡ�ļ���·��
CString CPlantCADDoc::Loaddirectory()
{
	CString sFolderPath;//ģ���ļ���·��
	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	//��ʼ����ڲ���bi��ʼ
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;//��ʼ���ƶ���rootĿ¼�ܲ����ף�
	bi.pszDisplayName = (LPWSTR)Buffer;//�˲�����ΪNULL������ʾ�Ի���
	bi.lpszTitle = L"ѡ�����ݱ����ļ���";
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;//�����ļ�
	bi.ulFlags = BIF_EDITBOX;//�����ļ�
	bi.lpfn = NULL;
	//��ʼ����ڲ���bi����
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);//������ʾѡ��Ի���
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, (LPWSTR)Buffer);
		//ȡ���ļ���·����Buffer��
		sFolderPath.Format(L"%s", Buffer);
	}
	LPMALLOC lpMalloc;
	if (FAILED(SHGetMalloc(&lpMalloc))) return L"";
	//�ͷ��ڴ�
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
