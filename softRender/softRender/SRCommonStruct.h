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

	SRPoint(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		w = 1;
	}

	float x;
	float y;
	float z;
	float w;

public:
	static SRPoint Lerp(SRPoint left, SRPoint right, float weight)
	{
		SRPoint ret;
		ret.x = left.x * (1 - weight) + right.x * weight;
		ret.y = left.y * (1 - weight) + right.y * weight;
		ret.z = left.z * (1 - weight) + right.z * weight;
		ret.w = left.w * (1 - weight) + right.w * weight;
		return ret;
	}
};

inline SRPoint operator / (SRPoint left, float num)
{
	SRPoint ret;
	ret.x = left.x / num;
	ret.y = left.y / num;
	ret.z = left.z / num;
	ret.w = left.w / num;
	return ret;
}

struct SRVector
{
	SRVector()
	{
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	SRVector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
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
	SRPoint m_pos;
	SRVector m_normal;
	SRColor m_color;
	float m_tx;
	float m_ty;

	static SRVertex Lerp(SRVertex left, SRVertex right, float weight)
	{
		SRVertex ret;

		ret.m_pos = SRPoint::Lerp(left.m_pos, right.m_pos, weight);
		ret.m_color = SRColor::Lerp(left.m_color, right.m_color, weight);
		
		return ret;
	}
};

struct  SRFragment
{
	SRColor m_color;
	float m_tx;
	float m_ty;
};

//typedef float Matrix4x4[4][4];
struct Matrix4x4
{
public:
	Matrix4x4()
	{
		m00 = m01 = m02 = m03 = 0;
		m10 = m11 = m12 = m13 = 0;
		m20 = m21 = m22 = m23 = 0;
		m30 = m31 = m32 = m33 = 0;
	}
	float m00, m01, m02, m03;
	float m10, m11, m12, m13;
	float m20, m21, m22, m23;
	float m30, m31, m32, m33;
};

const float PI = 3.141592f;



#endif