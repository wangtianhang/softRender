#ifndef COLORBUFFER
#define COLORBUFFER

#include <d3d9.h>

struct SRColor
{
	SRColor()
	{
		a = 0;
		r = 0;
		g = 0;
		b = 0;
	}
	float a;
	float r;
	float g;
	float b;

public:
	static SRColor lerp(SRColor left, SRColor right, float weight)
	{
		SRColor ret;
		ret.a = left.a * (1 - weight) + right.a * weight;
		ret.r = left.r * (1 - weight) + right.r * weight;
		ret.g = left.g * (1 - weight) + right.g * weight;
		ret.b = left.b * (1 - weight) + right.b * weight;
		return ret;
	}
};

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


