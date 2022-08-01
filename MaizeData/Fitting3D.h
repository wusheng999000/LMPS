#pragma once
#include <pcl/point_types.h>
#include <vector>
#include <Eigen/dense>
#include <vtkPolyLine.h>
#include <pcl/visualization/pcl_visualizer.h>
//#include <pcl/visualization/pcl_plotter.h>
#include <pcl/common/common.h>
using namespace std;
using namespace pcl;
using namespace Eigen;
typedef PointXYZ PointT;
class CFitting3D
{
public:
	CFitting3D(void);
	~CFitting3D(void);
	void setinputcloud(PointCloud<PointT>::Ptr input_cloud);//��������
	void grid_mean_xyz(double x_resolution,double y_resolution, vector<double>&x_mean, vector<double> &y_mean, vector<double>&z_mean, PointCloud<PointT>::Ptr &new_cloud);//ͶӰ��XOY�������������ÿ�������ڵ��������ֵ
	void line_fitting(vector<double>x, vector<double>y, double &k, double &b);//y=kx+b
	void polynomial2D_fitting(vector<double>x, vector<double>y, double &a, double &b, double &c);//y=a*x^2+b*x+c;
	void polynomial3D_fitting(vector<double>x, vector<double>y, vector<double>z, double &a, double &b, double &c);//z=a*(x^2+y^2)+b*sqrt(x^2+y^2)+c
	void polynomial3D_fitting_display(double step_);//��ά����չʾ
private:
	PointCloud<PointT>::Ptr cloud;
	PointT point_min;
	PointT point_max;
	double a_3d;
	double b_3d;
	double c_3d;
	double k_line;
	double b_line;
};

