#include "StdAfx.h"
#include "PointCloud.h"
#include "omp.h"
#include "math.h"
#include "glMath.h"
#include  <afxpriv.h>
#include "fit.h"

CPointCloud::CPointCloud(void)
{
	m_bPoint3DList = TRUE;
	m_bShowKPath = FALSE;
	m_bShowShortestPath = FALSE;

}

CPointCloud::~CPointCloud(void)
{

	mPrimitivePoint3DList.RemoveAll();
	
	mPoint3DList.RemoveAll();	    
	
}


void CPointCloud::InitPointCloud()
{
	mPrimitivePoint3DList.RemoveAll();
	mPoint3DList.RemoveAll();	      

	mPoint3DCurvatureList.RemoveAll();

	for (int i = 0; i < 4; i++)
	{
		mStick3leavesList[i].RemoveAll();
	}
	for (int i = 0; i < 3; i++)
	{
		mStick3leavesVeinXOZList[i].RemoveAll();
		mStick3leavesVeinList[i].RemoveAll();
	}
	mLeafNerMdlSplineList.RemoveAll();
	mInterPList.RemoveAll();
	mCurvatureList.RemoveAll();
}
  
void CPointCloud::drawSphere(GLfloat xx, GLfloat yy, GLfloat zz, GLfloat radius, GLfloat M, GLfloat N, ExColor3f mColor)
{
	float step_z = PI / M;
	float step_xy = 2 * PI / N;
	float x[4], y[4], z[4];

	float angle_z = 0.0;
	float angle_xy = 0.0;
	int i = 0, j = 0;
	glColor3f(mColor.r, mColor.g, mColor.b);
	//glBegin(GL_LINES);
	glBegin(GL_QUADS);
	for (i = 0; i < M; i++)
	{
		angle_z = i * step_z;

		for (j = 0; j < N; j++)
		{
			angle_xy = j * step_xy;

			x[0] = radius * sin(angle_z) * cos(angle_xy);
			y[0] = radius * sin(angle_z) * sin(angle_xy);
			z[0] = radius * cos(angle_z);

			x[1] = radius * sin(angle_z + step_z) * cos(angle_xy);
			y[1] = radius * sin(angle_z + step_z) * sin(angle_xy);
			z[1] = radius * cos(angle_z + step_z);

			x[2] = radius * sin(angle_z + step_z) * cos(angle_xy + step_xy);
			y[2] = radius * sin(angle_z + step_z) * sin(angle_xy + step_xy);
			z[2] = radius * cos(angle_z + step_z);

			x[3] = radius * sin(angle_z) * cos(angle_xy + step_xy);
			y[3] = radius * sin(angle_z) * sin(angle_xy + step_xy);
			z[3] = radius * cos(angle_z);

			for (int k = 0; k < 4; k++)
			{
				glVertex3f(xx + x[k], yy + y[k], zz + z[k]);
			}
		}
	}
	glEnd();
}
void CPointCloud::Draw( float unit, UINT mode )
{
	int i = 0, j = 0, nCnt = 0,iTEMP;
	int iOne,iTow,iThree;
	unit = 1.0;
	
	if (m_bPoint3DList)
	{
		nCnt = mPoint3DList.GetSize();
		glPointSize(5.0f);
		glBegin(GL_POINTS);
		glColor3f(0.0f, 1.0f, 0.0f);
		for (i = 0; i < nCnt; i++)
		{
			glVertex3f(mPoint3DList[i].x, mPoint3DList[i].y*unit, mPoint3DList[i].z*unit);
		}
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < nCnt - 1; i++)
		{
			glBegin(GL_LINES);
			glVertex3f(mPoint3DList[i].x, mPoint3DList[i].y, mPoint3DList[i].z);
			glVertex3f(mPoint3DList[i + 1].x, mPoint3DList[i + 1].y, mPoint3DList[i + 1].z);
			glEnd();
		}
	}
	
	if(m_bPrimitivePoint)
	{
		nCnt = mPrimitivePoint3DList.GetSize();
		glPointSize(2.0f);
		glBegin(GL_POINTS);
		for (i = 0; i < nCnt; i++)
		{
			if (mPrimitivePoint3DList[i].bShow)
			{
				//if (mPoint3DSelStatusList[i] == 1)
				//{
				//	glColor3f(1.0f, 0.0f, 0.0f);
				//}
				//else
				//{
				glColor3f(mPrimitivePoint3DList[i].r, mPrimitivePoint3DList[i].g, mPrimitivePoint3DList[i].b);
				//}
				//glColor3f(0.0f, 0.0f, 1.0f);
				glVertex3f(mPrimitivePoint3DList[i].x * unit, mPrimitivePoint3DList[i].y * unit, mPrimitivePoint3DList[i].z * unit);
				/*if(m_bLossPointcloud)
				{
					glColor3f(1.0f,0.0f,0.0f);
				}*/
			}
			else
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				glVertex3f(mPrimitivePoint3DList[i].x * unit, mPrimitivePoint3DList[i].y * unit, mPrimitivePoint3DList[i].z * unit);
			}
		}
		glEnd();
			
	}
	if (m_bStick3leavesPri)
	{
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);
		for (int i = 0; i < 4; i++)
		{
			nCnt = mStick3leavesList[i].GetSize();
			if (i == 0)
			{
				glColor3f(0.0f, 1.0f, 0.0f);

				for (int j = 0; j < nCnt; j++)
				{
					//glVertex3f(mStick3leavesList[i][j].x, mStick3leavesList[i][j].y, mStick3leavesList[i][j].z);
					drawSphere(mStick3leavesList[i][j].x, mStick3leavesList[i][j].y, mStick3leavesList[i][j].z, 0.5, 20, 20, ExColor3f(0.0, 1.0, 0.0));
				}
			}
			else
			{
				glColor3f(1.0f, 0.0f, 0.0f);
				for (int j = 0; j < nCnt; j++)
				{
					//glVertex3f(mStick3leavesList[i][j].x, mStick3leavesList[i][j].y, mStick3leavesList[i][j].z);
					drawSphere(mStick3leavesList[i][j].x, mStick3leavesList[i][j].y, mStick3leavesList[i][j].z, 0.5, 20, 20);
				}
			}
		}
		glEnd();
		nCnt = mStick3leavesList[0].GetSize();
		glColor3f(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < nCnt - 1; i++)
		{
			glBegin(GL_LINES);
			glVertex3f(mStick3leavesList[0][i].x, mStick3leavesList[0][i].y, mStick3leavesList[0][i].z);
			glVertex3f(mStick3leavesList[0][i + 1].x, mStick3leavesList[0][i + 1].y, mStick3leavesList[0][i + 1].z);
			glEnd();
		}

		for (int i = 0; i < 3; i++)
		{
			nCnt = mStick3leavesVeinList[i].GetSize();
			for (int j = 0; j < nCnt; j++)
			{
				drawSphere(mStick3leavesVeinList[i][j].x, mStick3leavesVeinList[i][j].y, mStick3leavesVeinList[i][j].z, 0.5 + 0.2, 20, 20, ExColor3f(1.0, 0.0, 0.0));
			}
		}
		glColor3f(0.0f, 0.0f, 1.0f);
		for (int i = 0; i < 3; i++)
		{
			nCnt = mStick3leavesVeinList[i].GetSize();
			for (int j = 0; j < nCnt - 1; j++)
			{
				glBegin(GL_LINES);
				glVertex3f(mStick3leavesVeinList[i][j].x, mStick3leavesVeinList[i][j].y, mStick3leavesVeinList[i][j].z);
				glVertex3f(mStick3leavesVeinList[i][j + 1].x, mStick3leavesVeinList[i][j + 1].y, mStick3leavesVeinList[i][j + 1].z);
				glEnd();
			}
		}
	}

}
Expoint3D CPointCloud::TranslationOrigin(CArray<Expoint3D,Expoint3D>& P3DList)
{
	int iCnt = P3DList.GetSize();
	float fTemp = 10000.0;
	int iOrder = 0;
	Expoint3D TargetPoint(0.0f,0.0f,0.0f);
	for(int i = 0; i < iCnt; i++)
	{
		if(P3DList[i].z < fTemp)
		{
			fTemp = P3DList[i].z;
			iOrder = i;
		}
	}
	TargetPoint = P3DList[iOrder];
	for(int i = 0; i < iCnt; i++)
	{
		P3DList[i].x = P3DList[i].x - TargetPoint.x;
		P3DList[i].y = P3DList[i].y - TargetPoint.y;
		P3DList[i].z = P3DList[i].z - TargetPoint.z;
	}
	return TargetPoint;
}

void CPointCloud::ModifiedRatioPointCloud(CArray<Expoint3D, Expoint3D>& P3DList,float fScale)
{
	int iCnt = 0;
	iCnt = P3DList.GetSize();
	for (int i = 0; i < iCnt; i++)
	{
		P3DList[i].x *= fScale;
		P3DList[i].y *= fScale;
		P3DList[i].z *= fScale;
	}
}

void CPointCloud::TranslationPointCloud(CArray<Expoint3D,Expoint3D>& P3DList,Expoint3D mPoint3D)
{
	int i , nCnt;
	nCnt = P3DList.GetSize();
	for( i = 0; i < nCnt; i++ )
	{
		P3DList[i].x = P3DList[i].x - mPoint3D.x;
		P3DList[i].y = P3DList[i].y - mPoint3D.y;
		P3DList[i].z = P3DList[i].z - mPoint3D.z;
	}
}

void CPointCloud::TranslationPrimitivePointCloud(float fX,float fY,float fZ)
{
	int i , nCnt;
	Expoint3D TargetPoint(fX,fY,fZ);
	nCnt = mPrimitivePoint3DList.GetSize();
	for( i = 0; i < nCnt; i++ )
	{
		mPrimitivePoint3DList[i].x = mPrimitivePoint3DList[i].x + TargetPoint.x;
		mPrimitivePoint3DList[i].y = mPrimitivePoint3DList[i].y + TargetPoint.y;
		mPrimitivePoint3DList[i].z = mPrimitivePoint3DList[i].z + TargetPoint.z;
	}
}


void CPointCloud::IteraCurveSmooth3D()
{
	int iNumPoint = mPoint3DList.GetSize();
	Expoint3D mp1, mp2;
	tVector planeVector, planePoint, linePointOne, linePointTow, IntersectPoint;
	int iNumNerMdlS = mLeafNerMdlSplineList.GetSize();
	bool bIntersectP;
	int ipm1 = 0, ipm2 = 0;
	int iNode = mCurvatureList.GetSize();
	for (int i = 0; i < iNode; i++)
	{
		if ((mCurvatureList[i] != 0) && (mCurvatureList[i] != iNumPoint - 1))
		{
			mp1 = mPoint3DList[mCurvatureList[i] - 1];
			mp2 = mPoint3DList[mCurvatureList[i] + 1];
			
			planeVector.x = mp2.x - mp1.x;
			planeVector.y = mp2.y - mp1.y;
			planeVector.z = mp2.z - mp1.z;
			planePoint.x = mPoint3DList[mCurvatureList[i]].x;
			planePoint.y = mPoint3DList[mCurvatureList[i]].y;
			planePoint.z = mPoint3DList[mCurvatureList[i]].z;
			ipm1 = 0;
			ipm2 = 0;
			for (int k = 0; k < mCurvatureList[i] - 1; k++)
			{
				ipm1 += mInterPList[k];
				ipm1++;
			}
			for (int k = 0; k < mCurvatureList[i] + 1; k++)
			{
				ipm2 += mInterPList[k];
				ipm2++;
			}
			for (int j = ipm1; j < ipm2; j++)
			{
				linePointOne.x = mLeafNerMdlSplineList[j].x;
				linePointOne.y = mLeafNerMdlSplineList[j].y;
				linePointOne.z = mLeafNerMdlSplineList[j].z;
				linePointTow.x = mLeafNerMdlSplineList[j + 1].x;
				linePointTow.y = mLeafNerMdlSplineList[j + 1].y;
				linePointTow.z = mLeafNerMdlSplineList[j + 1].z;
				bIntersectP = CalPlaneLinesegmentIntersectPoint(planeVector, planePoint, linePointOne, linePointTow, IntersectPoint);
				if (bIntersectP)
				{
					mPoint3DList[mCurvatureList[i]].x = IntersectPoint.x;
					mPoint3DList[mCurvatureList[i]].y = IntersectPoint.y;
					mPoint3DList[mCurvatureList[i]].z = IntersectPoint.z;
					break;
				}
			}
		}
	}
}


void CPointCloud::CurveSmooth3D(CArray<Expoint3D, Expoint3D>& mPt, CArray<Expoint3D, Expoint3D>& mPted)
{
	mPted.RemoveAll();
	int num = mPt.GetSize();
	if (num < 5) return;
	CPosition* testpt = new CPosition[num];
	for (int i = 0; i < num; i++)
	{
		testpt[i] = CPosition((double)mPt[i].x, (double)mPt[i].y, (double)mPt[i].z);
	}

	float fALLLength = 0.0;
	float fTemp = 0.0;
	for (int i = 0; i < num - 1; i++)
	{
		fTemp = mPt[i].DistanceTo(mPt[i + 1]);
		fALLLength += fTemp;
	}

	float fSubLength = 0.0;
	fSubLength = fALLLength / 30;
	int* Intnum = new int[num - 1];
	mInterPList.RemoveAll();
	for (int i = 0; i < num - 1; i++)
	{
		fTemp = mPt[i].DistanceTo(mPt[i + 1]);
		Intnum[i] = ceil(fTemp / fSubLength); 
		mInterPList.Add(Intnum[i]);
	}
	int num2 = num;
	CBSpline bspline;

	bspline.ThreeOrderBSplineInterpolatePt(testpt, num2, Intnum);

	mCurvatureList.RemoveAll();
	Expoint3D mTemp;
	int iNode = 0;
	float thresholdCur = 0.004;
	for (int i = 0; i < num2; i++)
	{
		mTemp.x = testpt[i].x;
		mTemp.y = testpt[i].y;
		mTemp.z = testpt[i].z;
		mTemp.curvature = testpt[i].dCurvature;
		mTemp.windingRate = testpt[i].dWindingRate;
		mPted.Add(mTemp);
		iNode = 0;
		if (mTemp.curvature > thresholdCur)
		{
			for (int j = 0; j < num; j++)
			{
				iNode += Intnum[j];
				iNode++;
				if (iNode > i)
				{
					mCurvatureList.Add(j);
					break;
				}
			}
		}
	}
	CArray<int, int> mCurvatureTest;
	iNode = mCurvatureList.GetSize();
	if (iNode > 0)
	{
		mCurvatureTest.Add(mCurvatureList[0]);
		for (int i = 1; i < iNode; i++)
		{
			if (mCurvatureList[i] != mCurvatureList[i - 1])
			{
				mCurvatureTest.Add(mCurvatureList[i]);
			}
		}
	}
	mCurvatureList.RemoveAll();
	iNode = mCurvatureTest.GetSize();
	for (int i = 0; i < iNode; i++)
	{
		mCurvatureList.Add(mCurvatureTest[i]);
	}
	delete Intnum;
	delete testpt;
}

void CPointCloud::LeafBasePlane(CArray<Expoint3D, Expoint3D>& mLeafPt)
{
	int iCnt = 0;
	iCnt = mLeafPt.GetSize();
	CArray<Expoint3D, Expoint3D> mPt;
	for (int i = 0; i < iCnt / 3; i++)
	{
		mPt.Add(mLeafPt[i]);
	}
	LinearFit2D(mPt);

	VECTORF vec;
	vec[0] = mFitLine[1].x - mFitLine[0].x;
	vec[1] = mFitLine[1].y - mFitLine[0].y;
	vec[2] = mFitLine[1].z - mFitLine[0].z;
	vec[3] = 0.0;
	VECTORF vecB;
	vecB[0] = 1.0;
	vecB[1] = 0.0;
	vecB[2] = 0.0;
	float fAngle;
	GetVecAnglef(vec, vecB, &fAngle);

	if ((vec[0] > 0.0) && (vec[1] > 0.0))
	{
		fAngle = 180 - fAngle;
	}
	else if ((vec[0] < 0.0) && (vec[1] > 0.0))
	{
		fAngle = 360 - fAngle;
	}

	Matx4x4 a;
	Rotate3D(2, fAngle, a);
	VECTORF S;
	VECTORF d;

	iCnt = mLeafPt.GetSize();
	for (int i = 0; i < iCnt; i++)
	{
		S[X] = mLeafPt[i].x;
		S[Y] = mLeafPt[i].y;
		S[Z] = mLeafPt[i].z;
		VecTransformf(S, d, a);
		mLeafPt[i].x = d[X];
		mLeafPt[i].y = d[Y];
		mLeafPt[i].z = d[Z];
	}

	iCnt = mLeafPt.GetSize();
	int iNum = 0;
	for (int i = 0; i < iCnt; i++)
	{
		if (mLeafPt[i].x > 0.0)
		{
			iNum++;
		}
	}
	if (iNum < (iCnt - iNum))
		//if (mLeafNerMdlSplineList[iCnt - 1].x < 0.0)
	{
		Rotate3D(2, 180, a);

		iCnt = mLeafPt.GetSize();
		for (int i = 0; i < iCnt; i++)
		{
			S[X] = mLeafPt[i].x;
			S[Y] = mLeafPt[i].y;
			S[Z] = mLeafPt[i].z;
			VecTransformf(S, d, a);
			mLeafPt[i].x = d[X];
			mLeafPt[i].y = d[Y];
			mLeafPt[i].z = d[Z];
		}
	}
}

void CPointCloud::LinearFit2D(CArray<Expoint3D, Expoint3D>& mPointCloud)
{
	size_t m_size = mPointCloud.GetSize();
	if (m_size < 2)
	{
		return;
	}

	std::vector<double> m_x, m_y;
	float a1, a2, b1, b2;
	m_x.resize(m_size);
	m_y.resize(m_size);
	for (int i = 0; i < m_size; i++)
	{
		m_x[i] = mPointCloud[i].x;
		m_y[i] = mPointCloud[i].y;
	}
	czy::Fit fit;
	fit.linearFit(m_x, m_y);
	a1 = fit.getSlope();
	b1 = fit.getIntercept();

	float fx, fy, fz;
	fz = 0.0;
	fx = -10.0;
	fy = a1 * fx + b1;
	mFitLine[0].x = fx;
	mFitLine[0].y = fy;
	mFitLine[0].z = fz;
	fz = 0.0;
	fx = 80.0;
	fy = a1 * fx + b1;
	mFitLine[1].x = fx;
	mFitLine[1].y = fy;
	mFitLine[1].z = fz;

	//Expoint3D mTemp;
	//mTemp = mFitLine[1] - mFitLine[0];
	//mFitLine[1] = ( mFitLine[1] - mFitLine[0])* 10  + mFitLine[0];	
}

void CPointCloud::SectionalCurvature(float& mCur, float& fCur, float& mWind, float& fWind)
{
	int num = mPoint3DList.GetSize();
	if (num < 5) return;
	CPosition* testpt = new CPosition[num];
	for (int i = 0; i < num; i++)
	{
		testpt[i] = CPosition((double)mPoint3DList[i].x, (double)mPoint3DList[i].y, (double)mPoint3DList[i].z);
	}
	int* Intnum = new int[num - 1];
	mInterPList.RemoveAll();
	for (int i = 0; i < num - 1; i++)
	{
		Intnum[i] = 0;
		mInterPList.Add(Intnum[i]);
	}
	int num2 = num;
	CBSpline bspline;
	bspline.ThreeOrderBSplineInterpolatePt(testpt, num2, Intnum);
	mCurvatureList.RemoveAll();
	Expoint3D mTemp;
	int iNode = 0;
	float thresholdCur = 0.004;
	float fTempCur = -1000.0;
	int iCur = 0;
	float fTempWind = -1000.0;
	int iWind = 0;
	for (int i = num2 * 0.2; i < num2; i++)
	{

		if (testpt[i].dCurvature > fTempCur)
		{
			fTempCur = testpt[i].dCurvature;
			iCur = i;
		}
	
		if (testpt[i].dWindingRate > fTempWind)
		{
			fTempWind = testpt[i].dWindingRate;
			iWind = i;
		}
	}
	fCur = fTempCur;
	mCur = iCur * 1.0 / num2;
	fWind = fTempWind;
	mWind = iWind * 1.0 / num2;
	delete Intnum;
	delete testpt;
}


BOOL CPointCloud::LoadLPLSPointCloudData(CString strPath)
{
	mPoint3DList.RemoveAll();
	//m_unitScan = 1.0;
	CString strTemp(_T(""));
	int i = 0;
	CStdioFile f;
	CFileException e;
	Expoint3D pPoint3D;
	CString pathname;
	BOOL m_bFlag = TRUE;
	char str[500];
	int iCnt = 0;
	pathname = strPath;

	CString strFileName = pathname;
	int ipos = strFileName.ReverseFind('\\');
	strFileName = strFileName.Right(strFileName.GetLength() - 1 - ipos);

	ipos = strFileName.ReverseFind('.');
	m_strFileName = strFileName.Left(ipos);

	CString strFilePath;
	ipos = pathname.ReverseFind('\\');
	strFilePath = pathname.Left(ipos + 1);
	m_strFilePath = strFilePath;
	/////////
	if (!f.Open(pathname, CFile::modeRead | CFile::typeText, &e))
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return false;
	}
	f.SeekToBegin();
	while (m_bFlag)
	{
		m_bFlag = f.ReadString(strTemp);
		strTemp.Trim();
		if (strTemp.GetAt(0) == '#' || strTemp.GetAt(0) == '\n' || strTemp.GetAt(0) == '%')
		{
		}
		else if (strTemp.GetLength() > 3)
		{
			for (i = 0; i < strTemp.GetLength(); i++)
			{
				str[i] = char(strTemp.GetAt(i));
			}
			str[i] = '\0';
			sscanf_s(str, "%f %f %f", &pPoint3D.x, &pPoint3D.y, &pPoint3D.z);
			pPoint3D.x = pPoint3D.x * m_unitScan;
			pPoint3D.y = pPoint3D.y * m_unitScan;
			pPoint3D.z = pPoint3D.z * m_unitScan;
			pPoint3D.iPointOne = iCnt;  
			pPoint3D.iPointTow = iCnt;  
			pPoint3D.iPointThree = iCnt;
			pPoint3D.iOrder = iCnt;
			pPoint3D.iCntConnect = 0;
			pPoint3D.bShow = FALSE;
			pPoint3D.bLink = TRUE;
			iCnt++;
			mPoint3DList.Add(pPoint3D);
		}
	}
	f.Close();
	return true;
}


void CPointCloud::SortPointCloud(CArray<Expoint3D, Expoint3D>& mP3DList, int iAxis)
{
	int i = 0, j = 0;
	int iNum = 0;
	float fMin = 10000.0;
	Expoint3D tPoint3D;
	int iNode = mP3DList.GetSize();
	for (i = 0; i < iNode; i++)
	{
		iNum = -1;
		if (iAxis == 1)
		{
			fMin = mP3DList[i].x;
		}
		else if (iAxis == 2)
		{
			fMin = mP3DList[i].y;
		}
		else if (iAxis == 3)
		{
			fMin = mP3DList[i].z;
		}

		for (j = i + 1; j < iNode; j++)
		{
			if (mP3DList[j].z < fMin)
			{
				if (iAxis == 1)
				{
					fMin = mP3DList[i].x;
				}
				else if (iAxis == 2)
				{
					fMin = mP3DList[i].y;
				}
				else if (iAxis == 3)
				{
					fMin = mP3DList[i].z;
				}
				iNum = j;
			}
		}
		if (iNum != -1)
		{
			tPoint3D = mP3DList[i];
			mP3DList[i] = mP3DList[iNum];
			mP3DList[iNum] = tPoint3D;
		}
	}
	for (i = 0; i < iNode; i++)
	{
		mP3DList[i].iOrder = i;
		mP3DList[i].iPointOne = i;
		mP3DList[i].iPointTow = i;
		mP3DList[i].iPointThree = i;
	}
}


BOOL CPointCloud::SavePC(CArray<Expoint3D, Expoint3D>& mPC, CString strPath, BOOL bRGB)
{
	CString strTemp("");
	int i = 0, j = 0, nCntPts = 0;
	nCntPts = mPC.GetSize();
	if (nCntPts == 0)
	{
		return FALSE;
	}
	CStdioFile f;
	CFileException e;
	if (!f.Open(strPath, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &e))
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return FALSE;
	}
	f.SeekToBegin();
	

	for (i = 0; i < nCntPts; i++)
	{
		if (bRGB)
		{
			strTemp.Format(_T("%f %f %f %f %f %f\n"), mPC[i].x, mPC[i].y, mPC[i].z, mPC[i].r, mPC[i].g, mPC[i].b);
		}
		else
		{
			strTemp.Format(_T("%f %f %f\n"), mPC[i].x, mPC[i].y, mPC[i].z);
		}

		f.WriteString(strTemp);
	}
	f.SeekToBegin();
	f.Close();
	return TRUE;
}


Expoint3D CPointCloud::LoadPrimitivePC(CString strPath, CArray<Expoint3D, Expoint3D>& mPC, bool bRGB, bool bRGBINT, bool bIntensity, bool bNormal)
{
	mPC.RemoveAll();
	//m_unitScan = 1.0;
	CString strTemp(_T(""));
	int i = 0;
	CStdioFile f;
	CFileException e;
	Expoint3D pPoint3D;
	Expoint3D pCenterPoint(0.0, 0.0, 0.0);
	BOOL m_bFlag = TRUE;
	char str[500];
	int iCnt = 0;
	if (!f.Open(strPath, CFile::modeRead | CFile::typeText, &e))
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		//AfxMessageBox(szError);
		//f.Close();
		return pPoint3D;
	}
	f.SeekToBegin();
	while (m_bFlag)
	{
		m_bFlag = f.ReadString(strTemp);
		strTemp.Trim();
		if (strTemp.GetAt(0) == '#' || strTemp.GetAt(0) == '\n' || strTemp.GetAt(0) == '%')
		{
		}
		else if (strTemp.GetLength() == 0)
		{
		}
		else if (strTemp.GetAt(0) == 'E')
		{
			pCenterPoint = pCenterPoint / iCnt;
			return pCenterPoint;
		}
		else if (strTemp.GetLength() > 3)
		{
			for (i = 0; i < strTemp.GetLength(); i++)
			{
				str[i] = char(strTemp.GetAt(i));
			}
			str[i] = '\0';
			if (bRGB)
			{
				sscanf_s(str, "%f %f %f %f %f %f", &pPoint3D.x, &pPoint3D.y, &pPoint3D.z, &pPoint3D.r, &pPoint3D.g, &pPoint3D.b);
				/*
				if (bRGBINT)
				{
					pPoint3D.r = pPoint3D.r / 255;
					pPoint3D.g = pPoint3D.g / 255;
					pPoint3D.b = pPoint3D.b / 255;
				}
				*/

				if ((pPoint3D.r > 1.0) && (pPoint3D.g > 1.0))
				{
					pPoint3D.r = pPoint3D.r / 255;
					pPoint3D.g = pPoint3D.g / 255;
					pPoint3D.b = pPoint3D.b / 255;
				}
				pPoint3D.x = pPoint3D.x * m_unitScan;
				pPoint3D.y = pPoint3D.y * m_unitScan;
				pPoint3D.z = pPoint3D.z * m_unitScan;
			}
			else
			{
				sscanf_s(str, "%f %f %f", &pPoint3D.x, &pPoint3D.y, &pPoint3D.z);
				pPoint3D.x = pPoint3D.x * m_unitScan;
				pPoint3D.y = pPoint3D.y * m_unitScan;
				pPoint3D.z = pPoint3D.z * m_unitScan;
			}
			mPC.Add(pPoint3D);
			pCenterPoint = pCenterPoint + pPoint3D;
			iCnt++;

		}
	}
	f.Close();
	pCenterPoint = pCenterPoint / iCnt;
	return pCenterPoint;
}