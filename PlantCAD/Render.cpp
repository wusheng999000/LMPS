// Render.cpp : 实现文件
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


// Render 绘图

void Render::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: 在此添加绘制代码
}


// Render 诊断

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


// Render 消息处理程序
