#pragma once

//�Ӿ�������
#include <gl/gl.h>
#include "SceneGeome.h"
#include "Matrix4x4.h"
class CSceneOperate
{
public:
	CSceneOperate(void);
	~CSceneOperate(void);

	void DrawCoordin(float unit, float rate);

	void DrawRotCoordin();		// ��ʾ��ת����ϵ
	void DrawTraCoordin();		// ��ʾƽ������ϵ
	void DrawScaCoordin();		// ��ʾ��������ϵ
	void MouseMove(CPoint point, CPoint down);
	int IsCoordinSel(CPoint point);
	float DistanceOfTwoPoints(CPoint p1, CPoint p2);
	bool GetScenePlanePt(CPoint point,SCENEPOINT3D& p,int nPlane);
	virtual void DrawText(float x,float y,float z,int ftsz,CString str,bool bCn = false);

public:
	int m_nOperate;		//��ǰ����
	int m_nSelType;		//��ǰѡ��״̬
	float m_rule;		//����ϵ��С
	float m_rate;
	float m_unit;		//��ǰ��λ
	int nSizeText;
	ScenePoint3D pBase;	//����
	float alpha;
	float quad;
	float tri1;
	float tri2;
	float tri12;
	float tri22;
	float pace;
	float sel;

	CMatrix4x4 mMatrix;	//����
};
