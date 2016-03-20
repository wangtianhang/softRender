#ifndef SRCOMMONSTURCT_H
#define SRCOMMONSTURCT_H

#include <math.h>

struct SRPoint
{
	SRPoint()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 1;
	}
	float x;
	float y;
	float z;
	float w;
};

struct SRVector
{
	SRVector()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}
	float x;
	float y;
	float z;
	float w;

	SRVector GetNormaliseVector()
	{
		SRVector ret;
		float magSq = x * x + y * y + z * z;
		if (magSq > 0)
		{
			float oneOverMag = 1.0f / sqrt(magSq);
			ret.x = x * oneOverMag;
			ret.y = y * oneOverMag;
			ret.z = z * oneOverMag;
			ret.w = 0;
		}
		return ret;
	}

	// µÑ¿¨¶û×ø±êÏµ²æ³Ë£¬µÑ¿¨¶ûÎªÓÒÊÖ×ø±êÏµ
	static SRVector GetCrossVector(SRVector left, SRVector right)
	{
		SRVector ret;
		ret.x = left.y * right.z - left.z * right.y;
		ret.y = left.z * right.x - left.x * right.z;
		ret.z = left.x * right.y - left.y * right.x;
		ret.w = 0;
		return ret;
	}
};



struct SRColor
{
	SRColor()
	{
		a = 0;
		r = 0;
		g = 0;
		b = 0;
	}
	float a;
	float r;
	float g;
	float b;

public:
	static SRColor Lerp(SRColor left, SRColor right, float weight)
	{
		SRColor ret;
		ret.a = left.a * (1 - weight) + right.a * weight;
		ret.r = left.r * (1 - weight) + right.r * weight;
		ret.g = left.g * (1 - weight) + right.g * weight;
		ret.b = left.b * (1 - weight) + right.b * weight;
		return ret;
	}
};

struct SRVertex
{
	SRPoint m_point;
	SRVector m_normal;
	SRColor m_color;
	float m_tx;
	float m_ty;

	static SRVertex Lerp(SRVertex left, SRVertex right, float weight)
	{
		SRVertex ret;

		ret.m_color = SRColor::Lerp(left.m_color, right.m_color, weight);
		
		return ret;
	}
};

typedef float Matrix4x4[4][4];

const float PI = 3.141592f;

const int m_width = 640;
const int m_height = 480;

#endif