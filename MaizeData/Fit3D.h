#pragma once
class CFit3D
{
public:
	CFit3D();
	~CFit3D();
public:
	CArray<Expoint3D, Expoint3D> mP3DList;//���б�
public:
	void LinearFit3D(CArray<Expoint3D, Expoint3D> &mPointCloud, Expoint3D& line_para1, Expoint3D& line_para2);//�������,ֱ�Ӵ��ݵ����б�
	void LinearFit3D(Expoint3D& line_para1, Expoint3D& line_para2);//�������,ֱ�Ӵ��ݵ����б�
	//�������,ֱ�Ӵ��ݵ����б�
	Expoint3D LinearFit3D(CArray<Expoint3D, Expoint3D>& mPointCloud);
};

