#include <d3d9.h>
#include <DxErr.h>

#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "d3d9.lib")

#include "SRSoftRender.h"

#include "SRColorBuffer.h"

#include "SRObj.h"

#include "SRMatrix.h"

#include "SRCamera.h"

#include "SRRasterization.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
//LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold Vertices
//LPDIRECT3DSURFACE9  g_offLineBuffer = NULL;

//LPDIRECT3DSURFACE9  g_backBuffer = NULL;
//SRColorBuffer * g_colorBuffer = NULL;

HRESULT SRSoftRender::Init(HWND hWnd, int width, int height)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;

	// Set up the structure used to create the D3DDevice
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;

	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	m_rasterizationMgr = new SRRasterization(width, height);

	m_width = width;
	m_height = height;

	return S_OK;
}

void SRSoftRender::InitTestModel()
{
	SRObj * testCube = new SRObj();
	testCube->InitToCube();
	m_objList.push_back(testCube);
}

void SRSoftRender::InitTestCamera()
{
	SRPoint cameraPos = SRPoint(0, 0, 10);
	SRVector cameraRight = SRVector(1, 0, 0);
	SRVector cameraUp = SRVector(0, 1, 0);
	m_camera = new SRCamera(cameraPos, cameraRight, cameraUp, m_width, m_height);
}

void SRSoftRender::Render()
{
	for (std::vector<SRObj *>::iterator iter = m_objList.begin(); iter != m_objList.end(); ++iter)
	{
		Matrix4x4 modelToWorldMatrix;
		TranslatePoint((*iter)->m_pos.x, (*iter)->m_pos.y, (*iter)->m_pos.z, modelToWorldMatrix);
		Matrix4x4 worldToViewMatrix;
		m_camera->GetWorldToViewMatrix(worldToViewMatrix);

		Matrix4x4 modelToViewMatrix;
		MatrixMultiMatrix(worldToViewMatrix, modelToWorldMatrix, modelToViewMatrix);

		// todo : 绕序检测

		std::vector<SRVertex> vertexVec;
		for (int i = 0; i < (*iter)->m_vertexVec.size(); ++i)
		{
			SRVertex ret = VertexShader(modelToViewMatrix, (*iter)->m_vertexVec[i]);
			vertexVec.push_back(ret);
		}

		// 透视投影
		Matrix4x4 viewToProjectionMatrix;
		m_camera->GetPerspectiveMatrix(viewToProjectionMatrix);
		for (int i = 0; i < vertexVec.size(); ++i)
		{
			vertexVec[i].m_pos = MatrixMultiPoint(viewToProjectionMatrix, vertexVec[i].m_pos);
			vertexVec[i].m_pos = vertexVec[i].m_pos / vertexVec[i].m_pos.w;
		}

		// todo : 规范化裁剪&重组

		// 视口变换
		Matrix4x4 projectionToScreenMatrix;
		m_rasterizationMgr->GetViewPortMatrix(projectionToScreenMatrix);
		for (int i = 0; i < vertexVec.size(); ++i)
		{
			vertexVec[i].m_pos = MatrixMultiPoint(projectionToScreenMatrix, vertexVec[i].m_pos);
			
		}

		// 光栅化
		m_rasterizationMgr->ClearBuffer();
		for (int i = 0; i < vertexVec.size() / 3; ++i)
		{
			m_rasterizationMgr->DrawTriangle(vertexVec[i * 3], vertexVec[i * 3 + 1], vertexVec[i * 3 + 2]);
		}
	}

	CopyToScreen();
}

void SRSoftRender::CopyToScreen()
{
	m_rasterizationMgr->CopyToScreen();
}

SRVertex SRSoftRender::VertexShader(Matrix4x4 modelToViewMatrix, SRVertex inVertex)
{
	// todo : 光照
	SRVertex ret;

	ret.m_pos = MatrixMultiPoint(modelToViewMatrix, inVertex.m_pos);

	ret.m_color = inVertex.m_color;

	return ret;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void SRSoftRender::CleanUp()
{
	//if (g_pVB != NULL)
	//	g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}




