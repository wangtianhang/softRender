#ifndef SRCOLORBUFFER_H
#define SRCOLORBUFFER_H

#include <d3d9.h>

#include "SRCommonStruct.h"

class SRColorBuffer
{

public:
	SRColorBuffer(int width, int height);
	inline void SetPixel(int x, int y, SRColor srColor)
	{
		D3DCOLOR color = D3DCOLOR_ARGB((int)(255 * srColor.a), (int)(255 * srColor.r), (int)(255 * srColor.g), (int)(255 * srColor.b));
		m_pBuffer[y * m_width + x] = color;
	}

	void CopyBufferToSurface(LPDIRECT3DSURFACE9 pSurface);

	void ClearBuffer();
private:
	int m_width = 0;
	int m_height = 0;
	D3DCOLOR * m_pBuffer = NULL;
};

#endif // !COLORBUFFER


