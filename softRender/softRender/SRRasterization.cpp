#include <d3d9.h>
#include <DxErr.h>

#include <float.h>

#include "SRRasterization.h"

#include "SRMatrix.h"

#include "SRColorBuffer.h"

#include "SRDepthBuffer.h"

//SRColorBuffer * g_colorBuffer = NULL;

extern LPDIRECT3DDEVICE9       g_pd3dDevice;

inline float GetWeight(int x0, int y0, int x1, int y1, int x, int y)
{
	if (x1 == x0 && y1 == y0)
	{
		return 1;
	}
	float totalDistance = sqrtf((x1 - x0) * (x1 - x0) + (y1 - y0) * (y1 - y0));
	float partDistance = sqrtf((x - x0) * (x - x0) + (y - y0) * (y - y0));
	float weight = partDistance / totalDistance;
	if (weight > 1)
	{
		weight = 1;
	}
	return weight;
}

inline float Lerp(float begin, float end, float weight)
{
	float ret = begin * (1 - weight) + end * weight;
	return ret;
}

SRRasterization::SRRasterization(int width, int height)
{
	m_width = width;
	m_height = height;

	m_depthBuffer = new SRDepthBuffer(width, height);
	m_colorBuffer = new SRColorBuffer(width, height, m_depthBuffer);
	
}

void SRRasterization::DrawTriangle(SRVertex vertex1, SRVertex vertex2, SRVertex vertex3)
{
	int x1 = round(vertex1.m_pos.x);
	int y1 = round(vertex1.m_pos.y);

	int x2 = round(vertex2.m_pos.x);
	int y2 = round(vertex2.m_pos.y);

	int x3 = round(vertex3.m_pos.x);
	int y3 = round(vertex3.m_pos.y);

	if ((x1 == x2 && y1 == y2)
		|| (x1 == x3 && y1 == y3)
		|| (x2 == x3 && y2 == y3))
	{
		return;
	}

	triangleCounter++;

	if (y1 == y2)
	{
		if (y3 <= y1) // 平底  
		{
			DrawTriangleBelowFlat2(x3, y3, vertex3, x1, y1, vertex1, x2, y2, vertex2);
		}
		else // 平顶  
		{
			DrawTriangleTopFlat2(x1, y1, vertex1, x2, y2, vertex2, x3, y3, vertex3);
		}
	}
	else if (y1 == y3)
	{
		if (y2 <= y1) // 平底  
		{
			DrawTriangleBelowFlat2(x2, y2, vertex2, x1, y1, vertex1, x3, y3, vertex3);
		}
		else // 平顶  
		{
			DrawTriangleTopFlat2(x1, y1, vertex1, x3, y3, vertex3, x2, y2, vertex2);
		}
	}
	else if (y2 == y3)
	{
		if (y1 <= y2) // 平底  
		{
			DrawTriangleBelowFlat2(x1, y1, vertex1, x2, y2, vertex2, x3, y3, vertex3);
		}
		else // 平顶  
		{
			DrawTriangleTopFlat2(x2, y2, vertex2, x3, y3, vertex3, x1, y1, vertex1);
		}
	}
	else
	{
		double xtop, ytop, xmiddle, ymiddle, xbottom, ybottom;
		SRVertex topVertex, middleVertex, bottomVertex, longSideMiddleVertex;
		if (y1 < y2 && y2 < y3) // y1 y2 y3  
		{
			xtop = x1;
			ytop = y1;
			topVertex = vertex1;
			xmiddle = x2;
			ymiddle = y2;
			middleVertex = vertex2;
			xbottom = x3;
			ybottom = y3;
			bottomVertex = vertex3;
		}
		else if (y1 < y3 && y3 < y2) // y1 y3 y2  
		{
			xtop = x1;
			ytop = y1;
			topVertex = vertex1;
			xmiddle = x3;
			ymiddle = y3;
			middleVertex = vertex3;
			xbottom = x2;
			ybottom = y2;
			bottomVertex = vertex2;
		}
		else if (y2 < y1 && y1 < y3) // y2 y1 y3  
		{
			xtop = x2;
			ytop = y2;
			topVertex = vertex2;
			xmiddle = x1;
			ymiddle = y1;
			middleVertex = vertex1;
			xbottom = x3;
			ybottom = y3;
			bottomVertex = vertex3;
		}
		else if (y2 < y3 && y3 < y1) // y2 y3 y1  
		{
			xtop = x2;
			ytop = y2;
			topVertex = vertex2;
			xmiddle = x3;
			ymiddle = y3;
			middleVertex = vertex3;
			xbottom = x1;
			ybottom = y1;
			bottomVertex = vertex1;
		}
		else if (y3 < y1 && y1 < y2) // y3 y1 y2  
		{
			xtop = x3;
			ytop = y3;
			topVertex = vertex3;
			xmiddle = x1;
			ymiddle = y1;
			middleVertex = vertex1;
			xbottom = x2;
			ybottom = y2;
			bottomVertex = vertex2;
		}
		else if (y3 < y2 && y2 < y1) // y3 y2 y1  
		{
			xtop = x3;
			ytop = y3;
			topVertex = vertex3;
			xmiddle = x2;
			ymiddle = y2;
			middleVertex = vertex2;
			xbottom = x1;
			ybottom = y1;
			bottomVertex = vertex1;
		}
		int xlongSide; // 长边在ymiddle时的x，来决定长边是在左边还是右边  
		xlongSide = (ymiddle - ytop) * (xbottom - xtop) / (ybottom - ytop) + xtop + 0.5;

		//float weight = 0;
		if (xlongSide <= xmiddle) // 左三角形  
		{
			float weight = GetWeight(xbottom, ybottom, xtop, ytop, xlongSide, ymiddle);

			longSideMiddleVertex = SRVertex::Lerp(bottomVertex, topVertex, weight);
			// 画平底  
			DrawTriangleBelowFlat2(xtop, ytop, topVertex, xlongSide, ymiddle, longSideMiddleVertex, xmiddle, ymiddle, middleVertex);

			// 画平顶  
			DrawTriangleTopFlat2(xlongSide, ymiddle, longSideMiddleVertex, xmiddle, ymiddle, middleVertex, xbottom, ybottom, bottomVertex);
		}
		else // 右三角形  
		{
			float weight = GetWeight(xbottom, ybottom, xtop, ytop, xlongSide, ymiddle);

			longSideMiddleVertex = SRVertex::Lerp(bottomVertex, topVertex, weight);

			// 画平底  
			DrawTriangleBelowFlat2(xtop, ytop, topVertex, xmiddle, ymiddle, middleVertex, xlongSide, ymiddle, longSideMiddleVertex);

			// 画平顶  
			DrawTriangleTopFlat2(xmiddle, ymiddle, middleVertex, xlongSide, ymiddle, longSideMiddleVertex, xbottom, ybottom, bottomVertex);
		}
	}
}

void SRRasterization::GetViewPortMatrix(Matrix4x4 & outMatrix)
{
	//Matrix4x4SetZero(outMatrix);

	outMatrix.m00 = m_width / 2; outMatrix.m03 = m_width / 2;
	outMatrix.m11 = m_height / 2; outMatrix.m13 = m_height / 2;
	outMatrix.m22 = 0.5f; outMatrix.m23 = 0.5f;
	outMatrix.m33 = 1;
}

void SRRasterization::CopyToScreen()
{
	g_pd3dDevice->BeginScene();

	LPDIRECT3DSURFACE9 backBuffer;
	HRESULT ret = g_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &backBuffer);

	D3DSURFACE_DESC surfacedesc;
	HRESULT ret2 = backBuffer->GetDesc(&surfacedesc);
	const TCHAR * message1 = DXGetErrorString(ret2);
	const TCHAR * message2 = DXGetErrorDescription(ret2);

	m_colorBuffer->CopyBufferToSurface(backBuffer);

	g_pd3dDevice->EndScene();

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}


void SRRasterization::DrawTriangleBelowFlat2(int x1, int y1, SRVertex vertex1, int x2, int y2, SRVertex vertex2, int x3, int y3, SRVertex vertex3)
{
	// 画实心平底三角形, x1为顶 x2在左，x3在右
	for (int y = y1; y <= y2; ++y)
	{
		int xs, xe;
		xs = (y - y1) * (x2 - x1) / (y2 - y1) + x1 + 0.5;
		xe = (y - y1) * (x3 - x1) / (y3 - y1) + x1 + 0.5;

		SRVertex xsVertex;
		float weightS = GetWeight(x2, y2, x1, y1, xs, y);
		xsVertex = SRVertex::Lerp(vertex2, vertex1, weightS);

		SRVertex xeVertex;
		float weightE = GetWeight(x1, y1, x3, y3, xe, y);
		xeVertex = SRVertex::Lerp(vertex1, vertex3, weightE);

		LineBres(xs, y, xsVertex, xe, y, xeVertex);
	}
}

void SRRasterization::DrawTriangleTopFlat2(int x1, int y1, SRVertex vertex1, int x2, int y2, SRVertex vertex2, int x3, int y3, SRVertex vertex3)
{
	// 画实心平顶三角形, y3为底 y1在左, y2在右
	for (int y = y1; y <= y3; ++y)
	{
		int xs, xe;
		xs = (y - y1) * (x3 - x1) / (y3 - y1) + x1 + 0.5;
		xe = (y - y2) * (x3 - x2) / (y3 - y2) + x2 + 0.5;

		SRVertex xsVertex;
		float weightS = GetWeight(x1, y1, x3, y3, xs, y);
		xsVertex = SRVertex::Lerp(vertex1, vertex3, weightS);

		SRVertex xeVertex;
		float weightE = GetWeight(x3, y3, x2, y2, xe, y);
		xeVertex = SRVertex::Lerp(vertex3, vertex2, weightE);

		LineBres(xs, y, xsVertex, xe, y, xeVertex);
	}
}

void SRRasterization::LineBres(int x0, int y0, SRVertex vertex0, int xEnd, int yEnd, SRVertex vertex1)
{
	int dx = abs(xEnd - x0), dy = abs(yEnd - y0);
	int p = 2 * dy - dx;
	int twoDy = 2 * dy, twoDyMinusDx = 2 * (dy - dx);
	int x, y;
	if (x0 > xEnd)
	{
		x = xEnd;
		y = yEnd;
		xEnd = x0;
	}
	else
	{
		x = x0;
		y = y0;
	}

	HandleFragment(x0, y0, vertex0, xEnd, yEnd, vertex1, x, y);

	while (x < xEnd)
	{
		x++;
		if (p < 0)
		{
			p += twoDy;
		}
		else
		{
			y++;
			p += twoDyMinusDx;
		}

		HandleFragment(x0, y0, vertex0, xEnd, yEnd, vertex1, x, y);
	}
}

void SRRasterization::HandleFragment(int x0, int y0, SRVertex & vertex0, int xEnd, int yEnd, SRVertex & vertex1, int x, int y)
{
	// todo : 做好规范体裁剪后应该不用判定这一步
	if (IsInScreen(x, y))
	{
		float weight = GetWeight(x0, y0, xEnd, yEnd, x, y);
		float distance = Lerp(vertex0.m_pos.z, vertex1.m_pos.z, weight);
		float cacheDistance = m_depthBuffer->GetDepth(x, y);

		if (cacheDistance != FLT_MAX)
		{
			int test = 0;
		}

		if (distance < cacheDistance)
		{
			SRColor srColor = SRColor::Lerp(vertex0.m_color, vertex1.m_color, weight);
			SRFragment srFragment;
			srFragment.m_color = srColor;
			SRColor color = PixelShader(srFragment);
			m_colorBuffer->SetPixel(x, y, color);
			m_depthBuffer->SetDepth(x, y, distance);
		}
		else
		{
			int test = 0;
		}
	}
}

bool SRRasterization::IsInScreen(int x, int y)
{
	if (x > 0
		&& x < m_width
		&& y > 0
		&& y < m_height)
	{
		return true;
	}
	else
	{
		return false;
	}
}


SRColor SRRasterization::PixelShader(SRFragment srFragment)
{
	// todo : 纹理映射
	return srFragment.m_color;
}

void SRRasterization::ClearBuffer()
{
	m_depthBuffer->ClearBuffer();
	m_colorBuffer->ClearBuffer();

	triangleCounter = 0;
}


