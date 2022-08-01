#ifndef CZY_MATH_FIT
#define CZY_MATH_FIT
#include <vector>

namespace czy{
	///
	/// \brief ���������
	///
	class Fit{
		std::vector<double> factor; ///<��Ϻ�ķ���ϵ��
		double ssr;                 ///<�ع�ƽ����
		double sse;                 ///<(ʣ��ƽ����)
		double rmse;                ///<RMSE���������
		std::vector<double> fitedYs;///<�����Ϻ��yֵ�������ʱ������Ϊ�������ʡ�ڴ�
	public:
		Fit();
		~Fit();

		///
		/// \brief ֱ�����-һԪ�ع�,��ϵĽ������ʹ��getFactor��ȡ������ʹ��getSlope��ȡб�ʣ�getIntercept��ȡ�ؾ�
		/// \param x �۲�ֵ��x
		/// \param y �۲�ֵ��y
		/// \param length x,y����ĳ���
		/// \param isSaveFitYs ��Ϻ�������Ƿ񱣴棬Ĭ�Ϸ�
		///
		//template<typename T>
		bool linearFit(const std::vector<double>& x, const std::vector<double>& y,bool isSaveFitYs=false);
		//template<typename T>
		bool linearFit(const double* x, const double* y,size_t length,bool isSaveFitYs=false);
		
		///
		/// \brief ����ʽ��ϣ����y=a0+a1*x+a2*x^2+����+apoly_n*x^poly_n
		/// \param x �۲�ֵ��x
		/// \param y �۲�ֵ��y
		/// \param poly_n ������ϵĽ�������poly_n=2����y=a0+a1*x+a2*x^2
		/// \param isSaveFitYs ��Ϻ�������Ƿ񱣴棬Ĭ����
		/// 
		template<typename T>
		void polyfit(const std::vector<typename T>& x,const std::vector<typename T>& y,int poly_n,bool isSaveFitYs=true);
		template<typename T>
		void polyfit(const T* x,const T* y,size_t length,int poly_n,bool isSaveFitYs=true);
		/// 
		/// \brief ��ȡϵ��
		/// \param ���ϵ��������
		///
		void getFactor(std::vector<double>& factor);
		/// 
		/// \brief ��ȡ��Ϸ��̶�Ӧ��yֵ��ǰ�������ʱ����isSaveFitYsΪtrue
		///
		void getFitedYs(std::vector<double>& fitedYs);
		/// 
		/// \brief ����x��ȡ��Ϸ��̵�yֵ
		/// \return ����x��Ӧ��yֵ
		///
		template<typename T>
		double getY(const T x);
		/// 
		/// \brief ��ȡб��
		/// \return б��ֵ
		///
		double getSlope();
		/// 
		/// \brief ��ȡ�ؾ�
		/// \return �ؾ�ֵ
		///
		double getIntercept();
		/// 
		/// \brief ʣ��ƽ����
		/// \return ʣ��ƽ����
		///
		double getSSE();
		/// 
		/// \brief �ع�ƽ����
		/// \return �ع�ƽ����
		///
		double getSSR();
		/// 
		/// \brief ���������
		/// \return ���������
		///
		double getRMSE();
		/// 
		/// \brief ȷ��ϵ����ϵ����0~1֮����������������ж�����Ŷȵ�һ����
		/// \return ȷ��ϵ��
		///
		double getR_square();
		/// 
		/// \brief ��ȡ����vector�İ�ȫsize
		/// \return ��С��һ������
		///
		template<typename T>
		size_t getSeriesLength(const std::vector<typename T>& x,const std::vector<typename T>& y);
		/// 
		/// \brief �����ֵ
		/// \return ��ֵ
		///
		template <typename T>
		static T Mean(const std::vector<T>& v);
		
		template <typename T>
		static T Mean(const T* v,size_t length);
		/// 
		/// \brief ��ȡ��Ϸ���ϵ���ĸ���
		/// \return ��Ϸ���ϵ���ĸ���
		///
		size_t getFactorSize();
		/// 
		/// \brief ���ݽ״λ�ȡ��Ϸ��̵�ϵ����
		/// ��getFactor(2),���ǻ�ȡy=a0+a1*x+a2*x^2+����+apoly_n*x^poly_n��a2��ֵ
		/// \return ��Ϸ��̵�ϵ��
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