#include "stdafx.h"
#include "Fit3D.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv.hpp>
#include <vector>

using namespace std;
using namespace cv;

CFit3D::CFit3D()
{
}


CFit3D::~CFit3D()
{
}


//线性拟合,直接传递点云列表
void CFit3D::LinearFit3D(CArray<Expoint3D, Expoint3D> &mPointCloud, Expoint3D& line_para1, Expoint3D& line_para2)
{
	int m_size = mPointCloud.GetSize();
	if (m_size == 0)
	{
		return;
	}
	std::vector<cv::Point3d> points;
	cv::Point3d mPoint3d;
	for (int i = 0; i<m_size; i++)
	{
		mPoint3d.x = mPointCloud[i].x;
		mPoint3d.y = mPointCloud[i].y;
		mPoint3d.z = mPointCloud[i].z;
		points.push_back(mPoint3d);
	}
	cv::Vec6f line_para;
	cv::fitLine(points, line_para, cv::DIST_L2, 0, 1e-2, 1e-2);
	///
	float fx0, fy0, fz0;
	fx0 = line_para[0];
	fy0 = line_para[1];
	fz0 = line_para[2];

	float fx1, fy1, fz1;
	fx1 = line_para[3];
	fy1 = line_para[4];
	fz1 = line_para[5];
	
	line_para1.x = (fx0 / fz0) *(0 - fz1) + fx1;
	line_para1.y = (fy0 / fz0) *(0 - fz1) + fy1;
	line_para1.z = 0.0;

	line_para2.x = (fx0 / fz0) *(200 - fz1) + fx1;
	line_para2.y = (fy0 / fz0) *(200 - fz1) + fy1;
	line_para2.z = 200.0;
	points.clear();
	vector<cv::Point3d>().swap(points);
}

//线性拟合,直接传递点云列表
void CFit3D::LinearFit3D(Expoint3D& line_para1, Expoint3D& line_para2)
{
	int m_size = mP3DList.GetSize();
	if (m_size == 0)
	{
		return;
	}
	std::vector<cv::Point3d> points;
	cv::Point3d mPoint3d;
	for (int i = 0; i<m_size; i++)
	{
		mPoint3d.x = mP3DList[i].x;
		mPoint3d.y = mP3DList[i].y;
		mPoint3d.z = mP3DList[i].z;
		points.push_back(mPoint3d);
	}
	cv::Vec6f line_para;
	cv::fitLine(points, line_para, cv::DIST_L2, 0, 1e-2, 1e-2);
	///
	float fx0, fy0, fz0;
	fx0 = line_para[0];
	fy0 = line_para[1];
	fz0 = line_para[2];

	float fx1, fy1, fz1;
	fx1 = line_para[3];
	fy1 = line_para[4];
	fz1 = line_para[5];

	line_para1.x = (fx0 / fz0) *(0 - fz1) + fx1;
	line_para1.y = (fy0 / fz0) *(0 - fz1) + fy1;
	line_para1.z = 0.0;

	line_para2.x = (fx0 / fz0) *(200 - fz1) + fx1;
	line_para2.y = (fy0 / fz0) *(200 - fz1) + fy1;
	line_para2.z = 200.0;
	points.clear();
	vector<cv::Point3d>().swap(points);
}

//线性拟合,直接传递点云列表
Expoint3D CFit3D::LinearFit3D(CArray<Expoint3D, Expoint3D>& mPointCloud)
{
	Expoint3D pDirection(0,0,0);
	int m_size = mPointCloud.GetSize();
	if (m_size == 0)
	{
		return pDirection;
	}
	std::vector<cv::Point3d> points;
	cv::Point3d mPoint3d;
	for (int i = 0; i < m_size; i++)
	{
		mPoint3d.x = mPointCloud[i].x;
		mPoint3d.y = mPointCloud[i].y;
		mPoint3d.z = mPointCloud[i].z;
		points.push_back(mPoint3d);
	}
	cv::Vec6f line_para;
	cv::fitLine(points, line_para, cv::DIST_L2, 0, 1e-2, 1e-2);
	//line_para[0],line_para[1],line_para[2]方向
	//line_para[3],line_para[4],line_para[5]方向上一点

	
	pDirection.x = line_para[0];
	pDirection.y = line_para[1];
	pDirection.z = line_para[2];
	
	points.clear();
	vector<cv::Point3d>().swap(points);
	return pDirection;
}