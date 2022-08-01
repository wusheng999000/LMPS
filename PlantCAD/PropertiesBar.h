
#if !defined(AFX_PROPERTIESBAR_H__022CA4C6_99C2_INCLUDED_)
#define AFX_PROPERTIESBAR_H__022CA4C6_99C2_INCLUDED_

#pragma once

#include "stdafx.h"

class CPropertiesBar : public CDockPageBar

{
// Construction
public:
	CPropertiesBar(void);
	using CDockPageBar::AddPage;

// Attributes
public:
	
// Operations
public:
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertiesBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	CObject * AddPage(CRuntimeClass* pClass,UINT nIDTemplate, LPCTSTR sText, UINT IconID);
	virtual ~CPropertiesBar(void);

		// Generated message map functions
protected:
	//{{AFX_MSG(CPropertiesBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIESBAR_H__022CA4C6_99C2_INCLUDED_)
