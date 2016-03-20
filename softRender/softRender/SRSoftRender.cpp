#include <d3d9.h>
#include <DxErr.h>

#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "d3d9.lib")

#include "SRSoftRender.h"

#include "SRColorBuffer.h"

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

	return S_OK;
}

void SRSoftRender::Render()
{
	// Clear the backbuffer to a blue color
	g_pd3dDevice->BeginScene();

	HRESULT ret = g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_backBuffer);

	D3DSURFACE_DESC surfacedesc;
	HRESULT ret2 = g_backBuffer->GetDesc(&surfacedesc);
	const TCHAR * message1 = DXGetErrorString(ret2);
	const TCHAR * message2 = DXGetErrorDescription(ret2);

	// todo : 设置正方形模型

	// todo : 转换到投影坐标系
	// todo : 光照

	// todo : 绕序检测
	// todo : 裁剪

	// todo : 视口变换

	// todo : 深度检测

	// todo : 光栅化
	// todo : 纹理映射

	g_colorBuffer->CopyBufferToSurface(g_backBuffer);

	g_pd3dDevice->EndScene();

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void SRSoftRender::VertexStage()
{

}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void SRSoftRender::Cleanup()
{
	//if (g_pVB != NULL)
	//	g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}


