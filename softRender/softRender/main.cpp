
#pragma warning( disable : 4996 ) // disable deprecated warning 
#include <strsafe.h>
#pragma warning( default : 4996 )

#include <math.h>

//#include "SRColorBuffer.h"
//#include "SRRasterization.h"
//#include "SRMatrix.h"
#include "SRSoftRender.h"

SRSoftRender * g_softRender = NULL;

const int WIDTH = 640;
const int HEIGHT = 480;

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
// HRESULT InitD3D(HWND hWnd)
// {
// 
// 
// 
// 
// 	// Device state would normally be set here
// 	//g_pd3dDevice->CreateOffscreenPlainSurface(300, 300, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &g_offLineBuffer, NULL);
// 
// 	
// }




// void RenderContent()
// {
// 
// 	
// }


//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID Render()
{
	//lineBres(10, 10, 20, 20, g_colorBuffer);

	//SRColor red;
	//red.a = 1;
	//red.r = 1;
	//SRColor green;
	//green.a = 1;
	//green.g = 1;
	//SRColor blue;
	//blue.a = 1;
	//blue.b = 1;
	//DrawTriangle(100, 200, red, 200, 100, green, 200, 300, blue);



	g_softRender->Render();
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
		g_softRender->CleanUp();
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
		WS_OVERLAPPED | WS_SYSMENU, 100, 100, WIDTH, HEIGHT,
		NULL, NULL, wc.hInstance, NULL);

	// Initialize Direct3D
	if (SUCCEEDED(
		(hWnd)))
	{
		g_softRender = new SRSoftRender();
		g_softRender->Init(hWnd, WIDTH, HEIGHT);

		g_softRender->InitTestModel();
		g_softRender->InitTestCamera();
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
