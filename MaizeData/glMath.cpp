/////////////////////////////////////////////////////////////////////////////
// glMath.c : global glMath function implementation file
//
// ModelMagic 3D and 'glOOP' (OpenGL Object Oriented Programming library)
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

#include "stdafx.h"
#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>

#include <cmath>
#include <cstdio>
#include "glMath.h"

 #include <math.h>
/*****************************************************************************
 *
 *  Misc. Math Routines
 *
 *****************************************************************************
 */

int Scale_down_to_power_of_2(long x)
{
//	PURPOSE    : Utility to scale the number x to the next lower power of 2.
//				 For example:  300 would get scaled to 256..
//
//	RETURNS    : The scaled value of x
//
	int i;
	LONG shifted_x;

	shifted_x = x;
	for (i = 0; ((i < 16) && (shifted_x != 0)); i++)
		shifted_x = shifted_x >> 1;

	if (i == 0)
		return 0;
	else
		return ((int)(pow((double)2, (double)(i-1))));
}

int WordAlign(int n)
{
	if(fmod((float)n, sizeof(RGBQUAD)))
	{
		// Word align the row..
		n += sizeof(RGBQUAD) - (int)fmod((float)n, sizeof(RGBQUAD));
	}

	return n;
}

BOOL IsEven(int n)
{
	double temp = fmod((double)n, 2.0);
	if(!temp)
		return TRUE;
	else
		return FALSE;
}

BOOL IsEven(float f)
{
	double temp = fmod((double)f, 2.0);
	if(!temp)
		return TRUE;
	else
		return FALSE;
}

GLfloat Radiansf(GLfloat Angle)
{
	double r = (double)Angle*PiOver180; 
	return(GLfloat)r;
}

GLfloat Degreesf(GLfloat Angle)
{
	double d = (double)Angle*PiUnder180;
	return(GLfloat)d;
}

GLfloat Sinf(GLfloat Angle)
{
	return((GLfloat)sin(Radiansf(Angle)));
}

GLfloat Cosf(GLfloat Angle)
{
	return((GLfloat)cos(Radiansf(Angle)));
}

GLfloat Tanf(GLfloat Angle)
{
	return((GLfloat)tan(Radiansf(Angle)));
}

GLfloat Powerf(GLfloat Base, int Exponent)
{
	GLfloat BPower;
	int   t;

	if(Exponent==0)
		return(1.0f);
	else
	{
		BPower=1.0f;
		for(t=1; t<=Exponent; t++)
			BPower*=Base;

		return(BPower);
	}
}

int Roundf(GLfloat x)
{
	if(x<0)
		return((int)(x-0.5));
	else
		return((int)(x+0.5));
}

float Roundf(GLfloat x, int numDecimalPlaces)
{
	double exponent, fraction;
	int whole, fractional;

	whole = (int)x;
	fraction = (double)(x-whole);

	exponent = pow(10.0, numDecimalPlaces);

	fractional = Roundf((float)(fraction * exponent));
	return (float)(whole+(float)fractional/exponent);
}

GLfloat Diff(GLfloat a, GLfloat b)
{
	if(a >= 0 && b >= 0)
	{
		if(a > b)
			return a-b;
		else
			return b-a;
	}
	if(a < 0 && b < 0)
	{
		if( a > b)
			return b-a;
		else
			return a-b;
	}
	if(a >= 0 && b < 0)
		return a-b;
	else
		return b-a;
}

GLdouble Radiansd(GLdouble Angle)
{
	double r = Angle*PiOver180; 
	return r;
}

GLdouble Degreesd(GLdouble Angle)
{
	double d = Angle*PiUnder180;
	return d;
}

GLdouble Cosd(GLdouble Angle)
{
	return((GLdouble)cos(Radiansd(Angle)));
}

GLdouble Sind(GLdouble Angle)
{
	return((GLdouble)sin(Radiansd(Angle)));
}


/*****************************************************************************
 *
 *  Vector Functions:
 *
 *****************************************************************************
 */

void Vec3f(GLfloat r, GLfloat s, GLfloat t, VECTORF a)
{
	a[X]=r;
	a[Y]=s;
	a[Z]=t;
}

void UnVec3f(VECTORF a, GLfloat *r, GLfloat *s, GLfloat *t)
{
	*r=a[X];
	*s=a[Y];
	*t=a[Z];
}

void Vec4f(GLfloat r, GLfloat s, GLfloat t, GLfloat u, VECTORF a)
{
	a[X]=r;
	a[Y]=s;
	a[Z]=t;
	a[3]=u;
}

void UnVec4f(VECTORF a, GLfloat *r, GLfloat *s, GLfloat *t, GLfloat *u)
{
	*r=a[X];
	*s=a[Y];
	*t=a[Z];
	*u=a[3];
}

void VecClearf(VECTORF a)
{
	a[X] = 0.0f;
	a[Y] = 0.0f;
	a[Z] = 0.0f;
	a[W] = 0.0f;
}

BOOL VecEqualf(VECTORF a, VECTORF b)
{
	if(fabs(a[X]-b[X]) > SMALL_NUMBER)
		return FALSE;

	if(fabs(a[Y]-b[Y]) > SMALL_NUMBER)
		return FALSE;

	if(fabs(a[Z]-b[Z]) > SMALL_NUMBER)
		return FALSE;

	return TRUE;
}

void VecCopy3f(VECTORF a, VECTORF b)
{
	b[X]=a[X];
	b[Y]=a[Y];
	b[Z]=a[Z];
}

void VecCopy4f(VECTORF a, VECTORF b)
{
	b[X]=a[X];
	b[Y]=a[Y];
	b[Z]=a[Z];
	b[W]=a[W];
}

void VecCopyf(VECTORF a, VECTORF b)
{
	b[X]=a[X];
	b[Y]=a[Y];
	b[Z]=a[Z];
	b[W]=a[W];
}

void VecSubf(VECTORF a, VECTORF b, VECTORF c)
{
	c[X]=a[X]-b[X];
	c[Y]=a[Y]-b[Y];
	c[Z]=a[Z]-b[Z];
}

void VecAddf(VECTORF a, VECTORF b, VECTORF c)
{
	c[X]=a[X]+b[X];
	c[Y]=a[Y]+b[Y];
	c[Z]=a[Z]+b[Z];
}

void VecAdd3f(VECTORF a, VECTORF b, VECTORF c, VECTORF d)
{
	d[X]=a[X]+b[X]+c[X];
	d[Y]=a[Y]+b[Y]+c[Y];
	d[Z]=a[Z]+b[Z]+c[Z];
}

void VecMultf(VECTORF a, VECTORF b, VECTORF c)
{
	c[X]=a[X]*b[X];
	c[Y]=a[Y]*b[Y];
	c[Z]=a[Z]*b[Z];
}

void VecScalef(VECTORF a, float scale, VECTORF b)
{
	b[X]=a[X]*scale;
	b[Y]=a[Y]*scale;
	b[Z]=a[Z]*scale;
}

GLfloat VecDiFFf(VECTORF a, VECTORF b)
{
	GLfloat fDiff;

	fDiff  = a[X]-b[X];
	fDiff += a[Y]-b[Y];
	fDiff += a[Z]-b[Z];

	return fDiff;
}

GLfloat VecDotf(VECTORF a, VECTORF b)
{
	GLfloat f;
	f = (a[X]*b[X] + a[Y]*b[Y] + a[Z]*b[Z]);
	return(Roundf(f, 5));
	//return f;
}

void VecCrossf(VECTORF a, VECTORF b, VECTORF c)
{
	c[X]=a[Y]*b[Z] - a[Z]*b[Y];
	c[Y]=a[Z]*b[X] - a[X]*b[Z];
	c[Z]=a[X]*b[Y] - a[Y]*b[X];
}

GLfloat VecLenf(VECTORF a)
{
	return(GLfloat)(sqrt(a[X]*a[X] + a[Y]*a[Y] + a[Z]*a[Z]));
}

void VecNormalizef(VECTORF a)
{
	GLfloat dist,invdist;

	dist=VecLenf(a);
	if(dist)
	{
		invdist=1.0f/dist;
		a[X]*=invdist;
		a[Y]*=invdist;
		a[Z]*=invdist;
		a[3]*=invdist;
	}
}

void CalNormalf(VECTORF a, VECTORF b, VECTORF c, VECTORF n, BOOL bCCW)
{
	// Calculate the surface normals of a plane, given points a, b and c
	// which reside on the surface of the plane.
	/*
                     ^ Vn (Normal)
                     |
                     | 
                     |
                     | 
                 Va  *------------------* Vb  (Vu)
                    /                 /
                  /                 / 
                /                 /
              /                 /
         Vc *------------------
       (Vv)	

	*/
	VECTORF	u, v;

	VecSubf(b, a, u);
	VecSubf(c, a, v);
	if(bCCW)
		VecCrossf(u, v, n);
	else
		VecCrossf(v, u, n);
	VecNormalizef(n);
}

BOOL GetVecAnglef(VECTORF a, VECTORF b, GLfloat *fAngle)
{
	// Calculate angle between two Normal vectors
	// where:
	//		u.v = u1v1 + u2v2 + u3v3
	//		u.v = |u||v|cos theta
	//		theta = inv cos(u.v/|u||v|)
	//

	double dLength;
	double dTheta;

	dLength = VecLenf(a)*VecLenf(b);
	if(dLength)	// Don't divide by Zero!
	{
		// Calculate the angle between the vectors
		dTheta = (VecDotf(a, b)) / dLength;
		if(fabs(dTheta-1) < SMALL_NUMBER)
		{
			*fAngle = 0;
			return TRUE;
		}
		if (dTheta > 1.0)
		{
			dTheta = 1.0;
		}
		if (dTheta < -1.0)
		{
			dTheta = -1.0;
		}
		*fAngle = Degreesf((GLfloat)acos(dTheta));
		if(*fAngle)
			return TRUE;
		else
		{
			// The acos function returns the arccosine of x in the
			// range 0 to PI radians. If x is less than -1 or greater than 1,
			// acos returns an indefinite result.
			if(dTheta < -1)
				*fAngle = 180.0f;
			else
				*fAngle = 0.0f;

			return TRUE;
		}
	}
	else
		return FALSE;
}

void GetEulerXYFromVector(VECTORF vec, GLfloat *rx, GLfloat *ry, GLfloat *rz)
{
	// Extract the Euler XY rotation values that points the Z-Axis in the 
	// direction of the given vector.
	//
	Matx4x4	matx;
	VECTORF	vecY;

	// Calculate the rotation about the x-axis
	if(vec[Y]==0)
		*rx = 0;
	else
		*rx = -Degreesf((GLfloat)atan2(vec[Y], vec[Z]));

	// Compensate for rounding errors
	Roundf(*rx, 5);

	// Rotate the vector by the inverse of the x-axis rotation
	Rotate3D(X, -*rx, matx);
	VecTransformf(vec, vecY, matx);

	// Calculate the rotation about the y-axis
	if(vecY[X]==0 && vecY[Z]>0)
		*ry = 0.0f;
	else
		*ry = Degreesf((GLfloat)atan2(vecY[X], vecY[Z]));

	// Compensate for rounding errors
	Roundf(*ry, 5);

	// Rotation about the z-axis is ambiguous, so we set it to zero
	*rz=0;
}


/*****************************************************************************
 *
 *  Affine Matrix Transformation Routines
 *
 *****************************************************************************

  We define a 4x4 matrix array, referenced as Row,Column as:

		| 0,0  0,1  0,2  0,3 |
		|                    |	
		| 1,0  1,1  1,2  1,3 |
		|                    |	
		| 2,0  2,1  2,2  2,3 |
		|                    |	
		| 3,0  3,1  3,2  3,3 |
*/

void ZeroMatrix(Matx4x4 a)
{
	// Initialize the matrix to the following values:
	//		0.0		0.0		0.0		0.0
	//		0.0		0.0		0.0		0.0
	//		0.0		0.0		0.0		0.0
	//		0.0		0.0		0.0		0.0
	//
	int i, j;

	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
			a[i][j]=0.0;
	}
}

void IdentityMatrix(Matx4x4 a)
{
	// Initialize the matrix to the following values:
	//		1.0		0.0		0.0		0.0
	//		0.0		1.0		0.0		0.0
	//		0.0		0.0		1.0		0.0
	//		0.0		0.0		0.0		1.0
	//
	int i, j;

	for (i=0; i<4; i++)
	{
		for (j=0; j<4; j++)
		{
			if(i==j)
				a[i][j]=1.0;
			else
				a[i][j]=0.0;
		}
	}
}

// 计算平移变换矩阵，在赋值前先将矩阵置为单位矩阵
void Translate3D(float tx, float ty, float tz, Matx4x4 a)
{
	//	Translation matrix identified as:
	//		 ----------------
	//		| 1   0   0   Tx |
	//		| 0   1   0   Ty |
	//		| 0   0   1   Tz |
	//		| 0   0   0   1  |
	//		 ----------------
	int i;

	ZeroMatrix(a);
	for (i=0; i<4; i++)
		a[i][i]=1.0;

	a[X][3]=tx;
	a[Y][3]=ty;
	a[Z][3]=tz;
}

void Scale3D(float sx, float sy, float sz, Matx4x4 a)
{
	// Scaling matrix identified as:
	//		 ----------------
	//		| Sx  0   0   0 |
	//		| 0   Sy  0   0 |
	//		| 0   0   Sz  0 |
	//		| 0   0   0   1 |
	//		 ----------------

	ZeroMatrix(a);
	a[X][X]=sx;
	a[Y][Y]=sy;
	a[Z][Z]=sz;
	a[3][3]=1.0;
}
//https://blog.csdn.net/stereohomology/article/details/47448759#opennewwindow
//向量旋转到Z轴映射的转换矩阵
void Rotate3DtoZ(float tx, float ty, float tz, Matx4x4 a)
{
	float c;
	ZeroMatrix(a);
	c = 1/ ((tx * tx +ty * ty) * sqrt(tx * tx +ty * ty + tz * tz));
	//	Rotation about the X-Axis matrix identified as:
			//		 -----------------------
			//		| 1     0      0      0 |
			//		| 0     cosX   -sinX  0 |
			//		| 0     sinX   cosX   0 |
			//		| 0     0      0      1 |
			//		 -----------------------

	a[X][X]= c * (tx * tx * tz + ty * ty * sqrt(tx * tx +ty * ty + tz * tz));
	a[X][Y]= c * (tx * ty * (tz - sqrt(tx * tx +ty * ty + tz * tz)));
	a[X][Z]= c * (-1 * tx * (tx * tx +ty * ty));
	a[Y][X]= c * (tx * ty * (tz - sqrt(tx * tx +ty * ty + tz * tz)));
	a[Y][Y]= c * (tx * tx * sqrt(tx * tx +ty * ty + tz * tz) + ty * ty * tz);
	a[Y][Z]= c * (-1 * ty * (tx * tx +ty * ty));

	a[Z][X]= c * tx * (tx * tx +ty * ty);
	a[Z][Y]= c * ty * (tx * tx +ty * ty);
	a[Z][Z]= c * tz * (tx * tx +ty * ty);

}
// 计算旋转变换矩阵，注意：Theta值为角度值,赋值前先将矩阵置为零矩阵
void Rotate3D(int m, float Theta, Matx4x4 a)
{
	float c, s;

	ZeroMatrix(a);
	c=Cosf(Theta);
	s=Sinf(Theta);

	// Compensate for rounding errors
	if(fabs(c)<SMALL_NUMBER)
		c=0.0f;
	if(fabs(s)<SMALL_NUMBER)
		s=0.0f;

	switch(m)
	{
		case X:
			//	Rotation about the X-Axis matrix identified as:
			//		 -----------------------
			//		| 1     0      0      0 |
			//		| 0     cosX   -sinX  0 |
			//		| 0     sinX   cosX   0 |
			//		| 0     0      0      1 |
			//		 -----------------------

			a[X][X]= 1.0;
			a[Y][Y]= c;
			a[Y][Z]=-s;
			a[Z][Y]= s;
			a[Z][Z]= c;
			a[3][3]= 1.0;
			break;

		case Y:
			//	Rotation about the Y-Axis matrix identified as:
			//		 -----------------------
			//		| cosY  0      sinY   0 |
			//		| 0     1      0      0 |
			//		| -sinY 0      cosY   0 |
			//		| 0     0      0      1 |
			//		 -----------------------

			a[X][X]= c;
			a[X][Z]= s;
			a[Y][Y]= 1.0;
			a[Z][X]=-s;
			a[Z][Z]= c;
			a[3][3]= 1.0;
			break;

		case Z:
			//	Rotation about the Z-Axis matrix identified as:
			//		 -----------------------
			//		| cosZ  -sinZ  0      0 |
			//		| sinZ  cosZ   0      0 |
			//		| 0     0      1      0 |
			//		| 0     0      0      1 |
			//		 -----------------------

			a[X][X]= c;
			a[X][Y]=-s;
			a[Y][X]= s;
			a[Y][Y]= c;
			a[Z][Z]= 1.0;
			a[3][3]= 1.0;
			break;
	}
}
	
void MultiplyMatricies(Matx4x4 a, Matx4x4 b, Matx4x4 c)
{
	int   i, j, k;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			for(k=0, c[i][j]=0; k<4; k++)
				c[i][j] += a[i][k] * b[k][j];
		}
	}
}

void MatrixCopy(Matx4x4 a, Matx4x4 b)
{
	int  i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			b[i][j]=a[i][j];
	}
}

void TransposeMatrix(Matx4x4 a)
{
	Matx4x4 M;
	int  i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			M[j][i]=a[i][j];
	}
	MatrixCopy(M, a);
}

void PrepareMatrix(float Ox,  float Oy,  float Oz,
				   float Sx,  float Sy,  float Sz,
				   float Rx,  float Ry,  float Rz,
				   float Tx,  float Ty,  float Tz,
				   Matx4x4 XForm)
{
	Matx4x4 M1, M2, M3, M4, M5, M6, M7, M8, M9, M10;

	Translate3D(Tx, Ty, Tz, M1);
	Scale3D(Sx, Sy, Sz, M2);
	Rotate3D(Z, Rz, M3);
	Rotate3D(Y, Ry, M4);
	Rotate3D(X, Rx, M5);
	Translate3D(Ox, Oy, Oz, M6);

	MultiplyMatricies(M2, M1, M7);
	MultiplyMatricies(M3, M7, M8);
	MultiplyMatricies(M4, M8, M9);
	MultiplyMatricies(M5, M9, M10);
	MultiplyMatricies(M6, M10, XForm);
}

void PrepareInvMatrix(float Ox,  float Oy,  float Oz,
					  float Sx,  float Sy,  float Sz,
					  float Rx,  float Ry,  float Rz,
					  float Tx,  float Ty,  float Tz,
					  Matx4x4 XForm)
{
	Matx4x4 M1, M2, M3, M4, M5, M6, M7, M8, M9, M10;

	Translate3D(-Ox, -Oy, -Oz, M1);
	Rotate3D(X, -Rx, M2);
	Rotate3D(Y, -Ry, M3);
	Rotate3D(Z, -Rz, M4);
	Scale3D(1/Sx, 1/Sy, 1/Sz, M5);
	Translate3D(-Tx, -Ty, -Tz, M6);

	MultiplyMatricies(M2, M1, M7);
	MultiplyMatricies(M3, M7, M8);
	MultiplyMatricies(M4, M8, M9);
	MultiplyMatricies(M5, M9, M10);
	MultiplyMatricies(M6, M10, XForm);
}

void SetRotationMatrix(float Rx,  float Ry,  float Rz,
					   Matx4x4 XForm)
{
	Matx4x4 M1, M2, M3, M4;

	Rotate3D(Z, Rz, M1);
	Rotate3D(Y, Ry, M2);
	Rotate3D(X, Rx, M3);

	MultiplyMatricies(M2, M1, M4);
	MultiplyMatricies(M3, M4, XForm);
}

void SetInvRotationMatrix(float Rx,  float Ry,  float Rz,
						  Matx4x4 XForm)
{
	Matx4x4 M1, M2, M3, M4;

	Rotate3D(X, -Rx, M1);
	Rotate3D(Y, -Ry, M2);
	Rotate3D(Z, -Rz, M3);

	MultiplyMatricies(M2, M1, M4);
	MultiplyMatricies(M3, M4, XForm);
}

void VecTransformf(VECTORF S, VECTORF d, Matx4x4 M)
{
	GLdouble x, y, z;

	// Transform the Source vector 'S' by the matrix 'M'
	x = M[X][X]*S[X] + M[X][Y]*S[Y] + M[X][Z]*S[Z] + M[X][3];//*S[3];
	y = M[Y][X]*S[X] + M[Y][Y]*S[Y] + M[Y][Z]*S[Z] + M[Y][3];//*S[3];
	z = M[Z][X]*S[X] + M[Z][Y]*S[Y] + M[Z][Z]*S[Z] + M[Z][3];//*S[3];

	// Compensate for rounding errors
	if(fabs(x) < SMALL_NUMBER)
		x = 0.0f;
	if(fabs(y) < SMALL_NUMBER)
		y = 0.0f;
	if(fabs(z) < SMALL_NUMBER)
		z = 0.0f;

	// Store the transformed values in the Destination
	// vector 'd'
	d[X] = (GLfloat)x;
	d[Y] = (GLfloat)y;
	d[Z] = (GLfloat)z;
}

void MatrixToEuler(Matx4x4 M, GLfloat *rx, GLfloat *ry, GLfloat *rz, BOOL bPositive)
{
	double C;
	double tx, ty;

	// Calculate the Y-Axis angle
	*ry  = (float)asin(M[X][Z]);
	C	 = cos(*ry);
	*ry *= (float)PiUnder180;

	if(fabs(C) > SMALL_NUMBER)	// Gimball lock?
	{
		// No gimball lock, so calculate the XZ-Axis angles
		tx	=  M[Z][Z]/C;
		ty	= -M[Y][Z]/C;
		*rx	= (float)(atan2(ty, tx) * PiUnder180);

		tx	=  M[X][X]/C;
		ty	= -M[X][Y]/C;
		*rz	= (float)(atan2(ty, tx) * PiUnder180);
	}
	else
	{
		// Gimball lock has occurred, so set the X-Axis angle to Zero and 
		// calculate the Z-Axis angle.
		*rx	= 0.0f;
		tx	= M[Y][Y];
		ty	= M[Y][X];
		*rz = (float)(atan2(ty, tx) * PiUnder180);
	}

	if(!bPositive) return;

	// Return only positive angles from [0-360]
	if(*rx < 0)	*rx += 360;
	if(*ry < 0)	*ry += 360;
	if(*rz < 0)	*rz += 360;
}

void MatrixToEuler(Matx4x4 M, VECTORF r, BOOL bPositive)
{
	double C;
	double tx, ty;

	// Calculate the Y-Axis angle
	r[Y]  = (float)asin(M[X][Z]);
	C	  = cos(r[Y]);
	r[Y] *= (float)PiUnder180;

	if(fabs(C) > SMALL_NUMBER)	// Gimball lock?
	{
		// No gimball lock, so calculate the XZ-Axis angles
		tx	 =  M[Z][Z]/C;
		ty	 = -M[Y][Z]/C;
		r[X] = (float)(atan2(ty, tx) * PiUnder180);
		tx	 =  M[X][X]/C;
		ty	 = -M[X][Y]/C;
		r[Z] = (float)(atan2(ty, tx) * PiUnder180);
	}
	else
	{
		// Gimball lock has occurred, so set the X-Axis angle to Zero and 
		// calculate the Z-Axis angle.
		r[X] = 0.0f;
		tx	 = M[Y][Y];
		ty	 = M[Y][X];
		r[Z] = (float)(atan2(ty, tx) * PiUnder180);
	}

	if(!bPositive) return;

	// Return only positive angles from [0-360]
	if(r[X] < 0)	r[X] += 360;
	if(r[Y] < 0)	r[Y] += 360;
	if(r[Z] < 0)	r[Z] += 360;
}


/*****************************************************************************
 *
 *  Misc OpenGL Related Functions:
 *
 *****************************************************************************
  We define a 4x4 matrix array,			OpenGL linear matrix format:
  referenced as Row,Column as:

	| 0,0  0,1  0,2  0,3 |					|a0  a4  a8   a12|
	|                    |					|                |
	| 1,0  1,1  1,2  1,3 |					|a1  a5  a9   a13|
	|                    |					|                |
	| 2,0  2,1  2,2  2,3 |					|a2  a6  a10  a14|
	|                    |					|                |
	| 3,0  3,1  3,2  3,3 |					|a3  a7  a11  a15|

 */

void GLMatrixTo4x4(GLdouble M[16], Matx4x4 a)
{
	int i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			a[i][j]=(float)M[(i*4)+j];
	}
}

void GLMatrixTo4x4(GLfloat M[16], Matx4x4 a)
{
	int i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			a[i][j]=(float)M[(i*4)+j];
	}
}

void Matx4x4ToGLMatrix(Matx4x4 a, GLdouble M[16])
{
	int i, j;

	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
			M[(i*4)+j]=(GLdouble)a[j][i];
	}
}

void GLIdentityMatrix(GLdouble M[16])
{
	// Initialize the matrix to the following values:
	//		1.0		0.0		0.0		0.0
	//		0.0		1.0		0.0		0.0
	//		0.0		0.0		1.0		0.0
	//		0.0		0.0		0.0		1.0
	//
	memset(M, 0, sizeof(GLdouble)*16);
	M[X] = M[5] = M[10] = M[15] = 1.0;
}

// Compute inverse of 4x4 transformation matrix.
// Code contributed by Jacques Leroy jle@star.be
// Return GL_TRUE for success, GL_FALSE for failure (singular matrix)
//
#define SWAP_ROWS(a, b) { GLdouble *_tmp = a; (a)=(b); (b)=_tmp; }
#define MAT(m,r,c) (m)[(c)*4+(r)]

BOOL InvertGLMatrix(GLdouble mat[16], GLdouble out[16])
{
   const GLdouble *m   = mat;
   GLdouble wtmp[4][8];
   GLdouble m0, m1, m2, m3, s;
   GLdouble *r0, *r1, *r2, *r3;
  
   r0 = wtmp[X], r1 = wtmp[Y], r2 = wtmp[Z], r3 = wtmp[3];
  
   r0[X] = MAT(m,0,0), r0[Y] = MAT(m,0,1),
   r0[Z] = MAT(m,0,2), r0[3] = MAT(m,0,3),
   r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
  
   r1[X] = MAT(m,1,0), r1[Y] = MAT(m,1,1),
   r1[Z] = MAT(m,1,2), r1[3] = MAT(m,1,3),
   r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
  
   r2[X] = MAT(m,2,0), r2[Y] = MAT(m,2,1),
   r2[Z] = MAT(m,2,2), r2[3] = MAT(m,2,3),
   r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
  
   r3[X] = MAT(m,3,0), r3[Y] = MAT(m,3,1),
   r3[Z] = MAT(m,3,2), r3[3] = MAT(m,3,3),
   r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;
  
   /* choose pivot - or die */
   if (fabs(r3[X])>fabs(r2[X])) SWAP_ROWS(r3, r2);
   if (fabs(r2[X])>fabs(r1[X])) SWAP_ROWS(r2, r1);
   if (fabs(r1[X])>fabs(r0[X])) SWAP_ROWS(r1, r0);
   if (0.0 == r0[X])  return GL_FALSE;
  
   /* eliminate first variable     */
   m1 = r1[X]/r0[X]; m2 = r2[X]/r0[X]; m3 = r3[X]/r0[X];
   s = r0[Y]; r1[Y] -= m1 * s; r2[Y] -= m2 * s; r3[Y] -= m3 * s;
   s = r0[Z]; r1[Z] -= m1 * s; r2[Z] -= m2 * s; r3[Z] -= m3 * s;
   s = r0[3]; r1[3] -= m1 * s; r2[3] -= m2 * s; r3[3] -= m3 * s;
   s = r0[4];
   if (s != 0.0) { r1[4] -= m1 * s; r2[4] -= m2 * s; r3[4] -= m3 * s; }
   s = r0[5];
   if (s != 0.0) { r1[5] -= m1 * s; r2[5] -= m2 * s; r3[5] -= m3 * s; }
   s = r0[6];
   if (s != 0.0) { r1[6] -= m1 * s; r2[6] -= m2 * s; r3[6] -= m3 * s; }
   s = r0[7];
   if (s != 0.0) { r1[7] -= m1 * s; r2[7] -= m2 * s; r3[7] -= m3 * s; }
  
   /* choose pivot - or die */
   if (fabs(r3[Y])>fabs(r2[Y])) SWAP_ROWS(r3, r2);
   if (fabs(r2[Y])>fabs(r1[Y])) SWAP_ROWS(r2, r1);
   if (0.0 == r1[Y])  return GL_FALSE;
  
   /* eliminate second variable */
   m2 = r2[Y]/r1[Y]; m3 = r3[Y]/r1[Y];
   r2[Z] -= m2 * r1[Z]; r3[Z] -= m3 * r1[Z];
   r2[3] -= m2 * r1[3]; r3[3] -= m3 * r1[3];
   s = r1[4]; if (0.0 != s) { r2[4] -= m2 * s; r3[4] -= m3 * s; }
   s = r1[5]; if (0.0 != s) { r2[5] -= m2 * s; r3[5] -= m3 * s; }
   s = r1[6]; if (0.0 != s) { r2[6] -= m2 * s; r3[6] -= m3 * s; }
   s = r1[7]; if (0.0 != s) { r2[7] -= m2 * s; r3[7] -= m3 * s; }
  
   /* choose pivot - or die */
   if (fabs(r3[Z])>fabs(r2[Z])) SWAP_ROWS(r3, r2);
   if (0.0 == r2[Z])  return GL_FALSE;
  
   /* eliminate third variable */
   m3 = r3[Z]/r2[Z];
   r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
   r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6],
   r3[7] -= m3 * r2[7];
  
   /* last check */
   if (0.0 == r3[3]) return GL_FALSE;
  
   s = 1.0/r3[3];              /* now back substitute row 3 */
   r3[4] *= s; r3[5] *= s; r3[6] *= s; r3[7] *= s;
  
   m2 = r2[3];                 /* now back substitute row 2 */
   s  = 1.0/r2[Z];
   r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
   r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
   m1 = r1[3];
   r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
   r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
   m0 = r0[3];
   r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
   r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;
  
   m1 = r1[Z];                 /* now back substitute row 1 */
   s  = 1.0/r1[Y];
   r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
   r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
   m0 = r0[Z];
   r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
   r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;
  
   m0 = r0[Y];                 /* now back substitute row 0 */
   s  = 1.0/r0[X];
   r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
   r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);
  
   MAT(out,0,0) = r0[4]; MAT(out,0,1) = r0[5],
   MAT(out,0,2) = r0[6]; MAT(out,0,3) = r0[7],
   MAT(out,1,0) = r1[4]; MAT(out,1,1) = r1[5],
   MAT(out,1,2) = r1[6]; MAT(out,1,3) = r1[7],
   MAT(out,2,0) = r2[4]; MAT(out,2,1) = r2[5],
   MAT(out,2,2) = r2[6]; MAT(out,2,3) = r2[7],
   MAT(out,3,0) = r3[4]; MAT(out,3,1) = r3[5],
   MAT(out,3,2) = r3[6]; MAT(out,3,3) = r3[7]; 
  
   return GL_TRUE;
}
#undef SWAP_ROWS

void Transformf(VECTORF S, VECTORF d, GLdouble M[16])
{
	GLdouble x, y, z;

	// Transform the Source vector 'S' by the matrix 'M'
	x = M[X]*S[X] + M[4]*S[Y] + M[8] *S[Z] + M[12];
	y = M[Y]*S[X] + M[5]*S[Y] + M[9] *S[Z] + M[13];
	z = M[Z]*S[X] + M[6]*S[Y] + M[10]*S[Z] + M[14];

	// Compensate for rounding errors
	if(fabs(x) < SMALL_NUMBER)
		x = 0.0f;
	if(fabs(y) < SMALL_NUMBER)
		y = 0.0f;
	if(fabs(z) < SMALL_NUMBER)
		z = 0.0f;

	// Store the transformed values in the Destination
	// vector 'd'
	d[X] = (GLfloat)x;
	d[Y] = (GLfloat)y;
	d[Z] = (GLfloat)z;
}

/* dst = transpose(src) */
void TransposeGLMatrix(GLdouble dst[16], GLdouble src[16])
{
	dst[X] = src[X];
	dst[Y] = src[4];
	dst[Z] = src[8];
	dst[3] = src[12];

	dst[4] = src[Y];
	dst[5] = src[5];
	dst[6] = src[9];
	dst[7] = src[13];

	dst[8] = src[Z];
	dst[9] = src[6];
	dst[10] = src[10];
	dst[11] = src[14];

	dst[12] = src[3];
	dst[13] = src[7];
	dst[14] = src[11];
	dst[15] = src[15];
}

/* dst = a + b */
void AddGLMatrices(GLdouble dst[16], GLdouble a[16], GLdouble b[16])
{
	dst[X] = a[X] + b[X];
	dst[Y] = a[Y] + b[Y];
	dst[Z] = a[Z] + b[Z];
	dst[3] = a[3] + b[3];

	dst[4] = a[4] + b[4];
	dst[5] = a[5] + b[5];
	dst[6] = a[6] + b[6];
	dst[7] = a[7] + b[7];

	dst[8] = a[8] + b[8];
	dst[9] = a[9] + b[9];
	dst[10] = a[10] + b[10];
	dst[11] = a[11] + b[11];

	dst[12] = a[12] + b[12];
	dst[13] = a[13] + b[13];
	dst[14] = a[14] + b[14];
	dst[15] = a[15] + b[15];
}

/* dst = a * b */
void MultGLMatrices(GLdouble dst[16], const GLdouble a[16], const GLdouble b[16])
{
	int i, j;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			dst[i * 4 + j] = b[i * 4 + 0] * a[0 * 4 + j] +
							 b[i * 4 + 1] * a[1 * 4 + j] +
							 b[i * 4 + 2] * a[2 * 4 + j] +
							 b[i * 4 + 3] * a[3 * 4 + j];
		}
	}
}

void CopyGLMatrix(GLdouble dst[16], GLdouble src[16])
{
	int i;

	for (i=0; i<16; i++)
		dst[i] = src[i];
}

void BuildGLFrustumMatrix(GLdouble m[16], GLdouble l, GLdouble r, GLdouble b, GLdouble t,
						GLdouble n, GLdouble f)
{
	m[X] = (2.0*n) / (r-l);
	m[Y] = 0.0;
	m[Z] = 0.0;
	m[3] = 0.0;

	m[4] = 0.0;
	m[5] = (2.0*n) / (t-b);
	m[6] = 0.0;
	m[7] = 0.0;

	m[8] = (r+l) / (r-l);
	m[9] = (t+b) / (t-b);
	m[10] = -(f+n) / (f-n);
	m[11] = -1.0;

	m[12] = 0.0;
	m[13] = 0.0;
	m[14] = -(2.0*f*n) / (f-n);
	m[15] = 0.0;
}

void BuildGLPerspectiveMatrix(GLdouble m[16], GLdouble fovy, GLdouble aspect,
							  GLdouble zNear, GLdouble zFar)
{
	GLdouble xmin, xmax, ymin, ymax;

	ymax = zNear * tan(fovy * PI / 360.0);
	ymin = -ymax;

	xmin = ymin * aspect;
	xmax = ymax * aspect;

	BuildGLFrustumMatrix(m, xmin, xmax, ymin, ymax, zNear, zFar);
}

/* Build a 4x4 matrix transform based on the parameters for gluLookAt.
 * Code lifted from Brian Paul's MesaGLU.
 */
void BuildGLLookAtMatrix(GLdouble m[16], GLdouble eyex, GLdouble eyey, GLdouble eyez,
						 GLdouble centerx, GLdouble centery, GLdouble centerz,
						 GLdouble upx, GLdouble upy, GLdouble upz)
{
	GLdouble x[3], y[3], z[3];
	GLdouble mag;

	/* Make rotation matrix */

	/* Z vector */
	z[X] = eyex - centerx;
	z[Y] = eyey - centery;
	z[Z] = eyez - centerz;
	if(z[X]==0) z[X] = 0.01;
	if(z[Y]==0) z[Y] = 0.01;
	if(z[Z]==0) z[Z] = 0.01;
	mag = sqrt( z[X]*z[X] + z[Y]*z[Y] + z[Z]*z[Z] );
	if (mag)	// mpichler, 19950515
	{
		z[X] /= mag;
		z[Y] /= mag;
		z[Z] /= mag;
	}

	/* Y vector */
	y[X] = upx;
	y[Y] = upy;
	y[Z] = upz;

	/* X vector = Y cross Z */
	x[X] =  y[Y]*z[Z] - y[Z]*z[Y];
	x[Y] = -y[X]*z[Z] + y[Z]*z[X];
	x[Z] =  y[X]*z[Y] - y[Y]*z[X];

	/* Recompute Y = Z cross X */
	y[X] =  z[Y]*x[Z] - z[Z]*x[Y];
	y[Y] = -z[X]*x[Z] + z[Z]*x[X];
	y[Z] =  z[X]*x[Y] - z[Y]*x[X];

	/* mpichler, 19950515 */
	/* cross product gives area of parallelogram, which is < 1.0 for
	 * non-perpendicular unit-length vectors; so normalize x, y here
	 */

	mag = sqrt( x[X]*x[X] + x[Y]*x[Y] + x[Z]*x[Z] );
	if (mag)
	{
		x[X] /= mag;
		x[Y] /= mag;
		x[Z] /= mag;
	}

	mag = sqrt( y[X]*y[X] + y[Y]*y[Y] + y[Z]*y[Z] );
	if (mag)
	{
		y[X] /= mag;
		y[Y] /= mag;
		y[Z] /= mag;
	}

#define M(row,col)  m[col*4+row]
	M(0,0) = x[X];  M(0,1) = x[Y];  M(0,2) = x[Z];  M(0,3) = -x[X]*eyex + -x[Y]*eyey + -x[Z]*eyez;
	M(1,0) = y[X];  M(1,1) = y[Y];  M(1,2) = y[Z];  M(1,3) = -y[X]*eyex + -y[Y]*eyey + -y[Z]*eyez;
	M(2,0) = z[X];  M(2,1) = z[Y];  M(2,2) = z[Z];  M(2,3) = -z[X]*eyex + -z[Y]*eyey + -z[Z]*eyez;
	M(3,0) = 0.0;   M(3,1) = 0.0;   M(3,2) = 0.0;   M(3,3) = 1.0;
#undef M
}

//*******************tVector计算函数******************

//////////////////////////////////////////////////////////////
//实矩阵求逆的全选主元高斯-约当法

int rinv(int n,float a[]) 
{ 
//	int *is,*js,i,j,k,l,u,v;
	int i,j,k,l,u,v;
	float d,p;
	/*is=(int*)malloc(n*sizeof(int));
	js=(int*)malloc(n*sizeof(int));*/
	std::vector<int> is;
	std::vector<int> js;
	is.resize(n);
	js.resize(n);

	for (k=0; k<=n-1; k++)
	{ d=0.0;
	for (i=k; i<=n-1; i++)
		for (j=k; j<=n-1; j++)
		{ l=i*n+j; p=(float)fabs(a[l]);
	if (p>d) { d=p; is[k]=i; js[k]=j;}
	}
	if (d+1.0==1.0)
	{ 
//		free(is); free(js); printf("err**not inv\n");
		is.clear();
		js.clear();
		return(0);
	}
	if (is[k]!=k)
		for (j=0; j<=n-1; j++)
		{ u=k*n+j; v=is[k]*n+j;
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	if (js[k]!=k)
		for (i=0; i<=n-1; i++)
		{ u=i*n+k; v=i*n+js[k];
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	l=k*n+k;
	a[l]=(float)1.0/a[l];
	for (j=0; j<=n-1; j++)
		if (j!=k)
		{ u=k*n+j; a[u]=a[u]*a[l];}
		for (i=0; i<=n-1; i++)
			if (i!=k)
				for (j=0; j<=n-1; j++)
					if (j!=k)
					{ u=i*n+j;
		a[u]=a[u]-a[i*n+k]*a[k*n+j];
		}
		for (i=0; i<=n-1; i++)
			if (i!=k)
			{ u=i*n+k; a[u]=-a[u]*a[l];}
	}
	for (k=n-1; k>=0; k--)
	{ if (js[k]!=k)
	for (j=0; j<=n-1; j++)
	{ u=k*n+j; v=js[k]*n+j;
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	if (is[k]!=k)
		for (i=0; i<=n-1; i++)
		{ u=i*n+k; v=i*n+is[k];
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	}
//	free(is); free(js);
	is.clear();
	js.clear();
	return(1);
}

bool ContraMatrix(tMatrix &mat)//矩阵求逆
{
	int i;
	static float a[16];
	for(i=0;i<16;i++)
		a[i]=mat.m[i];
	if(rinv(4,a)!=0)
	{
		for(i=0;i<16;i++)
			mat.m[i] = a[i];

		return true;
	}
	else return false;
}

///////////////////////////////////////////////////////////////////////////////
/*矢量矩阵相乘*/
void MultVectorByMatrix(tMatrix &mat, tVector &v,tVector &result)
{
	result.x = (mat.m[0] * v.x) +
		(mat.m[4] * v.y) +	
		(mat.m[8] * v.z) +
		mat.m[12];
	result.y = (mat.m[1] * v.x) +
		(mat.m[5] * v.y) +	
		(mat.m[9] * v.z) +
		mat.m[13];
	result.z = (mat.m[2] * v.x) +
		(mat.m[6] * v.y) +	
		(mat.m[10] * v.z) +
		mat.m[14];
}

// 计算绕任意轴dir2旋转角度ang的旋转矩阵mat
void GetRotationMatrix( float ang, const tVector& dir2, tMatrix& mat)
{
	tVector dir(dir2);

	NormalizeVector(dir);

	ang = DEGTORAD(ang);
	float fCos = cosf( ang );
	float fSin = sinf( ang );

	mat.m[0] = ( dir.x * dir.x ) * ( 1.0f - fCos ) + fCos;
	mat.m[1] = ( dir.x * dir.y ) * ( 1.0f - fCos ) - (dir.z * fSin);
	mat.m[2] = ( dir.x * dir.z ) * ( 1.0f - fCos ) + (dir.y * fSin);

	mat.m[4] = ( dir.y * dir.x ) * ( 1.0f - fCos ) + (dir.z * fSin);
	mat.m[5] = ( dir.y * dir.y ) * ( 1.0f - fCos ) + fCos ;
	mat.m[6] = ( dir.y * dir.z ) * ( 1.0f - fCos ) - (dir.x * fSin);

	mat.m[8] = ( dir.z * dir.x ) * ( 1.0f - fCos ) - (dir.y * fSin);
	mat.m[9] = ( dir.z * dir.y ) * ( 1.0f - fCos ) + (dir.x * fSin);
	mat.m[10] = ( dir.z * dir.z ) * ( 1.0f - fCos ) + fCos;

	mat.m[3] = mat.m[7] = mat.m[11] = 0;
	mat.m[12] = mat.m[13] = mat.m[14] = 0;
	mat.m[15] = 1;
}

/* returns squared length of input vector */  
/*向量平方长度*/  
double VectorSquaredLength(tVector &v) 
{
	return((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

/* returns length of input vector */
/*向量长度*/
double VectorLength(tVector &v) 
{
	return(sqrt(VectorSquaredLength(v)));
}

/* destructively normalizes the input vector */
/*向量规格化*/
void NormalizeVector(tVector &v) 
{
	float len = (float)VectorLength(v);
	if (len != 0.0) 
	{ 
		v.x /= len;  
		v.y /= len; 
		v.z /= len; 
	}
	else
	{
		v.x = 0.0;
		v.y = 0.0;
		v.z = 0.0;
	}
}

/*点积*/
double DotProduct(tVector &v1, tVector &v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

/* return the cross product result = v1 cross v2 */
/*叉积*/
void CrossProduct(tVector &v1, tVector &v2, tVector &result)
{
	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
}

/*矢量的平方距离*/
double VectorSquaredDistance(tVector &v1, tVector &v2) 
{
	return(	((v1.x - v2.x) * (v1.x - v2.x)) + 
		((v1.y - v2.y) * (v1.y - v2.y)) + 	
		((v1.z - v2.z) * (v1.z - v2.z)) ); 	
}

/*矢量的比例缩放*/
void ScaleVector(tVector &v, float scale, tVector &result) 
{
	result.x = v.x * scale;
	result.y = v.y * scale;
	result.z = v.z * scale;
}

/*矢量求和*/
void VectorSum(tVector &v1, tVector &v2, tVector &result) 
{
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
}

/*矢量求差*/
void VectorDifference(tVector &v1, tVector &v2, tVector &result) 
{
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
}

//通过三个不共线的顶点求出一个面的法向量
void TriangleNormal(tVector &v1,tVector &v2, tVector &v3, tVector &result)
{
	tVector vector1,vector2,normal;
	VectorDifference(v1,v2,vector1);
	VectorDifference(v2,v3,vector2);

	CrossProduct(vector1,vector2,normal);
	NormalizeVector(normal);

	result.x = normal.x;
	result.y = normal.y;
	result.z = normal.z;
}

// ***************************************************************
// 求一点绕空间向量按指定坐标轴转动指定角度后的坐标点
// 空间向量为p1->p2
// 							-LCF-
// ***************************************************************
void RotateVertical (tVector p1, tVector p2, tVector& resultp,float ang, const char axis)
{
	/*
	空间向量: p1->p2;
	返回坐标点:resultp;
	转动角度:ang;
	*/
	float sin_theta,cos_theta;
	float x,y,z;
	float tempX,tempY,tempZ;

	sin_theta = sinf( DEGTORAD(ang) );
	cos_theta = cosf( DEGTORAD(ang) );

	x = p2.x - p1.x;
	y = p2.y - p1.y;
	z = p2.z - p1.z;

	if(axis == 'x'||axis =='X')
	{
		tempX = x;
		tempY = y*cos_theta - z*sin_theta;
		tempZ = y*sin_theta + z*cos_theta;
	}
	else if(axis == 'y'||axis =='Y')
	{
		tempX = x*cos_theta - z*sin_theta;
		tempY = y;
		tempZ = x*sin_theta + z*cos_theta;
	}
	else if(axis == 'z'||axis =='Z')
	{
		tempX = x*cos_theta - y*sin_theta;
		tempY = x*sin_theta + y*cos_theta;
		tempZ = z;
	}
	else
	{
		tempX = x;
		tempY = y;
		tempZ = z;
	}

	resultp.x = tempX + p1.x;
	resultp.y = tempY + p1.y;
	resultp.z = tempZ + p1.z;
}

//////////////////////////////////////////////////////
//求垂直于某空间向量、距离为r的一个坐标点
//空间向量为p1->p2
//////////////////////////////////////////////////////
void RotateVerticalByRadius (tVector p1, tVector p2, tVector& resultp,float r)
{
	/*
	空间向量: p1->p2;
	返回坐标点:resultp;
	半径:r;
	*/
	float x,y,z;
	float delta;
	float p2_y;
	tVector rp;

	tVector OriginP1, OriginP2;

	OriginP1 = p1;
	OriginP2 = p2;
	
	//先将p1和p2移动到原点
	x = p1.x;y=p1.y;z=p1.z;

	p1.x = p1.x - x;
	p1.y = p1.y - y;
	p1.z = p1.z - z;

	p2.x = p2.x - x;
	p2.y = p2.y - y;
	p2.z = p2.z - z;
	
	//计算p1->p2与z轴的夹角
	if(p2.y != p1.y)
	{
		delta = atanf((p2.x - p1.x)/(p2.y - p1.y));
		delta = abs( RADTODEG( delta ) );
	}
	else
		delta = 90.0f;

	if(p1.x <= p2.x)
	{
		if(p1.y >= p2.y)
			delta = 180.0f - delta;
	}
	else
	{
		if(p1.y <= p2.y)
			delta = 360.0f - delta;

		else
			delta = 180.0f + delta;
	}

	p2_y = p2.z;		//记录p2在z轴的值

	//将p1->p2投影到xoy平面
	p1.z = 0.0;
	p2.z = 0.0;

	RotateVertical(p1,p2,rp,delta,'z');

	rp.x = rp.x + r;

	//逆向旋转
	RotateVertical(p1,rp,p2,-delta,'z');
	p2.z = p2_y;	//将p2从xoy平面移回三维空间

	//从原点移回
	resultp.x = p2.x + x;
	resultp.y = p2.y + y;
	resultp.z = p2.z + z;

	RotationPointByVector(delta, OriginP1, OriginP2, resultp, rp);	
	resultp = rp;
} 

//////////////////////////////////////////////////////
//求垂直于某空间向量，且平行于xoy平面、距离为r的一个坐标点
//空间向量为p1->p2
//////////////////////////////////////////////////////
void GetPointVerticalToVector (tVector p1, tVector p2, tVector& resultp,float r)
{
	/*
	空间向量: p1->p2;
	返回坐标点:resultp;
	半径:r;
	*/
	float x,y,z;
	float delta;
	float p2_y;
	tVector rp;

	tVector OriginP1, OriginP2;

	OriginP1 = p1;
	OriginP2 = p2;

	//先将p1和p2移动到原点
	x = p1.x;y=p1.y;z=p1.z;

	p1.x = p1.x - x;
	p1.y = p1.y - y;
	p1.z = p1.z - z;

	p2.x = p2.x - x;
	p2.y = p2.y - y;
	p2.z = p2.z - z;

	//计算p1->p2与z轴的夹角
	if(p2.y != p1.y)
	{
		delta = atanf((p2.x - p1.x)/(p2.y - p1.y));
		delta = abs( RADTODEG( delta ) );
	}
	else
		delta = 90.0f;

	if(p1.x <= p2.x)
	{
		if(p1.y >= p2.y)
			delta = 180.0f - delta;
	}
	else
	{
		if(p1.y <= p2.y)
			delta = 360.0f - delta;

		else
			delta = 180.0f + delta;
	}

	p2_y = p2.z;		//记录p2在z轴的值

	//将p1->p2投影到xoy平面
	p1.z = 0.0;
	p2.z = 0.0;

	RotateVertical(p1,p2,rp,delta,'z');

	rp.x = rp.x + r;

	//逆向旋转
	RotateVertical(p1,rp,p2,-delta,'z');
	p2.z = p2_y;	//将p2从xoy平面移回三维空间

	//从原点移回
	resultp.x = p2.x + x;
	resultp.y = p2.y + y;
	resultp.z = p2.z + z;
} 

//////////////////////////////////////////////////////
//求空间点绕空间向量转动ang度后的坐标
//空间向量为p1->p2，p3为需要转动的点
//////////////////////////////////////////////////////
void RotationPointByVector( float ang, tVector p1, tVector p2, tVector p3, tVector& p4)
{
	/*
	通过将空间向量转换到过原点的向量后，计算出空间点绕该向量旋转的旋转矩阵
	然后用该点的矩阵乘上这个旋转矩阵即可得到旋转指定角度后的点坐标，最后将点按原点坐标逆平移回去
	空间点的矩阵表示为四元向量[x y z 1]
	*/
	float x,y,z;
	float m[4][4];    //绕空间任意向量旋转的旋转矩阵
	tVector dir;

	x=p1.x;
	y=p1.y;
	z=p1.z;

	//将p1点移动到原点
	p1.x=p1.x-x;
	p1.y=p1.y-y;
	p1.z=p1.z-z;
	//将p2和p3移动到相当于原点的坐标
	p2.x=p2.x-x;
	p2.y=p2.y-y;
	p2.z=p2.z-z;

	p3.x=p3.x-x;
	p3.y=p3.y-y;
	p3.z=p3.z-z;

	dir.x = p2.x - p1.x;
	dir.y = p2.y - p1.y;
	dir.z = p2.z - p1.z;

	NormalizeVector(dir);

	ang = - DEGTORAD( ang );

	float fCos = cosf( ang );
	float fSin = sinf( ang ); 

	m[0][0] = ( dir.x * dir.x ) * ( 1.0f - fCos ) + fCos;
	m[0][1] = ( dir.x * dir.y ) * ( 1.0f - fCos ) - (dir.z * fSin);
	m[0][2] = ( dir.x * dir.z ) * ( 1.0f - fCos ) + (dir.y * fSin);

	m[1][0] = ( dir.y * dir.x ) * ( 1.0f - fCos ) + (dir.z * fSin);
	m[1][1] = ( dir.y * dir.y ) * ( 1.0f - fCos ) + fCos ;
	m[1][2] = ( dir.y * dir.z ) * ( 1.0f - fCos ) - (dir.x * fSin);

	m[2][0] = ( dir.z * dir.x ) * ( 1.0f - fCos ) - (dir.y * fSin);
	m[2][1] = ( dir.z * dir.y ) * ( 1.0f - fCos ) + (dir.x * fSin);
	m[2][2] = ( dir.z * dir.z ) * ( 1.0f - fCos ) + fCos;

	m[0][3] = m[1][3] = m[2][3] = 0;
	m[3][0] = m[3][1] = m[3][2] = 0;
	m[3][3] = 1;

	p4.x = p3.x * m[0][0] + p3.y * m[1][0] + p3.z * m[2][0] + m[3][0] + x;
	p4.y = p3.x * m[0][1] + p3.y * m[1][1] + p3.z * m[2][1] + m[3][1] + y;
	p4.z = p3.x * m[0][2] + p3.y * m[1][2] + p3.z * m[2][2] + m[3][2] + z;
}

float RandNum (float min, float max)
{
	unsigned int r;
	float	x;

	r = rand();
	x = (float)(r & 0x7fff) / (float)0x7fff;
	return (x * (max - min) + min);
}
//计算两个空间向量之间的转角 
float RotateAngle(tVector a, tVector b)
{
	/*
	假定b是围绕N这个单位向量旋转了cita角达到了b
	那么显然(a×b)*N就是我们需要的c的模了
	另外，我们需要知道的是，从a到b的旋转角度是0到360度范围的
	借助atan2函数，可以完美的计算出这个旋转角度
	cita ＝ atan2（ (a×b)*N,  a*b)
	*/
	
	float cita;
	tVector N,p1,p2;

	//N为a,b的单位法向量
	CrossProduct(a,b,N);
	NormalizeVector(N);

	CrossProduct(a,b,p1);
	cita = atan2(DotProduct(p1,N),DotProduct(a,b));

	cita = abs( RADTODEG( cita ) );

	return cita;
}
//取得两个点之间的距离
float GetDistance(tVector a, tVector b)
{
	return sqrt((a.x - b.x)* (a.x - b.x) + (a.y - b.y)* (a.y - b.y)+(a.z - b.z)* (a.z - b.z));
}

//计算矢量与XYZ轴正向的夹角
void VectorToXYZAngle(tVector &v, float &angleX, float &angleY, float &angleZ)
{
	tVector vX,vY,vZ;

	vX.x = 1.0;	vX.y = 0.0;	vX.z = 0.0;
	vY.x = 0.0;	vY.y = 1.0;	vY.z = 0.0;
	vZ.x = 0.0;	vZ.y = 0.0;	vZ.z = 1.0;

	float fCos;

	//计算两个向量的夹角，通过以下公式计算余弦
	//v1 * v2 = |v1|*|v2|*cos(a)
	fCos = DotProduct(v,vX) / (VectorLength(v)*VectorLength(vX));

	fCos = acos(fCos); //将余弦转换为弧度
	angleX = RADTODEG(fCos); //将弧度转换为角度

	fCos = DotProduct(v,vY) / (VectorLength(v)*VectorLength(vY));
	fCos = acos(fCos); //将余弦转换为弧度
	angleY = RADTODEG(fCos); //将弧度转换为角度

	fCos = DotProduct(v,vZ) / (VectorLength(v)*VectorLength(vZ));
	fCos = acos(fCos); //将余弦转换为弧度
	angleZ = RADTODEG(fCos); //将弧度转换为角度
}
//计算点p1到三维平面S的投影点p3
//平面S由平面法向量p2和平面上的点P0组成
void ProjectivepointVectorToPlane(tVector &p3, tVector p1, tVector p2, tVector p0)
{
	float ftemp1,ftemp2;
	float t = 0.0;
	
	//p2.x * (x-p0.x) + p2.y * (y- p0.y) + p2.z * (z-p0.z) = 0;
	//void VecSubf(VECTORF a, VECTORF b, VECTORF c);
	ftemp1 = VectorSquaredLength(p2) ;
	VectorDifference(p0, p1, p1) ;
	ftemp2 = DotProduct(p1, p2);
	t = ftemp2 / ftemp1;
	p3.x = t * p2.x + p1.x;
	p3.y = t * p2.y + p1.y;
	p3.z = t * p2.z + p1.z;
}

//计算点p1到三维平面S的投影点p3
//平面S由ax+by+cz+d=0表示，
void ProjectivepointVectorToPlane2(tVector &p3,float*  fCoefficients, tVector p1)
{
	float a, b, c, d;
	a = fCoefficients[0];
	b = fCoefficients[1];
	c = fCoefficients[2];
	d = fCoefficients[3];

	p3.x = ((b*b + c*c)*p1.x - a*(b*p1.y + c*p1.z + d)) / (a*a + b*b + c*c);
	p3.y = ((a*a + c*c)*p1.y - b*(a*p1.x + c*p1.z + d)) / (a*a + b*b + c*c);
	p3.z = ((b*b + a*a)*p1.z - c*(a*p1.x + b*p1.y + d)) / (a*a + b*b + c*c);
}
//向量随着法线旋转到XOY平面上，result为旋转结果，p1为待旋转向量，p2为法线
void VectorToXOYByNormal(tVector &result,tVector p1,tVector p2)
{
	float Rz,Ry;
	tVector temp;
	NormalizeVector(p2); 
	Matx4x4 XForm;
	Rz = atan(p2.y/p2.x);
	Rotate3D(Z, 2* PI -Rz, XForm);
	//SetRotationMatrix(0.0,  Ry,  Rz,XForm);
	tMatrix mat;
	int t = 0;
	for(int i =0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			mat.m[t++]=XForm[i][j];
		}
	}
	// a转M
   // Matx4x4ToGLMatrix(XForm,(double)mat.m);
	MultVectorByMatrix(mat, p1,temp);
    Ry = atan(p2.z/p2.x);
	Rotate3D(Y, Ry, XForm);
	t = 0;
	for(int i =0; i < 4 ; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			mat.m[t++]=XForm[i][j];
		}
	}
	MultVectorByMatrix(mat, temp,result);
}

bool FitCicle(const float* CicleX, const float* CicleY, const int Len, Point2* Center, float* Radius)
{
	if (Len < 3) return false;
	float* xx = (float*)malloc(sizeof(float)*Len);
	if (!xx) return false;
	memcpy(xx,CicleX, sizeof(float)*Len);
	float* yy = (float*)malloc(sizeof(float)*Len);
	if (!yy)
	{
		free(xx);
		return false;
	}
	memcpy(yy, CicleY, sizeof(float)*Len);
	float X1,X2, X3,Y1,Y2,Y3,X1Y1,X1Y2,X2Y1;
	X1=X2=X3=Y1=Y2=Y3=X1Y1=X1Y2=X2Y1=0;
	int i = 0;
	bool Equalx = false, Equaly = false;
	for (i = 0; i < Len; i++)
	{
		X1 = X1 + xx[i];
		Y1 = Y1 + yy[i];
		if (yy[i] != Y1 / (i + 1))
		{
			Equaly = true;
		}
		if (xx[i] != X1 / (i + 1))
		{
			Equalx = true;
		}
		X2 = X2 + xx[i] * xx[i];
		Y2 = Y2 + yy[i] * yy[i];
		X3 = X3 + xx[i] * xx[i] * xx[i];
		Y3 = Y3 + yy[i] * yy[i] * yy[i];
		X1Y1 = X1Y1 + xx[i] * yy[i];
		X1Y2 = X1Y2 + xx[i] * yy[i] * yy[i];
		X2Y1 = X2Y1 + xx[i] * xx[i] * yy[i];
	}
    if(!Equalx||!Equaly)
	{
		free(xx);
        free(yy);
        return false;
    }
    float C1, D1, E1, G1, H1, N1;
	float a, b, c;
	N1 = Len;
	C1 = N1*X2 - X1*X1;
	D1 = N1*X1Y1 - X1*Y1;
	E1 = N1*X3 + N1*X1Y2 - (X2 + Y2)*X1;
	G1 = N1*Y2 - Y1*Y1;
	H1 = N1*X2Y1 + N1*Y3 - (X2 + Y2)*Y1;
	a = (H1*D1 - E1*G1) / (C1*G1 - D1*D1 + 1e-10);
	b = (H1*C1 - E1*D1) / (D1*D1 - G1*C1 + 1e-10);
	c = -(a*X1 + b*Y1 + X2 + Y2) / (N1 + 1e-10);
	Center->x = a / (-2);
	Center->y = b / (-2);
	float dTemp = a*a + b*b - 4 * c;
	if (dTemp < 0)
	{
		free(xx);
		free(yy);
		return false;
	}
	*Radius = sqrt(dTemp) / 2;
	free(xx);
	free(yy);
	return true;
}


//通过三个不共线的点求平面方程,2019.10.8
void PlaneEquationByThreePoint(tVector v1,tVector v2, tVector v3, float* fCoefficients)
{
	float a, b, c, d;
	a = (v3.y - v1.y)*(v3.z - v1.z) - (v2.z - v1.z)*(v3.y - v1.y);
	b = (v3.x - v1.x)*(v2.z - v1.z) - (v2.x - v1.x)*(v3.x - v1.x);
	c = (v2.x - v1.x)*(v3.y - v1.y) - (v3.x - v1.x)*(v2.y - v1.y);
	d = -(a * v1.x + b * v1.y + c * v1.z);
	fCoefficients[0] = a;
	fCoefficients[1] = b;
	fCoefficients[2] = c;
	fCoefficients[3] = d;
}

//点到平面的距离 2019.10.8
float DistancePointToPlane_Coefficient(tVector p1,float* fCoefficients)
{
	float a, b, c, d;
	a = fCoefficients[0];
	b = fCoefficients[1];
	c = fCoefficients[2];
	d = fCoefficients[3];
	float fDis = a * p1.x + b * p1.y + c *p1.z + d;
	float fTemp = sqrt(p1.x * p1.x + p1.y * p1.y + p1.z * p1.z);
	fDis = fDis / fTemp;
	return fDis;
}
//求三维空间中点a到向量b的垂足点result
//点a(x1,y1,z1),向量b(x2,y2,z2),设垂足result(k*x2,k*y2,k*z2),则有a result向量c为（k*x2-x1,k*y2-y1,k*z2-z1）
//向量c和向量b垂直，即(x2,y2,z2)*（k*x2-x1,k*y2-y1,k*z2-z1）=0，即可求得k.
void PointToVectorPedal(tVector a, tVector b, tVector &result)
{
	float k = 0.0;
	k = (a.x * b.x + a.y * b.y + a.z * b.z) / (b.x * b.x + b.y * b.y + b.z * b.z);
	result.x = k * b.x;
	result.y = k * b.y;
	result.z = k * b.z;
}

//求三维空间中点a到向量b的距离
float PointToVectorDistance(tVector a, tVector b)
{
	float k = 0.0;
	tVector result;
	k = (a.x * b.x + a.y * b.y + a.z * b.z) / (b.x * b.x + b.y * b.y + b.z * b.z);
	result.x = k * b.x;
	result.y = k * b.y;
	result.z = k * b.z;
	float fDistance = 0.0;
	fDistance = sqrt((a.x - result.x) * (a.x - result.x) + (a.y - result.y) * (a.y - result.y) + (a.z - result.z) * (a.z - result.z));
	return fDistance;
}

//计算任意多边形的面积，顶点按照顺时针或者逆时针方向排列
//points 为多边形的逆时针或顺时针顺序节点
double ComputePolygonArea(const std::vector<Point2> &points)
{
	int point_num = points.size();
	if (point_num < 3)return 0.0;
	double s = points[0].y * (points[point_num - 1].x - points[1].x);
	for (int i = 1; i < point_num; ++i)
		s += points[i].y * (points[i - 1].x - points[(i + 1) % point_num].x);
	return fabs(s / 2.0);
}

//直线和平面的交点
// planeVector 平面法向量；planePoint 平面上一点；lineVector 直线向量；linePoint 直线上一点
tVector CalPlaneLineIntersectPoint(tVector planeVector, tVector planePoint, tVector lineVector, tVector linePoint)
{
	tVector returnResult;
    float vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, t, vpt;
	vp1 = planeVector.x;
	vp2 = planeVector.y;
	vp3 = planeVector.z;
	n1 = planePoint.x;
	n2 = planePoint.y;
	n3 = planePoint.z;
	v1 = lineVector.x;
	v2 = lineVector.y;
	v3 = lineVector.z;
	m1 = linePoint.x;
	m2 = linePoint.y;
	m3 = linePoint.z;
	vpt = v1 * vp1 + v2 * vp2 + v3 * vp3;
	//首先判断直线是否与平面平行
	if(vpt == 0)
	{
		returnResult.x = 0.0;
		returnResult.y = 0.0;
		returnResult.z = 0.0;
	}
	else
	{
		t = ((n1  - m1) * vp1 + (n2 - m2) * vp2 + (n3 - m3) * vp3) / vpt;
		returnResult.x = m1 + v1 * t;
		returnResult.y = m2 + v2 * t;
		returnResult.z = m3 + v3 * t;
	}
	return returnResult;
}
//线段和平面的交点
// planeVector 平面法向量；planePoint 平面上一点；linePointOne 线段端点；linePointTow 线段端点
bool CalPlaneLinesegmentIntersectPoint(tVector planeVector, tVector planePoint, tVector linePointOne, tVector linePointTow, tVector &IntersectPoint)
{
	tVector returnResult;
	float vp1, vp2, vp3, n1, n2, n3, v1, v2, v3, m1, m2, m3, t, vpt;
	tVector ta, tb;
	vp1 = planeVector.x;
	vp2 = planeVector.y;
	vp3 = planeVector.z;
	n1 = planePoint.x;
	n2 = planePoint.y;
	n3 = planePoint.z;
	v1 = linePointTow.x - linePointOne.x;
	v2 = linePointTow.y - linePointOne.y;
	v3 = linePointTow.z - linePointOne.z;
	m1 = linePointOne.x;
	m2 = linePointOne.y;
	m3 = linePointOne.z;
	vpt = v1 * vp1 + v2 * vp2 + v3 * vp3;
	float fDifference = 0.0;
	//首先判断直线是否与平面平行
	if (vpt == 0)
	{
		returnResult.x = 0.0;
		returnResult.y = 0.0;
		returnResult.z = 0.0;
		return false;
	}
	else
	{
		t = ((n1 - m1) * vp1 + (n2 - m2) * vp2 + (n3 - m3) * vp3) / vpt;
		returnResult.x = m1 + v1 * t;
		returnResult.y = m2 + v2 * t;
		returnResult.z = m3 + v3 * t;
		ta.x = linePointTow.x - linePointOne.x;
		ta.y = linePointTow.y - linePointOne.y;
		ta.z = linePointTow.z - linePointOne.z;

		tb.x = returnResult.x - linePointOne.x;
		tb.y = returnResult.y - linePointOne.y;
		tb.z = returnResult.z - linePointOne.z;
		float fDis1 = sqrt((returnResult.x - linePointOne.x)*(returnResult.x - linePointOne.x) + (returnResult.y - linePointOne.y)*(returnResult.y - linePointOne.y) + (returnResult.z - linePointOne.z)*(returnResult.z - linePointOne.z));
		float fDis2 = sqrt((returnResult.x - linePointTow.x)*(returnResult.x - linePointTow.x) + (returnResult.y - linePointTow.y)*(returnResult.y - linePointTow.y) + (returnResult.z - linePointTow.z)*(returnResult.z - linePointTow.z));
		float fDis3 = sqrt((linePointOne.x - linePointTow.x)*(linePointOne.x - linePointTow.x) + (linePointOne.y - linePointTow.y)*(linePointOne.y - linePointTow.y) + (linePointOne.z - linePointTow.z)*(linePointOne.z - linePointTow.z));
		fDifference = fDis1 + fDis2 - fDis3;
		fDifference = fabs(fDifference);
		if (fDifference < 0.001)
		{//近似线段穿过平面
			IntersectPoint.x = returnResult.x;
			IntersectPoint.y = returnResult.y;
			IntersectPoint.z = returnResult.z;
			return true;
		}
	}
	return false;
}

//给定直线向量 pVector,和直线上一点linePointOne，计算直线上距离linePointOne的长度为fLength上的另一点
void CalSegmentExtendedLineNode(tVector pVector, tVector linePointOne, float fLength, tVector& linePointTow)
{
	float fTemp = 0.0;
	fTemp = 1 + (pVector.y / pVector.x) * (pVector.y / pVector.x) + (pVector.z / pVector.x) * (pVector.z / pVector.x);
	fTemp = fLength * fLength / fTemp;
	linePointTow.x = sqrt(fTemp) + linePointOne.x;
	linePointTow.y = linePointOne.y + (pVector.y / pVector.x) * (linePointTow.x - linePointOne.x);
	linePointTow.z = linePointOne.z + (pVector.z / pVector.x) * (linePointTow.x - linePointOne.x);
}