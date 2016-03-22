
#ifndef SRRASTERIZATION_H
#define SRRASTERIZATION_H

#include <math.h>
//#include "SRColorBuffer.h"

#include "SRCommonStruct.h"

class SRColorBuffer;
class SRDepthBuffer;

class SRRasterization
{
public:
	SRRasterization(int width, int height);

	// 画任意实心三角形
	void DrawTriangle(SRVertex vertex1, SRVertex vertex2, SRVertex vertex3);

	void GetViewPortMatrix(Matrix4x4 & outMatrix);

	void CopyToScreen();

	void ClearBuffer();

private:
	// 画实心平底三角形
	void DrawTriangleBelowFlat2(int x1, int y1, SRVertex vertex1, int x2, int y2, SRVertex vertex2, int x3, int y3, SRVertex vertex3);

	// 画实心平顶三角形 
	void DrawTriangleTopFlat2(int x1, int y1, SRVertex vertex0, int x2, int y2, SRVertex vertex2, int x3, int y3, SRVertex vertex3);

	void LineBres(int x0, int y0, SRVertex vertex0, int xEnd, int yEnd, SRVertex vertex1);

	//bool IsInScreen(int x, int y);

	inline void HandleFragment(int x0, int y0, SRVertex & vertex0, int xEnd, int yEnd, SRVertex & vertex1, int x, int y);

	inline bool IsInScreen(int x, int y);

	inline SRColor PixelShader(SRFragment srFragment);

	SRColorBuffer * m_colorBuffer;
	SRDepthBuffer * m_depthBuffer;

	int m_width;
	int m_height;

	int triangleCounter = 0;
};

#endif