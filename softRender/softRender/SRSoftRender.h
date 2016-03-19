#ifndef SRSOFTRENDER_H
#define SRSOFTRENDER_H

//#include "SRObj.h"

#include <vector>

class SRObj;
class SRCamera;
class SRLight;

class SRSoftRender
{
public:
	void Render();

	void VertexStage();
	
	std::vector<SRObj *> m_objList;
	std::vector<SRLight *> m_lightList;

	SRCamera * m_camera;
};

#endif