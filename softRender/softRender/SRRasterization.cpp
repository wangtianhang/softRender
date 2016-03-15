#include "SRRasterization.h"

extern SRColorBuffer * g_colorBuffer;

inline float GetWeight(int x0, int y0, int x1, int y1, int x, int y)
{
// 	int dx = abs(x1 - x0);
// 	int dy = abs(y1 - y0);
// 	if (dx == 0 && dy == 0)
// 	{
// 		return 1;
// 	}
// 
// 	if (dx > dy)
// 	{
// 		int xMin;
// 		int xMax;
// 		if (x0 < x1)
// 		{
// 			xMin = x0;
// 			xMax = x1;
// 		}
// 		else
// 		{
// 			xMin = x1;
// 			xMax = x0;
// 		}
// 
// 		if (x < xMin)
// 		{
// 			return 0;
// 		}
// 		if (x > xMax)
// 		{
// 			return 1;
// 		}
// 		float weight = (float)(x - xMin) / dx;
// 		return weight;
// 	}
// 	else
// 	{
// 		int yMin;
// 		int yMax;
// 		if (y0 < y1)
// 		{
// 			yMin = y0;
// 			yMax = y1;
// 		}
// 		else
// 		{
// 			yMin = y1;
// 			yMax = y0;
// 		}
// 
// 		if (y < yMin)
// 		{
// 			return 0;
// 		}
// 		if (y > yMax)
// 		{
// 			return 1;
// 		}
// 		float weight = (float)(y - yMin) / dy;
// 		return weight;
// 	}
	if (x1 == x0 && y1 == y0)
	{
		return 1;
	}
	float totalDistance = sqrtf((x1 - x0) * (x1 - x0) + (y1- y0) * (y1 - y0));
	float partDistance = sqrtf((x - x0) * (x - x0) + (y - y0) * (y - y0));
	float weight = partDistance / totalDistance;
	if(weight > 1)
	{
		weight = 1;
	}
	return weight;
}

void lineBres(int x0, int y0, SRColor color0, int xEnd, int yEnd, SRColor colorEnd)
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

	//float lineDistance = sqrtf((xEnd - x0) * (xEnd - x0) + (yEnd - y0) * (yEnd - y0));

	//float pointDistance = sqrtf((x - x0) * (x - x0) + (y - y0) * (y - y0));
	//float weight = pointDistance / lineDistance;
	float weight = GetWeight(x0, y0, xEnd, yEnd, x, y);
	//float a = color0.a * (1 - weight) + colorEnd.a;
	//float r = color0.r * (1 - weight) + colorEnd.r;
	//float g = color0.g * (1 - weight) + colorEnd.g;
	//float b = color0.b * (1 - weight) + colorEnd.b;
	SRColor srColor = SRColor::lerp(color0, colorEnd, weight);
	D3DCOLOR color = D3DCOLOR_ARGB((int)(255 * srColor.a), (int)(255 * srColor.r), (int)(255 * srColor.g), (int)(255 * srColor.b));

	g_colorBuffer->SetPixel(x, y, color);

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

		//float pointDistance = sqrtf((x - x0) * (x - x0) + (y - y0) * (y - y0));
		//float weight = pointDistance / lineDistance;
		float weight = GetWeight(x0, y0, xEnd, yEnd, x, y);
		//float a = color0.a * (1 - weight) + colorEnd.a;
		//float r = color0.r * (1 - weight) + colorEnd.r;
		//float g = color0.g * (1 - weight) + colorEnd.g;
		//float b = color0.b * (1 - weight) + colorEnd.b;
		SRColor srColor = SRColor::lerp(color0, colorEnd, weight);
		D3DCOLOR color = D3DCOLOR_ARGB((int)(255 * srColor.a), (int)(255 * srColor.r), (int)(255 * srColor.g), (int)(255 * srColor.b));

		g_colorBuffer->SetPixel(x, y, color);
	}
}

// 画实心平底三角形, x1为顶 x2在左，x3在右
void DrawTriangleBelowFlat2(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3)
{
	for (int y = y1; y <= y2; ++y)
	{
		int xs, xe;
		xs = (y - y1) * (x2 - x1) / (y2 - y1) + x1 + 0.5;
		xe = (y - y1) * (x3 - x1) / (y3 - y1) + x1 + 0.5;

		SRColor xsColor;
		float weightS = GetWeight(x2, y2, x1, y1, xs, y);
		//xsColor.a = color1.a * (1 - weightS) + color2.a;
		//xsColor.r = color1.r * (1 - weightS) + color2.r;
		//xsColor.g = color1.g * (1 - weightS) + color2.g;
		//xsColor.b = color1.b * (1 - weightS) + color2.b;
		xsColor = SRColor::lerp(color2, color1, weightS);

		SRColor xeColor;
		float weightE = GetWeight(x1, y1, x3, y3, xe, y);
		
		//xeColor.a = color2.a * (1 - weightS) + color3.a;
		//xeColor.r = color2.r * (1 - weightS) + color3.r;
		//xeColor.g = color2.g * (1 - weightS) + color3.g;
		//xeColor.b = color2.b * (1 - weightS) + color3.b;
		xeColor = SRColor::lerp(color1, color3, weightE);

		lineBres(xs, y, xsColor, xe, y, xeColor);
	}
}

// 画实心平顶三角形, y3为底 y1在左, y2在右
void DrawTriangleTopFlat2(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3)
{
	for (int y = y1; y <= y3; ++y)
	{
		int xs, xe;
		xs = (y - y1) * (x3 - x1) / (y3 - y1) + x1 + 0.5;
		xe = (y - y2) * (x3 - x2) / (y3 - y2) + x2 + 0.5;

		SRColor xsColor;
		float weightS = GetWeight(x1, y1, x3, y3, xs, y);
		//xsColor.a = color2.a * (1 - weightS) + color1.a;
		//xsColor.r = color2.r * (1 - weightS) + color1.r;
		//xsColor.g = color2.g * (1 - weightS) + color1.g;
		//xsColor.b = color2.b * (1 - weightS) + color1.b;
		xsColor = SRColor::lerp(color1, color3, weightS);

		SRColor xeColor;
		float weightE = GetWeight(x3, y3, x2, y2, xe, y);

		//xeColor.a = color1.a * (1 - weightS) + color3.a;
		//xeColor.r = color1.r * (1 - weightS) + color3.r;
		//xeColor.g = color1.g * (1 - weightS) + color3.g;
		//xeColor.b = color1.b * (1 - weightS) + color3.b;
		xeColor = SRColor::lerp(color3, color2, weightE);

		lineBres(xs, y, xsColor, xe, y, xeColor);
	}
}

// 画任意实心三角形
void DrawTriangle(int x1, int y1, SRColor color1, int x2, int y2, SRColor color2, int x3, int y3, SRColor color3)
{
	if (y1 == y2)
	{
		if (y3 <= y1) // 平底  
		{
			DrawTriangleBelowFlat2(x3, y3, color3, x1, y1, color1, x2, y2, color2);
		}
		else // 平顶  
		{
			DrawTriangleTopFlat2(x1, y1, color1, x2, y2, color2, x3, y3, color3);
		}
	}
	else if (y1 == y3)
	{
		if (y2 <= y1) // 平底  
		{
			DrawTriangleBelowFlat2(x2, y2, color2, x1, y1, color1, x3, y3, color3);
		}
		else // 平顶  
		{
			DrawTriangleTopFlat2(x1, y1, color1, x3, y3, color3, x2, y2, color2);
		}
	}
	else if (y2 == y3)
	{
		if (y1 <= y2) // 平底  
		{
			DrawTriangleBelowFlat2(x1, y1, color1, x2, y2, color2, x3, y3, color3);
		}
		else // 平顶  
		{
			DrawTriangleTopFlat2(x2, y2, color2, x3, y3, color3, x1, y1, color1);
		}
	}
	else
	{
		double xtop, ytop, xmiddle, ymiddle, xbottom, ybottom;
		SRColor topColor, middleColr, bottomColor, longSideMiddleColor;
		if (y1 < y2 && y2 < y3) // y1 y2 y3  
		{
			xtop = x1;
			ytop = y1;
			topColor = color1;
			xmiddle = x2;
			ymiddle = y2;
			middleColr = color2;
			xbottom = x3;
			ybottom = y3;
			bottomColor = color3;
		}
		else if (y1 < y3 && y3 < y2) // y1 y3 y2  
		{
			xtop = x1;
			ytop = y1;
			topColor = color1;
			xmiddle = x3;
			ymiddle = y3;
			middleColr = color3;
			xbottom = x2;
			ybottom = y2;
			bottomColor = color2;
		}
		else if (y2 < y1 && y1 < y3) // y2 y1 y3  
		{
			xtop = x2;
			ytop = y2;
			topColor = color2;
			xmiddle = x1;
			ymiddle = y1;
			middleColr = color1;
			xbottom = x3;
			ybottom = y3;
			bottomColor = color3;
		}
		else if (y2 < y3 && y3 < y1) // y2 y3 y1  
		{
			xtop = x2;
			ytop = y2;
			topColor = color2;
			xmiddle = x3;
			ymiddle = y3;
			middleColr = color3;
			xbottom = x1;
			ybottom = y1;
			bottomColor = color1;
		}
		else if (y3 < y1 && y1 < y2) // y3 y1 y2  
		{
			xtop = x3;
			ytop = y3;
			topColor = color3;
			xmiddle = x1;
			ymiddle = y1;
			middleColr = color1;
			xbottom = x2;
			ybottom = y2;
			bottomColor = color2;
		}
		else if (y3 < y2 && y2 < y1) // y3 y2 y1  
		{
			xtop = x3;
			ytop = y3;
			topColor = color3;
			xmiddle = x2;
			ymiddle = y2;
			middleColr = color2;
			xbottom = x1;
			ybottom = y1;
			bottomColor = color1;
		}
		int xlongSide; // 长边在ymiddle时的x，来决定长边是在左边还是右边  
		xlongSide = (ymiddle - ytop) * (xbottom - xtop) / (ybottom - ytop) + xtop + 0.5;

		//float weight = 0;
		if (xlongSide <= xmiddle) // 左三角形  
		{
			float weight = GetWeight(xbottom, ybottom, xtop, ytop, xlongSide, ymiddle);
				
			longSideMiddleColor = SRColor::lerp(bottomColor, topColor, weight);
			// 画平底  
			DrawTriangleBelowFlat2(xtop, ytop, topColor, xlongSide, ymiddle, longSideMiddleColor, xmiddle, ymiddle, middleColr);

			// 画平顶  
			DrawTriangleTopFlat2(xlongSide, ymiddle, longSideMiddleColor, xmiddle, ymiddle, middleColr, xbottom, ybottom, bottomColor);
		}
		else // 右三角形  
		{
			float weight = GetWeight(xbottom, ybottom, xtop, ytop, xlongSide, ymiddle);

			longSideMiddleColor = SRColor::lerp(bottomColor, topColor, weight);

			// 画平底  
			DrawTriangleBelowFlat2(xtop, ytop, topColor, xmiddle, ymiddle, middleColr, xlongSide, ymiddle, longSideMiddleColor);

			// 画平顶  
			DrawTriangleTopFlat2(xmiddle, ymiddle, middleColr, xlongSide, ymiddle, longSideMiddleColor, xbottom, ybottom, bottomColor);
		}
	}
}