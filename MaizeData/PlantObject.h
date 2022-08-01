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
	//���ݿ����
	BOOL ReleaseConnection(CDatabase* db);
	void GetDatabaseConnection(CString& dbname , CDatabase* db);
	CString GetSysPath();
	void RecalcuBox();//��ʼ�����ؼ���Box
	void SetShow(bool bShow = true);
public:
	int nOrder;							//���
	int nPlantOrder;					//����ֲ�����
	CString m_sObj;						//����
	CString m_sName;					//����
	CString m_sVarName;					//Ʒ������
	CString m_sTypeName;				//����
	float m_unit;						//��λ
	bool m_bNormal;						//��ʾ�����棬Ĭ������
	ExColor3f mColor;					//��ɫ
	CString msTexturePath;				//����·��
	GLuint* mTexture;					//����ָ����ʼλ��
	int nTextureIndex;					//����������
	BOOL m_bTextureGenerated;
	int nGrowthDay;						//��ǰ����ʱ��
	int	nStartDay;						//��ʼ����ʱ��
	int	nStopDay;						//ֹͣ����ʱ��
	int	nOldDay;						//˥��ʱ��
	int	nEndDay;						//��ֹʱ��

	BOOL m_bObjectCalcued;				//�������
	BOOL m_bParamInited;				//������ɳ�ʼ��
	BOOL m_bKeyParamGenerated;
	BOOL m_bShowNormal;
	BOOL m_bShow;						//�ɼ�
	Expoint3D mBoxVertex[8];			//��Χ�ж��㣬(�ݲ�ʹ�� ExBox)
	BOOL m_bShowBox;					//��ʾ\���ذ�Χ��
	float mLocalCoordin[16];			//�ֲ�����ϵ����
	Expoint3D pBase;					//����
	float mAzim,mElev,mRoll;			//����ŷ���ǣ����㣬����ŷ���Ǳ�������ֲ�����ϵ�����غ�

	//������̬�ṹ
	CArray<Expoint3D,Expoint3D> Vertex;		//����
	CArray<Expoint3D,Expoint3D> Normal;		//����
	CArray<Expoint3D,Expoint3D> Texture;	//����
	CArray<int,int> Face;
	int nHDivide;							//���򻮷���
	int nVDivide;							//���򻮷���

	int nDesignMode;						//���ģʽ��0��̬ģʽ��1��̬ģʽ

	enum DrawMode
	{
		mode_null = 0,
		points = 1,
		line = 2,
		solid = 3,
		render =4
	};
	DrawMode mDrawMode;
	enum LifeState						//�����׶�
	{
		gestation = 0,					//������
		growth = 1,						//������
		mature = 2,						//������
		effete = 3,						//˥����
		wizen = 4						//��ή
	};
	LifeState mLifeState;
	enum GrowthPeriod					//����ʱ��
	{
		seed = 0,						//����
		seedling = 1,					//������
		three = 2,						//��Ҷչ
		joint = 3,						//�ν���
		sbugle = 4,						//С���ȿ���
		bbugle = 5,						//�����ȿ���
		tassel = 6,						//������
		spin = 7,						//��˿��
		milk = 8,						//������
		harvest = 9,					//������
	};
	GrowthPeriod mGrowthPeriod;
};
