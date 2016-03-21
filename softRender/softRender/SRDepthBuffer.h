#ifndef SRDEPTHBUFFER_H
#define SRDEPTHBUFFER_H

class SRDepthBuffer
{
public:
	SRDepthBuffer(int width, int height);

	inline void SetDepth(int x, int y, float depth)
	{
		m_pDepthArray[y * m_width + x] = depth;
	}

	inline float GetDepth(int x, int y)
	{
		float ret = m_pDepthArray[y * m_width + x];
		return ret;
	}

	void ClearBuffer();

	float * m_pDepthArray;
	int m_width = 0;
	int m_height = 0;
};

#endif