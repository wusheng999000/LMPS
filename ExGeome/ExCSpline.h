#pragma once
#include <afxtempl.h>
#include "Expoint3D.h"

//预定义类型

class AFX_EXT_CLASS CExCSpline
{
public:
	CExCSpline(void);
	~CExCSpline(void);

	void CalcuCSpline();
	BOOL Init(CArray<Expoint3D,Expoint3D> &p,BOOL bClosed = FALSE);
	void SetVector(Expoint3D vecStart,Expoint3D vecEnd);
	void SetA(float ma);
	void SetPace(float pace);
	void Reset();

public:
	CArray<Expoint3D,Expoint3D> pt_Model;       //定义数组存储型值点
	CArray<Expoint3D,Expoint3D> pt_Inter;       //定义数组存储插值点
	BOOL m_bInited;
	BOOL m_bCalcued;
	BOOL m_bClosed;
private:
	float a;
	float mPace;
};

class AFX_EXT_CLASS CExCSurface
{
public:
	CExCSurface(void);
	~CExCSurface(void);

	void CalcuCSurface();
	void SetA(float mau,float mav);
	void SetPace(float upace, float vpace);
	BOOL Init(CArray<Expoint3D,Expoint3D> &p,int nCntR, BOOL bUClosed = FALSE, BOOL bVClosed = FALSE, BOOL bULinear = FALSE, BOOL bVLinear = FALSE);
	BOOL SetVector(BOOL bU,CArray<Expoint3D,Expoint3D> &vecStart,CArray<Expoint3D,Expoint3D> &vecEnd);
	void Reset();
public:
	CArray<Expoint3D,Expoint3D> pt_Model;       //定义数组存储型值点
	CArray<Expoint3D,Expoint3D> pt_Inter;       //定义数组存储插值点
	int nCntModelU;								//点的排数
	int nCntModelV;								//点的排数
	int nCntInterU;
	int nCntInterV;
	BOOL m_bULinear;
	BOOL m_bVLinear;
	BOOL m_bUClosed;
	BOOL m_bVClosed;
	BOOL m_bInited;
	BOOL m_bCalcued;
private:
	float aU;
	float aV;
	float mUPace;
	float mVPace;
};
