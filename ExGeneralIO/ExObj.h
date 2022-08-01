#pragma once
#include <vector>
typedef struct objVector
{
	float m_fVec[3];
}OBJVECTOR;

typedef struct objTriangle
{
	int v0,v1,v2;	//������������
	int t0,t1,t2;	//������������
	int n0,n1,n2;	//������������
	//���Pnt����
	int nType;		//
	CString sType;
	int nPlant;
	int nOrgan;
	int nOrder;
}OBJTRIANGLE;

typedef std::vector<OBJVECTOR>		POINTARRAY;		// ������
typedef std::vector<OBJTRIANGLE>	TRIANGLEARRAY;	// ������

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

	// �õ�����
	OBJVECTOR	GetVertex(int index);
	OBJVECTOR	GetNormal(int index);
	OBJVECTOR	GetTexCoord(int index);
	OBJTRIANGLE	GetTriangle(int index);
	CString		GetObjName();
	CString		GetMtlName();
	CString		GetObjProp();
	// �õ�����
	int NumVertexs();
	int NumNormals();
	int NumTexCoords();
	int NumTriangles();
	//
	bool IsNull();
public:
	POINTARRAY			m_VertexArray;		// ������Ϣ
	POINTARRAY			m_NormalArray;		// ������Ϣ
	POINTARRAY			m_TexCoordArray;	// ������Ϣ
	TRIANGLEARRAY		m_TriangleArray;	// ����������
	CString				m_objName;			// ��
	CString				m_mtlName;			// ������
	CString				m_objProp;			// ������
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
	CString		m_mtlName;					// ������
	CString		m_texName;					// ������
	OBJVECTOR	m_ColorAmbient;				// ������ɫ
	OBJVECTOR	m_ColorDiffuse;				// ��������ɫ
	OBJVECTOR	m_ColorSpecular;			// ���淴����ɫ
	float		m_SpecularPower;			// ������ǿ�� 0 - 128
};

class AFX_EXT_CLASS ExportOBJFile
{
	// ʵ��
public:
	ExportOBJFile();
	~ExportOBJFile();
	// �������
	void Clear();
	void AddOBJData(OBJFileData obj);
	void AddMTLData(MTLFileData mtl);
	void AddOBJData(CArray<OBJFileData,OBJFileData>& obj);
	void AddMTLData(CArray<MTLFileData,MTLFileData>& mtl);
	void AddOBJData(std::vector<OBJFileData>& obj);
	void AddMTLData(std::vector<MTLFileData>& mtl);
	// д�ļ�
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

	// �õ�����
	int NumObjs();
	int NumMtls();
	bool IsNull();
	OBJFileData GetOBJAt(int nIndex);
	MTLFileData GetMTLAt(int nIndex);

protected:
	// д�����ļ�

	// ����
public:
	std::vector<OBJFileData>	m_ObjData;		// ģ������
	std::vector<MTLFileData>	m_MtlData;		// ��������
	CString			m_FileName;
	CString			m_szFileName;
	CString			m_szPathName;
	CString			m_szFilePathName;
};

