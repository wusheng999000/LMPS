#pragma once

//视景操作类
#include <gl/gl.h>
#include "SceneGeome.h"
#include "Matrix4x4.h"
class CSceneOperate
{
public:
	CSceneOperate(void);
	~CSceneOperate(void);

	void DrawCoordin(float unit, float rate);

	void DrawRotCoordin();		// 显示旋转坐标系
	void DrawTraCoordin();		// 显示平移坐标系
	void DrawScaCoordin();		// 显示缩放坐标系
	void MouseMove(CPoint point, CPoint down);
	int IsCoordinSel(CPoint point);
	float DistanceOfTwoPoints(CPoint p1, CPoint p2);
	bool GetScenePlanePt(CPoint point,SCENEPOINT3D& p,int nPlane);
	virtual void DrawText(float x,float y,float z,int ftsz,CString str,bool bCn = false);

public:
	int m_nOperate;		//当前操作
	int m_nSelType;		//当前选择状态
	float m_rule;		//坐标系大小
	float m_rate;
	float m_unit;		//当前单位
	int nSizeText;
	ScenePoint3D pBase;	//基点
	float alpha;
	float quad;
	float tri1;
	float tri2;
	float tri12;
	float tri22;
	float pace;
	float sel;

	CMatrix4x4 mMatrix;	//矩阵
};
