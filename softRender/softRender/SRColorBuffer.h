#ifndef SRCOLORBUFFER_H
#define SRCOLORBUFFER_H

#include <d3d9.h>

#include "SRCommonStruct.h"

class SRColorBuffer
{

public:
	SRColorBuffer(int width, int height);
	void SetPixel(int x, int y, D3DCOLOR color);
	void CopyBufferToSurface(LPDIRECT3DSURFACE9 pSurface);
private:
	int m_width = 0;
	int m_height = 0;
	D3DCOLOR * m_pBuffer = NULL;
};

#endif // !COLORBUFFER


