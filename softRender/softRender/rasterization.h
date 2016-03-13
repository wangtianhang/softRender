
#ifndef RASTERIZATION
#define RASTERIZATION

#include <math.h>
#include "colorBuffer.h"

void lineBres(int x0, int y0, int xEnd, int yEnd);

// ��ʵ��ƽ��������
void DrawTriangleBelowFlat2(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

// ��ʵ��ƽ�������� 
void DrawTriangleTopFlat2(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

// ������ʵ��������
void DrawTriangle(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

#endif