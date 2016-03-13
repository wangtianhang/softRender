#ifndef COLORBUFFER
#define COLORBUFFER

#include <d3d9.h>

class ColorBuffer
{

public:
	ColorBuffer(int width, int height);
	void SetPixel(int x, int y, D3DCOLOR color);
	void CopyBufferToSurface(LPDIRECT3DSURFACE9 pSurface);
private:
	int m_width = 0;
	int m_height = 0;
	D3DCOLOR * m_pBuffer = NULL;
};

#endif // !COLORBUFFER


