#pragma once
#include "gl/gl.h"
#include "gl/glu.h"
#pragma comment(lib,"opengl32.lib")

#ifndef SCENE_MAX_TEXTURE
#define SCENE_MAX_TEXTURE 10
#endif
class AFX_EXT_CLASS CSceneTexture
{
public:
	CSceneTexture(void);
	~CSceneTexture(void);

	GLuint	texCube[6];
	GLuint	texObject[SCENE_MAX_TEXTURE];	//最大支持20个纹理
	void LoadTextureObject(CString mPath[]);
	void LoadTextureCube();
	CString GetSysPath();
};
