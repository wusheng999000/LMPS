#ifndef _EXPOINT3D_H_
#define _EXPOINT3D_H_
#include <math.h>
#include<vector>
#pragma once

class AFX_EXT_CLASS Expoint3D
{
public:
	Expoint3D(void);
	virtual ~Expoint3D(void);
	Expoint3D(float mx,float my, float mz);
	void Supplement(Expoint3D &pt,Expoint3D p);//补充赋值
	void Supplement(Expoint3D &pt);//补充赋值
	void operator =(const Expoint3D &p);
	Expoint3D operator +(const Expoint3D &p);
	Expoint3D operator -(const Expoint3D &p);
	Expoint3D operator ^(const Expoint3D &p);
	Expoint3D operator *(const float t);
	Expoint3D operator /(const float t);
	float operator *(const Expoint3D &p);
	void Set(float px,float py,float pz);
	float DistanceTo(Expoint3D p);
	float AngleTo(Expoint3D p);//夹角，作向量表示
	void Unitize();
	Expoint3D PartTo(Expoint3D p,float t);
	void Rotate(Expoint3D b, int nAxis, float mVal, bool bRad = false );
	Expoint3D Rotate(int nAxis,float mVal,BOOL bRad = FALSE);
	Expoint3D Rotate(Expoint3D b, Expoint3D p, int nAxis, float mVal, BOOL bRad = FALSE);
	Expoint3D CardinalTo(Expoint3D p0,Expoint3D p1,Expoint3D p2,Expoint3D p3,float t,float a);
	float Mode();
	Expoint3D Normal(Expoint3D p);//正交向量
	float DisPointToLine(Expoint3D p1,Expoint3D pt);//点到直线之间的距离
													
	float VecCross(Expoint3D p1);//向量叉乘
public:
	float x,y,z;//坐标
	float r,g,b;//颜色
	int iIntensity;//反射强度
    int iPointOne;//三个临接点
	int iPointTow;//三个临接点
	int iPointThree;//三个临接点
	int iCntConnect;//连通数
	int iOrder;//点序列
    int iDensity;//密度
	BOOL bShow;//是否高亮显示
	BOOL bLink;//是否已连接
    float fRadius;
	float  curvature;//曲率
	float  windingRate;//绕率
	std::vector<int> NodeList;//节点的连接边节点
};

class AFX_EXT_CLASS ExColor3f
{
public:
	ExColor3f(void);
	virtual ~ExColor3f(void);
	ExColor3f(float mr,float mg, float mb);

	void SetColor( ExColor3f color );
	void SetColor(float mr,float mg, float mb);

	void SetREFColor( COLORREF rf );
	ExColor3f GetColor();
	ExColor3f PartTo(ExColor3f clr, float rate);
	void GetColorREFRGB(int& refR, int& refG, int& refB);
	COLORREF GetREFColor();

public:
	float r,g,b;
    int iOrder;//编号
};

class AFX_EXT_CLASS ExColor3i
{
public:
	ExColor3i(void);
	virtual ~ExColor3i(void);
	ExColor3i(int mr,int mg, int mb);

	void SetColor( ExColor3i color );
	void SetColor(int mr,int mg, int mb);
	ExColor3i GetColor();
public:
	int r,g,b;
};

//边
class AFX_EXT_CLASS ExEdge
{
public:
	ExEdge(void);
	virtual ~ExEdge(void);
	ExEdge(int iPoint1, int iPoint2, BOOL mLink = TRUE);
public:
	int iP1;//边的节点编号，在点云中的编号
	int iP2;//边的节点编号，在点云中的编号
	int iOrderP1;//iP1在有向图中的编号
	int iOrderP2;//iP2在有向图中的编号
	float fEdgeLength;//边长度
	BOOL mLinkEdge;//连接边
};

class AFX_EXT_CLASS ExTriangle
{
public:
	ExTriangle(void);
	virtual ~ExTriangle(void);
	ExTriangle(Expoint3D pt0,Expoint3D pt1, Expoint3D pt2);

	void SetVertex(Expoint3D pt0,Expoint3D pt1, Expoint3D pt2);
	void SetNormal(Expoint3D nm0,Expoint3D nm1, Expoint3D nm2);
	void SetTexture(Expoint3D tx0,Expoint3D tx1, Expoint3D tx2);
	void CalcuNormal();
	ExTriangle Offset(float mOffset);
public:
	Expoint3D v0,v1,v2,v3;		//中心点，顶点
	Expoint3D n;				//法向
	Expoint3D n0,n1,n2;			//法向
	Expoint3D t0,t1,t2;			//法向
	ExColor3f clr;
};

class AFX_EXT_CLASS ExBox
{
public:
	ExBox(void);
	virtual ~ExBox(void);
	ExBox(Expoint3D pt[8]);
	ExBox(Expoint3D p0,Expoint3D p1,Expoint3D p2,Expoint3D p3,\
		Expoint3D p4,Expoint3D p5,Expoint3D p6,Expoint3D p7);
	void SetBox(Expoint3D pt[8]);
	void SetBox(Expoint3D p0,Expoint3D p1,Expoint3D p2,Expoint3D p3,\
		Expoint3D p4,Expoint3D p5,Expoint3D p6,Expoint3D p7);
	void SetColor(ExColor3f mClr);

public:
	Expoint3D p[8];
	ExColor3f clr;
};
class AFX_EXT_CLASS CPosition
{
public:
	CPosition(double _x, double _y, double _z) { x = _x; y = _y; z = _z; }
	CPosition() {};
	bool operator==(const CPosition & pt) { return (x == pt.x && y == pt.y && z == pt.z); }
public:
	double  x;
	double  y;
	double  z;
	double  dCurvature;//曲率
	double  dWindingRate;//绕率
} ;

#endif