#pragma once
#include "plantobject.h"
#include "glMath.h"
#define WM_POINTCLOUD_CHANGE WM_USER + 1010			//
#define WM_POINTCLOUD_LOADMODEL WM_USER + 1011			//
#define WM_POINTCLOUD_OPERUNDO WM_USER + 1012
class AFX_EXT_CLASS CPointCloud
{
public:
	CPointCloud(void);
	~CPointCloud(void);
public:
	virtual void Draw( float unit, UINT mode = 2 );	
	void drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius = 10.0, GLfloat M = 20, GLfloat N = 20, ExColor3f mColor = ExColor3f(0.5f, 0.5f, 0.0f));
	virtual void InitPointCloud();
	void SortPointCloud(CArray<Expoint3D, Expoint3D>& mP3DList, int iAxis = 3);
	Expoint3D LoadPrimitivePC(CString strPath, CArray<Expoint3D, Expoint3D>& mPC, bool bRGB = false, bool bRGBINT = false, bool bIntensity = false, bool bNormal = false);
	
	BOOL LoadLPLSPointCloudData();
	
	BOOL LoadLPLSPointCloudData(CString strPath);
	
	BOOL SavePC(CArray<Expoint3D, Expoint3D>& mPC, CString strPath, BOOL bRGB);
public:
	Expoint3D TranslationOrigin(CArray<Expoint3D, Expoint3D>& P3DList);
	void TranslationPrimitivePointCloud(float fX, float fY, float fZ);
	void TranslationPointCloud(CArray<Expoint3D, Expoint3D>& P3DList, Expoint3D mPoint3D);
	void ModifiedRatioPointCloud(CArray<Expoint3D, Expoint3D>& P3DList, float fScale);
	void IteraCurveSmooth3D();
	void CurveSmooth3D(CArray<Expoint3D, Expoint3D>& mPt, CArray<Expoint3D, Expoint3D>& mPted);
	void LeafBasePlane(CArray<Expoint3D, Expoint3D>& mLeafPt);
	void LinearFit2D(CArray<Expoint3D, Expoint3D>& mPointCloud);
	void SectionalCurvature(float& mCur, float& fCur, float& mWind, float& fWind);
public:
	CString m_strFileName;
	CString m_strFilePath;
	float mboundingBoxMin[3];
	float mboundingBoxMax[3]; 
	BOOL m_bPoint3DList;
	BOOL m_bPrimitivePoint;
	BOOL m_bStick3leavesPri;
	CArray<Expoint3D,Expoint3D> mPrimitivePoint3DList;
	CArray<Expoint3D,Expoint3D> mPoint3DList;	    
	CArray<float,float>         mPoint3DCurvatureList;
	float m_unitScan;
	
	float m_vecCoefficients[4];
	BOOL m_bShowKPath;
	BOOL m_bShowShortestPath;
	CArray<Expoint3D, Expoint3D> mStick3leavesVeinXOZList[3];
	CArray<Expoint3D, Expoint3D> mStick3leavesList[4];
	CArray<Expoint3D, Expoint3D> mStick3leavesVeinList[3];
	Expoint3D  mFitLine[2];
	CArray<Expoint3D, Expoint3D> mLeafNerMdlSplineList;
	CArray<int, int> mInterPList;
	CArray<int, int> mCurvatureList;
	

};
