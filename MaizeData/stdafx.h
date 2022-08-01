// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

//#define _BIND_TO_CURRENT_VCLIBS_VERSION 1

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE ��
#include <afxodlgs.h>       // MFC OLE �Ի�����
#include <afxdisp.h>        // MFC �Զ�����
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC ���ݿ���
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO ���ݿ���
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#if _DEBUG
#pragma comment(lib,"../x64/Debug/ExGeome.lib")
#pragma comment(lib,"../x64/Debug/ExGUI.lib")
#pragma comment(lib,"../x64/Debug/ExDB.lib")
#pragma comment(lib,"../x64/Debug/ExGeneralIO.lib")
#else
#pragma comment(lib,"../x64/Release/ExGeome.lib")
#pragma comment(lib,"../x64/Release/ExGUI.lib")
#pragma comment(lib,"../x64/Release/ExDB.lib")
#pragma comment(lib,"../x64/Release/ExGeneralIO.lib")
#endif

#include "../ExGeome/Expoint3D.h"
#include "../ExGeome/BSpline.h"
#include "../ExGeome/ExBSpline.h"
#include "../ExGeome/ExCSpline.h"

#include "../ExGUI/ExEditList.h"
#include "../ExGUI/ExSlidList.h"
#include "../ExGUI/ExPropList.h"
#include "../ExGUI/ExTreeCtrl.h"
#include "../ExDB/ODBCRecordset.h"
#include "../ExGeneralIO/ExObj.h"

#include "Afxtempl.h"

#include <locale>
#include <afxcontrolbars.h>
#ifndef LEAF_MDLPTS_WIDTH 
#define LEAF_MDLPTS_WIDTH 9
#endif

#ifndef LEAF_MDLPTS_LENGTH 
#define LEAF_MDLPTS_LENGTH 13		//����С��4��Ҷ�����ߴ��й���
#endif
#undef max 
#undef min