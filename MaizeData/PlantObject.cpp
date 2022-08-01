#include "StdAfx.h"
#include "PlantObject.h"

CPlantObject::CPlantObject(void)
{
	Reset();
}

CPlantObject::~CPlantObject(void)
{
}

CPlantObject::CPlantObject(const CPlantObject &mObject) 
{ 
	nOrder = mObject.nOrder;							//序号
	nPlantOrder = mObject.nPlantOrder;					//所属植株序号
	m_sObj = mObject.m_sObj;							//对象
	m_sName = mObject.m_sName;
	m_sVarName = mObject.m_sVarName;					//品种名称
	m_unit = mObject.m_unit;							//单位
	mColor = mObject.mColor;							//颜色
	msTexturePath = mObject.msTexturePath;				//纹理路径
	mTexture = mObject.mTexture;						//纹理指针起始位置
	nTextureIndex = mObject.nTextureIndex;				//纹理索引号
	m_bTextureGenerated = mObject.m_bTextureGenerated;
	nGrowthDay = mObject.nGrowthDay;					//当前生长时刻
	nStartDay = mObject.nStartDay;						//开始生长时刻
	nStopDay = mObject.nStopDay;						//停止生长时刻
	nOldDay = mObject.nOldDay;							//衰老时刻
	nEndDay = mObject.nEndDay;							//终止时刻
	m_bObjectCalcued = mObject.m_bObjectCalcued;		//计算完成
	m_bParamInited = mObject.m_bParamInited;			//参数完成初始化
	m_bKeyParamGenerated = mObject.m_bKeyParamGenerated;
	m_bShowNormal = mObject.m_bShowNormal;
	m_bShowBox = mObject.m_bShowBox;
	pBase = mObject.pBase;
	nDesignMode = mObject.nDesignMode;
	m_bNormal = mObject.m_bNormal;

	int i = 0;
	for( i = 0; i < 8; i++ )
	{
		mBoxVertex[i] = mObject.mBoxVertex[i];
	}
	for( i = 0; i < 16; i++ )
	{
		mLocalCoordin[i] = mObject.mLocalCoordin[i];
	}

	//几何形态结构
	Vertex.Copy(mObject.Vertex);		//顶点
	Normal.Copy(mObject.Normal);		//法向
	Texture.Copy(mObject.Texture);		//纹理
	nHDivide = mObject.nHDivide;							//横向划分数
	nVDivide = mObject.nVDivide;							//纵向划分数

	mDrawMode = mObject.mDrawMode;
	mLifeState = mObject.mLifeState;
	mGrowthPeriod = mObject.mGrowthPeriod;
}

void CPlantObject::operator = (const CPlantObject &mObject)
{
	Copy(mObject);
}

BOOL CPlantObject::GenerateTexture(CString path, GLuint& nIndex)
{
	BITMAP BM;
	HBITMAP hBmp;
	//Front
	glGenTextures(1,&nIndex);
	glBindTexture(GL_TEXTURE_2D, nIndex);
	hBmp = (HBITMAP)LoadImage(AfxGetInstanceHandle(),path, IMAGE_BITMAP, 256, 256, LR_LOADFROMFILE|LR_CREATEDIBSECTION);    
	GetObject(hBmp, sizeof (BM), &BM);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, BM.bmWidth, BM.bmHeight,GL_RGB, GL_UNSIGNED_BYTE,BM.bmBits);
//	glTexImage2D(GL_TEXTURE_2D,0,3,BM.bmWidth,BM.bmHeight,0,GL_RGB,GL_UNSIGNED_BYTE,BM.bmBits);
	return TRUE;
}

float CPlantObject::GetCardinalVal(float t, float a, float y[])
{
	return float(y[0]*(t*t*t*(-a)+t*t*(2.0*a)+t*(-a)+1.0*(0.0))+y[1]*(t*t*t*(2.0-a)+t*t*(a-3.0)+t*(0.0)+1.0*(1.0))+y[2]*(t*t*t*(a-2.0)+t*t*(3.0-2.0*a)+t*(a)+1.0*(0.0))+y[3]*(t*t*t*(a)+t*t*(-a)+t*(0.0)+1.0*(0.0)));
}

Expoint3D CPlantObject::GetMovePt(Expoint3D p, float mx, float my, float mz)
{
	Expoint3D pt;
	pt.x = p.x + mx;
	pt.y = p.y + my;
	pt.z = p.z + mz;
	return pt;
}

Expoint3D CPlantObject::GetMovePt(Expoint3D p, Expoint3D pOffset)
{
	Expoint3D pt;
	pt = p + pOffset;
	return pt;
}

Expoint3D CPlantObject::GetRotatePt(Expoint3D p, int nAxis, float mVal, BOOL bRad)
{//bRad = FALSE(表示角度值),TRUE弧度值，默认角度值
	Expoint3D pt;
	if( !bRad ) mVal = float(mVal * 3.1416 / 180.0);
	if( nAxis == 0 )        //绕x轴旋转
	{
		pt.x = p.x;
		pt.y = p.y * cos(mVal) - p.z * sin(mVal);
		pt.z = p.y * sin(mVal) + p.z * cos(mVal);
	}
	if( nAxis == 1 )        //绕y轴旋转
	{
		pt.x = p.z * sin(mVal) + p.x * cos(mVal);
		pt.y = p.y;
		pt.z = p.z * cos(mVal) - p.x * sin(mVal);
	}
	if( nAxis == 2 )        //绕z轴旋转
	{
		pt.x = p.x * cos(mVal) - p.y * sin(mVal);
		pt.y = p.x * sin(mVal) + p.y * cos(mVal);
		pt.z = p.z;
	}
	return pt;
}

Expoint3D CPlantObject::GetRotatePt(Expoint3D b, Expoint3D p, int nAxis, float mVal, BOOL bRad)
{//bRad = FALSE(表示角度值),TRUE弧度值，默认角度值,b基点
	Expoint3D pt;
	if( !bRad ) mVal = float(mVal * 3.1416 / 180.0);
	if( nAxis == 0 )        //绕x轴旋转
	{
		pt.x = p.x;
		pt.y = b.y + (p.y - b.y) * cos(mVal) - (p.z - b.z) * sin(mVal);
		pt.z = b.z + (p.y - b.y) * sin(mVal) + (p.z - b.z) * cos(mVal);
	}
	if( nAxis == 1 )        //绕y轴旋转
	{
		pt.x = b.x + (p.z - b.z) * sin(mVal) + (p.x - b.x) * cos(mVal);
		pt.y = p.y;
		pt.z = b.z + (p.z - b.z) * cos(mVal) - (p.x - b.x) * sin(mVal);
	}
	if( nAxis == 2 )        //绕z轴旋转
	{
		pt.x = b.x + (p.x-b.x) * cos(mVal) - (p.y-b.y) * sin(mVal);
		pt.y = b.y + (p.x-b.x) * sin(mVal) + (p.y-b.y) * cos(mVal);
		pt.z = p.z;
	}
	return pt;
}

Expoint3D CPlantObject::GetScalePt(Expoint3D p, float mx, float my, float mz)
{
	if(my <= 0) my = mx;
	if(mz <= 0) mz = mx;
	Expoint3D pt;
	pt.x = p.x * mx;
	pt.y = p.y * my;
	pt.z = p.z * mz;
	return pt;
}

Expoint3D CPlantObject::GetScalePt(Expoint3D b, Expoint3D p, float mx, float my, float mz)
{
	if(my <= 0) my = mx;
	if(mz <= 0) mz = mx;
	Expoint3D pt;
	pt.x = b.x + (p.x - b.x) * mx;
	pt.y = b.y + (p.y - b.y) * my;
	pt.z = b.z + (p.z - b.z) * mz;
	return pt;
}

void CPlantObject::SetShow(bool bShow)
{
	m_bShow = bShow;
}

void CPlantObject::Reset()
{
	int i = 0;
	m_sName = _T("");
	m_sVarName = _T("");
	m_sTypeName = _T("");
	m_unit = 10.0f;
	mColor.SetColor(0.0f,0.0f,0.0f);
	msTexturePath = _T("");
	mTexture = NULL;
	nTextureIndex = 0;
	m_bTextureGenerated = FALSE;
	m_bParamInited = FALSE;
	m_bKeyParamGenerated = FALSE;
	m_bShowNormal = FALSE;
	m_bShowBox = TRUE;
	m_bShow = TRUE;
	nGrowthDay = 0;
	nStartDay = 0;
	nStopDay = 0;
	nOldDay = 0;
	nEndDay = 0;
	Vertex.RemoveAll();
	Normal.RemoveAll();
	Texture.RemoveAll();
	nDesignMode = 0;
	m_bNormal = true;

	m_bObjectCalcued = FALSE;
	mDrawMode = mode_null;
	mLifeState = gestation;
	mGrowthPeriod = seed;
	nPlantOrder = 0;
	nOrder = 0;
}

void CPlantObject::CalcuLifeStatus(int nDay)
{
	
}

void CPlantObject::GetDatabaseConnection(CString& dbname, CDatabase *db)
{
	//初始化数据库对象，进行数据库连接
	try{
		CString cs;
		cs = _T("Driver={Microsoft Access Driver (*.mdb)};Dbq=") + dbname;
		db->OpenEx(cs.GetBuffer(0));
	}
	catch (CDBException *e)
	{
		AfxMessageBox(_T("无法打开用户数据库!"));
	}
}

CString CPlantObject::GetSysPath()
{//获取系统目录，Exe、Image、Database的上级
	CString strPath;
	TCHAR exeFullPath[500]; //
	GetModuleFileName(NULL,exeFullPath,500);//得到程序模块名称，全路径
	strPath = exeFullPath;
	int i = 0, j = 0, k = 0, n = strPath.GetLength();
	for( i = 0; i < n; i++ )
	{
		if( strPath.GetAt(i) == '\\' )
			strPath.SetAt(i,'/');
	}
	for( i = n-1; i >= 0; i-- )
	{
		j++;
		if( strPath.GetAt(i) == '/' )
			k++;
		if( k == 2 )
		{
			strPath = strPath.Left(n-j);
			return strPath;
		}
	}
	return _T("");
}

BOOL CPlantObject::ReleaseConnection(CDatabase* db)
{
	//如果数据库对象是打开的，则关闭数据库对象
	if(db->IsOpen())
	{
		db->Close();
	}
	return 1;
}

BOOL CPlantObject::Draw( float unit, UINT mode )
{
	if(!m_bShow) return FALSE;
	if(!m_bObjectCalcued) return FALSE;
	if( nGrowthDay < nStartDay )return FALSE;
	if(mode == 4 && mTexture == NULL)mode = 3;
	//暂画成熟期
	int i = 0, j = 0;
	int nCnt = Vertex.GetSize();
	if(m_bShowNormal)				//绘制法向
	{
		for( i = 0; i <= nVDivide; i++ )
		{
			for( j = 0; j <= nHDivide; j++ )
			{
				glBegin(GL_LINES);
				glColor3f(1.0f,1.0f,0.0f);
				glVertex3f(Vertex[ i * (nHDivide+1) + j].x*m_unit/unit, Vertex[ i * (nHDivide+1) + j].y*m_unit/unit, Vertex[ i * (nHDivide+1) + j].z*m_unit/unit );
				glColor3f(1.0f,0.0f,0.0f);
				glVertex3f((Vertex[i*(nHDivide+1)+j].x+Normal[i*(nHDivide+1)+j].x)*m_unit/unit, (Vertex[i*(nHDivide+1)+j].y+Normal[i*(nHDivide+1)+j].y)*m_unit/unit, (Vertex[i*(nHDivide+1)+j].z+Normal[i*(nHDivide+1)+j].z)*m_unit/unit );
				glEnd();
			}
		}
	}
	if( mode == 1 )
	{
		//点
		glPointSize(2.0f);
		glColor3f(mColor.r,mColor.g,mColor.b);
		glBegin(GL_POINTS);
		for( i = 0; i < nCnt; i++ )
		{
			glVertex3f(Vertex[i].x*m_unit/unit, Vertex[i].y*m_unit/unit, Vertex[i].z*m_unit/unit );
		}
		glEnd();
		glPointSize(1.0f);
	}
	else if( mode == 2 )
	{
		if( nCnt != (nHDivide+1)*(nVDivide+1) ) return FALSE;
		//线条
		glColor3f(mColor.r,mColor.g,mColor.b);
		for( i = 0; i <= nVDivide; i++ )
		{
			for( j = 1; j <= nHDivide; j++ )
			{
				glBegin(GL_LINES);
				glVertex3f(Vertex[ i * (nHDivide+1) + j].x*m_unit/unit, Vertex[ i * (nHDivide+1) + j].y*m_unit/unit, Vertex[ i * (nHDivide+1) + j].z*m_unit/unit );
				glVertex3f(Vertex[ i * (nHDivide+1) + j - 1].x*m_unit/unit, Vertex[ i * (nHDivide+1) + j - 1].y*m_unit/unit, Vertex[ i * (nHDivide+1) + j - 1].z*m_unit/unit );
				glEnd();
			}
		}
		for( i = 1; i <= nVDivide; i++ )
		{
			for( j = 0; j <= nHDivide; j++ )
			{
				glBegin(GL_LINES);
				glVertex3f(Vertex[ i * (nHDivide+1) + j].x*m_unit/unit, Vertex[ i * (nHDivide+1) + j].y*m_unit/unit, Vertex[ i * (nHDivide+1) + j].z*m_unit/unit );
				glVertex3f(Vertex[ (i - 1) * (nHDivide+1) + j].x*m_unit/unit, Vertex[(i - 1) * (nHDivide+1) + j].y*m_unit/unit, Vertex[ (i - 1) * (nHDivide+1) + j].z*m_unit/unit);
				glEnd();
			}
		}
	}
	else if( mode == 3 )
	{
		//实体
		if( nCnt != (nHDivide+1)*(nVDivide+1) ) return FALSE;
		if( Normal.GetSize() != (nHDivide+1)*(nVDivide+1) ) return FALSE;
		glColor3f(mColor.r,mColor.g,mColor.b);
		for( i = 1; i <= nVDivide; i++ )
		{
			for( j = 1; j <= nHDivide; j++ )
			{
				glBegin(GL_QUADS);
				glNormal3f(Normal[(i-1)*(nHDivide+1)+j-1].x, Normal[(i-1)*(nHDivide+1)+j-1].y, Normal[(i-1)*(nHDivide+1)+j-1].z);
				glVertex3f(Vertex[(i-1)*(nHDivide+1)+j-1].x*m_unit/unit, Vertex[(i-1)*(nHDivide+1)+j-1].y*m_unit/unit, Vertex[(i-1)*(nHDivide+1)+j-1].z*m_unit/unit);
				glNormal3f(Normal[(i-1)*(nHDivide+1)+j].x, Normal[(i-1)*(nHDivide+1)+j].y, Normal[(i-1)*(nHDivide+1)+j].z);
				glVertex3f(Vertex[(i-1)*(nHDivide+1)+j].x*m_unit/unit, Vertex[(i-1)*(nHDivide+1)+j].y*m_unit/unit, Vertex[(i-1)*(nHDivide+1)+j].z*m_unit/unit);
				glNormal3f(Normal[i*(nHDivide+1)+j].x, Normal[i*(nHDivide+1)+j].y, Normal[i*(nHDivide+1)+j].z);
				glVertex3f(Vertex[i*(nHDivide+1)+j].x*m_unit/unit, Vertex[i*(nHDivide+1)+j].y*m_unit/unit, Vertex[i*(nHDivide+1)+j].z*m_unit/unit);
				glNormal3f(Normal[i*(nHDivide+1)+j-1].x, Normal[i*(nHDivide+1)+j-1].y, Normal[i*(nHDivide+1)+j-1].z);
				glVertex3f(Vertex[i*(nHDivide+1)+j-1].x*m_unit/unit, Vertex[i*(nHDivide+1)+j-1].y*m_unit/unit, Vertex[i*(nHDivide+1)+j-1].z*m_unit/unit);
				glEnd();
			}
		}
	}
	else if( mode == 4 )
	{
		//渲染
		if( nCnt != (nHDivide+1)*(nVDivide+1) ) return FALSE;
		if( Normal.GetSize() != (nHDivide+1)*(nVDivide+1) ) return FALSE;
		if( Texture.GetSize() != (nHDivide+1)*(nVDivide+1) ) return FALSE;
		glEnable(GL_TEXTURE_2D);
		if(	nDesignMode )					//动态模式，使用颜色
			glColor3f(mColor.r,mColor.g,mColor.b);
		else
			glColor3f(1.0f, 1.0f, 1.0f);

		glBindTexture( GL_TEXTURE_2D, *(mTexture+nTextureIndex));
		for( i = 1; i <= nVDivide; i++ )
		{
			for( j = 1; j <= nHDivide; j++ )
			{
				glBegin(GL_QUADS);
				glTexCoord2d(Texture[(i-1)*(nHDivide+1)+j-1].x, Texture[(i-1)*(nHDivide+1)+j-1].y);
				glNormal3f(Normal[(i-1)*(nHDivide+1)+j-1].x, Normal[(i-1)*(nHDivide+1)+j-1].y, Normal[(i-1)*(nHDivide+1)+j-1].z);
				glVertex3f(Vertex[(i-1)*(nHDivide+1)+j-1].x*m_unit/unit, Vertex[(i-1)*(nHDivide+1)+j-1].y*m_unit/unit, Vertex[(i-1)*(nHDivide+1)+j-1].z*m_unit/unit);
				glTexCoord2d(Texture[(i-1)*(nHDivide+1)+j].x, Texture[(i-1)*(nHDivide+1)+j].y);
				glNormal3f(Normal[(i-1)*(nHDivide+1)+j].x, Normal[(i-1)*(nHDivide+1)+j].y, Normal[(i-1)*(nHDivide+1)+j].z);
				glVertex3f(Vertex[(i-1)*(nHDivide+1)+j].x*m_unit/unit, Vertex[(i-1)*(nHDivide+1)+j].y*m_unit/unit, Vertex[(i-1)*(nHDivide+1)+j].z*m_unit/unit);
				glTexCoord2d(Texture[i*(nHDivide+1)+j].x, Texture[i*(nHDivide+1)+j].y);
				glNormal3f(Normal[i*(nHDivide+1)+j].x, Normal[i*(nHDivide+1)+j].y, Normal[i*(nHDivide+1)+j].z);
				glVertex3f(Vertex[i*(nHDivide+1)+j].x*m_unit/unit, Vertex[i*(nHDivide+1)+j].y*m_unit/unit, Vertex[i*(nHDivide+1)+j].z*m_unit/unit);
				glTexCoord2d(Texture[i*(nHDivide+1)+j-1].x, Texture[i*(nHDivide+1)+j-1].y);
				glNormal3f(Normal[i*(nHDivide+1)+j-1].x, Normal[i*(nHDivide+1)+j-1].y, Normal[i*(nHDivide+1)+j-1].z);
				glVertex3f(Vertex[i*(nHDivide+1)+j-1].x*m_unit/unit, Vertex[i*(nHDivide+1)+j-1].y*m_unit/unit, Vertex[i*(nHDivide+1)+j-1].z*m_unit/unit);
				glEnd();
			}
		}
		glDisable(GL_TEXTURE_2D);
	}
	//绘制包围盒
	//if( m_bShowBox )
	//{
	//	DrawBox(unit,mode);
	//}
	return TRUE;
}

void CPlantObject::DrawBox( float unit, UINT mode )
{
	if( !m_bShowBox )return;
	//p0-p1 X,p0-p3 Y, p0-p4 Z
	Expoint3D p1, p2, p3, p4;	
	int i = 0;//共12条边
	//p0-p1
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
	for( i = 0; i < 12; i++ )
	{
		switch(i)
		{
		case 0:		p1 = mBoxVertex[0];		p2 = mBoxVertex[1];	break;
		case 1:		p1 = mBoxVertex[1];		p2 = mBoxVertex[2];	break;
		case 2:		p1 = mBoxVertex[2];		p2 = mBoxVertex[3];	break;
		case 3:		p1 = mBoxVertex[3];		p2 = mBoxVertex[0];	break;
		case 4:		p1 = mBoxVertex[4];		p2 = mBoxVertex[5];	break;
		case 5:		p1 = mBoxVertex[5];		p2 = mBoxVertex[6];	break;
		case 6:		p1 = mBoxVertex[6];		p2 = mBoxVertex[7];	break;
		case 7:		p1 = mBoxVertex[7];		p2 = mBoxVertex[4];	break;
		case 8:		p1 = mBoxVertex[0];		p2 = mBoxVertex[4];	break;
		case 9:		p1 = mBoxVertex[1];		p2 = mBoxVertex[5];	break;
		case 10:	p1 = mBoxVertex[2];		p2 = mBoxVertex[6];	break;
		case 11:	p1 = mBoxVertex[3];		p2 = mBoxVertex[7];	break;
		default : break;
		}
		p3 = p1.PartTo(p2,0.3f);
		p4 = p1.PartTo(p2,0.7f);
		glVertex3f(p1.x*m_unit/unit, p1.y*m_unit/unit, p1.z*m_unit/unit );
		glVertex3f(p3.x*m_unit/unit, p3.y*m_unit/unit, p3.z*m_unit/unit );
		glVertex3f(p4.x*m_unit/unit, p4.y*m_unit/unit, p4.z*m_unit/unit );
		glVertex3f(p2.x*m_unit/unit, p2.y*m_unit/unit, p2.z*m_unit/unit );
	}
	glEnd();
}

void CPlantObject::RecalcuBox()
{//初始化或重计算包围盒
	int i = 0, nCnt = Vertex.GetSize();
	float Xmin = 10000.0f, Xmax = -10000.0f,Ymin = 10000.0f,Ymax = -10000.0f, Zmin = 10000.0f,Zmax = -10000.0f;
	for( i = 0; i < nCnt; i++ )
	{
		if(Vertex[i].x > Xmax) Xmax = Vertex[i].x;
		if(Vertex[i].y > Ymax) Ymax = Vertex[i].y;
		if(Vertex[i].z > Zmax) Zmax = Vertex[i].z;
		if(Vertex[i].x < Xmin) Xmin = Vertex[i].x;
		if(Vertex[i].y < Ymin) Ymin = Vertex[i].y;
		if(Vertex[i].z < Zmin) Zmin = Vertex[i].z;
	}
	mBoxVertex[0].Set(Xmin,Ymin,Zmin);
	mBoxVertex[1].Set(Xmax,Ymin,Zmin);
	mBoxVertex[2].Set(Xmax,Ymax,Zmin);
	mBoxVertex[3].Set(Xmin,Ymax,Zmin);
	mBoxVertex[4].Set(Xmin,Ymin,Zmax);
	mBoxVertex[5].Set(Xmax,Ymin,Zmax);
	mBoxVertex[6].Set(Xmax,Ymax,Zmax);
	mBoxVertex[7].Set(Xmin,Ymax,Zmax);
}

void CPlantObject::SetTexturePath( CString strPath )
{
	msTexturePath = strPath;
	m_bTextureGenerated = FALSE;
}

void CPlantObject::SetTexture( GLuint* tex )
{
	mTexture = tex;
}

void CPlantObject::SetTextureIndex( int nIndex )
{
	nTextureIndex = nIndex;
}

void CPlantObject::Move(Expoint3D offset)
{
	int i = 0, nCnt = Vertex.GetSize();
	for( i = 0; i < nCnt; i++ )
	{
		Vertex[i] = GetMovePt(Vertex[i],offset);
	}
	//Box
	for( i = 0; i < 8; i++ )
	{
		mBoxVertex[i] = GetMovePt(mBoxVertex[i],offset);
	}
	//
	pBase = GetMovePt(pBase,offset); 
}

void CPlantObject::Scale( float mRatex, float mRatey, float mRatez )
{
	if(mRatey <= 0) mRatey = mRatex;
	if(mRatez <= 0) mRatez = mRatex;
	int i = 0, nCnt = Vertex.GetSize();
	for( i = 0; i < nCnt; i++ )
	{
		Vertex[i] = GetScalePt(Vertex[i],mRatex,mRatey,mRatez);
	}
	//Box
	for( i = 0; i < 8; i++ )
	{
		mBoxVertex[i] = GetScalePt(mBoxVertex[i],mRatex,mRatey,mRatez);
	}
}

void CPlantObject::Rotate( int nAxis, float mVal, BOOL bRad )
{
	if(Vertex.GetSize()!=Normal.GetSize())return;
	int i = 0, nCnt = Vertex.GetSize();
	for( i = 0; i < nCnt; i++ )
	{
		Vertex[i] = GetRotatePt(Vertex[i],nAxis,mVal,bRad);
		Normal[i] = GetRotatePt(Normal[i],nAxis,mVal,bRad);
	}
	//Box
	for( i = 0; i < 8; i++ )
	{
		mBoxVertex[i] = GetRotatePt(mBoxVertex[i],nAxis,mVal,bRad);
	}
}

void CPlantObject::Scale( Expoint3D base, float mRatex, float mRatey, float mRatez )
{//以基点base缩放
	if(mRatey <= 0) mRatey = mRatex;
	if(mRatez <= 0) mRatez = mRatex;
	int i = 0, nCnt = Vertex.GetSize();
	for( i = 0; i < nCnt; i++ )
	{
		Vertex[i] = GetScalePt(base,Vertex[i],mRatex,mRatey,mRatez);
	}
	//Box
	for( i = 0; i < 8; i++ )
	{
		mBoxVertex[i] = GetScalePt(base, mBoxVertex[i],mRatex,mRatey,mRatez);
	}
}

void CPlantObject::Rotate( Expoint3D base, int nAxis, float mVal, BOOL bRad )
{//绕基点base旋转
	if(Vertex.GetSize()!=Normal.GetSize())return;
	int i = 0, nCnt = Vertex.GetSize();
	for( i = 0; i < nCnt; i++ )
	{
		Vertex[i] = GetRotatePt(base,Vertex[i],nAxis,mVal,bRad);
		Normal[i] = GetRotatePt(base,Normal[i],nAxis,mVal,bRad);
	}
	//Box
	for( i = 0; i < 8; i++ )
	{
		mBoxVertex[i] = GetRotatePt(base,mBoxVertex[i],nAxis,mVal,bRad);
	}
}

void CPlantObject::ReCalculateNormal(BOOL bMark)
{//计算法向
	Expoint3D vec1,vec2,vec3;
	int i = 0, j = 0;
	if( nVDivide < 1 ) return;
	if(Vertex.GetSize()!=(nVDivide+1)*(nHDivide+1))return;
	Normal.RemoveAll();
	Normal.SetSize((nVDivide+1)*(nHDivide+1));
	for( i = 0; i <= nVDivide; i++ )
	{
		for( j = 0; j <= nHDivide; j++ )
		{
			if( i == 0 )
			{
				vec1 = Vertex[(nHDivide+1)+j] - Vertex[j];
			}
			else
			{
				vec1 = Vertex[i*(nHDivide+1)+j] - Vertex[(i-1)*(nHDivide+1)+j];
			}
			if( j == 0 )
			{
				vec2 = Vertex[i*(nHDivide+1)+j+1] - Vertex[i*(nHDivide+1)+j];
			}
			else
			{
				vec2 = Vertex[i*(nHDivide+1)+j] - Vertex[i*(nHDivide+1)+j-1];
			}
			if(bMark)
				vec3 = vec1.Normal(vec2);
			else
				vec3 = vec2.Normal(vec1);
			Normal.SetAt(i*(nHDivide+1)+j,vec3);			
		}
	}
}

void CPlantObject::ReCalculateTexture()
{//重计算纹理坐标
	int i = 0, j = 0;
	if(Vertex.GetSize()!=(nVDivide+1)*(nHDivide+1))return;
	Texture.RemoveAll();
	Expoint3D tex;
	for( i = 0; i <= nVDivide; i++ )
	{
		for( j = 0; j <= nHDivide; j++ )
		{
			tex.x = float(float(j)/nHDivide);
			tex.y = float(float(i)/nVDivide);
			tex.z = 0.0f;
			Texture.Add(tex);		
		}
	}
}

BOOL CPlantObject::OutputModel( CString mPath, float unit, float mScale, int nIndexPlant, int nIndexOrgan, BOOL bVertex, BOOL bColor, BOOL bNormal,	BOOL bTexture, BOOL bFace, BOOL bProp)
{//输出模型数据到面元文件*.pnt
	if(!m_bObjectCalcued)return FALSE;
	CString strTemp("");
	int i = 0, j = 0, ma = 0, mb = 0, mc = 0;
	int nCnt = 0, nCntVertex = 0, nCntFace = 0, nCntProp = 0;
	CStdioFile f;
	CFileException e;

	GetFileInfo(mPath,nCntVertex,nCntFace,nCntProp);
	if (!f.Open(mPath, CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate|CFile::typeText, &e))
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return FALSE;
	}
	//到结尾
	f.SeekToEnd();
	//输出点
	if(bVertex)
	{
		f.WriteString(_T("g\n"));
		for( i = 0; i <= nVDivide; i++ )
		{
			for( j = 0; j <= nHDivide; j++ )
			{
				if(bColor)
				{
					strTemp.Format(_T("v %.3f %.3f %.3f %.3f %.3f %.3f\n"),\
						Vertex[i*(nHDivide+1)+j].x*m_unit/unit,Vertex[i*(nHDivide+1)+j].y*m_unit/unit,Vertex[i*(nHDivide+1)+j].z*m_unit/unit,\
						mColor.r,mColor.g,mColor.b);
				}
				else
				{
					strTemp.Format(_T("v %.3f %.3f %.3f\n"),\
						Vertex[i*(nHDivide+1)+j].x*m_unit/unit,Vertex[i*(nHDivide+1)+j].y*m_unit/unit,Vertex[i*(nHDivide+1)+j].z*m_unit/unit);
				}
				f.WriteString(strTemp);
			}
		}
		f.WriteString(_T("\n"));
	}
	if(bNormal)
	{
		for( i = 0; i <= nVDivide; i++ )
		{
			for( j = 0; j <= nHDivide; j++ )
			{
				strTemp.Format(_T("vn %.3f %.3f %.3f\n"),\
					Normal[i*(nHDivide+1)+j].x,Normal[i*(nHDivide+1)+j].y,Normal[i*(nHDivide+1)+j].z);
				f.WriteString(strTemp);
			}
		}
		f.WriteString(_T("\n"));
	}
	if(bTexture)
	{
		for( i = 0; i <= nVDivide; i++ )
		{
			for( j = 0; j <= nHDivide; j++ )
			{
				strTemp.Format(_T("vt %.3f %.3f\n"),\
					Texture[i*(nHDivide+1)+j].x,Texture[i*(nHDivide+1)+j].y);
				f.WriteString(strTemp);
			}
		}
	}
	if(bVertex)
	{
		strTemp.Format(_T("# %d Vertexes\n"),(nHDivide+1)*(nVDivide+1));
		f.WriteString(strTemp);
		f.WriteString(_T("\n"));
	}
	//输出面
	if(bFace)
	{
		CString strOutputMark;
		if(m_sObj == _T("Stalk"))
			strOutputMark = _T("stem");
		else if(m_sObj == _T("Leaf"))
			strOutputMark = _T("leaf");
		else if(m_sObj == _T("Back"))
			strOutputMark = _T("back");
		else if(m_sObj == _T("Sheath"))
			strOutputMark = _T("shth");
		else if(m_sObj == _T("Tassel"))
			strOutputMark = _T("tasl");
		else if(m_sObj == _T("Ear"))
			strOutputMark = _T("ear");
		else if(m_sObj == _T("Land"))
			strOutputMark = _T("land");
		else
			strOutputMark = _T("oter");

		strTemp.Format(_T("g %s_%d_%d\n"),strOutputMark,nIndexPlant,nIndexOrgan);
		f.WriteString(strTemp);
		strTemp.Format(_T("usemtl %s\n"),strOutputMark );
		f.WriteString(strTemp);
		if(bProp)
		{
			strTemp.Format(_T("prop %s %d %d\n"),strOutputMark,nIndexPlant,nIndexOrgan);
			f.WriteString(strTemp);
		}
		for( i = 1; i <= nVDivide; i++ )
		{
			for( j = 1; j <= nHDivide; j++ )
			{
				ma = nCntVertex+1+(i-1)*(nHDivide+1)+j-1;
				mb = nCntVertex+1+(i-1)*(nHDivide+1)+j;
				mc = nCntVertex+1+i*(nHDivide+1)+j;
				strTemp.Format(_T("f %d/%d/%d %d/%d/%d %d/%d/%d\n"),ma,ma,ma,mb,mb,mb,mc,mc,mc);
				f.WriteString(strTemp);
				ma = nCntVertex+1+i*(nHDivide+1)+j;
				mb = nCntVertex+1+i*(nHDivide+1)+j-1;
				mc = nCntVertex+1+(i-1)*(nHDivide+1)+j-1;
				strTemp.Format(_T("f %d/%d/%d %d/%d/%d %d/%d/%d\n"),ma,ma,ma,mb,mb,mb,mc,mc,mc);
				f.WriteString(strTemp);
			}
		}
		strTemp.Format(_T("# %d Faces\n"),nHDivide*nVDivide*2);
		f.WriteString(strTemp);
		f.WriteString(_T("\n"));
/*		if(bProp)
		{
			nCnt = 1;
			for( i = 1; i <= nVDivide; i++ )
			{
				for( j = 1; j <= nHDivide; j++ )
				{
					strTemp.Format(_T("prop %s %d %d %d %d\n"),strOutputMark,nCntFace+nCnt,nIndexPlant,nIndexOrgan,nCnt);
					f.WriteString(strTemp);
					nCnt++;
					strTemp.Format(_T("prop %s %d %d %d %d\n"),strOutputMark,nCntFace+nCnt,nIndexPlant,nIndexOrgan,nCnt);
					f.WriteString(strTemp);
					nCnt++;
				}
			}
			f.WriteString(_T("\n"));
		}*/
	}
	f.Close();
	return TRUE;
}

BOOL CPlantObject::GetFileInfo(CString path, int& nVertex, int& nFace, int& nProp)
{
	CStdioFile f;
	CFileException e;
	BOOL m_bFlag = TRUE;
	CString strTemp;
	if (!f.Open(path, CFile::modeRead|CFile::typeText, &e))
	{
		return false;
	}
	f.SeekToBegin();
	nVertex = 0;
	nFace = 0;
	nProp = 0;
	while( m_bFlag )   
	{   
		m_bFlag = f.ReadString(strTemp);
		if(strTemp.GetLength() > 2 && strTemp.GetAt(0) == 'v' && strTemp.GetAt(1) == ' ')	//Introductions
		{
			nVertex++;	
		} 
		else if(strTemp.GetLength() > 0 && strTemp.GetAt(0) == 'f')
		{
			nFace++;
		}
		else if(strTemp.GetLength() > 4 && strTemp.GetAt(0) == 'p' && strTemp.GetAt(1) == 'r' && strTemp.GetAt(2) == 'o' && strTemp.GetAt(3) == 'p')			//Params
		{
			nProp++;
		}
		else if(strTemp.GetLength() > 2 && strTemp.GetAt(0) == 'v' && strTemp.GetAt(1) == 'n')			//Params
		{
			;
		}   
	}
	f.Close();
	if(nFace != nProp)
	{
		nFace = 0;
		nProp = 0;
		return false;
	}
	return true;
}

BOOL CPlantObject::OutputModelCan( CString mPath, float unit, float mScale, int nIndexPlant, int nIndexOrgan )
{
	if(!m_bObjectCalcued)return FALSE;
	CString strTemp("");
	int i = 0, j = 0, ma = 0, mb = 0, mc = 0;
	int nCnt = 0, nCntVertex = 0, nCntFace = 0, nCntProp = 0;
	CStdioFile f;
	CFileException e;
	if (!f.Open(mPath, CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate|CFile::typeText, &e))
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return FALSE;
	}
	//到结尾
	f.SeekToEnd();
	//输出面
	CString strMark;
	if(m_sObj == "Stalk")
		strMark = _T("s");
	else if(m_sObj == "Leaf")
		strMark = _T("f");
	nCnt = 0;
	for( i = 1; i <= nVDivide; i++ )
	{
		for( j = 1; j <= nHDivide; j++ )
		{
			ma = (i-1)*(nHDivide+1)+j-1;
			mb = (i-1)*(nHDivide+1)+j;
			mc = i*(nHDivide+1)+j;
			strTemp.Format(_T("%s %d %d %d %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n"),\
				strMark,nIndexPlant,nIndexOrgan,nCnt,\
				Vertex[ma].x*m_unit/unit,Vertex[ma].y*m_unit/unit,Vertex[ma].z*m_unit/unit,\
				Vertex[mb].x*m_unit/unit,Vertex[mb].y*m_unit/unit,Vertex[mb].z*m_unit/unit,\
				Vertex[mc].x*m_unit/unit,Vertex[mc].y*m_unit/unit,Vertex[mc].z*m_unit/unit);
			f.WriteString(strTemp);
			nCnt++;
			ma = i*(nHDivide+1)+j;
			mb = i*(nHDivide+1)+j-1;
			mc = (i-1)*(nHDivide+1)+j-1;
			strTemp.Format(_T("%s %d %d %d %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f\n"),\
				strMark,nIndexPlant,nIndexOrgan,nCnt,\
				Vertex[ma].x*m_unit/unit,Vertex[ma].y*m_unit/unit,Vertex[ma].z*m_unit/unit,\
				Vertex[mb].x*m_unit/unit,Vertex[mb].y*m_unit/unit,Vertex[mb].z*m_unit/unit,\
				Vertex[mc].x*m_unit/unit,Vertex[mc].y*m_unit/unit,Vertex[mc].z*m_unit/unit);
			f.WriteString(strTemp);
			nCnt++;
		}
	}
	f.Close();
	return TRUE;
}

BOOL CPlantObject::OutputModelCnt( CString mPath, float unit, int nIndexPlant, int nIndexOrgan)
{
	if(!m_bObjectCalcued)return FALSE;
	CString strTemp("");
	int i = 0, j = 0, ma = 0, mb = 0, mc = 0;
	int nCnt = 0, nCntVertex = 0;

	CStdioFile f;
	CFileException e;
//	GetFileInfoCnt(mPath, nCntVertex);
	if (!f.Open(mPath, CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate|CFile::typeText, &e))
	{
		TCHAR szError[1024];
		e.GetErrorMessage(szError, 1024);
		AfxMessageBox(szError);
		return FALSE;
	}
	//到结尾
	f.SeekToEnd();
	//输出面元
	int nType = 0;
	if(m_sObj == "Stalk")
		nType = 0;
	else if(m_sObj == "Leaf")
		nType = 1;
	else if(m_sObj == "Tassel")
		nType = 2;
	else if(m_sObj == "Ear")
		nType = 3;
	else if(m_sObj == "Root")
		nType = 4;
	else if(m_sObj == "Land")
		nType = 5;

	nCnt = 0;
	for( i = 1; i <= nVDivide; i++ )
	{
		for( j = 1; j <= nHDivide; j++ )
		{
			ma = (i-1)*(nHDivide+1)+j-1;
			mb = (i-1)*(nHDivide+1)+j;
			mc = i*(nHDivide+1)+j;
//                             ID     V1              V2              V3             RGB1        RGB2           RGB3
//			strTemp.Format(_T("%d %.3f %.3f %.3f|%.3f %.3f% .3f|%.3f %.3f %.3f|%.3f %.3f %.3f|%.3f %.3f %.3f|%.3f %.3f %.3f|RGB1%d %d %d \n");
//							      n1              n2             n3           t1         t2        t3
//							  %.3f %.3f %.3f|%.3f %.3f %.3f|%.3f %.3f %.3f|%.3f %.3f|%.3f %.3f|%.3f %.3f
			strTemp.Format(_T("%d %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %d %d %d %d %d %.3f %.3f %.3f %.3f %.3f %d %.3f %.3f %.3f %.3f %.3f %d %.3f %.3f %.3f %.3f %.3f %d %.3f %.3f %.3f %.3f %.3f\n"),\
				/*nCntVertex+nCnt*/0, \
				Vertex[ma].x*m_unit/unit,Vertex[ma].y*m_unit/unit,Vertex[ma].z*m_unit/unit,\
				Vertex[mb].x*m_unit/unit,Vertex[mb].y*m_unit/unit,Vertex[mb].z*m_unit/unit,\
				Vertex[mc].x*m_unit/unit,Vertex[mc].y*m_unit/unit,Vertex[mc].z*m_unit/unit,\
				mColor.r,mColor.g,mColor.b,mColor.r,mColor.g,mColor.b,mColor.r,mColor.g,mColor.b,\
				Normal[ma].x,Normal[ma].y,Normal[ma].z,	Normal[mb].x,Normal[mb].y,Normal[mb].z,\
				Normal[mc].x,Normal[mc].y,Normal[mc].z, Texture[ma].x,Texture[ma].y,\
				Texture[mb].x,Texture[mb].y, Texture[mc].x,Texture[mc].y,1,nType,nIndexPlant,nIndexOrgan,\
				0,0.0f,0.0f,0.0f,0.0f,0.0f,0,0.0f,0.0f,0.0f,0.0f,0.0f,0,0.0f,0.0f,0.0f,0.0f,0.0f,0,0.0f,0.0f,0.0f,0.0f,0.0f);

			f.WriteString(strTemp);
			nCnt++;
			ma = i*(nHDivide+1)+j;
			mb = i*(nHDivide+1)+j-1;
			mc = (i-1)*(nHDivide+1)+j-1;
			strTemp.Format(_T("%d %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %.3f %d %d %d %d %d %.3f %.3f %.3f %.3f %.3f %d %.3f %.3f %.3f %.3f %.3f %d %.3f %.3f %.3f %.3f %.3f %d %.3f %.3f %.3f %.3f %.3f\n"),\
				/*nCntVertex+nCnt*/0, \
				Vertex[ma].x*m_unit/unit,Vertex[ma].y*m_unit/unit,Vertex[ma].z*m_unit/unit,\
				Vertex[mb].x*m_unit/unit,Vertex[mb].y*m_unit/unit,Vertex[mb].z*m_unit/unit,\
				Vertex[mc].x*m_unit/unit,Vertex[mc].y*m_unit/unit,Vertex[mc].z*m_unit/unit,\
				mColor.r,mColor.g,mColor.b,mColor.r,mColor.g,mColor.b,mColor.r,mColor.g,mColor.b,\
				Normal[ma].x,Normal[ma].y,Normal[ma].z,	Normal[mb].x,Normal[mb].y,Normal[mb].z,\
				Normal[mc].x,Normal[mc].y,Normal[mc].z, Texture[ma].x,Texture[ma].y,\
				Texture[mb].x,Texture[mb].y, Texture[mc].x,Texture[mc].y,1,nType,nIndexPlant,nIndexOrgan,\
				0,0.0f,0.0f,0.0f,0.0f,0.0f,0,0.0f,0.0f,0.0f,0.0f,0.0f,0,0.0f,0.0f,0.0f,0.0f,0.0f,0,0.0f,0.0f,0.0f,0.0f,0.0f);
			f.WriteString(strTemp);
			nCnt++;
		}
	}
	f.Close();
	return TRUE;
}

bool CPlantObject::ConvertToObj( OBJFileData& obj, MTLFileData& mtl, float rate, float scale, bool bNormal, bool bTexture, bool bFace)
{
	//将当前PlantObject转化为OBJFileData对象
	if(!m_bObjectCalcued)return false;
	CString strTemp("");
	int i = 0, j = 0, a = 0, b = 0, c = 0;
	OBJVECTOR vec;
	OBJTRIANGLE tri;
	obj.Clear();
	//点
	for( i = 0; i <= nVDivide; i++ )
	{
		for( j = 0; j <= nHDivide; j++ )
		{
			vec.m_fVec[0] = float( Vertex[i*(nHDivide+1)+j].x * rate );
			vec.m_fVec[1] = float( Vertex[i*(nHDivide+1)+j].y * rate );
			vec.m_fVec[2] = float( Vertex[i*(nHDivide+1)+j].z * rate );
			obj.AddVertex(vec);
			if( bNormal )
			{
				vec.m_fVec[0] = float( Normal[i*(nHDivide+1)+j].x );
				vec.m_fVec[1] = float( Normal[i*(nHDivide+1)+j].y );
				vec.m_fVec[2] = float( Normal[i*(nHDivide+1)+j].z );
				obj.AddNormal(vec);
			}
			if( bTexture )
			{
				vec.m_fVec[0] = float( Texture[i*(nHDivide+1)+j].x );
				vec.m_fVec[1] = float( Texture[i*(nHDivide+1)+j].y );
				vec.m_fVec[2] = float( Texture[i*(nHDivide+1)+j].z );
				obj.AddTexCoord(vec);
			}
		}
	}
	//面
	if(bFace)
	{
		tri.nOrgan = nOrder;
		tri.nPlant = nPlantOrder;
		if( m_sObj == _T("Land") )
			tri.sType = _T("land");
		else if(m_sObj == "Sensor")
			tri.sType = _T("detc");
		else if(m_sObj == "Stalk")
			tri.sType = _T("stem");
		else if(m_sObj == "Leaf")
			tri.sType = _T("leaf");
		else if(m_sObj == "Back")
			tri.sType = _T("back");
		else if(m_sObj == "Sheath")
			tri.sType = _T("shth");
		else if(m_sObj == "Ear")
			tri.sType = _T("frut");
		else if(m_sObj == "Tassel")
			tri.sType = _T("flwr");
		else if(m_sObj == "Root")
			tri.sType = _T("oter");
		else
			tri.sType = _T("oter");

		for( i = 1; i <= nVDivide; i++ )
		{
			if(	m_bNormal )
			{
				for( j = 1; j <= nHDivide; j++ )
				{
					a = 1+(i-1)*(nHDivide+1)+j-1;
					b = 1+i*(nHDivide+1)+j;
					c = 1+(i-1)*(nHDivide+1)+j;
					tri.v0 = tri.n0 = tri.t0 = a;	
					tri.v1 = tri.n1 = tri.t1 = b;	
					tri.v2 = tri.n2 = tri.t2 = c;

					obj.AddTriangle(tri);
					a = 1+i*(nHDivide+1)+j;
					b = 1+(i-1)*(nHDivide+1)+j-1;
					c = 1+i*(nHDivide+1)+j-1;
					tri.v0 = tri.n0 = tri.t0 = a;	
					tri.v1 = tri.n1 = tri.t1 = b;	
					tri.v2 = tri.n2 = tri.t2 = c;
					obj.AddTriangle(tri);
				}
			}
			else
			{
				for( j = 1; j <= nHDivide; j++ )
				{
					a = 1+(i-1)*(nHDivide+1)+j-1;					// i  ,j ---i  , j-1
					b = 1+(i-1)*(nHDivide+1)+j;						//    |  \     |
					c = 1+i*(nHDivide+1)+j;							//    |   \    |
					tri.v0 = tri.n0 = tri.t0 = a;					// i-1,j -- i-1, j-1	
					tri.v1 = tri.n1 = tri.t1 = b;	
					tri.v2 = tri.n2 = tri.t2 = c;

					obj.AddTriangle(tri);
					a = 1+i*(nHDivide+1)+j;
					b = 1+i*(nHDivide+1)+j-1;
					c = 1+(i-1)*(nHDivide+1)+j-1;
					tri.v0 = tri.n0 = tri.t0 = a;	
					tri.v1 = tri.n1 = tri.t1 = b;	
					tri.v2 = tri.n2 = tri.t2 = c;
					obj.AddTriangle(tri);
				}
			}
		}
	}
	return true;
}

bool CPlantObject::ConvertToObjPageOne( OBJFileData& obj, MTLFileData& mtl, float rate, float scale, bool bNormal, bool bTexture, bool bFace, float xStart, float yStart, float xEnd, float yEnd )
{
	//将当前PlantObject转化为OBJFileData对象
	if(!m_bObjectCalcued)return false;
	CString strTemp("");
	int i = 0, j = 0, a = 0, b = 0, c = 0;
	OBJVECTOR vec;
	OBJTRIANGLE tri;
	obj.Clear();
	float xRange = xEnd - xStart, yRange = yEnd - yStart;
	//点
	for( i = 0; i <= nVDivide; i++ )
	{
		for( j = 0; j <= nHDivide; j++ )
		{
			vec.m_fVec[0] = float( Vertex[i*(nHDivide+1)+j].x * rate );
			vec.m_fVec[1] = float( Vertex[i*(nHDivide+1)+j].y * rate );
			vec.m_fVec[2] = float( Vertex[i*(nHDivide+1)+j].z * rate );
			obj.AddVertex(vec);
			if( bNormal )
			{
				vec.m_fVec[0] = float( Normal[i*(nHDivide+1)+j].x );
				vec.m_fVec[1] = float( Normal[i*(nHDivide+1)+j].y );
				vec.m_fVec[2] = float( Normal[i*(nHDivide+1)+j].z );
				obj.AddNormal(vec);
			}
			if( bTexture )
			{
				vec.m_fVec[0] = float( xStart + Texture[i*(nHDivide+1)+j].x * xRange );
				vec.m_fVec[1] = float( yStart + Texture[i*(nHDivide+1)+j].y * yRange );
				vec.m_fVec[2] = float( Texture[i*(nHDivide+1)+j].z );
				obj.AddTexCoord(vec);
			}
		}
	}
	//面
	if(bFace)
	{
		tri.nOrgan = nOrder;
		tri.nPlant = nPlantOrder;
		if( m_sObj == _T("Land") )
			tri.sType = _T("land");
		else if(m_sObj == "Sensor")
			tri.sType = _T("detc");
		else if(m_sObj == "Stalk")
			tri.sType = _T("stem");
		else if(m_sObj == "Leaf")
			tri.sType = _T("leaf");
		else if(m_sObj == "Back")
			tri.sType = _T("back");
		else if(m_sObj == "Sheath")
			tri.sType = _T("shth");
		else if(m_sObj == "Ear")
			tri.sType = _T("frut");
		else if(m_sObj == "Tassel")
			tri.sType = _T("flwr");
		else if(m_sObj == "Root")
			tri.sType = _T("oter");
		else
			tri.sType = _T("oter");

		for( i = 1; i <= nVDivide; i++ )
		{
			if(m_bNormal)
			{
				for( j = 1; j <= nHDivide; j++ )
				{
					a = 1+(i-1)*(nHDivide+1)+j-1;
					b = 1+i*(nHDivide+1)+j;
					c = 1+(i-1)*(nHDivide+1)+j;
					tri.v0 = tri.n0 = tri.t0 = a;	
					tri.v1 = tri.n1 = tri.t1 = b;	
					tri.v2 = tri.n2 = tri.t2 = c;

					obj.AddTriangle(tri);
					a = 1+i*(nHDivide+1)+j;
					b = 1+(i-1)*(nHDivide+1)+j-1;
					c = 1+i*(nHDivide+1)+j-1;
					tri.v0 = tri.n0 = tri.t0 = a;	
					tri.v1 = tri.n1 = tri.t1 = b;	
					tri.v2 = tri.n2 = tri.t2 = c;
					obj.AddTriangle(tri);
				}
			}
			else
			{
				for( j = 1; j <= nHDivide; j++ )
				{
					a = 1+(i-1)*(nHDivide+1)+j-1;
					b = 1+(i-1)*(nHDivide+1)+j;
					c = 1+i*(nHDivide+1)+j;
					tri.v0 = tri.n0 = tri.t0 = a;	
					tri.v1 = tri.n1 = tri.t1 = b;	
					tri.v2 = tri.n2 = tri.t2 = c;

					obj.AddTriangle(tri);
					a = 1+i*(nHDivide+1)+j;
					b = 1+i*(nHDivide+1)+j-1;
					c = 1+(i-1)*(nHDivide+1)+j-1;
					tri.v0 = tri.n0 = tri.t0 = a;	
					tri.v1 = tri.n1 = tri.t1 = b;	
					tri.v2 = tri.n2 = tri.t2 = c;
					obj.AddTriangle(tri);
				}
			}
		}
	}
	return true;
}

BOOL CPlantObject::GetFileInfoCnt(CString path, int& nPiece)
{
	CStdioFile f;
	CFileException e;
	BOOL m_bFlag = TRUE;
	CString strTemp;
	if (!f.Open(path, CFile::modeRead|CFile::typeText, &e))
	{
		return false;
	}
	f.SeekToBegin();
	nPiece = 0;
	while( m_bFlag )   
	{   
		m_bFlag = f.ReadString(strTemp);
		if( strTemp.GetLength() > 5 )	//Introductions
		{
			nPiece++;	
		} 
	}
	f.Close();
	return true;
}

void CPlantObject::Copy(const CPlantObject& mObject)
{
	nOrder = mObject.nOrder;							//序号
	nPlantOrder = mObject.nPlantOrder;					//所属植株序号
	m_sObj = mObject.m_sObj;							//对象
	m_sName = mObject.m_sName;
	m_sVarName = mObject.m_sVarName;					//品种名称
	m_unit = mObject.m_unit;							//单位
	mColor = mObject.mColor;							//颜色
	msTexturePath = mObject.msTexturePath;				//纹理路径
	mTexture = mObject.mTexture;						//纹理指针起始位置
	nTextureIndex = mObject.nTextureIndex;				//纹理索引号
	m_bTextureGenerated = mObject.m_bTextureGenerated;
	nGrowthDay = mObject.nGrowthDay;					//当前生长时刻
	nStartDay = mObject.nStartDay;						//开始生长时刻
	nStopDay = mObject.nStopDay;						//停止生长时刻
	nOldDay = mObject.nOldDay;							//衰老时刻
	nEndDay = mObject.nEndDay;							//终止时刻
	m_bObjectCalcued = mObject.m_bObjectCalcued;		//计算完成
	m_bParamInited = mObject.m_bParamInited;			//参数完成初始化
	m_bKeyParamGenerated = mObject.m_bKeyParamGenerated;
	m_bShowNormal = mObject.m_bShowNormal;
	m_bShowBox = mObject.m_bShowBox;
	pBase = mObject.pBase;
	m_bNormal = mObject.m_bNormal;

	int i = 0;
	for( i = 0; i < 8; i++ )
	{
		mBoxVertex[i] = mObject.mBoxVertex[i];
	}
	for( i = 0; i < 16; i++ )
	{
		mLocalCoordin[i] = mObject.mLocalCoordin[i];
	}

	//几何形态结构
	Vertex.Copy(mObject.Vertex);		//顶点
	Normal.Copy(mObject.Normal);		//法向
	Texture.Copy(mObject.Texture);		//纹理
	nHDivide = mObject.nHDivide;							//横向划分数
	nVDivide = mObject.nVDivide;							//纵向划分数

	mDrawMode = mObject.mDrawMode;
	mLifeState = mObject.mLifeState;
	mGrowthPeriod = mObject.mGrowthPeriod;
}

void CPlantObject::CopySimple(const CPlantObject& mObject,float scale )
{//根据scale大小确定网格简化倍数，仅拷贝Vertex、Normal、Texture
	if( mObject.nHDivide < 1||mObject.nVDivide < 1 ) return;
	if( mObject.Vertex.GetSize() != (mObject.nVDivide+1)*(mObject.nHDivide+1))return;
	if( mObject.Normal.GetSize() != mObject.Vertex.GetSize())return;
	if( mObject.Texture.GetSize() != mObject.Vertex.GetSize() )return;
	if( scale < 1.0 ) scale = 1.0;
	float mDel = pow(2.0f,float(scale-1.0));
	nHDivide = int(mObject.nHDivide/mDel);
	nVDivide = int(mObject.nVDivide/mDel);
	if( nHDivide < 1 ) nHDivide = 1;
	if( nVDivide < 1 ) nVDivide = 1;
	float mDelH = float(float(mObject.nHDivide)/nHDivide);
	float mDelV = float(float(mObject.nVDivide)/nVDivide);
	//设置
	Vertex.SetSize((nHDivide+1)*(nVDivide+1));
	Normal.SetSize((nHDivide+1)*(nVDivide+1));
	Texture.SetSize((nHDivide+1)*(nVDivide+1));
	int i = 0, j = 0, m = 0, n = 0;
	for( i = 0; i <= nVDivide; i++ )
	{
		if( i == 0 )
			m = 0;
		else if( i == nVDivide)
			m = mObject.nVDivide;
		else
			m = int(i*mDelV);
		for( j = 0; j <= nHDivide; j++ )
		{
			if( j == 0 )
				n = 0;
			else if( j == nHDivide)
				n = mObject.nHDivide;
			else
				n = int(j*mDelH);
			Vertex[i*(nHDivide+1)+j] = mObject.Vertex[m*(mObject.nHDivide+1)+n];
			Normal[i*(nHDivide+1)+j] = mObject.Normal[m*(mObject.nHDivide+1)+n];
			Texture[i*(nHDivide+1)+j] = mObject.Texture[m*(mObject.nHDivide+1)+n];
		}
	}
	//纹理
	nOrder = mObject.nOrder;
	nPlantOrder = mObject.nPlantOrder;
	m_sObj = mObject.m_sObj;
	m_sName = mObject.m_sName;
	m_sVarName = mObject.m_sVarName;
	m_unit = mObject.m_unit;
	mColor = mObject.mColor;
	mTexture = mObject.mTexture;
	nTextureIndex = mObject.nTextureIndex;
}