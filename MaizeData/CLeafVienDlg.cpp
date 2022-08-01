// CLeafVienDlg.cpp: 
//

#include "stdafx.h"
#include "CLeafVienDlg.h"
#include "afxdialogex.h"
#include "PointCloud.h"
#include "Fit3D.h"
// CLeafVienDlg 对话框

IMPLEMENT_DYNAMIC(CLeafVienDlg, CDialogEx)

CLeafVienDlg::CLeafVienDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LeafVienDlg, pParent)
{

}

CLeafVienDlg::~CLeafVienDlg()
{
}

void CLeafVienDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLeafVienDlg, CDialogEx)
	ON_BN_CLICKED(IDC_InputLeafVeinBtn, &CLeafVienDlg::OnBnClickedInputleafveinbtn)
	ON_BN_CLICKED(IDC_BatchSmothBtn, &CLeafVienDlg::OnBnClickedBatchsmothbtn)
	ON_BN_CLICKED(IDC_BatchPhenBtn, &CLeafVienDlg::OnBnClickedBatchphenbtn)
	ON_BN_CLICKED(IDC_LoadDataBtn, &CLeafVienDlg::OnBnClickedLoaddatabtn)
END_MESSAGE_MAP()



void CLeafVienDlg::LoadMaizeModel()
{
	if (!m_pMaizePointCloud)
	{
		CWnd* pParent = this->GetParent();
		UINT nID = GetDlgCtrlID();
		::PostMessage(pParent->GetSafeHwnd(), WM_POINTCLOUD_LOADMODEL, nID, 0);
		AfxGetMainWnd()->SendMessage(WM_POINTCLOUD_LOADMODEL, nID, 0);
	}
}

void CLeafVienDlg::SetObject(CPointCloud* pPointCloud)
{
	m_pMaizePointCloud = pPointCloud;
}
void CLeafVienDlg::OnBnClickedInputleafveinbtn()
{

	LoadMaizeModel();
	m_pMaizePointCloud->m_unitScan = 1.0;
	m_pMaizePointCloud->InitPointCloud();
	//m_pMaizePointCloud->LoadPointCloudData();
	BOOL bOk = false;

	int i = 0;
	CStdioFile f;
	CFileException e;
	CString pathname;
	CFileDialog dlg(TRUE, _T("*.smoot"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("PointCloud files(*.smoot)|*.smoot|Allfiles(*.*)|*.*||"));
	if (dlg.DoModal())
	{
		pathname = dlg.GetPathName();
		bOk = m_pMaizePointCloud->LoadLPLSPointCloudData(pathname);
	}

	int iCnt = m_pMaizePointCloud->mPoint3DList.GetSize();
	if (iCnt < 5)
	{
		return;
	}
	m_ptBase = m_pMaizePointCloud->mPoint3DList[0];
	m_pMaizePointCloud->TranslationPointCloud(m_pMaizePointCloud->mPoint3DList, m_ptBase);
	m_pMaizePointCloud->m_bPoint3DList = true;
	m_pMaizePointCloud->m_bStick3leavesPri = false;
	InvalidatePointCloudView();//刷新视口
}


BOOL CPointCloud::LoadLPLSPointCloudData()
{
	int i = 0;
	CStdioFile f;
	CFileException e;
	CString pathname;
	CFileDialog dlg(TRUE, _T("*.smoot"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("PointCloud files(*.smoot)|*.smoot|Allfiles(*.*)|*.*||"));
	if (dlg.DoModal() == IDOK)
	{
		pathname = dlg.GetPathName();
		i = i + 1;
		return LoadLPLSPointCloudData(pathname);
	}
	else
	{
		return false;
	}
}
void CLeafVienDlg::InvalidatePointCloudView()
{
	//Message
	CWnd* pParent = this->GetParent();
	UINT nID = GetDlgCtrlID();
	//::PostMessage(pParent->GetSafeHwnd(),WM_POINTCLOUD_CHANGE,nID,0);
	//AfxGetMainWnd()->SendMessage(WM_POINTCLOUD_CHANGE, nID, 0);
	CString strText = L"100:10:dfffgg";

	strText = "";
	strText.Format(_T("%d:%d:"), 0, 0);

	strText = strText + m_pMaizePointCloud->m_strFileName;
	AfxGetMainWnd()->SendMessage(WM_POINTCLOUD_CHANGE, nID, (LPARAM)strText.GetBuffer(256));
}


CString CLeafVienDlg::Loaddirectory()
{
	CString sFolderPath;
	BROWSEINFO bi;
	char Buffer[MAX_PATH];

	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = (LPWSTR)Buffer;
	bi.lpszTitle = L"select folder";
	//bi.ulFlags = BIF_BROWSEINCLUDEFILES;
	bi.ulFlags = BIF_EDITBOX;
	bi.lpfn = NULL;
	
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, (LPWSTR)Buffer);

		sFolderPath.Format(L"%s", Buffer);
	}
	LPMALLOC lpMalloc;
	if (FAILED(SHGetMalloc(&lpMalloc))) return L"";
	
	lpMalloc->Free(pIDList);
	lpMalloc->Release();
	return sFolderPath;
}

void CLeafVienDlg::OnBnClickedBatchsmothbtn()
{
	UpdateData(TRUE);
	CString m_cstrFileList = L"";
	CString strPath;
	CString m_strFileName;
	CFileFind tempFind;
	BOOL bFound; 
	CString sFolderPath;
	BOOL bRootDirectory = FALSE;
	int ipos = 0;
	float fUnitScan = 0;
	int iTemp = 0;
	LoadMaizeModel();
	m_pMaizePointCloud->m_unitScan = 1.0;

	sFolderPath = Loaddirectory();
	if (sFolderPath.GetLength() == 0)
	{
		MessageBox(L"select folder!", L"tips", MB_OK | MB_ICONWARNING);
		return;
	}
	mVarietyPhenotypeList.RemoveAll();
	bFound = tempFind.FindFile(sFolderPath + L"\\*.*");
	CString strTmp;   
	while (bFound)    
	{
		bFound = tempFind.FindNextFile(); 
										  
		if (tempFind.IsDots())
		{
			continue;
		}
		else if (tempFind.IsDirectory())
		{
			strPath = tempFind.GetFilePath();
			SmoothFileTraversal(strPath);
		}
	}
	tempFind.Close();
	MessageBox(L"Finish!");
}


void CLeafVienDlg::SmoothFileTraversal(CString strPath)
{
	CFileFind tempFind;
	BOOL bFound; 
	bFound = tempFind.FindFile(strPath + L"\\*.*");
	bool bRootDirectory;
	int idataSource = 1;
	while (bFound)
	{
		bFound = tempFind.FindNextFile();
		if (tempFind.IsDots())
		{
			continue;
		}
		else if (tempFind.IsDirectory())
		{
			strPath = tempFind.GetFilePath();
			
			bRootDirectory = RootDirectory(strPath);
			if (bRootDirectory)
			{
				Stick3leaves_Smooth(strPath, idataSource);
			}
			else
			{
				SmoothFileTraversal(strPath);
			}
		}
	}
	tempFind.Close();
}

BOOL CLeafVienDlg::RootDirectory(CString strPath)
{
	CFileFind tempFind;
	BOOL bFound; 
	bFound = tempFind.FindFile(strPath + L"\\*.*");
	CString strTmp;   
	CString strFileName;
	CString strTxt;
	int ipos = 0;
	while (bFound)     
	{
		bFound = tempFind.FindNextFile(); 
		if (tempFind.IsDots())
		{
			continue;
		}
		else if (!tempFind.IsDirectory() && !tempFind.IsDots())
		{
			tempFind.Close();
			return TRUE;
		}
	}
	return FALSE;
}

void CLeafVienDlg::Stick3leaves_Smooth(CString strPath, int idataSource)
{

	float fUnitScan = 0;
	//m_pMaizePointCloud->m_unitScan = 1.0;
	m_pMaizePointCloud->m_unitScan = 0.1;
	m_pMaizePointCloud->InitPointCloud();
	CString strPathL;
	
	strPathL = strPath + _T("\\0.txt");
	m_pMaizePointCloud->LoadPrimitivePC(strPathL, m_pMaizePointCloud->mStick3leavesList[0]);
	strPathL = strPath + _T("\\F-3.txt");
	m_pMaizePointCloud->LoadPrimitivePC(strPathL, m_pMaizePointCloud->mStick3leavesList[1]);
	strPathL = strPath + _T("\\F.txt");
	m_pMaizePointCloud->LoadPrimitivePC(strPathL, m_pMaizePointCloud->mStick3leavesList[2]);
	strPathL = strPath + _T("\\F+3.txt");
	m_pMaizePointCloud->LoadPrimitivePC(strPathL, m_pMaizePointCloud->mStick3leavesList[3]);

	int iCnt = 0;
	iCnt = m_pMaizePointCloud->mStick3leavesList[0].GetSize();
	if (iCnt < 4) return;
	float fTemp = 0.0;
	
	for (int i = 0; i < 4; i++)
	{
		iCnt = m_pMaizePointCloud->mStick3leavesList[i].GetSize();
		for (int j = 0; j < iCnt; j++)
		{
			m_pMaizePointCloud->mStick3leavesList[i][j].z *= -1;
		}
	}

	m_pMaizePointCloud->SortPointCloud(m_pMaizePointCloud->mStick3leavesList[0]);
	
	Expoint3D pBasePt = m_pMaizePointCloud->mStick3leavesList[0][0];
	for (int i = 0; i < 4; i++)
	{
		m_pMaizePointCloud->TranslationPointCloud(m_pMaizePointCloud->mStick3leavesList[i], pBasePt);
	}

	for (int i = 1; i < 4; i++)
	{
		m_pMaizePointCloud->mStick3leavesVeinList[i - 1].RemoveAll();
		iCnt = m_pMaizePointCloud->mStick3leavesList[i].GetSize();
		if (iCnt > 0)
		{
			for (int j = 2; j < iCnt; j = j + 5)
			{
				m_pMaizePointCloud->mStick3leavesVeinList[i - 1].Add(m_pMaizePointCloud->mStick3leavesList[i][j]);
			}
			m_pMaizePointCloud->mStick3leavesVeinList[i - 1].Add(m_pMaizePointCloud->mStick3leavesList[i][iCnt - 1]);
		}
	}
	
	CArray<Expoint3D, Expoint3D> mP3DList;
	iCnt = m_pMaizePointCloud->mStick3leavesList[0].GetSize();
	for (int i = 0; i < 4; i++)
	{
		mP3DList.Add(m_pMaizePointCloud->mStick3leavesList[0][i]);
	}
	Expoint3D mTempPT;
	mTempPT = (m_pMaizePointCloud->mStick3leavesList[0][0] + m_pMaizePointCloud->mStick3leavesList[0][1]) * 0.5;
	mP3DList.Add(mTempPT);
	mTempPT = (m_pMaizePointCloud->mStick3leavesList[0][1] + m_pMaizePointCloud->mStick3leavesList[0][2]) * 0.5;
	mP3DList.Add(mTempPT);
	mTempPT = (m_pMaizePointCloud->mStick3leavesList[0][2] + m_pMaizePointCloud->mStick3leavesList[0][3]) * 0.5;
	mP3DList.Add(mTempPT);
	CFit3D mFit3D;
	mFit3D.LinearFit3D(mP3DList, m_pMaizePointCloud->mFitLine[0], m_pMaizePointCloud->mFitLine[1]);
	////////////////////////////////////////////////////////////////////////////////////////////////////
	
	MaizeCorrectVertical();
	
	for (int i = 1; i < 4; i++)
	{
		m_pMaizePointCloud->mStick3leavesVeinList[i - 1].RemoveAll();
		iCnt = m_pMaizePointCloud->mStick3leavesList[i].GetSize();
		if (iCnt > 0)
		{
			for (int j = 2; j < iCnt; j = j + 5)
			{
				m_pMaizePointCloud->mStick3leavesVeinList[i - 1].Add(m_pMaizePointCloud->mStick3leavesList[i][j]);
			}
			m_pMaizePointCloud->mStick3leavesVeinList[i - 1].Add(m_pMaizePointCloud->mStick3leavesList[i][iCnt - 1]);
		}
	}
	
	CArray<Expoint3D, Expoint3D> mTempList;//顶点
	Expoint3D mpoint;
	//float fDisInterval = 40; 
	float fDisInterval = 40;
	int iNumNode = 0;
	for (int k = 0; k < 3; k++)
	{
		m_pMaizePointCloud->mLeafNerMdlSplineList.RemoveAll();
		mTempList.RemoveAll();
		
		iCnt = m_pMaizePointCloud->mStick3leavesVeinList[k].GetSize();
		if (iCnt == 0)
		{
			continue;
		}
		m_pMaizePointCloud->mPoint3DList.RemoveAll();
		for (int j = 0; j < iCnt; j++)
		{
			m_pMaizePointCloud->mPoint3DList.Add(m_pMaizePointCloud->mStick3leavesVeinList[k][j]);
		}
		mTempList.Add(m_pMaizePointCloud->mPoint3DList[0]);
		for (int i = 0; i < iCnt - 1; i++)
		{
			fTemp = m_pMaizePointCloud->mPoint3DList[i].DistanceTo(m_pMaizePointCloud->mPoint3DList[i + 1]);
			iNumNode = ceil(fTemp / fDisInterval);
			for (int j = 0; j < iNumNode - 1; j++)
			{
				mpoint = m_pMaizePointCloud->mPoint3DList[i] + (m_pMaizePointCloud->mPoint3DList[i + 1] - m_pMaizePointCloud->mPoint3DList[i]) * ((j + 1) * 1.0 / iNumNode);
				mTempList.Add(mpoint);
			}
			mTempList.Add(m_pMaizePointCloud->mPoint3DList[i + 1]);
		}
		m_pMaizePointCloud->mPoint3DList.RemoveAll();
		iCnt = mTempList.GetSize();
		for (int i = 0; i < iCnt; i++)
		{
			m_pMaizePointCloud->mPoint3DList.Add(mTempList[i]);
		}
		for (int i = 0; i < 20; i++)
		{
			m_pMaizePointCloud->CurveSmooth3D(m_pMaizePointCloud->mPoint3DList, m_pMaizePointCloud->mLeafNerMdlSplineList);
			m_pMaizePointCloud->IteraCurveSmooth3D();
		}
		m_pMaizePointCloud->mStick3leavesVeinList[k].RemoveAll();
		iCnt = m_pMaizePointCloud->mLeafNerMdlSplineList.GetSize();
		for (int i = 0; i < iCnt; i++)
		{
			m_pMaizePointCloud->mStick3leavesVeinList[k].Add(m_pMaizePointCloud->mLeafNerMdlSplineList[i]);
		}
	}
	
	strPathL = strPath + _T("\\F-3.smoot");
	m_pMaizePointCloud->SavePC(m_pMaizePointCloud->mStick3leavesVeinList[0], strPathL, false);
	strPathL = strPath + _T("\\F.smoot");
	m_pMaizePointCloud->SavePC(m_pMaizePointCloud->mStick3leavesVeinList[1], strPathL, false);
	strPathL = strPath + _T("\\F+3.smoot");
	m_pMaizePointCloud->SavePC(m_pMaizePointCloud->mStick3leavesVeinList[2], strPathL, false);
}


void CLeafVienDlg::MaizeCorrectVertical()
{
	int iCnt = 0;
	Expoint3D mStemVector;
	mStemVector = m_pMaizePointCloud->mFitLine[1] - m_pMaizePointCloud->mFitLine[0];
	/*
	tVector a, b, result;
	b.x = mStemVector.x;
	b.y = mStemVector.y;
	b.z = mStemVector.z;
	iCnt = m_pMaizePointCloud->mStick3leavesList[0].GetSize();
	for(int i = 0; i < iCnt; i++)
	{
		a.x = m_pMaizePointCloud->mStick3leavesList[0][i].x;
		a.y = m_pMaizePointCloud->mStick3leavesList[0][i].y;
		a.z = m_pMaizePointCloud->mStick3leavesList[0][i].z;
		PointToVectorPedal(a, b, result);
		m_pMaizePointCloud->mStick3leavesList[0][i].x = result.x;
		m_pMaizePointCloud->mStick3leavesList[0][i].y = result.y;
		m_pMaizePointCloud->mStick3leavesList[0][i].z = result.z;
	}
	*/
	
	Matx4x4 aM;
	VECTORF S;
	VECTORF d;
	Rotate3DtoZ(mStemVector.x, mStemVector.y, mStemVector.z, aM);
	
	for (int i = 0; i < 4; i++)
	{
		iCnt = m_pMaizePointCloud->mStick3leavesList[i].GetSize();
		for (int j = 0; j < iCnt; j++)
		{
			S[X] = m_pMaizePointCloud->mStick3leavesList[i][j].x;
			S[Y] = m_pMaizePointCloud->mStick3leavesList[i][j].y;
			S[Z] = m_pMaizePointCloud->mStick3leavesList[i][j].z;
			VecTransformf(S, d, aM);
			m_pMaizePointCloud->mStick3leavesList[i][j].x = d[X];
			m_pMaizePointCloud->mStick3leavesList[i][j].y = d[Y];
			m_pMaizePointCloud->mStick3leavesList[i][j].z = d[Z];
		}
	}
	
	Expoint3D pBasePt = m_pMaizePointCloud->mStick3leavesList[0][0];
	for (int i = 0; i < 4; i++)
	{
		m_pMaizePointCloud->TranslationPointCloud(m_pMaizePointCloud->mStick3leavesList[i], pBasePt);
	}
}

void CLeafVienDlg::OnBnClickedBatchphenbtn()
{
	CString m_cstrFileList = L"";
	CString strPath;
	CString m_strFileName;
	CFileFind tempFind;
	BOOL bFound; 
	CString sFolderPath;
	BOOL bRootDirectory = FALSE;
	int ipos = 0;
	sFolderPath = Loaddirectory();
	if (sFolderPath.GetLength() == 0)
	{
		MessageBox(L"select folder!", L"tips", MB_OK | MB_ICONWARNING);
		return;
	}
	mVarietyPhenotypeList.RemoveAll();
	bFound = tempFind.FindFile(sFolderPath + L"\\*.*");
	CString strTmp;   
	while (bFound)   
	{
		bFound = tempFind.FindNextFile(); 
										  
		if (tempFind.IsDots())
		{
			continue;
		}
		else if (tempFind.IsDirectory())
		{
			strPath = tempFind.GetFilePath();
			SmoothPhenFileTraversal(strPath);
		}
	}
	tempFind.Close();
	strPath = sFolderPath + _T("\\PAR_1.txt");
	SaveParameter2(strPath);
	MessageBox(L"Finish!");
}


void CLeafVienDlg::SmoothPhenFileTraversal(CString strPath)
{
	CFileFind tempFind;
	BOOL bFound; 
	bFound = tempFind.FindFile(strPath + L"\\*.*");
	CString strTmp;   
	CString strFileName;
	CString strTxt;
	int ipos = 0;
	bool bRootDirectory;
	int iCnt = 0;
	Expoint3D mTempPT;
	while (bFound)     
	{
		bFound = tempFind.FindNextFile(); 
		if (tempFind.IsDots())
		{
			continue;
		}
		else if (tempFind.IsDirectory())
		{
			strPath = tempFind.GetFilePath();
			
			bRootDirectory = RootDirectory(strPath);
			if (bRootDirectory)
			{
				m_strNameVariety = "";
				m_iNumVariety = 0;
				m_iNumSample = 0;
				for (int i = 0; i < 3; i++)
				{
					m_fAngle[i] = 0.0;
					m_fLength[i] = 0.0;
					m_fVerticalHeight[i] = 0.0;
					m_fHorizontalLength[i] = 0.0;
					m_fUpwardGrowthMeasure[i] = 0.0;
					m_fOutwardGrowthMeasure[i] = 0.0;
					m_fDeviationAngle[i] = 0.0;
					m_iTipTop[i] = 1;
					m_fDeviationTip[i] = 0.0;
					m_fCurvatureRatio[i] = 0.0;
					m_fVolume[i] = 0.0;
					m_fMaxCur[i] = 0.0;
					m_fMaxCurPos[i] = 0.0;
					m_fMaxWind[i] = 0.0;
					m_fMaxWindPos[i] = 0.0;
					m_fProjectionArea[i] = 0.0;
				}
				/////////////////////////////
				float fUnitScan = 0;
				m_pMaizePointCloud->m_unitScan = 1.0;
				m_pMaizePointCloud->InitPointCloud();
				CString strPathL;
				strPathL = strPath + _T("\\F-3.smoot");
				m_pMaizePointCloud->LoadPrimitivePC(strPathL, m_pMaizePointCloud->mStick3leavesVeinList[0]);
				strPathL = strPath + _T("\\F.smoot");
				m_pMaizePointCloud->LoadPrimitivePC(strPathL, m_pMaizePointCloud->mStick3leavesVeinList[1]);
				strPathL = strPath + _T("\\F+3.smoot");
				m_pMaizePointCloud->LoadPrimitivePC(strPathL, m_pMaizePointCloud->mStick3leavesVeinList[2]);
				///////////////////////////////////////////////////////////
				for (int i = 0; i < 3; i++)
				{
					m_pMaizePointCloud->mStick3leavesVeinXOZList[i].RemoveAll();
					iCnt = m_pMaizePointCloud->mStick3leavesVeinList[i].GetSize();
					if (iCnt > 5)
					{
						for (int j = 0; j < iCnt; j++)
						{
							m_pMaizePointCloud->mStick3leavesVeinXOZList[i].Add(m_pMaizePointCloud->mStick3leavesVeinList[i][j]);
						}
						mTempPT = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][0];
						m_pMaizePointCloud->TranslationPointCloud(m_pMaizePointCloud->mStick3leavesVeinXOZList[i], mTempPT);
						m_pMaizePointCloud->LeafBasePlane(m_pMaizePointCloud->mStick3leavesVeinXOZList[i]);
					}
				}
				////////////////////////////////////////////////////
				LeafLength();	
				LeafAngle2();
				LeafVeinGrowth();
				DeviationAngle();
				DeviationTip();
				LeafVeinCurvatureRatio();
				LeafVeinCurvatureAndWindingRate();
				LeafVeinProjectionArea2();						 
				LeafVeinVolume(); 
				///////////////////////////////////////////
				CString strPathNum;
				ipos = strPath.ReverseFind('\\');
				strTmp = strPath.Right(strPath.GetLength() - 1 - ipos);
				m_iNumSample = _ttoi(strTmp);
				strPathNum = strPath.Left(ipos);
				ipos = strPathNum.ReverseFind('\\');
				m_strNameVariety = strPathNum.Right(strPathNum.GetLength() - 1 - ipos);
				tPhenotype mPhenotype;
				mPhenotype.strNameVariety = m_strNameVariety;
				mPhenotype.iNumSample = m_iNumSample;
				for (int i = 0; i < 3; i++)
				{
					mPhenotype.fLength[i] = m_fLength[i];
					mPhenotype.fAngle[i] = m_fAngle[i];
					mPhenotype.fVerticalHeight[i] = m_fVerticalHeight[i];
					mPhenotype.fHorizontalLength[i] = m_fHorizontalLength[i];
					mPhenotype.fUpwardGrowthMeasure[i] = m_fUpwardGrowthMeasure[i];
					mPhenotype.fOutwardGrowthMeasure[i] = m_fOutwardGrowthMeasure[i];
					mPhenotype.fDeviationAngle[i] = m_fDeviationAngle[i];
					mPhenotype.iTipTop[i] = m_iTipTop[i];
					mPhenotype.fDeviationTip[i] = m_fDeviationTip[i];
					mPhenotype.fCurvatureRatio[i] = m_fCurvatureRatio[i];
					mPhenotype.fMaxCur[i] = m_fMaxCur[i];
					mPhenotype.fMaxCurPos[i] = m_fMaxCurPos[i];
					mPhenotype.fMaxWind[i] = m_fMaxWind[i];
					mPhenotype.fMaxWindPos[i] = m_fMaxWindPos[i];
					mPhenotype.fProjectionArea[i] = m_fProjectionArea[i];
					mPhenotype.fVolume[i] = m_fVolume[i];
				}
				mVarietyPhenotypeList.Add(mPhenotype);
			}
			else
			{
				SmoothPhenFileTraversal(strPath);
			}
		}
	}
	tempFind.Close();
}


void CLeafVienDlg::LeafLength()
{
	int iCnt = 0;
	float fLength = 0.0;
	for (int i = 0; i < 3; i++)
	{
		fLength = 0.0;
		iCnt = m_pMaizePointCloud->mStick3leavesVeinList[i].GetSize();
		for (int j = 0; j < iCnt - 1; j++)
		{
			float fLen = m_pMaizePointCloud->mStick3leavesVeinList[i][j].DistanceTo(m_pMaizePointCloud->mStick3leavesVeinList[i][j + 1]);
			fLength += fLen;
		}
		m_fLength[i] = fLength;
	}
}


void CLeafVienDlg::LeafAngle2()
{
	int iCnt = 0;
	Expoint3D mStemVector(0.0, 0.0, 1.0);
	Expoint3D mLeafVector;
	float fAngle = 0.0;
	for (int i = 0; i < 3; i++)
	{
		fAngle = 0.0;
		iCnt = m_pMaizePointCloud->mStick3leavesVeinList[i].GetSize();
		if (iCnt < 5)
		{
			continue;
		}
		//mStemVector = m_pMaizePointCloud->mStick3leavesList[0][i + 1] - m_pMaizePointCloud->mStick3leavesList[0][i];
		for (int j = 1; j < 11; j++)
		{
			mLeafVector = m_pMaizePointCloud->mStick3leavesVeinList[i][j + 1] - m_pMaizePointCloud->mStick3leavesVeinList[i][1];
			float fAng = mStemVector.AngleTo(mLeafVector);
			fAng = fAng * 180 / PI;
			fAngle += fAng;
		}
		m_fAngle[i] = fAngle / 10;
	}
}


void CLeafVienDlg::LeafVeinGrowth()
{
	int iCnt = 0;
	float fMin = 10000.0;
	float fMax = -10000.0;

	for (int i = 0; i < 3; i++)
	{
		fMin = 10000.0;
		fMax = -10000.0;
		iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
		for (int j = 0; j < iCnt - 1; j++)
		{
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z < fMin)
			{
				fMin = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z;
			}
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z > fMax)
			{
				fMax = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z;
			}
		}
		m_fVerticalHeight[i] = fMax - fMin;
	}

	for (int i = 0; i < 3; i++)
	{
		fMin = 10000.0;
		fMax = -10000.0;
		iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
		for (int j = 0; j < iCnt - 1; j++)
		{
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].x < fMin)
			{
				fMin = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].x;
			}
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].x > fMax)
			{
				fMax = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].x;
			}
		}
		m_fHorizontalLength[i] = fMax - fMin;
	}

	for (int i = 0; i < 3; i++)
	{
		if (m_fLength[i] != 0.0)
		{
			m_fUpwardGrowthMeasure[i] = m_fVerticalHeight[i] / m_fLength[i];
			m_fOutwardGrowthMeasure[i] = m_fHorizontalLength[i] / m_fLength[i];
		}
	}
}

void CLeafVienDlg::DeviationAngle()
{
	int iCnt = 0;
	float fAngle = 0.0;
	Expoint3D mLeafVector;
	VECTORF vec;
	VECTORF vecB;
	vecB[0] = 1.0;
	vecB[1] = 0.0;
	vecB[2] = 0.0;
	vecB[3] = 0.0;
	for (int i = 0; i < 3; i++)
	{
		iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
		if (iCnt > 5)
		{
			mLeafVector = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][iCnt - 1];
			
			vec[0] = mLeafVector.x;
			vec[1] = mLeafVector.y;
			vec[2] = 0.0;
			vec[3] = 0.0;
			GetVecAnglef(vec, vecB, &fAngle);
			if ((vec[0] < 0.0) && (vec[1] > 0.0))
			{
				fAngle = 180 - fAngle;
			}
			else if ((vec[0] < 0.0) && (vec[1] < 0.0))
			{
				fAngle = 180 - fAngle;
			}
			m_fDeviationAngle[i] = fAngle;
		}
	}
}

void CLeafVienDlg::DeviationTip()
{
	int iCnt = 0;
	float fLength = 0.0;
	int iNum;
	float fMaxHIGH = -1000.0;
	int iNumTip[3];
	for (int i = 0; i < 3; i++)
	{
		fMaxHIGH = -1000.0;
		iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
		iNum = 0;
		if (iCnt > 5)
		{
			for (int j = 0; j < iCnt; j++)
			{
				if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z > fMaxHIGH)
				{
					fMaxHIGH = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z;
					iNum = j;
				}
			}
			iNumTip[i] = iNum;
			if (iNum == iCnt - 1)
			{
				m_iTipTop[i] = 1;
			}
			else
			{
				m_iTipTop[i] = 0;
			}
		}
		else
		{
			m_iTipTop[i] = 1;
		}
	}
	float fLength1 = 0.0;
	float fLength2 = 0.0;
	for (int i = 0; i < 3; i++)
	{
		fLength2 = 0.0;
		if (m_iTipTop[i])
		{
			m_fDeviationTip[i] = 0.0;
		}
		else
		{
			iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
			for (int j = iNumTip[i]; j < iCnt - 1; j++)
			{
				fLength = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].DistanceTo(m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j + 1]);
				fLength2 += fLength;
			}
			m_fDeviationTip[i] = fLength2 / m_fLength[i];
		}
	}
}

void CLeafVienDlg::LeafVeinCurvatureRatio()
{
	int iCnt = 0;
	float fLength = 0.0;
	int iNum;
	float fMaxHIGH = -1000.0;
	int iNumTip[3];
	for (int i = 0; i < 3; i++)
	{
		iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
		if (iCnt > 5)
		{
			fLength = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][0].DistanceTo(m_pMaizePointCloud->mStick3leavesVeinXOZList[i][iCnt - 1]);
			m_fCurvatureRatio[i] = fLength / m_fLength[i];
		}
	}
}


void CLeafVienDlg::LeafVeinCurvatureAndWindingRate()
{
	int iCnt = 0;
	int iVeinNode = 10;
	int iIntervalNode = 0;
	float mCur, fCur, mWind, fWind;
	for (int i = 0; i < 3; i++)
	{
		m_pMaizePointCloud->mPoint3DList.RemoveAll();
		iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
		if (iCnt < 5)
		{
			continue;
		}
		iIntervalNode = iCnt / iVeinNode;
		for (int j = 0; j < iCnt - 1; j = j + iIntervalNode)
		{
			m_pMaizePointCloud->mPoint3DList.Add(m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j]);
		}
		m_pMaizePointCloud->mPoint3DList.Add(m_pMaizePointCloud->mStick3leavesVeinXOZList[i][iCnt - 1]);

		m_pMaizePointCloud->SectionalCurvature(mCur, fCur, mWind, fWind);
		m_fMaxCur[i] = fCur;
		m_fMaxCurPos[i] = mCur;
		m_fMaxWind[i] = fWind;
		m_fMaxWindPos[i] = mWind;
	}
}

float CLeafVienDlg::LeafVeinProjectionArea()
{
	float fProjectionArea = 0.0;
	float fTemp = 0.0;
	float fTempArea = 0.0;
	int iNumNerMdlS = m_pMaizePointCloud->mLeafNerMdlSplineList.GetSize();
	Expoint3D mpt1, mpt2, mpt3, mpt4;
	for (int i = 0; i < iNumNerMdlS - 1; i++)
	{
		mpt1 = m_pMaizePointCloud->mLeafNerMdlSplineList[i];
		mpt2 = m_pMaizePointCloud->mLeafNerMdlSplineList[i + 1];

		mpt3 = mpt1;
		mpt3.z = 0.0;
		mpt4 = mpt2;
		mpt4.z = 0.0;
		fTemp = mpt3.DistanceTo(mpt4);
		fTempArea = (fabs(mpt1.z) + fabs(mpt2.z)) * fTemp * 0.5;
		fProjectionArea += fTempArea;
	}
	return fProjectionArea;
}


void CLeafVienDlg::LeafVeinVolume()
{
	float fVolume = 0.0;
	float fTemp = 0.0;
	float fHigh[2];
	float fX[2];
	float fY[2];
	int iCnt = 0;
	for (int i = 0; i < 3; i++)
	{
		fVolume = 0.0;
		iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
		if (iCnt < 5)
		{
			m_fProjectionArea[i] = -10000;
			continue;
		}
		fHigh[0] = 1000;
		fHigh[1] = -1000;
		fX[0] = 1000;
		fX[1] = -1000;
		fY[0] = 1000;
		fY[1] = -1000;
		for (int j = 0; j < iCnt - 1; j++)
		{
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].x < fX[0])
			{
				fX[0] = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].x;
			}
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].x > fX[1])
			{
				fX[1] = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].x;
			}
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].y < fY[0])
			{
				fY[0] = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].y;
			}
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].y > fY[1])
			{
				fY[1] = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].y;
			}
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z < fHigh[0])
			{
				fHigh[0] = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z;
			}
			if (m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z > fHigh[1])
			{
				fHigh[1] = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j].z;
			}
		}
		m_fVolume[i] = (fX[1] - fX[0]) * (fY[1] - fY[0]) * (fHigh[1] - fHigh[0]);
	}
}


BOOL CLeafVienDlg::SaveParameter2(CString strPath)
{
	CString strTemp("");
	CString strLine("");
	int i = 0, j = 0, nCntPts = 0;
	CStdioFile f;
	CFileException e;
	CString pathname;
	pathname = strPath;
	if (!f.Open(pathname, CFile::modeCreate | CFile::modeWrite | CFile::typeText, &e))
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return false;
	}
	f.SeekToBegin();

	strLine = _T("# phenotyping parameters file");
	strTemp = _T("\n");
	strLine += strTemp;
	f.WriteString(strLine);
	int iCnt = 0;
	iCnt = mVarietyPhenotypeList.GetSize();
	strLine = _T("#NameVariety PlantID Angle Length VerticalHeight HorizontalLength UpwardGrowthMeasure OutwardGrowthMeasure DeviationAngle TipTop DeviationTip CurvatureRatio MaxCurvature CurvaturePos MaxWindingRate WindingRatePos ProjectionArea Volume");
	strTemp = _T("\n");
	strLine += strTemp;
	f.WriteString(strLine);

	for (int i = 0; i < iCnt; i++)
	{
		strTemp.Format(_T(" %d %f %f %f %f %f %f %f %d %f %f %f %f %f %f %f %f\n"), mVarietyPhenotypeList[i].iNumSample, mVarietyPhenotypeList[i].fAngle[1], mVarietyPhenotypeList[i].fLength[1], \
			mVarietyPhenotypeList[i].fVerticalHeight[1], mVarietyPhenotypeList[i].fHorizontalLength[1], mVarietyPhenotypeList[i].fUpwardGrowthMeasure[1], \
			mVarietyPhenotypeList[i].fOutwardGrowthMeasure[1], mVarietyPhenotypeList[i].fDeviationAngle[1], mVarietyPhenotypeList[i].iTipTop[1], mVarietyPhenotypeList[i].fDeviationTip[1], mVarietyPhenotypeList[i].fCurvatureRatio[1], \
			mVarietyPhenotypeList[i].fMaxCur[1], mVarietyPhenotypeList[i].fMaxCurPos[1], mVarietyPhenotypeList[i].fMaxWind[1], mVarietyPhenotypeList[i].fMaxWindPos[1], mVarietyPhenotypeList[i].fProjectionArea[1], mVarietyPhenotypeList[i].fVolume[1]);
		strLine = mVarietyPhenotypeList[i].strNameVariety + strTemp;
		f.WriteString(strLine);
	}
	f.SeekToBegin();
	f.Close();
	return true;
}


void CLeafVienDlg::LeafVeinProjectionArea2()
{
	float fProjectionArea = 0.0;
	float fTemp = 0.0;
	float fTempArea = 0.0;
	Expoint3D mpt1, mpt2, mpt3, mpt4;
	int iCnt = 0;
	for (int i = 0; i < 3; i++)
	{
		fProjectionArea = 0.0;
		iCnt = m_pMaizePointCloud->mStick3leavesVeinXOZList[i].GetSize();
		if (iCnt < 5)
		{
			m_fProjectionArea[i] = -10000;
			continue;
		}
		for (int j = 0; j < iCnt - 1; j++)
		{
			mpt1 = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j];
			mpt2 = m_pMaizePointCloud->mStick3leavesVeinXOZList[i][j + 1];
			mpt3 = mpt1;
			mpt3.z = 0.0;
			mpt4 = mpt2;
			mpt4.z = 0.0;
			fTemp = mpt3.DistanceTo(mpt4);
			fTempArea = (fabs(mpt1.z) + fabs(mpt2.z)) * fTemp * 0.5;
			fProjectionArea += fTempArea;
		}
		m_fProjectionArea[i] = fProjectionArea;
	}
}

void CLeafVienDlg::OnBnClickedLoaddatabtn()
{
	BROWSEINFO bi;
	char Buffer[MAX_PATH];

	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = (LPWSTR)Buffer;
	bi.lpszTitle = L"Select Digital data folder";

	bi.ulFlags = BIF_EDITBOX;
	bi.lpfn = NULL;
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
	if (pIDList)
	{
		SHGetPathFromIDList(pIDList, (LPWSTR)Buffer);
	
		sFolderPath.Format(L"%s", Buffer);
	}
	LPMALLOC lpMalloc;
	if (FAILED(SHGetMalloc(&lpMalloc))) return;
	
	lpMalloc->Free(pIDList);
	lpMalloc->Release();

	
	UpdateData(TRUE);
	//float fUnitScan = 0;
	int iTemp = 0;
	LoadMaizeModel();
	//iTemp = m_UnitScanCOMBO.GetCurSel();
	//iTemp = iTemp - 1;
	//fUnitScan = pow(10.0, iTemp);
	//m_pMaizePointCloud->m_unitScan = fUnitScan;
	m_pMaizePointCloud->m_unitScan = 0.1;
	m_pMaizePointCloud->InitPointCloud();

	CString strPath;
	
	strPath = sFolderPath + _T("\\0.txt");
	m_pMaizePointCloud->LoadPrimitivePC(strPath, m_pMaizePointCloud->mStick3leavesList[0]);
	strPath = sFolderPath + _T("\\F-3.txt");
	m_pMaizePointCloud->LoadPrimitivePC(strPath, m_pMaizePointCloud->mStick3leavesList[1]);
	strPath = sFolderPath + _T("\\F.txt");
	m_pMaizePointCloud->LoadPrimitivePC(strPath, m_pMaizePointCloud->mStick3leavesList[2]);
	strPath = sFolderPath + _T("\\F+3.txt");
	m_pMaizePointCloud->LoadPrimitivePC(strPath, m_pMaizePointCloud->mStick3leavesList[3]);
	
	int iCnt = 0;
	iCnt = m_pMaizePointCloud->mStick3leavesList[0].GetSize();
	if (iCnt < 4) return;
	float fTemp = 0.0;
	
	bool bZAxisDir = TRUE;
	
	if (bZAxisDir)
	{
		for (int i = 0; i < 4; i++)
		{
			iCnt = m_pMaizePointCloud->mStick3leavesList[i].GetSize();
			for (int j = 0; j < iCnt; j++)
			{
				m_pMaizePointCloud->mStick3leavesList[i][j].z *= -1;
			}
		}
	}

	
	m_pMaizePointCloud->SortPointCloud(m_pMaizePointCloud->mStick3leavesList[0]);

	
	Expoint3D pBasePt = m_pMaizePointCloud->mStick3leavesList[0][0];
	for (int i = 0; i < 4; i++)
	{
		m_pMaizePointCloud->TranslationPointCloud(m_pMaizePointCloud->mStick3leavesList[i], pBasePt);
	}
	
	for (int i = 1; i < 4; i++)
	{
		m_pMaizePointCloud->mStick3leavesVeinList[i - 1].RemoveAll();
		iCnt = m_pMaizePointCloud->mStick3leavesList[i].GetSize();
		if (iCnt > 1)
		{
			for (int j = 2; j < iCnt; j = j + 5)
			{
				m_pMaizePointCloud->mStick3leavesVeinList[i - 1].Add(m_pMaizePointCloud->mStick3leavesList[i][j]);
			}
			m_pMaizePointCloud->mStick3leavesVeinList[i - 1].Add(m_pMaizePointCloud->mStick3leavesList[i][iCnt - 1]);
		}
	}
	
	CArray<Expoint3D, Expoint3D> mP3DList;
	iCnt = m_pMaizePointCloud->mStick3leavesList[0].GetSize();
	for (int i = 0; i < 4; i++)
	{
		mP3DList.Add(m_pMaizePointCloud->mStick3leavesList[0][i]);
	}
	Expoint3D mTempPT;
	mTempPT = (m_pMaizePointCloud->mStick3leavesList[0][0] + m_pMaizePointCloud->mStick3leavesList[0][1]) * 0.5;
	mP3DList.Add(mTempPT);
	mTempPT = (m_pMaizePointCloud->mStick3leavesList[0][1] + m_pMaizePointCloud->mStick3leavesList[0][2]) * 0.5;
	mP3DList.Add(mTempPT);
	mTempPT = (m_pMaizePointCloud->mStick3leavesList[0][2] + m_pMaizePointCloud->mStick3leavesList[0][3]) * 0.5;
	mP3DList.Add(mTempPT);
	CFit3D mFit3D;
	mFit3D.LinearFit3D(mP3DList, m_pMaizePointCloud->mFitLine[0], m_pMaizePointCloud->mFitLine[1]);
	//m_pMaizePointCloud->LinearFit(mP3DList);
	m_pMaizePointCloud->m_bPoint3DList = false;
	m_pMaizePointCloud->m_bStick3leavesPri = true;
	InvalidatePointCloudView();
}
