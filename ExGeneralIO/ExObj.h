#pragma once
#include <vector>
typedef struct objVector
{
	float m_fVec[3];
}OBJVECTOR;

typedef struct objTriangle
{
	int v0,v1,v2;	//顶点坐标索引
	int t0,t1,t2;	//纹理坐标索引
	int n0,n1,n2;	//法线坐标索引
	//添加Pnt索引
	int nType;		//
	CString sType;
	int nPlant;
	int nOrgan;
	int nOrder;
}OBJTRIANGLE;

typedef std::vector<OBJVECTOR>		POINTARRAY;		// 点数组
typedef std::vector<OBJTRIANGLE>	TRIANGLEARRAY;	// 面数组

class AFX_EXT_CLASS OBJFileData
{
public:
	OBJFileData(void);
	~OBJFileData(void);

	void	AddVertex(OBJVECTOR ver);
	void	AddNormal(OBJVECTOR nor);
	void	AddTexCoord(OBJVECTOR tex);
	void	AddTriangle(OBJTRIANGLE tri);
	void	SetTriangle(int nIndex, OBJTRIANGLE tri);
	void	SetObjName(CString name);
	void	SetMtlName(CString name);
	void	SetObjProp(CString prop);
	void	Append(OBJFileData obj);
	void	Clear();

	// 得到数据
	OBJVECTOR	GetVertex(int index);
	OBJVECTOR	GetNormal(int index);
	OBJVECTOR	GetTexCoord(int index);
	OBJTRIANGLE	GetTriangle(int index);
	CString		GetObjName();
	CString		GetMtlName();
	CString		GetObjProp();
	// 得到总数
	int NumVertexs();
	int NumNormals();
	int NumTexCoords();
	int NumTriangles();
	//
	bool IsNull();
public:
	POINTARRAY			m_VertexArray;		// 顶点信息
	POINTARRAY			m_NormalArray;		// 法线信息
	POINTARRAY			m_TexCoordArray;	// 纹理信息
	TRIANGLEARRAY		m_TriangleArray;	// 三角面索引
	CString				m_objName;			// 名
	CString				m_mtlName;			// 材质名
	CString				m_objProp;			// 属性名
};

class AFX_EXT_CLASS MTLFileData 
{
public:
	MTLFileData();
	~MTLFileData();
	void	SetMtlName(CString name);
	void	SetTexName(CString name);
	void	SetAmbient(float r = 0.0f, float g = 0.0f, float b = 0.0f);
	void	SetAmbient(float m[3]);
	void	SetDiffuse(float r = 0.0f, float g = 0.0f, float b = 0.0f);
	void	SetDiffuse(float m[3]);
	void	SetSpecular(float r = 0.0f, float g = 0.0f, float b = 0.0f);
	void	SetSpecular(float m[3]);
	void	SetSpecularPower(float m = 0.0f);

public:
	CString		m_mtlName;					// 材质名
	CString		m_texName;					// 纹理名
	OBJVECTOR	m_ColorAmbient;				// 环境颜色
	OBJVECTOR	m_ColorDiffuse;				// 漫反射颜色
	OBJVECTOR	m_ColorSpecular;			// 镜面反射颜色
	float		m_SpecularPower;			// 漫反射强度 0 - 128
};

class AFX_EXT_CLASS ExportOBJFile
{
	// 实现
public:
	ExportOBJFile();
	~ExportOBJFile();
	// 添加数据
	void Clear();
	void AddOBJData(OBJFileData obj);
	void AddMTLData(MTLFileData mtl);
	void AddOBJData(CArray<OBJFileData,OBJFileData>& obj);
	void AddMTLData(CArray<MTLFileData,MTLFileData>& mtl);
	void AddOBJData(std::vector<OBJFileData>& obj);
	void AddMTLData(std::vector<MTLFileData>& mtl);
	// 写文件
	bool WriteObjFile(CString m_FileName);
	bool WritePntFile(CString m_FileName);
	bool WriteMtlFile(CString m_FileName);
	bool OutputObjFile();
	bool OutputPntFile();
	bool LoadObjFile(CString m_FileName);
	bool LoadPntFile(CString m_FileName);
	bool LoadMtlFile(CString m_FileName);
	bool InputObjFile();
	bool InputPntFile( bool bClear = true );
	void AnalyseFace(CString strVal, int& nType, int nVal[9]);

	// 得到总数
	int NumObjs();
	int NumMtls();
	bool IsNull();
	OBJFileData GetOBJAt(int nIndex);
	MTLFileData GetMTLAt(int nIndex);

protected:
	// 写材质文件

	// 属性
public:
	std::vector<OBJFileData>	m_ObjData;		// 模型数据
	std::vector<MTLFileData>	m_MtlData;		// 材质数据
	CString			m_FileName;
	CString			m_szFileName;
	CString			m_szPathName;
	CString			m_szFilePathName;
};

