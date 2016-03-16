#ifndef SRMATRIX_H
#define SRMATRIX_H

#include <math.h>

// 坐标系选择右手坐标系
// 法向量从模型空间转到世界空间，乘以转换矩阵的逆矩阵的转置矩阵
// 法向量从世界空间转到相机空间，不发生空间扭曲，直接乘以转换矩阵就好

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

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	// todo:看3d游戏引擎设计p14页填充

	return &matTransl3D;
}

Matrix4x4 * PointScaleByXYZ(float x, float y, float z)
{
	Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(matTransl3D);

	matTransl3D[0][0] = x;
	matTransl3D[1][1] = y;
	matTransl3D[2][2] = z;

	return &matTransl3D;
}

Matrix4x4 * MatrixMultiMatrix(Matrix4x4 m1, Matrix4x4 m2)
{
	Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(matTransl3D);

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			matTransl3D[row][col] = 
				m1[row][0] * m2[0][col] +
				m1[row][1] * m2[1][col] + 
				m1[row][2] * m2[2][col] + 
				m1[row][3] * m2[3][col];
		}
	}

	return &matTransl3D;
}

SRPoint MatrixMultiPoint(Matrix4x4 m1, SRPoint point)
{
	SRPoint ret;
	ret.x = m1[0][0] * point.x + m1[0][1] * point.y + m1[0][2] * point.z + m1[0][3] * point.w;
	ret.y = m1[1][0] * point.x + m1[1][1] * point.y + m1[1][2] * point.z + m1[1][3] * point.w;
	ret.z = m1[2][0] * point.x + m1[2][1] * point.y + m1[2][2] * point.z + m1[2][3] * point.w;
	ret.w = m1[3][0] * point.x + m1[3][1] * point.y + m1[3][2] * point.z + m1[3][3] * point.w;
	return point;
}

SRVector MatrixMultiVector(Matrix4x4 m1, SRVector vector)
{
	SRVector ret;
	ret.x = m1[0][0] * vector.x + m1[0][1] * vector.y + m1[0][2] * vector.z + m1[0][3] * vector.w;
	ret.y = m1[1][0] * vector.x + m1[1][1] * vector.y + m1[1][2] * vector.z + m1[1][3] * vector.w;
	ret.z = m1[2][0] * vector.x + m1[2][1] * vector.y + m1[2][2] * vector.z + m1[2][3] * vector.w;
	ret.w = m1[3][0] * vector.x + m1[3][1] * vector.y + m1[3][2] * vector.z + m1[3][3] * vector.w;
	return ret;
}

#endif