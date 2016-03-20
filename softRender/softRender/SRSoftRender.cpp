#include <d3d9.h>
#include <DxErr.h>

#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "d3d9.lib")

#include "SRSoftRender.h"

#include "SRColorBuffer.h"

#include "SRObj.h"

#include "SRMatrix.h"

#include "SRCamera.h"

//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
//LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold Vertices
//LPDIRECT3DSURFACE9  g_offLineBuffer = NULL;
LPDIRECT3DSURFACE9  g_backBuffer = NULL;

SRColorBuffer * g_colorBuffer = NULL;

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

	g_colorBuffer = new SRColorBuffer(width, height);

	m_testCube = new SRObj();
	m_testCube->InitToCube();

	SRPoint cameraPos = SRPoint(0, 0, 10);
	SRVector cameraRight = SRVector(1, 0, 0);
	SRVector cameraUp = SRVector(0, 1, 0);
	m_camera = new SRCamera(cameraPos, cameraRight, cameraUp, width, height);

	return S_OK;
}

void SRSoftRender::Render()
{
	Matrix4x4 modelToWorldMatrix;
	TranslatePoint(m_testCube->m_pos.x, m_testCube->m_pos.y, m_testCube->m_pos.z, modelToWorldMatrix);
	Matrix4x4 worldToViewMatrix;
	m_camera->GetWorldToViewMatrix(worldToViewMatrix);

	Matrix4x4 modelToViewMatrix;
	MatrixMultiMatrix(worldToViewMatrix, modelToWorldMatrix, modelToWorldMatrix);

	std::vector<SRVertex> viewSpaceVertexVec;
	for (int i = 0; i < m_testCube->m_vertexVec.size(); ++i)
	{
		SRVertex ret = VertexStage(modelToWorldMatrix, m_testCube->m_vertexVec[i]);
		viewSpaceVertexVec.push_back(ret);
	}
	// todo : 透视投影
	// todo : 光照

	// todo : 绕序检测
	// todo : 裁剪

	// todo : 视口变换

	// todo : 深度检测

	// todo : 光栅化
	// todo : 纹理映射

	CopyToScreen();
}

void SRSoftRender::CopyToScreen()
{
	g_pd3dDevice->BeginScene();

	HRESULT ret = g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_backBuffer);

	D3DSURFACE_DESC surfacedesc;
	HRESULT ret2 = g_backBuffer->GetDesc(&surfacedesc);
	const TCHAR * message1 = DXGetErrorString(ret2);
	const TCHAR * message2 = DXGetErrorDescription(ret2);

	g_colorBuffer->CopyBufferToSurface(g_backBuffer);

	g_pd3dDevice->EndScene();

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


SRVertex SRSoftRender::VertexStage(Matrix4x4 modelToViewMatrix, SRVertex inVertex)
{
	SRVertex ret;

	ret.m_point = MatrixMultiPoint(modelToViewMatrix, inVertex.m_point);

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


