#ifndef _SCENE_GEOME_H_SCENE_DLL_
#define _SCENE_GEOME_H_SCENE_DLL_

const float SCENE_PI = float(3.14159);
const int SCENE_VIEW_TO_PACE = 20;

typedef class ScenePoint3D{
public:
	ScenePoint3D(){x=0.0;y=0.0;z=0.0;}
	ScenePoint3D(float p_x,float p_y, float p_z){x=p_x;y=p_y;z=p_z;}
	virtual ~ScenePoint3D(){};
	ScenePoint3D operator +(const ScenePoint3D &p){ScenePoint3D pt;pt.x=p.x+x;pt.y=p.y+y;pt.z=p.z+z;return pt;}
	ScenePoint3D operator -(const ScenePoint3D &p){ScenePoint3D pt;pt.x=x-p.x;pt.y=y-p.y;pt.z=z-p.z;return pt;}
	ScenePoint3D operator ^(const ScenePoint3D &p){ScenePoint3D pt;pt.x=float(0.5*(p.x+x));pt.y=float(0.5*(p.y+y));pt.z=float(0.5*(p.z+z));return pt;}
	ScenePoint3D operator *(const float t){ScenePoint3D pt;pt.x=t*x;pt.y=t*y;pt.z=t*z;return pt;}
	void Set(float px,float py,float pz){x=px;y=py;z=pz;}
	float DistanceTo(ScenePoint3D p){return float(sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y)+(p.z-z)*(p.z-z)));}	
	void Unitize(){float t=float(sqrt(x*x+y*y+z*z));if(t<0.00001)return;x/=t;y/=t;z/=t;}
	ScenePoint3D PartTo(ScenePoint3D p,float t){ScenePoint3D pt;pt.x=x+t*(p.x-x);pt.y=y+t*(p.y-y);pt.z=z+t*(p.z-z);return pt;}
	float Mode(){return float(sqrt(x*x+y*y+z*z));}
public:	
	float x,y,z;
}SCENEPOINT3D;


#endif 