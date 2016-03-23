#include <memory.h>

#include <float.h>

#include "SRDepthBuffer.h"




SRDepthBuffer::SRDepthBuffer(int width, int height)
{
	m_pDepthArray = new float[width * height];

	m_width = width;
	m_height = height;
}

void SRDepthBuffer::ClearBuffer()
{
	//memset(m_pDepthArray, 0, m_width * m_height);
	for (int i = 0; i < m_height; ++i)
	{
		for (int j = 0; j < m_width; ++j)
		{
			m_pDepthArray[i * m_width + j] = FLT_MIN;
		}
	}
}

// void SRDepthBuffer::SetDepth(int x, int y, float depth)
// {
// 	m_pDepthArray[y * m_width + x] = depth;
// }

// float SRDepthBuffer::GetDepth(int x, int y)
// {
// 	float ret = m_pDepthArray[y * m_width + x];
// 	return ret;
// }
