#pragma once
#include "Expoint3D.h"

/*typedef struct tagPosition
{
	double  x;
	double  y;
	double  z;
	tagPosition(double _x, double _y, double _z) { x = _x; y = _y; z = _z;}
	tagPosition() {};
	bool operator==(const tagPosition & pt) { return (x == pt.x && y == pt.y && z == pt.z); }
} CPosition;
*/
class AFX_EXT_CLASS CBSpline
{

public:
	CBSpline(void);
	~CBSpline(void);
	void TwoOrderBSplineSmooth(CPosition *pt, int Num);
	void TwoOrderBSplineInterpolatePt(CPosition *&pt, int &Num, int *InsertNum);
	double F02(double t);
	double F12(double t);
	double F22(double t);

	void ThreeOrderBSplineSmooth(CPosition *pt, int Num);
	void ThreeOrderBSplineInterpolatePt(CPosition *&pt, int &Num, int *InsertNum);
	double F03(double t);
	double F13(double t);
	double F23(double t);
	double F33(double t);

	double D01(double t);
	double D11(double t);
	double D21(double t);
	double D31(double t);

	double D02(double t);
	double D12(double t);
	double D22(double t);
};

