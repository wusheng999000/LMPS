/////////////////////////////////////////////////////////////////////////////
// CMatrix4x4.h : Header file; Defines the class definitions
//
// ModelMagic3D and 'glOOP' (OpenGL Object Oriented Programming library)
// Copyright ?ImageWare Development 1997, 2004
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

#pragma once

#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CMatrix4x4

#ifndef SMALL_NUMBER
#define SMALL_NUMBER	1.0E-6
#endif

#ifndef LARGE_NUMBER
#define LARGE_NUMBER	1E20
#endif

#ifndef PI
#define PI				3.14159265f
#endif

#ifndef PiOver180
#define PiOver180		1.74532925199433E-002f
#endif

#ifndef PiUnder180
#define PiUnder180		5.72957795130823E+001f
#endif

#ifndef DEGTORAD
#define DEGTORAD(A)	((A * PI) / 180.0f)
#endif

#ifndef RADTODEG
#define RADTODEG(A)	((A * 180.0f) / PI)
#endif

class CMatrix4x4
{
public:
	CMatrix4x4();
	CMatrix4x4(float a0,  float a1,  float a2,  float a3,
			   float a4,  float a5,  float a6,  float a7,
			   float a8,  float a9,  float a10, float a11,
			   float a12, float a13, float a14, float a15);
	CMatrix4x4(const CMatrix4x4 &m);
    ~CMatrix4x4();

	// 重载运算符
public:
	void operator = (const CMatrix4x4 m);
	CMatrix4x4 operator*(const CMatrix4x4 m);
	
	// 实现
public:
	// 清零
	void Clear();
	// 生成矩阵
	void Transpose();
	CMatrix4x4 GetTranspose();
	// 单位矩阵
	void SetIdentity();
	// 变化矩阵
	void SetTranslate(float Tx, float Ty, float Tz);
	void SetScale(float Sx, float Sy, float Sz);
	void SetRotationX(float fAngle);
	void SetRotationY(float fAngle);
	void SetRotationZ(float fAngle);
	// 设置矩阵
	void SetAffineMatrix(float Ox,  float Oy,  float Oz,
						 float Sx,  float Sy,  float Sz,
						 float Rx,  float Ry,  float Rz,
						 float Tx,  float Ty,  float Tz);
	void SetInvAffineMatrix(float Ox,  float Oy,  float Oz,
							float Sx,  float Sy,  float Sz,
							float Rx,  float Ry,  float Rz,
							float Tx,  float Ty,  float Tz);
	// 设置旋转矩阵
	void SetRotationMatrix(float Rx,  float Ry,  float Rz);
	void SetInvRotationMatrix(float Rx,  float Ry,  float Rz);
	// 得到各轴转角
	void MatrixToEuler(float *rx, float *ry, float *rz, bool bPositive = false);
	bool InvertMatrix();
	// 属性
public:
	float m_fMatrix[16];			// 矩阵数组
};
