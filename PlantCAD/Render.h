#pragma once


// Render ��ͼ

class Render : public CView
{
	DECLARE_DYNCREATE(Render)

protected:
	Render();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~Render();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


