// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

//#define _BIND_TO_CURRENT_VCLIBS_VERSION 1

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����

#if _DEBUG
#pragma comment(lib,"../x64/Debug/SceneDll.lib")
#pragma comment(lib,"../x64/Debug/DockingBar.lib")
#pragma comment(lib,"../x64/Debug/ExGUI.lib")
#pragma comment(lib,"../x64/Debug/MaizeData.lib")
#pragma comment(lib,"../x64/Debug/ExGeneralIO.lib")
#else
#pragma comment(lib,"../x64/Release/SceneDll.lib")
#pragma comment(lib,"../x64/Release/DockingBar.lib")
#pragma comment(lib,"../x64/Release/ExGUI.lib")
#pragma comment(lib,"../x64/Release/MaizeData.lib")
#pragma comment(lib,"../x64/Release/ExGeneralIO.lib")
#endif

#include "../DockingBar/sizecbar.h"
#include "../DockingBar/AutoHideBar.h"
#include "../DockingBar/DockPageBar.h"

#include "../SceneDll/GLEnableView.h"
#include "../SceneDll/SceneTexture.h"
#include "../ExGUI/ExPropList.h"
#include "../ExGUI/ExEditList.h"
#include "../ExGUI/ExSliderBar.h"
#include "../ExGUI/ExTreeCtrl.h"
#include "../ExGUI/ExListCtrl.h"
#include "../ExGUI/ExToolBar.h"
#include "../ExGUI/ExGLDisplay.h"

#include "../MaizeData/PointCloud.h"
#include "../MaizeData/CLeafVienDlg.h"

#include "../ExGeneralIO/ExObj.h"
#pragma comment(lib,"HtmlHelp.lib")
#include "HtmlHelp.h"


#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>                     // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT
#include <afxcontrolbars.h>


#define MAX_CNT_MAIZELEAF 30

#define SELECTPIXEL 5




#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


