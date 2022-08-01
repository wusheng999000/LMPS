// PlantCADDoc.h : CPlantCADDoc 
//

#pragma once
#include "PlantCADView.h"

class CPlantCADDoc : public CDocument
{
protected: 
	CPlantCADDoc();
	DECLARE_DYNCREATE(CPlantCADDoc)


public:


	BOOL m_bPlantFormLoaded;			
	BOOL m_bPlantLifeLoaded;			
	enum ObjectType						
	{
		OBJECT_NULL = 0,				
		MAIZE = 1,						
		WHEAT = 2						
	};
	ObjectType m_uObjectType;
	enum OperationType					
	{
		OPERATION_NULL = 0,				
		PLANTFORM = 1,					
		ORGANDESIGN = 2,				
		COLONYDESIGN = 3,				
		TEMPLDESIGN = 4,				
		MAIZEFAROPC = 5,                
		MAIZEKINECTPC = 6,              
		KINECTDEVICE = 7,              
		MULTIVIEWPC = 8,                
		//CANOPYRESULT = 9				
		SIXLEAFSTAGEPC = 9,             
		PREPROCESS = 10,                
		PROCFLOW = 11,                  
		TURNTABLE = 12,                 
		ORGANSEGMENT = 13,              
		WheatPC = 14,                   
		PhenotypicAnalysis = 15         

	};
	OperationType m_uOperationType;
	enum MouseOperate					
	{
		OPERATE_NULL = 0,				
		OPERATE_NORMAL = 1,				
		OPERATE_DRAW = 2,				
		OPERATE_PICK = 3,				
		OPERATE_MOVE = 4,				
		OPERATE_ROTATE = 5,				
		OPERATE_SCALE = 6
	};
	MouseOperate m_uMouseOperate;
	enum OrganType
	{
		ORGAN_NULL = 0,
		STALK = 1,
		LEAF = 2,
		TASSEL = 3,
		EAR = 4,
		ROOT = 5
	};
	OrganType m_uOrganType;	


	int m_nCntLeaf;
	BOOL m_bLeafDataLoaded;										
	BOOL m_bLeafShowSheath;
	BOOL m_bLeafShowLeaf;
	BOOL m_bLeafShowLeafmdl;
	CPointCloud mPointCloud;

	BOOL m_bLandDataLoaded;										
	
	bool m_bSqenOutput;											
	int m_nOrderSqen;
	HDC m_hDC;


	CString m_sObjectType;										
	CString m_sObjectName;										
	CString m_sObjectVarName;									
	//
	int	m_nCurFrame;					
	int m_nCurObject;					
	int m_nCurView;						
	int m_nCurPointNum;
	int m_nSkelPointNum;
	CString m_strCurPCFileName;
	//System Lights
	float light_ambient[8][4]; 
	float light_position[8][4];
	float light_diffuse[8][4];
	float light_specular[8][4];
	BOOL m_bLightEnable[8];
	BOOL m_bLightFixed;

	BOOL m_bOperateChanged;


	CSceneTexture mTexture;
	CString texPath[SCENE_MAX_TEXTURE];			
	BOOL m_bTextureGenerated;


	ExportOBJFile mObjExport;

	int m_iCurOperationClassObject;
	
public:

	
	void Draw( float unit, UINT mode);
	void InitSystemLights( void );
	void ResetSystem();							
	void InitSystem();
	CView* GetActiveView();
	void Invalidate();
	CString Loaddirectory();
	void GenerateTexture(int nIndex);

	CString GetSysPath();

	//Texture
	void InitTexturePath();


	//
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);


public:
	virtual ~CPlantCADDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


protected:
	DECLARE_MESSAGE_MAP()
public:
	//System & Common

	//SceneToolBar
	afx_msg void OnSceneOrtho();
	afx_msg void OnUpdateSceneOrtho(CCmdUI *pCmdUI);
	afx_msg void OnScenePersp();
	afx_msg void OnUpdateScenePersp(CCmdUI *pCmdUI);
	afx_msg void OnSceneFront();
	afx_msg void OnSceneBack();
	afx_msg void OnSceneLeft();
	afx_msg void OnSceneRight();
	afx_msg void OnSceneTop();
	afx_msg void OnSceneBottom();
	afx_msg void OnSceneTrans();
	afx_msg void OnUpdateSceneTrans(CCmdUI *pCmdUI);
	afx_msg void OnSceneRotXY();
	afx_msg void OnUpdateSceneRotXY(CCmdUI *pCmdUI);
	afx_msg void OnSceneRotYZ();
	afx_msg void OnUpdateSceneRotYZ(CCmdUI *pCmdUI);
	afx_msg void OnSceneRotZX();
	afx_msg void OnUpdateSceneRotZX(CCmdUI *pCmdUI);
	afx_msg void OnSceneScale();
	afx_msg void OnUpdateSceneScale(CCmdUI *pCmdUI);
	afx_msg void OnSceneRepos();
	afx_msg void OnSceneAxis();
	afx_msg void OnUpdateSceneAxis(CCmdUI *pCmdUI);
	afx_msg void OnSceneGridXY();
	afx_msg void OnUpdateSceneGridXY(CCmdUI *pCmdUI);
	afx_msg void OnSceneGridYZ();
	afx_msg void OnUpdateSceneGridYZ(CCmdUI *pCmdUI);
	afx_msg void OnSceneGridZX();
	afx_msg void OnUpdateSceneGridZX(CCmdUI *pCmdUI);
	afx_msg void OnSceneCube();
	afx_msg void OnUpdateSceneCube(CCmdUI *pCmdUI);
	afx_msg void OnSceneText();
	afx_msg void OnUpdateSceneText(CCmdUI *pCmdUI);
	afx_msg void OnSceneLight();
	afx_msg void OnUpdateSceneLight(CCmdUI *pCmdUI);
	afx_msg void OnSceneLightparam();
	afx_msg void OnScenePoint();
	afx_msg void OnUpdateScenePoint(CCmdUI *pCmdUI);
	afx_msg void OnSceneLine();
	afx_msg void OnUpdateSceneLine(CCmdUI *pCmdUI);
	afx_msg void OnScenePolygon();
	afx_msg void OnUpdateScenePolygon(CCmdUI *pCmdUI);
	afx_msg void OnSceneRender();
	afx_msg void OnUpdateSceneRender(CCmdUI *pCmdUI);
	afx_msg void OnSceneProperties();


	

	//Operate
	afx_msg void OnOperateNormal();
	afx_msg void OnUpdateOperateNormal(CCmdUI *pCmdUI);
	afx_msg void OnOperateDraw();
	afx_msg void OnUpdateOperateDraw(CCmdUI *pCmdUI);
	afx_msg void OnOperateDrawpick();
	afx_msg void OnUpdateOperateDrawpick(CCmdUI *pCmdUI);
	afx_msg void OnOperateMove();
	afx_msg void OnUpdateOperateMove(CCmdUI *pCmdUI);
	afx_msg void OnOperateRotate();
	afx_msg void OnUpdateOperateRotate(CCmdUI *pCmdUI);
	afx_msg void OnOperateScale();
	afx_msg void OnUpdateOperateScale(CCmdUI *pCmdUI);

	afx_msg void OnHelp();
	afx_msg void OnLeafvienph();
};


