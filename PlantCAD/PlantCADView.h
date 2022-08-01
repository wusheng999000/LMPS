// PlantCADView.h : CPlantCADView 类的接口
//

#pragma once
#include "PlantCADDoc.h"


class CPlantCADDoc;

class CPlantCADView : public CGLEnableView //CView
{
public: 
	CPlantCADView();
	DECLARE_DYNCREATE(CPlantCADView)


public:
	CPlantCADDoc* GetDocument() const;
	CDC* pDC;

	CString mSqenPath;					


	// 重写
public:
	//	virtual void OnDraw(CDC* pDC);  
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	void OnDrawGL();

	void Stick3leaves_bmpOutput(CString strPath);

	void GetALLpcScreenPt(CArray<CPoint, CPoint>&  mPcPreList);
	void GetALLpcScreenPt2(float fMinX, float fMaxX, float fMinY, float fMaxY, CArray<ExEdge, ExEdge>& mPolyEdgeList);//点云转化为屏幕坐标

	BOOL LineIntersect(Expoint3D p1, Expoint3D p2, Expoint3D p3, Expoint3D p4, Expoint3D& IntersectP);

	BOOL LineIntersect(Expoint3D p1, Expoint3D p2, Expoint3D p3, Expoint3D p4);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CPlantCADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


protected:
	DECLARE_MESSAGE_MAP()
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
public:
	void SetLights();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnOutputBmpFile();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();

	virtual void OnInitialUpdate();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnViewbase();
};


#ifndef _DEBUG  // PlantCADView.cpp 中的调试版本
inline CPlantCADDoc* CPlantCADView::GetDocument() const
{ return reinterpret_cast<CPlantCADDoc*>(m_pDocument); }
#endif

