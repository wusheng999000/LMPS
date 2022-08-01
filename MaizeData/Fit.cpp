#include "StdAfx.h"
#include "fit.h"
using namespace czy; 
Fit::Fit(void)
{
	ssr = 0.0;                 ///<回归平方和
	sse = 0.0;                 ///<(剩余平方和)
	rmse = 0.0;
	factor.resize(2,0);
}

Fit::~Fit()
{
}

//template<typename T>
bool Fit::linearFit(const std::vector<double>& x, const std::vector<double>& y,bool isSaveFitYs)
{
	return linearFit(&x[0],&y[0],getSeriesLength(x,y),isSaveFitYs);
}

//template<typename T>
bool Fit::linearFit(const double* x, const double* y,size_t length,bool isSaveFitYs)
{
	factor.resize(2,0);
	double t1=0, t2=0, t3=0, t4=0;
	for(int i=0; i<length; ++i)
	{
		t1 += x[i]*x[i];
		t2 += x[i];
		t3 += x[i]*y[i];
		t4 += y[i];
	}
	factor[1] = (t3*length - t2*t4) / (t1*length - t2*t2);
	factor[0] = (t1*t4 - t2*t3) / (t1*length - t2*t2);
	//////////////////////////////////////////////////////////////////////////
	//计算误差
	calcError(x,y,length,this->ssr,this->sse,this->rmse,isSaveFitYs);
	return true;
}
///
/// \brief 多项式拟合，拟合y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n
/// \param x 观察值的x
/// \param y 观察值的y
/// \param poly_n 期望拟合的阶数，若poly_n=2，则y=a0+a1*x+a2*x^2
/// \param isSaveFitYs 拟合后的数据是否保存，默认是
/// 
template<typename T>
void Fit::polyfit(const std::vector<typename T>& x
	,const std::vector<typename T>& y
	,int poly_n
	,bool isSaveFitYs)
{
	polyfit(&x[0],&y[0],getSeriesLength(x,y),poly_n,isSaveFitYs);
}

template<typename T>
void Fit::polyfit(const T* x,const T* y,size_t length,int poly_n,bool isSaveFitYs)
{
	factor.resize(poly_n+1,0);
	int i,j;
	//double *tempx,*tempy,*sumxx,*sumxy,*ata;
	std::vector<double> tempx(length,1.0);
	std::vector<double> tempy(y,y+length);
	std::vector<double> sumxx(poly_n*2+1);
	std::vector<double> ata((poly_n+1)*(poly_n+1));
	std::vector<double> sumxy(poly_n+1);
	for (i=0;i<2*poly_n+1;i++)
	{
		for (sumxx[i]=0,j=0;j<length;j++)
		{
			sumxx[i]+=tempx[j];
			tempx[j]*=x[j];
		}
	}
	for (i=0;i<poly_n+1;i++)
	{
		for (sumxy[i]=0,j=0;j<length;j++)
		{
			sumxy[i]+=tempy[j];
			tempy[j]*=x[j];
		}
	}
	for (i=0;i<poly_n+1;i++)
	{
		for (j=0;j<poly_n+1;j++)
		{
			ata[i*(poly_n+1)+j]=sumxx[i+j];
		}
	}
	gauss_solve(poly_n+1,ata,factor,sumxy);
	//计算拟合后的数据并计算误差
	fitedYs.reserve(length);
	calcError(&x[0],&y[0],length,this->ssr,this->sse,this->rmse,isSaveFitYs);
}
/// 
/// \brief 获取系数
/// \param 存放系数的数组
///
void Fit::getFactor(std::vector<double>& factor)
{
	factor = this->factor;
}
/// 
/// \brief 获取拟合方程对应的y值，前提是拟合时设置isSaveFitYs为true
///
void Fit::getFitedYs(std::vector<double>& fitedYs)
{
	fitedYs = this->fitedYs;
}

/// 
/// \brief 根据x获取拟合方程的y值
/// \return 返回x对应的y值
///
template<typename T>
double Fit::getY(const T x)
{
	double ans(0);
	for (size_t i=0;i<factor.size();++i)
	{
		ans += factor[i]*pow((double)x,(int)i);
	}
	return ans;
}
/// 
/// \brief 获取斜率
/// \return 斜率值
///
double Fit::getSlope(){return factor[1];}
/// 
/// \brief 获取截距
/// \return 截距值
///
double Fit::getIntercept(){return factor[0];}
/// 
/// \brief 剩余平方和
/// \return 剩余平方和
///
double Fit::getSSE()
{
	return sse;
}
/// 
/// \brief 回归平方和
/// \return 回归平方和
///
double Fit::getSSR()
{
	return ssr;
}
/// 
/// \brief 均方根误差
/// \return 均方根误差
///
double Fit::getRMSE()
{
	return rmse;
}
/// 
/// \brief 确定系数，系数是0~1之间的数，是数理上判定拟合优度的一个量
/// \return 确定系数
///
double Fit::getR_square()
{
	return 1-(sse/(ssr+sse));
}
/// 
/// \brief 获取两个vector的安全size
/// \return 最小的一个长度
///
template<typename T>
size_t Fit::getSeriesLength(const std::vector<typename T>& x
	,const std::vector<typename T>& y)
{
	return (x.size() > y.size() ? y.size() : x.size());
}
/// 
/// \brief 计算均值
/// \return 均值
///
template <typename T>
static T Fit::Mean(const std::vector<T>& v)
{
	return Mean(&v[0],v.size());
}
template <typename T>
static T Fit::Mean(const T* v,size_t length)
{
	T total(0);
	for (size_t i=0;i<length;++i)
	{
		total += v[i];
	}
	return (total / length);
}
/// 
/// \brief 获取拟合方程系数的个数
/// \return 拟合方程系数的个数
///
size_t Fit::getFactorSize()
{
	return factor.size();
}
/// 
/// \brief 根据阶次获取拟合方程的系数，
/// 如getFactor(2),就是获取y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n中a2的值
/// \return 拟合方程的系数
///
double Fit::getFactor(size_t i)
{
	return factor.at(i);
}
template<typename T>
void Fit::calcError(const T* x,const T* y,size_t length,double& r_ssr,double& r_sse,double& r_rmse,bool isSaveFitYs)
{
	T mean_y = Mean<T>(y,length);
	T yi(0);
	fitedYs.reserve(length);
	for (int i=0; i<length; ++i)
	{
		yi = getY(x[i]);
		r_ssr += ((yi-mean_y)*(yi-mean_y));//计算回归平方和
		r_sse += ((yi-y[i])*(yi-y[i]));//残差平方和
		if (isSaveFitYs)
		{
			fitedYs.push_back(double(yi));
		}
	}
	r_rmse = sqrt(r_sse/(double(length)));
}
template<typename T>
void Fit::gauss_solve(int n,std::vector<typename T>& a,std::vector<typename T>& x,std::vector<typename T>& b)
{
	gauss_solve(n,&a[0],&x[0],&b[0]);
}

template<typename T> void Fit::gauss_solve(int n,T* a,T* x,T* b)
{
	int i,j,k,r;
	double max;
	for (k=0;k<n-1;k++)
	{
		max=fabs(a[k*n+k]); /*find maxmum*/
		r=k;
		for (i=k+1;i<n-1;i++)
		{
			if (max<fabs(a[i*n+i]))
			{
				max=fabs(a[i*n+i]);
				r=i;
			}
		}
		if (r!=k)
		{
			for (i=0;i<n;i++)         /*change array:A[k]&A[r] */
			{
				max=a[k*n+i];
				a[k*n+i]=a[r*n+i];
				a[r*n+i]=max;
			}
		}
		max=b[k];                    /*change array:b[k]&b[r]     */
		b[k]=b[r];
		b[r]=max;
		for (i=k+1;i<n;i++)
		{
			for (j=k+1;j<n;j++)
			{
				a[i*n+j]-=a[i*n+k]*a[k*n+j]/a[k*n+k];
			}
			b[i]-=a[i*n+k]*b[k]/a[k*n+k];
		}
	}
	for (i=n-1;i>=0;x[i]/=a[i*n+i],i--)
	{
		for (j=i+1,x[i]=b[i];j<n;j++)
		{
			x[i]-=a[i*n+j]*x[j];
		}
	}
}