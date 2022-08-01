#pragma once
#include "stdafx.h"
#include "gl/gl.h"
#include "gl/glu.h"

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

#ifndef PI
#define PI 3.1416
#endif

#ifndef SCENE_MAX_TEXTURE
#define SCENE_MAX_TEXTURE 10
#endif

class AFX_EXT_CLASS CPlantObject
{
public:
	CPlantObject(void);
	~CPlantObject(void);
	CPlantObject(const CPlantObject &mObject);
	virtual void operator = (const CPlantObject &mObject);
	BOOL GenerateTexture(CString path, GLuint& nIndex);
	float GetCardinalVal(float t, float a, float y[]);
	Expoint3D GetMovePt(Expoint3D p, float mx, float my, float mz);
	Expoint3D GetMovePt(Expoint3D p, Expoint3D pOffset);
	Expoint3D GetRotatePt(Expoint3D p, int nAxis, float mVal, BOOL bRad = FALSE);
	Expoint3D GetRotatePt(Expoint3D b, Expoint3D p, int nAxis, float mVal, BOOL bRad = FALSE);
	Expoint3D GetScalePt(Expoint3D p, float mx, float my = -1.0f, float mz = -1.0f);
	Expoint3D GetScalePt(Expoint3D b, Expoint3D p, float mx, float my = -1.0f, float mz = -1.0f);
	void SetTexturePath( CString strPath );
	void SetTexture( GLuint* tex );
	void SetTextureIndex( int nIndex );
	void Reset();
	void Copy(const CPlantObject& mObject);
	void CopySimple(const CPlantObject& mObject,float scale = 1.0f);
	void CalcuLifeStatus(int nDay = -1);
	BOOL Draw( float unit, UINT mode = 2 );
	void DrawBox( float unit, UINT mode = 2 );
	void Move(Expoint3D offset);
	void Scale( float mRatex, float mRatey = -1.0f, float mRatez = -1.0f );
	void Rotate( int nAxis, float mVal, BOOL bRad = 0 );
	void Scale( Expoint3D base, float mRatex, float mRatey = -1.0f, float mRatez = -1.0f );
	void Rotate( Expoint3D base, int nAxis, float mVal, BOOL bRad = 0 );
	void ReCalculateNormal(BOOL bMark = TRUE);
	void ReCalculateTexture();
	BOOL OutputModel( CString mPath, float unit = 1000.0f, float mScale = 1.0f, int nIndexPlant = 0, int nIndexOrgan = 0,\
		BOOL bVertex = TRUE, BOOL bColor = FALSE, BOOL bNormal = TRUE,\
		BOOL bTexture = TRUE, BOOL bFace = TRUE, BOOL bProp = TRUE );
	bool ConvertToObj( OBJFileData& obj, MTLFileData& mtl, float rate = 1.0f, float scale = 1.0f, bool bNormal = true, bool bTexture = true, bool bFace = true);
	bool ConvertToObjPageOne( OBJFileData& obj, MTLFileData& mtl, float rate = 1.0f, float scale = 1.0f, bool bNormal = true, bool bTexture = true, bool bFace = true, float xStart = 0.0f, float yStart = 0.0f, float xEnd = 1.0f, float yEnd = 1.0f );
	BOOL OutputModelCan( CString mPath, float unit = 1000.0, float mScale = 1.0f, int nIndexPlant = 0, int nIndexOrgan = 0);
	BOOL OutputModelCnt( CString mPath, float unit = 1000.0, int nIndexPlant = 0, int nIndexOrgan = 0);
	BOOL GetFileInfo(CString path, int& nVertex, int& nFace, int& nProp);
	BOOL GetFileInfoCnt(CString path, int& nPiece);
	//数据库操作
	BOOL ReleaseConnection(CDatabase* db);
	void GetDatabaseConnection(CString& dbname , CDatabase* db);
	CString GetSysPath();
	void RecalcuBox();//初始化或重计算Box
	void SetShow(bool bShow = true);
public:
	int nOrder;							//序号
	int nPlantOrder;					//所属植株序号
	CString m_sObj;						//对象
	CString m_sName;					//名称
	CString m_sVarName;					//品种名称
	CString m_sTypeName;				//物种
	float m_unit;						//单位
	bool m_bNormal;						//表示正反面，默认正面
	ExColor3f mColor;					//颜色
	CString msTexturePath;				//纹理路径
	GLuint* mTexture;					//纹理指针起始位置
	int nTextureIndex;					//纹理索引号
	BOOL m_bTextureGenerated;
	int nGrowthDay;						//当前生长时刻
	int	nStartDay;						//开始生长时刻
	int	nStopDay;						//停止生长时刻
	int	nOldDay;						//衰老时刻
	int	nEndDay;						//终止时刻

	BOOL m_bObjectCalcued;				//计算完成
	BOOL m_bParamInited;				//参数完成初始化
	BOOL m_bKeyParamGenerated;
	BOOL m_bShowNormal;
	BOOL m_bShow;						//可见
	Expoint3D mBoxVertex[8];			//包围盒顶点，(暂不使用 ExBox)
	BOOL m_bShowBox;					//显示\隐藏包围盒
	float mLocalCoordin[16];			//局部坐标系矩阵
	Expoint3D pBase;					//基点
	float mAzim,mElev,mRoll;			//三个欧拉角，基点，三个欧拉角表达可能与局部坐标系矩阵重合

	//几何形态结构
	CArray<Expoint3D,Expoint3D> Vertex;		//顶点
	CArray<Expoint3D,Expoint3D> Normal;		//法向
	CArray<Expoint3D,Expoint3D> Texture;	//纹理
	CArray<int,int> Face;
	int nHDivide;							//横向划分数
	int nVDivide;							//纵向划分数

	int nDesignMode;						//设计模式，0静态模式，1动态模式

	enum DrawMode
	{
		mode_null = 0,
		points = 1,
		line = 2,
		solid = 3,
		render =4
	};
	DrawMode mDrawMode;
	enum LifeState						//生命阶段
	{
		gestation = 0,					//孕育期
		growth = 1,						//生长期
		mature = 2,						//成熟期
		effete = 3,						//衰退期
		wizen = 4						//枯萎
	};
	LifeState mLifeState;
	enum GrowthPeriod					//生育时期
	{
		seed = 0,						//播种
		seedling = 1,					//出苗期
		three = 2,						//三叶展
		joint = 3,						//拔节期
		sbugle = 4,						//小喇叭口期
		bbugle = 5,						//大喇叭口期
		tassel = 6,						//抽穗期
		spin = 7,						//吐丝期
		milk = 8,						//乳熟期
		harvest = 9,					//成熟期
	};
	GrowthPeriod mGrowthPeriod;
};
