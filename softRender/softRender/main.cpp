#include <d3d9.h>
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )
#include <DxErr.h>

#include <math.h>

#include "SRColorBuffer.h"
#include "SRRasterization.h"
#include "SRMatrix.h"

#pragma comment(lib, "dxerr.lib")
#pragma comment(lib, "d3d9.lib")


//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
//LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL; // Buffer to hold Vertices
//LPDIRECT3DSURFACE9  g_offLineBuffer = NULL;
LPDIRECT3DSURFACE9  g_backBuffer = NULL;
SRColorBuffer * g_colorBuffer = NULL;

// A structure for our custom vertex type
//struct CUSTOMVERTEX
//{
//	FLOAT x, y, z, rhw; // The transformed position for the vertex
//	DWORD color;        // The vertex color
//};

// Our custom FVF, which describes our custom vertex structure
//#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)
// struct Color
// {
// 	float a, r, g, b;
// };

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D(HWND hWnd)
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
	d3dpp.BackBufferWidth = 640;
	d3dpp.BackBufferHeight = 480;

	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;

	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	g_colorBuffer = new SRColorBuffer(640, 480);

	// Device state would normally be set here
	//g_pd3dDevice->CreateOffscreenPlainSurface(300, 300, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_offLineBuffer, NULL);

	return S_OK;
}


//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
	//if (g_pVB != NULL)
	//	g_pVB->Release();

	if (g_pd3dDevice != NULL)
		g_pd3dDevice->Release();

	if (g_pD3D != NULL)
		g_pD3D->Release();
}

void RenderContent()
{
	//lineBres(10, 10, 20, 20, g_colorBuffer);
	SRColor red;
	red.a = 1;
	red.r = 1;
	SRColor green;
	green.a = 1;
	green.g = 1;
	SRColor blue;
	blue.a = 1;
	blue.b = 1;

	DrawTriangle(100, 200, red, 200, 100, green, 200, 300, blue);
}


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	// Clear the backbuffer to a blue color
	g_pd3dDevice->BeginScene();

	HRESULT ret = g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &g_backBuffer);

	D3DSURFACE_DESC surfacedesc;
	HRESULT ret2= g_backBuffer->GetDesc(&surfacedesc);

	/*D3DLOCKED_RECT pRect;
	HRESULT ret3 = g_backBuffer->LockRect(&pRect, NULL, NULL);
	const TCHAR * message1 = DXGetErrorString(ret3);
	const TCHAR * message2 = DXGetErrorDescription(ret3);
	
	D3DCOLOR * pColorArray = (D3DCOLOR *)pRect.pBits;
	for (int i = 0; i < 480; ++i)
	{
		for (int j = 0; j < 640; ++j)
		{
			pColorArray[i * 640 + j] = D3DCOLOR_ARGB(255, 0, 255, 0);
		}
	}

	g_backBuffer->UnlockRect();*/

	RenderContent();

	g_colorBuffer->CopyBufferToSurface(g_backBuffer);

	g_pd3dDevice->EndScene();
	//D3DSURFACE_DESC surfacedesc;
	//HRESULT ret2 = g_offLineBuffer->GetDesc(&surfacedesc);

	//D3DLOCKED_RECT pRect;
	//g_offLineBuffer->LockRect(&pRect, NULL, NULL);
	

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain(HINSTANCE hInst, HINSTANCE, LPWSTR, INT)
{
	UNREFERENCED_PARAMETER(hInst);

	// Register the window class
	WNDCLASSEX wc =
	{
		sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"softRender", NULL
	};
	RegisterClassEx(&wc);

	// Create the application's window
	HWND hWnd = CreateWindow(L"softRender", L"softRenderInstance",
		WS_OVERLAPPED | WS_SYSMENU, 100, 100, 640, 480,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(
		(hWnd)))
	{
		InitD3D(hWnd);
		// Create the vertex buffer
// 		if (SUCCEEDED(InitVB()))
// 		{
			// Show the window
			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			// Enter the message loop
			MSG msg;
			ZeroMemory(&msg, sizeof(msg));
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
					Render();
			}
/*		}*/
	}

	UnregisterClass(L"softRender", wc.hInstance);
	return 0;
}
