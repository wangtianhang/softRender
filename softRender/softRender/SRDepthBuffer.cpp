#include "SRDepthBuffer.h"


SRDepthBuffer::SRDepthBuffer(int width, int height)
{
	m_pDepthArray = new float[width * height];

	m_width = width;
	m_height = height;
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
