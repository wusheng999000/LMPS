/////////////////////////////////////////////////////////////////////////////
// glMath.h : Header file; Defines the class definitions
//
// ModelMagic3D and 'glOOP' (OpenGL Object Oriented Programming library)
// Copyright ?ImageWare Development 1997, 2002
//
// OpenGL is a registered trademark of Silicon Graphics
//
//
// This program is provided for educational and personal use only and
// is provided without guarantee or warrantee expressed or implied.
//
// Commercial use is strictly prohibited without written permission
// from ImageWare Development.
//
// This program is -not- in the public domain.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef GLMATH_H_H
#define GLMATH_H_H

#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>
#include <vector>


/////////////////////////////////////////////////////////////////////////////
// glMath Definitions:
//
#define PI				3.14159265f
#define PiOver180		1.74532925199433E-002f
#define PiUnder180		5.72957795130823E+001f
#define DEGTORAD(A)	((A * PI) / 180.0f)
#define RADTODEG(A)	((A * 180.0f) / PI)
#define SMALL_NUMBER	1.0E-6
#define LARGE_NUMBER	1E20

#define X				0	// Used for Coordinate array index
#define Y				1
#define Z				2
#define W				3

#define R				0	// Used for Color array index
#define G				1
#define B				2
#define A				3

#define TS				0	// Used for Texture coordinate array index
#define TT				1
#define TR				2
#define TQ				3

/////////////////////////////////////////////////////////////////////////////
// Type Definitions:
//
typedef GLfloat					VECTORF[4];
typedef GLfloat					COLORF[4];
typedef GLdouble				Matx4x4[4][4];

//人工采集的枝单元标记
struct tBranchUnit
{
	int branchType;//枝标识：0(无)标识连续的单叶，单叶数量；1（A）标识叶簇枝，叶簇枝中叶片个数；2（B）标识在此处有分枝，分枝编号
	int branchNum;//表示上面枝类型后面的数字
};

//人工采集的枝干（枝条）数据
struct tBranchLink
{
	std::vector<tBranchUnit> branchUnitLink;//枝单元链表
	int iBranchNum;//当前枝编号
	int iBranchFather;//父枝条编号
	float fLength;//枝条长度
	float fRadiu;//枝条直径
	~tBranchLink(){branchUnitLink.clear();}
};

// B样条曲线结构变量
struct tSplineOrgan
{
	std::vector<int> pointIndex;	// 控制点在控制点数组中的位置
	GLfloat		m_fColor[4];		// RGBA color component
	int branchType; 
	/*
	0--根主干；
	1--中间主干;
	2--主枝;
	3--长枝；
	4--中枝；
	5--短枝;
	*/
	int level;
	float radiu;	  //半径
	float radiuRatio; //上下半径比例
	int	 topShape;	  //顶部形状 
	/*
	0--尖顶;
	1--斜顶；一般是修剪的结果
	2--平顶;
	*/
	bool bLeaf;	 //是否能着生叶子
	bool bFruit; //是否能着生果实
	bool bTendril;//是否着生卷须
	bool bLateralShoot;	  //是否着生芽/或副梢

	int nParentBranch;	// 父枝条的编号
	int nParentPoint;	// 父节点编号
	int nLevel;			// 在树形结构中的层级（树干为0，往上依次+1）
	bool bUsed;//标记为已使用
	~tSplineOrgan(){pointIndex.clear();}
};
typedef struct tagVector
{
	tagVector(float a = 0, float b = 0, float c = 0)
		:x(a),y(b),z(c)
	{
	}
	union {
		float x;
		float u;
		float r;
	};
	union {
		float y;
		float v;
		float g;
	};
	union {
		float z;
		float w;
		float b;
	};
} tVector;

// 点坐标索引
typedef struct tagVertexIndex
{
	int v0,v1,v2;	//顶点坐标索引
	int t0,t1,t2;	//纹理坐标索引
	int n0,n1,n2;  //法线坐标索引
	//添加Pnt索引
	int nType;		//
	CString sType;
	int nPlant;
	int nOrgan;
	int nOrder;
}tTriangle;

struct Point2
{
	float x;
    float y;
};
/////////////////////////////////////////////////////////////////////////////
// External function prototypes:
//

// 各种数学相关函数
// 得到离x最近的2的n次方值
int Scale_down_to_power_of_2(long x);
// 得到总占用位数
int WordAlign(int n);
// 判断是否为偶数
BOOL IsEven(int n);
BOOL IsEven(float f);
// 得到弧度角
GLfloat Radiansf(GLfloat Angle);
GLdouble Radiansd(GLdouble Angle);
// 得到角度
GLfloat Degreesf(GLfloat Angle);
GLdouble Degreesd(GLdouble Angle);
// 角度计算公式
GLfloat Cosf(GLfloat Angle);
GLdouble Cosd(GLdouble Angle);
GLfloat Sinf(GLfloat Angle);
GLdouble Sind(GLdouble Angle);
GLfloat Tanf(GLfloat Angle);
// Base的Exponent次方
GLfloat Powerf(GLfloat Base, int Exponent);
// 约等于
int Roundf(GLfloat x);
// 约等于 numDecimalPlaces为精度
float Roundf(GLfloat x, int numDecimalPlaces);
// a b差值
GLfloat Diff(GLfloat a, GLfloat b);
// 生成在min到max范围内的任意浮点数,共有32,767种可能的整数
float RandNum (float min, float max);
// 向量函数
// 判断向量是否相等
BOOL VecEqualf(VECTORF a, VECTORF b);
// 向量清零
void VecClearf(VECTORF a);
// 向量赋值
void Vec3f(GLfloat r, GLfloat s, GLfloat t, VECTORF a);
void Vec4f(GLfloat r, GLfloat s, GLfloat t, GLfloat u, VECTORF a);
// 得到向量值
void UnVec3f(VECTORF a, GLfloat *r, GLfloat *s, GLfloat *t);
void UnVec4f(VECTORF a, GLfloat *r, GLfloat *s, GLfloat *t, GLfloat *u);
// a复制给b
void VecCopyf(VECTORF a, VECTORF b);
void VecCopy3f(VECTORF a, VECTORF b);
void VecCopy4f(VECTORF a, VECTORF b);
// a - b = c
void VecSubf(VECTORF a, VECTORF b, VECTORF c);
// a + b = c
void VecAddf(VECTORF a, VECTORF b, VECTORF c);
// a + b + c = d
void VecAdd3f(VECTORF a, VECTORF b, VECTORF c, VECTORF d);
// a * b = c
void VecMultf(VECTORF a, VECTORF b, VECTORF c);
// a * scale = b
void VecScalef(VECTORF a, float scale, VECTORF b);
// a b差值
GLfloat VecDiFFf(VECTORF a, VECTORF b);
// 点积
GLfloat VecDotf(VECTORF a, VECTORF b);
// 叉积
void VecCrossf(VECTORF a, VECTORF b, VECTORF c);
// 长度
GLfloat VecLenf(VECTORF a);
// 单位化
void VecNormalizef(VECTORF a);
// 计算面法线n
void CalNormalf(VECTORF a, VECTORF b, VECTORF c, VECTORF n, BOOL bCCW=TRUE);
// 向量夹角
BOOL GetVecAnglef(VECTORF a, VECTORF b, GLfloat *fAngle);
// 向量xyz轴夹角
void GetEulerXYFromVector(VECTORF vec, GLfloat *rx, GLfloat *ry, GLfloat *rz);
// 矩阵仿射转换函数
// 零矩阵
void ZeroMatrix(Matx4x4 a);
// 单位矩阵
void IdentityMatrix(Matx4x4 a);
// 平移矩阵
void Translate3D(float tx, float ty, float tz, Matx4x4 a);
// 规模矩阵
void Scale3D(float sx, float sy, float sz, Matx4x4 a);
// 旋转矩阵
void Rotate3D(int m, float Theta, Matx4x4 a);
//按照向量vec
//https://blog.csdn.net/stereohomology/article/details/47448759#opennewwindow
//向量旋转到Z轴映射的转换矩阵
void Rotate3DtoZ(float tx, float ty, float tz, Matx4x4 a);
// a * b = c
void MultiplyMatricies(Matx4x4 a, Matx4x4 b, Matx4x4 c);
// a复制给b
void MatrixCopy(Matx4x4 a, Matx4x4 b);
// 转置矩阵
void TransposeMatrix(Matx4x4 a);
// Ox全局平移，Sx局部规模，Rx局部旋转，Tx局部平移，XForm转换矩阵
void PrepareMatrix(float Ox,  float Oy,  float Oz,
						  float Sx,  float Sy,  float Sz,
						  float Rx,  float Ry,  float Rz,
						  float Tx,  float Ty,  float Tz,
						  Matx4x4 XForm);
// Ox全局平移，Sx局部规模，Rx局部旋转，Tx局部平移，XForm反转矩阵
void PrepareInvMatrix(float Px,  float Py,  float Pz,
							 float Sx,  float Sy,  float Sz,
							 float Rx,  float Ry,  float Rz,
							 float Tx,  float Ty,  float Tz,
							 Matx4x4 XForm);
// 旋转矩阵
void SetRotationMatrix(float Rx,  float Ry,  float Rz,
							  Matx4x4 XForm);
// 旋转反转矩阵
void SetInvRotationMatrix(float Rx,  float Ry,  float Rz,
								 Matx4x4 XForm);
// sx * M = dx
void VecTransformf(VECTORF sx, VECTORF dx, Matx4x4 M);
// 矩阵xyz轴夹角
void MatrixToEuler(Matx4x4 M, GLfloat *rx, GLfloat *ry, GLfloat *rz, BOOL bPositive=FALSE);
void MatrixToEuler(Matx4x4 M, VECTORF r, BOOL bPositive=FALSE);

// OpenGL相关函数
// M转a
void GLMatrixTo4x4(GLdouble M[16], Matx4x4 a);
void GLMatrixTo4x4(GLfloat M[16], Matx4x4 a);
// a转M
void Matx4x4ToGLMatrix(Matx4x4 a, GLdouble M[16]);
// 得到单位矩阵
void GLIdentityMatrix(GLdouble M[16]);
// 反转矩阵
BOOL InvertGLMatrix(GLdouble mat[16], GLdouble out[16]);
// sx * M = dx
void Transformf(VECTORF sx, VECTORF dx, GLdouble M[16]);
// 转置矩阵
void TransposeGLMatrix(GLdouble dst[16], GLdouble src[16]);
// a + b = dst
void AddGLMatrices(GLdouble dst[16], GLdouble a[16], GLdouble b[16]);
// a * b = dst
void MultGLMatrices(GLdouble dst[16], const GLdouble a[16], const GLdouble b[16]);
// src复制给dst
void CopyGLMatrix(GLdouble dst[16], GLdouble src[16]);
// 建立平截头体矩阵
void BuildGLFrustumMatrix(GLdouble m[16], GLdouble l, GLdouble r, GLdouble b, GLdouble t,
								GLdouble n, GLdouble f);
// 建立透视投影矩阵
void BuildGLPerspectiveMatrix(GLdouble m[16], GLdouble fovy, GLdouble aspect,
									  GLdouble zNear, GLdouble zFar);
// 建立摄像机矩阵
void BuildGLLookAtMatrix(GLdouble m[16], GLdouble eyex, GLdouble eyey, GLdouble eyez,
								 GLdouble centerx, GLdouble centery, GLdouble centerz,
								 GLdouble upx, GLdouble upy, GLdouble upz);
// tVector需要的函数
typedef struct tagMatrix
{
	float m[16];
} tMatrix;

// 逆矩阵
bool    ContraMatrix(tMatrix &mat);//矩阵求逆
// v * mat = result
void	MultVectorByMatrix(tMatrix &mat, tVector &v,tVector &result);
// 向量平方长度
double	VectorSquaredLength(tVector &v); 
// 向量长度
double	VectorLength(tVector &v); 
// 单位化
void	NormalizeVector(tVector &v); 
// 点积
double	DotProduct(tVector &v1, tVector &v2);
// 叉积
void	CrossProduct(tVector &v1, tVector &v2, tVector &result);
// 矢量的平方距离
double	VectorSquaredDistance(tVector &v1, tVector &v2);
// 矢量的比例缩放
void	ScaleVector(tVector &v, float scale, tVector &result);
// 矢量求和
void	VectorSum(tVector &v1, tVector &v2, tVector &result);
// 矢量求差
void	VectorDifference(tVector &v1, tVector &v2, tVector &result);
// 计算绕任意轴dir2旋转角度ang的旋转矩阵mat
void	GetRotationMatrix( float ang, const tVector& dir2, tMatrix& mat);

//通过三个不共线的顶点求出一个面的法向量
void TriangleNormal(tVector &v1,tVector &v2, tVector &v3, tVector &result);
//通过三个不共线的点求平面方程,2019.10.8
void PlaneEquationByThreePoint(tVector v1,tVector v2, tVector v3, float* fCoefficients);
// 求一点绕空间向量按指定坐标轴转动指定角度后的坐标点
void RotateVertical (tVector p1, tVector p2, tVector& resultp,float ang, const char axis);
// 求垂直于某空间向量、距离为r的一个坐标点
void	RotateVerticalByRadius (tVector p1, tVector p2, tVector& resultp,float r);
// 求空间点绕空间向量转动ang度后的坐标
void	RotationPointByVector( float ang, tVector p1, tVector p2, tVector p3, tVector& p4);
// 求垂直于某空间向量，且平行于xoy平面、距离为r的一个坐标点
void	GetPointVerticalToVector(tVector p1, tVector p2, tVector& resultp,float r);
//计算两个空间向量之间的转角 
float	RotateAngle(tVector a, tVector b);
//取得两个点之间的距离
float	GetDistance(tVector a, tVector b);	
//计算矢量与XYZ轴正向的夹角
void	VectorToXYZAngle(tVector &v, float &angleX, float &angleY, float &angleZ);
//计算点p1到三维平面S的投影点p3
//平面S由平面法向量p2和平面上的点P0组成
void ProjectivepointVectorToPlane(tVector &p3, tVector p1, tVector p2, tVector p0);
//计算点p1到三维平面S的投影点p3
//平面S由ax+by+cz+d=0表示，
void ProjectivepointVectorToPlane2(tVector &p3,float*  fCoefficients, tVector p1);
//点到平面的距离 2019.10.8
float DistancePointToPlane_Coefficient(tVector p1,float* fCoefficients);
//向量随着法线旋转到XOY平面上，result为旋转结果，p1为待旋转向量，p2为法线
void VectorToXOYByNormal(tVector &result,tVector p1, tVector p2);
bool FitCicle( const float* CicleX, const float* CicleY, const int Len, Point2* Center, float* Radius);//圆拟合
//求三维空间中点a到向量b的垂足点result
void PointToVectorPedal(tVector a, tVector b, tVector &result);
//求三维空间中点a到向量b的距离
float PointToVectorDistance(tVector a, tVector b);
//计算任意多边形的面积
double ComputePolygonArea(const std::vector<Point2> &points);
//直线和平面的交点
tVector CalPlaneLineIntersectPoint(tVector planeVector, tVector planePoint,tVector lineVector,tVector linePoint);
//线段和平面的交点，如果有交点，返回ture,如果没有交点，返回false
//线段和平面的交点
// planeVector 平面法向量；planePoint 平面上一点；linePointOne 线段端点；linePointTow 线段端点
bool CalPlaneLinesegmentIntersectPoint(tVector planeVector, tVector planePoint, tVector linePointOne, tVector linePointTow, tVector &IntersectPoint);
//给定直线向量 pVector,和直线上一点linePointOne，计算直线上距离linePointOne的长度为fLength上的另一点
void CalSegmentExtendedLineNode(tVector pVector, tVector linePointOne, float fLength,tVector& linePointTow);
#endif