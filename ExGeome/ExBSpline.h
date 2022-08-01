#pragma once

#include <afxtempl.h>
#include "Expoint3D.h"

//Ԥ��������
#define SURFACE_TYPE_OPEN 80201
#define SURFACE_TYPE_CLOS 80202
#define SPLINE_TYPE_OPEN  80203
#define SPLINE_TYPE_CLOS  80204

//Ԥ������Χ
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
	CArray<Expoint3D,Expoint3D> pt_Ctrl;        //��������洢���Ƶ�
	CArray<Expoint3D,Expoint3D> pt_Model;       //��������洢��ֵ��
	CArray<Expoint3D,Expoint3D> pt_Inter;       //��������洢��ֵ��
	CArray<float,float> m_Node;			        //����ڵ�ʸ��
	Expoint3D vec_s;							//�����׶�����
	Expoint3D vec_e;							//����ĩ������
	BOOL m_bVecSpected;						    //��ʾ��ĩ�������ѱ�����
	BOOL m_bMdlPtSet;						    //��ʾ��ֵ���Ѿ��������
	BOOL m_bCtrlPtSet;						    //��ʾ������Ƶ��Ѿ������û��������
	BOOL m_bInterPtGot;							//��ʾ���߲�ֵ���Ѿ�������
	BOOL m_bInited;								//��ʾ�����ѱ���ʼ��
	BOOL m_bItrPlt;								//��������Ϊ��ֵ����
	
	UINT m_uType;								//������������
	int	m_nCntMdlPt;						    //����������ֵ�����
	int m_nCntCtrlPt;						    //�������߿��Ƶ����
	int	m_nCntSplnPt;						    //�������߲�ֵ�����
	float m_Pace;							    //�������߲�ֵ����
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
	CArray<Expoint3D,Expoint3D> pt_Ctrl;        //��������洢���Ƶ�
	CArray<Expoint3D,Expoint3D> pt_Model;       //��������洢��ֵ��
	CArray<Expoint3D,Expoint3D> pt_Inter;       //��������洢��ֵ��
protected:
	CArray<float,float> m_Node_u;				//����u��ڵ�ʸ��
	CArray<float,float> m_Node_v;				//����v��ڵ�ʸ��
	CArray<Expoint3D,Expoint3D> vec_us;         //����u���׶�������
	CArray<Expoint3D,Expoint3D> vec_ue;         //����u��ĩ��������
	CArray<Expoint3D,Expoint3D> vec_vs;         //����v���׶�������
	CArray<Expoint3D,Expoint3D> vec_ve;         //����v��ĩ��������
	BOOL m_bVecSpected_u;						//��ʾu����ĩ�������ѱ�����
	BOOL m_bVecSpected_v;					    //��ʾv����ĩ�������ѱ�����
	BOOL m_bMdlPtSet;							//��ʾ��ֵ���Ѿ��������
	BOOL m_bCtrlPtSet;						    //��ʾ������Ƶ��Ѿ������û��������
	BOOL m_bInterPtGot;							//��ʾ���߲�ֵ���Ѿ�������
	BOOL m_bInited;								//��ʾ�����ѱ���ʼ��
	BOOL m_bShowLine;							//��ʾ�Ƿ���ʾ����
	BOOL m_bShowPoint;							//��ʾ�Ƿ���ʾ��
	
	BOOL m_bItrPlt;								//��������Ϊ��ֵ����
	UINT m_uType_u;							    //��������u������
	UINT m_uType_v;								//��������v������
public:
	int	m_nCntMdlPt_u;						    //��������u����ֵ�����
	int	m_nCntMdlPt_v;							//��������v����ֵ�����
	int m_nCntCtrlPt_u;							//��������u����Ƶ����
	int m_nCntCtrlPt_v;						    //��������v����Ƶ����
	int	m_nCntSplnPt_u;							//��������u���ֵ�����
	int	m_nCntSplnPt_v;							//��������v���ֵ�����
	float m_Pace_u;								//��������u���ֵ����
	float m_Pace_v;								//��������v���ֵ����
};