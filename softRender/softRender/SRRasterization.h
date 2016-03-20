
#ifndef SRRASTERIZATION_H
#define SRRASTERIZATION_H

#include <math.h>
//#include "SRColorBuffer.h"

#include "SRCommonStruct.h"

class SRRasterization
{
public:
	void LineBres(int x0, int y0, SRVertex vertex0, int xEnd, int yEnd, SRVertex vertex1);

	// ��ʵ��ƽ��������
	void DrawTriangleBelowFlat2(int x1, int y1, SRVertex vertex1, int x2, int y2, SRVertex vertex2, int x3, int y3, SRVertex vertex3);

	// ��ʵ��ƽ�������� 
	void DrawTriangleTopFlat2(int x1, int y1, SRVertex vertex0, int x2, int y2, SRVertex vertex2, int x3, int y3, SRVertex vertex3);

	// ������ʵ��������
	void DrawTriangle(int x1, int y1, SRVertex vertex1, int x2, int y2, SRVertex vertex2, int x3, int y3, SRVertex vertex3);

	void GetViewPortMatrix(Matrix4x4 outMatrix);

	//bool IsInScreen(int x, int y);
	SRColor FragmentStage(SRFragment srFragment);

	inline bool IsInScreen(int x, int y);

	int m_width;
	int m_height;
};

#endif