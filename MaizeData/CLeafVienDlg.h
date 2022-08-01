#pragma once
#include"resource.h"
typedef struct tagPhenotype
{
	CString strNameVariety;
	int iNumVariety;
	int iNumSample;
	float fAngle[3];
	float fLength[3];
	float fVerticalHeight[3];
	float fHorizontalLength[3];
	float fUpwardGrowthMeasure[3];
	float fOutwardGrowthMeasure[3];
	float fDeviationAngle[3];
	int iTipTop[3];
	float fDeviationTip[3];
	float fCurvatureRatio[3];
	float fCurvature[12];
	float fWindingRate[12];
	float fVolume[3];
	float fMaxCur[3];
	float fMaxCurPos[3];
	float fMaxWind[3];
	float fMaxWindPos[3];
	float fProjectionArea[3];
}tPhenotype;
// CLeafVienDlg 
class CPointCloud;
class AFX_EXT_CLASS CLeafVienDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLeafVienDlg)

public:
	CLeafVienDlg(CWnd* pParent = NULL);
	virtual ~CLeafVienDlg();
	CPointCloud* m_pMaizePointCloud;

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LeafVienDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedInputleafveinbtn();
public:
	Expoint3D m_ptBase;
	CArray<tPhenotype, tPhenotype> mVarietyPhenotypeList;
	CString sFolderPath;
	CString m_strNameVariety;
	CString m_strFileName;
	int m_iNumVariety;
	int m_iNumSample;
	float m_fAngle[3];
	float m_fLength[3];
	float m_fVerticalHeight[3];
	float m_fHorizontalLength[3];
	float m_fUpwardGrowthMeasure[3];
	float m_fOutwardGrowthMeasure[3];
	float m_fUpwardGrowthMeasure_Mid[3];
	float m_fOutwardGrowthMeasure_Mid[3];
	float m_fUpwardGrowthMeasure_Tip[3];
	float m_fOutwardGrowthMeasure_Tip[3];
	float m_fTangentAngle[3];
	float m_fDeviationAngle[3];
	float m_fDeviationAngle_Mid[3];
	int m_iTipTop[3];
	float m_fDeviationTip[3];
	float m_fCurvatureRatio[3];
	float m_fCurvature[12];
	float m_fWindingRate[12];
	float m_fVolume[3];
	float m_fProjectionArea[3];
	float m_fMaxCur[3];
	float m_fMaxCurPos[3];
	float m_fMaxWind[3];
	float m_fMaxWindPos[3];
	float m_fSpacingArea_1[3];
	float m_fSpacingArea_2[3];
	float m_fMidCurvature[3];
	float m_fLengthTipRatio[3]; 
public:
	CString Loaddirectory();
	void LoadMaizeModel();
	void SetObject(CPointCloud* pPointCloud);
	void InvalidatePointCloudView();
	void SmoothFileTraversal(CString strPath);
	BOOL RootDirectory(CString strPath);
	void Stick3leaves_Smooth(CString strPath, int idataSource);
	void MaizeCorrectVertical();
	void SmoothPhenFileTraversal(CString strPath);

	void LeafLength();	
	void LeafAngle2();
	void LeafVeinGrowth();
	void DeviationAngle();
	void DeviationTip();
	void LeafVeinCurvatureRatio(); 
	void LeafVeinCurvatureAndWindingRate();
	void LeafVeinProjectionArea2();					 
	void LeafVeinVolume(); 
	float LeafVeinProjectionArea();

	
	BOOL SaveParameter2(CString strPath);
	afx_msg void OnBnClickedBatchsmothbtn();
	afx_msg void OnBnClickedBatchphenbtn();
	afx_msg void OnBnClickedLoaddatabtn();
};
