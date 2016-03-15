#ifndef SRMATRIX_H
#define SRMATRIX_H

#include <math.h>

// ����ϵѡ����������ϵ
// ��������ģ�Ϳռ�ת������ռ䣬����ת�������������ת�þ���
// ������������ռ�ת������ռ䣬�������ռ�Ť����ֱ�ӳ���ת������ͺ�

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
};

typedef float Matrix4x4[4][4];
//typedef float * PMatrix4x4;

void Matrix4x4SetIdentity(Matrix4x4 matIdent4x4)
{
	int row, col;
	for (row = 0; row < 4; row++)
	{
		for (col = 0; col < 4; col++)
		{
			matIdent4x4[row][col] = (row == col);
		}
	}
}

Matrix4x4 * TranslatePoint(float tx, float ty, float tz)
{
	Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(matTransl3D);

	matTransl3D[0][3] == tx;
	matTransl3D[1][3] == ty;
	matTransl3D[2][3] == tz;
	
	return &matTransl3D;
}

Matrix4x4 * PointRotateByZ(float radTheta)
{
	Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(matTransl3D);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	matTransl3D[0][0] == cosTheta;
	matTransl3D[0][1] == -sinTheta;
	matTransl3D[1][0] == sinTheta;
	matTransl3D[1][1] == cosTheta;

	return &matTransl3D;
}

Matrix4x4  * PointRotateByY(float radTheta)
{
	Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(matTransl3D);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	matTransl3D[0][0] == cosTheta;
	matTransl3D[0][2] == sinTheta;
	matTransl3D[2][0] == -sinTheta;
	matTransl3D[2][2] == cosTheta;

	return &matTransl3D;
}

Matrix4x4 * PointRotateByX(float radTheta)
{
	Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(matTransl3D);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	matTransl3D[1][1] == cosTheta;
	matTransl3D[1][2] == -sinTheta;
	matTransl3D[2][1] == sinTheta;
	matTransl3D[2][2] == cosTheta;

	return &matTransl3D;
}

Matrix4x4 * PointRotateByNormalVector(SRVector vector, float radTheta)
{
	Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(matTransl3D);

	// todo:��3d��Ϸ�������p14ҳ���

	return &matTransl3D;
}

#endif