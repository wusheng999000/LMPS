#pragma once

#define PIT_CATALOG		0	//Catalog
#define PIT_EDIT		1	//Edit
#define PIT_COMBO		2	//Dropdown
#define PIT_COLOR		3	//Color						e.g. "128 128 128"
#define PIT_FONT		4	//Font
#define PIT_FILE		5	//File Select Dialog
#define PIT_DATE		6	//Date						e.g. "2005/7/3"
#define PIT_TIME		7	//Time						e.g. "12:32:45"

class CExPropItem
{
public:
	CExPropItem(void);
	~CExPropItem(void);

	CExPropItem(const CExPropItem& item)
	{
		m_catalog	 = item.m_catalog;
		m_propName   = item.m_propName;
		m_curValue   = item.m_curValue;
		m_nItemType  = item.m_nItemType;
		m_cmbItems   = item.m_cmbItems;
		m_propDesc	 = item.m_propDesc;
		m_nItemOrder = item.m_nItemOrder;
		m_bItemShow  = item.m_bItemShow;
		m_bEnable    = item.m_bEnable;
	};
	CExPropItem(CString catalog, CString propName, CString curValue, int nItemType, 
		CString cmbItems, CString propDesc, BOOL bEnable, BOOL bItemShow, int nItemOrder)
	{
		m_catalog	 = catalog;
		m_propName   = propName;
		m_curValue   = curValue;
		m_nItemType  = nItemType;
		m_cmbItems   = cmbItems;
		m_propDesc	 = propDesc;
		m_bItemShow  = bItemShow;
		m_nItemOrder = nItemOrder;
		m_bEnable    = bEnable;
	};
	void SetItem(CString catalog, CString propName, CString curValue, int nItemType, 
		CString cmbItems, CString propDesc, BOOL bEnable, BOOL bItemShow, int nItemOrder)
	{
		m_catalog	 = catalog;
		m_propName   = propName;
		m_curValue   = curValue;
		m_nItemType  = nItemType;
		m_cmbItems   = cmbItems;
		m_propDesc	 = propDesc;
		m_bItemShow  = bItemShow;
		m_nItemOrder = nItemOrder;
		m_bEnable    = bEnable;
	};
public:
	CString m_catalog;       //Catalog
	CString m_propName;      //Name
	CString m_curValue;      //CurValue
	CString m_cmbItems;      //ComboItems if
	CString m_propDesc;      //Description
	BOOL    m_bEnable;       //Enable
	int m_nItemType;         //ItemType
	int m_nItemOrder;        //ItemOrder
	BOOL m_bItemShow;        //ItemShow
};
