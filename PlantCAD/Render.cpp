// Render.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PlantCAD.h"
#include "Render.h"


// Render

IMPLEMENT_DYNCREATE(Render, CView)

Render::Render()
{

}

Render::~Render()
{
}

BEGIN_MESSAGE_MAP(Render, CView)
END_MESSAGE_MAP()


// Render ��ͼ

void Render::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���
}


// Render ���

#ifdef _DEBUG
void Render::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void Render::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// Render ��Ϣ�������
