#ifndef SRSOFTRENDER_H
#define SRSOFTRENDER_H

//#include "SRObj.h"
#include <windows.h>

#include <vector>

#include "SRCommonStruct.h"

class SRObj;
class SRCamera;
class SRLight;

class SRSoftRender
{
public:
	HRESULT Init(HWND hWnd, int width, int height);

	void Render();

	void CopyToScreen();

	SRVertex VertexStage(Matrix4x4 modelToViewMatrix, SRVertex inVertex);

	void CleanUp();
	
	//std::vector<SRObj *> m_objList;
	SRObj * m_testCube;
	std::vector<SRLight *> m_lightList;

	SRCamera * m_camera;
};

#endif