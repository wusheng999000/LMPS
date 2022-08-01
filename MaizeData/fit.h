#ifndef CZY_MATH_FIT
#define CZY_MATH_FIT
#include <vector>

namespace czy{
	///
	/// \brief 曲线拟合类
	///
	class Fit{
		std::vector<double> factor; ///<拟合后的方程系数
		double ssr;                 ///<回归平方和
		double sse;                 ///<(剩余平方和)
		double rmse;                ///<RMSE均方根误差
		std::vector<double> fitedYs;///<存放拟合后的y值，在拟合时可设置为不保存节省内存
	public:
		Fit();
		~Fit();

		///
		/// \brief 直线拟合-一元回归,拟合的结果可以使用getFactor获取，或者使用getSlope获取斜率，getIntercept获取截距
		/// \param x 观察值的x
		/// \param y 观察值的y
		/// \param length x,y数组的长度
		/// \param isSaveFitYs 拟合后的数据是否保存，默认否
		///
		//template<typename T>
		bool linearFit(const std::vector<double>& x, const std::vector<double>& y,bool isSaveFitYs=false);
		//template<typename T>
		bool linearFit(const double* x, const double* y,size_t length,bool isSaveFitYs=false);
		
		///
		/// \brief 多项式拟合，拟合y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n
		/// \param x 观察值的x
		/// \param y 观察值的y
		/// \param poly_n 期望拟合的阶数，若poly_n=2，则y=a0+a1*x+a2*x^2
		/// \param isSaveFitYs 拟合后的数据是否保存，默认是
		/// 
		template<typename T>
		void polyfit(const std::vector<typename T>& x,const std::vector<typename T>& y,int poly_n,bool isSaveFitYs=true);
		template<typename T>
		void polyfit(const T* x,const T* y,size_t length,int poly_n,bool isSaveFitYs=true);
		/// 
		/// \brief 获取系数
		/// \param 存放系数的数组
		///
		void getFactor(std::vector<double>& factor);
		/// 
		/// \brief 获取拟合方程对应的y值，前提是拟合时设置isSaveFitYs为true
		///
		void getFitedYs(std::vector<double>& fitedYs);
		/// 
		/// \brief 根据x获取拟合方程的y值
		/// \return 返回x对应的y值
		///
		template<typename T>
		double getY(const T x);
		/// 
		/// \brief 获取斜率
		/// \return 斜率值
		///
		double getSlope();
		/// 
		/// \brief 获取截距
		/// \return 截距值
		///
		double getIntercept();
		/// 
		/// \brief 剩余平方和
		/// \return 剩余平方和
		///
		double getSSE();
		/// 
		/// \brief 回归平方和
		/// \return 回归平方和
		///
		double getSSR();
		/// 
		/// \brief 均方根误差
		/// \return 均方根误差
		///
		double getRMSE();
		/// 
		/// \brief 确定系数，系数是0~1之间的数，是数理上判定拟合优度的一个量
		/// \return 确定系数
		///
		double getR_square();
		/// 
		/// \brief 获取两个vector的安全size
		/// \return 最小的一个长度
		///
		template<typename T>
		size_t getSeriesLength(const std::vector<typename T>& x,const std::vector<typename T>& y);
		/// 
		/// \brief 计算均值
		/// \return 均值
		///
		template <typename T>
		static T Mean(const std::vector<T>& v);
		
		template <typename T>
		static T Mean(const T* v,size_t length);
		/// 
		/// \brief 获取拟合方程系数的个数
		/// \return 拟合方程系数的个数
		///
		size_t getFactorSize();
		/// 
		/// \brief 根据阶次获取拟合方程的系数，
		/// 如getFactor(2),就是获取y=a0+a1*x+a2*x^2+……+apoly_n*x^poly_n中a2的值
		/// \return 拟合方程的系数
		///
		double getFactor(size_t i);
	private:
		template<typename T>
		void calcError(const T* x,const T* y,size_t length,double& r_ssr,double& r_sse,double& r_rmse,bool isSaveFitYs=true);
		template<typename T>
		void gauss_solve(int n,std::vector<typename T>& a,std::vector<typename T>& x,std::vector<typename T>& b);
		template<typename T> void gauss_solve(int n,T* a,T* x,T* b);
		//template<typename T> T add(T a,T b);
	};
}
#endif