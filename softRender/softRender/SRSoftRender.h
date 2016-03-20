#ifndef SRSOFTRENDER_H
#define SRSOFTRENDER_H

//#include "SRObj.h"
#include <windows.h>

#include <vector>

class SRObj;
class SRCamera;
class SRLight;

class SRSoftRender
{
public:
	HRESULT Init(HWND hWnd, int width, int height);

	void Render();

	void VertexStage();

	void Cleanup();
	
	std::vector<SRObj *> m_objList;
	std::vector<SRLight *> m_lightList;

	SRCamera * m_camera;
};

#endif