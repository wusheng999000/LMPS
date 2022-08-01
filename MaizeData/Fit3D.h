#pragma once
class CFit3D
{
public:
	CFit3D();
	~CFit3D();
public:
	CArray<Expoint3D, Expoint3D> mP3DList;//点列表
public:
	void LinearFit3D(CArray<Expoint3D, Expoint3D> &mPointCloud, Expoint3D& line_para1, Expoint3D& line_para2);//线性拟合,直接传递点云列表
	void LinearFit3D(Expoint3D& line_para1, Expoint3D& line_para2);//线性拟合,直接传递点云列表
	//线性拟合,直接传递点云列表
	Expoint3D LinearFit3D(CArray<Expoint3D, Expoint3D>& mPointCloud);
};

