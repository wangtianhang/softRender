
#include <d3d9.h>
#include <DxErr.h>

#include <memory.h>

#include <iostream>

#include "SRColorBuffer.h"
#include "SRDepthBuffer.h"

SRColorBuffer::SRColorBuffer(int width, int height, SRDepthBuffer * pDepthBuffer)
{
	m_width = width;
	m_height = height;
	m_pBuffer = new D3DCOLOR[width * height]();
	m_pDepthBuffer = pDepthBuffer;
}

// void SRColorBuffer::SetPixel(int x, int y, SRColor srColor)
// {
// 	D3DCOLOR color = D3DCOLOR_ARGB((int)(255 * srColor.a), (int)(255 * srColor.r), (int)(255 * srColor.g), (int)(255 * srColor.b));
// 	m_pBuffer[y * m_width + x] = color;
// }

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
			if (m_pBuffer[i * m_width + j] != 0)
			{
				float depth = m_pDepthBuffer->GetDepth(j, i);
				//std::cout << i << " " << j << depth << std::endl;
				std::string output = "";
				char c[50];
				_itoa_s(j, c, 10);
				output += c;
				output += " ";
				_itoa_s(i, c, 10);
				output += c;
				output += " ";
				_gcvt_s(c, 50, depth, 30);
				output += c;
				output += "\n";
				OutputDebugString(output.c_str());
			}
			pColorArray[i * m_width + j] = m_pBuffer[i * m_width + j];
		}
	}

	pSurface->UnlockRect();
}

void SRColorBuffer::ClearBuffer()
{
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			m_pBuffer[i * m_width + j] = 0;
		}
	}
}

