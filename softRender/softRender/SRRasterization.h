
#ifndef SRRASTERIZATION_H
#define SRRASTERIZATION_H

#include <math.h>
#include "SRColorBuffer.h"

void LineBres(int x0, int y0, int xEnd, int yEnd);

// 画实心平底三角形
void DrawTriangleBelowFlat2(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

// 画实心平顶三角形 
void DrawTriangleTopFlat2(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

// 画任意实心三角形
void DrawTriangle(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3);

#endif