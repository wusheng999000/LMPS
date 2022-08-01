// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

//#define _BIND_TO_CURRENT_VCLIBS_VERSION 1

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxole.h>         // MFC OLE 类
#include <afxodlgs.h>       // MFC OLE 对话框类
#include <afxdisp.h>        // MFC 自动化类
#endif // _AFX_NO_OLE_SUPPORT

#ifndef _AFX_NO_DB_SUPPORT
#include <afxdb.h>                      // MFC ODBC 数据库类
#endif // _AFX_NO_DB_SUPPORT

#ifndef _AFX_NO_DAO_SUPPORT
#include <afxdao.h>                     // MFC DAO 数据库类
#endif // _AFX_NO_DAO_SUPPORT

#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC 对 Windows 公共控件的支持
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
#define LEAF_MDLPTS_LENGTH 13		//不能小于4，叶脉曲线处有关联
#endif
#undef max 
#undef min