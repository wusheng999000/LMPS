#pragma once

#include <afxtempl.h>
#include "Expoint3D.h"

//预定义类型
#define SURFACE_TYPE_OPEN 80201
#define SURFACE_TYPE_CLOS 80202
#define SPLINE_TYPE_OPEN  80203
#define SPLINE_TYPE_CLOS  80204

//预定义误差范围
#ifndef ZERO
#define ZERO 0.00001
#endif

class AFX_EXT_CLASS CExBSpline
{
public:
	CExBSpline(void);
	virtual ~CExBSpline(void);
	void SetVector(Expoint3D vecs, Expoint3D vece);
	BOOL Init(CArray<Expoint3D,Expoint3D> &p,BOOL m_bItr=TRUE, UINT uType = SPLINE_TYPE_OPEN);
	void SetPace(float mPace);
	BOOL CalcuBSpline();
	void Reset();
protected:
	int CycMinus(int m,int n,int k);
	int CycPlus(int m,int n,int k);
	Expoint3D BSpline(Expoint3D p[4],float node[8],float u);
	Expoint3D BSpline(Expoint3D p[4],float u);
	BOOL GetBSplineCtrlPts(CArray<Expoint3D,Expoint3D> &pMdl,CArray<Expoint3D,Expoint3D> &pCtrl,UINT uType,Expoint3D vecs=Expoint3D(0.0,0.0,0.0),Expoint3D vece=Expoint3D(0.0,0.0,0.0));
	void CacuNode();
	void Gauss(CArray<float,float> &m_a,CArray<float,float> &m_y,CArray<float,float> &m_x);
	void Chase(CArray<float,float> &a,CArray<float,float> &b,CArray<float,float> &c,CArray<float,float> &d,CArray<float,float> &x);
	BOOL GetBSpline();

public:
	CArray<Expoint3D,Expoint3D> pt_Ctrl;        //定义数组存储控制点
	CArray<Expoint3D,Expoint3D> pt_Model;       //定义数组存储型值点
	CArray<Expoint3D,Expoint3D> pt_Inter;       //定义数组存储插值点
	CArray<float,float> m_Node;			        //定义节点矢量
	Expoint3D vec_s;							//定义首端向量
	Expoint3D vec_e;							//定义末端向量
	BOOL m_bVecSpected;						    //标示首末端向量已被设置
	BOOL m_bMdlPtSet;						    //标示型值点已经设置完成
	BOOL m_bCtrlPtSet;						    //标示曲面控制点已经计算获得或设置完成
	BOOL m_bInterPtGot;							//标示曲线插值点已经计算获得
	BOOL m_bInited;								//标示数据已被初始化
	BOOL m_bItrPlt;								//定义曲线为插值曲线
	
	UINT m_uType;								//定义曲线类型
	int	m_nCntMdlPt;						    //定义曲线型值点个数
	int m_nCntCtrlPt;						    //定义曲线控制点个数
	int	m_nCntSplnPt;						    //定义曲线插值点个数
	float m_Pace;							    //定义曲线插值步长
};

class AFX_EXT_CLASS CExBSurface
{
public:
	CExBSurface(void);
	virtual ~CExBSurface(void);
	BOOL SetVector(int nNote,CArray<Expoint3D,Expoint3D> &vecs,CArray<Expoint3D,Expoint3D> &vece);
	BOOL Init(CArray<Expoint3D,Expoint3D> &p,int nCntv,BOOL m_bItr=TRUE,UINT uType=SURFACE_TYPE_OPEN,UINT vType=SURFACE_TYPE_OPEN);
	void SetPace(float uPace,float vPace);
	BOOL CalcuBSurface();
	void Reset();
protected:
	Expoint3D BSpline(Expoint3D p[4],float node[8],float u);
	Expoint3D BSpline(Expoint3D p[4],float u);
	BOOL GetBSurface();
	int CycMinus(int m,int n,int k);
	int CycPlus(int m,int n,int k);
	BOOL GetCtrlPts();
	void CacuNode();
	BOOL GetBSplineCtrlPts(CArray<Expoint3D,Expoint3D> &pMdl,CArray<Expoint3D,Expoint3D> &pCtrl,UINT uType, Expoint3D vecs = Expoint3D(0.0,0.0,0.0), Expoint3D vece = Expoint3D(0.0,0.0,0.0));
	void Gauss(CArray<float,float> &m_a,CArray<float,float> &m_y,CArray<float,float> &m_x);
	void Chase(CArray<float,float> &a,CArray<float,float> &b,CArray<float,float> &c,CArray<float,float> &d,CArray<float,float> &x);

public:
	CArray<Expoint3D,Expoint3D> pt_Ctrl;        //定义数组存储控制点
	CArray<Expoint3D,Expoint3D> pt_Model;       //定义数组存储型值点
	CArray<Expoint3D,Expoint3D> pt_Inter;       //定义数组存储插值点
protected:
	CArray<float,float> m_Node_u;				//定义u向节点矢量
	CArray<float,float> m_Node_v;				//定义v向节点矢量
	CArray<Expoint3D,Expoint3D> vec_us;         //定义u向首端向量组
	CArray<Expoint3D,Expoint3D> vec_ue;         //定义u向末端向量组
	CArray<Expoint3D,Expoint3D> vec_vs;         //定义v向首端向量组
	CArray<Expoint3D,Expoint3D> vec_ve;         //定义v向末端向量组
	BOOL m_bVecSpected_u;						//标示u向首末端向量已被设置
	BOOL m_bVecSpected_v;					    //标示v向首末端向量已被设置
	BOOL m_bMdlPtSet;							//标示型值点已经设置完成
	BOOL m_bCtrlPtSet;						    //标示曲面控制点已经计算获得或设置完成
	BOOL m_bInterPtGot;							//标示曲线插值点已经计算获得
	BOOL m_bInited;								//标示数据已被初始化
	BOOL m_bShowLine;							//标示是否显示线条
	BOOL m_bShowPoint;							//标示是否显示点
	
	BOOL m_bItrPlt;								//定义曲面为插值曲面
	UINT m_uType_u;							    //定义曲面u向类型
	UINT m_uType_v;								//定义曲面v向类型
public:
	int	m_nCntMdlPt_u;						    //定义曲面u向型值点个数
	int	m_nCntMdlPt_v;							//定义曲面v向型值点个数
	int m_nCntCtrlPt_u;							//定义曲面u向控制点个数
	int m_nCntCtrlPt_v;						    //定义曲面v向控制点个数
	int	m_nCntSplnPt_u;							//定义曲面u向插值点个数
	int	m_nCntSplnPt_v;							//定义曲面v向插值点个数
	float m_Pace_u;								//定义曲面u向插值步长
	float m_Pace_v;								//定义曲面v向插值步长
};