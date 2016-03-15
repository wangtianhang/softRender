
#include <d3d9.h>
#include <DxErr.h>

#include "SRColorBuffer.h"



SRColorBuffer::SRColorBuffer(int width, int height)
{
	m_width = width;
	m_height = height;
	m_pBuffer = new D3DCOLOR[width * height]();
}

void SRColorBuffer::SetPixel(int x, int y, D3DCOLOR color)
{
	//int convertY = m_height - y - 1;
	m_pBuffer[y * m_width + x] = color;
}

void SRColorBuffer::CopyBufferToSurface(LPDIRECT3DSURFACE9 pSurface)
{
	D3DLOCKED_RECT pRect;
	HRESULT ret3 = pSurface->LockRect(&pRect, NULL, NULL);
	const TCHAR * message1 = DXGetErrorString(ret3);
	const TCHAR * message2 = DXGetErrorDescription(ret3);

	D3DCOLOR * pColorArray = (D3DCOLOR *)pRect.pBits;
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			pColorArray[i * m_width + j] = m_pBuffer[i * m_width + j];
		}
	}

	pSurface->UnlockRect();
}