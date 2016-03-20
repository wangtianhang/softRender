#ifndef SRSOFTRENDER_H
#define SRSOFTRENDER_H

//#include "SRObj.h"
#include <windows.h>

#include <vector>

#include "SRCommonStruct.h"

class SRObj;
class SRCamera;
class SRLight;
class SRRasterization;

class SRSoftRender
{
public:
	HRESULT Init(HWND hWnd, int width, int height);

	void InitTestModel();

	void InitTestCamera();

	void Render();

	void CopyToScreen();

	SRVertex VertexShader(Matrix4x4 modelToViewMatrix, SRVertex inVertex);

	void CleanUp();
	
	std::vector<SRObj *> m_objList;
	//SRObj * m_testCube;
	std::vector<SRLight *> m_lightList;
	SRCamera * m_camera;
	SRRasterization * m_rasterizationMgr;
	int m_width;
	int m_height;
};

#endif