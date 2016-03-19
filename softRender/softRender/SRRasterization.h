
#ifndef SRRASTERIZATION_H
#define SRRASTERIZATION_H

#include <math.h>
//#include "SRColorBuffer.h"

#include "SRCommonStruct.h"

class SRRasterization
{
public:
	void LineBres(int x0, int y0, SRColor color0, int xEnd, int yEnd, SRColor colorEnd);

	// ��ʵ��ƽ��������
	void DrawTriangleBelowFlat2(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

	// ��ʵ��ƽ�������� 
	void DrawTriangleTopFlat2(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

	// ������ʵ��������
	void DrawTriangle(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

	void GetViewPortMatrix(Matrix4x4 outMatrix);
};

#endif