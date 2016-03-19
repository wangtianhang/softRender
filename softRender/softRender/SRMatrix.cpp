#include "SRMatrix.h"


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

void TranslatePoint(float tx, float ty, float tz, Matrix4x4 outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	outMatrix[0][3] == tx;
	outMatrix[1][3] == ty;
	outMatrix[2][3] == tz;

	//return &matTransl3D;
}

void PointRotateByZ(float radTheta, Matrix4x4 outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	outMatrix[0][0] == cosTheta;
	outMatrix[0][1] == -sinTheta;
	outMatrix[1][0] == sinTheta;
	outMatrix[1][1] == cosTheta;

	//return &matTransl3D;
}

void PointRotateByY(float radTheta, Matrix4x4 outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	outMatrix[0][0] == cosTheta;
	outMatrix[0][2] == sinTheta;
	outMatrix[2][0] == -sinTheta;
	outMatrix[2][2] == cosTheta;

	//return &matTransl3D;
}

void PointRotateByX(float radTheta, Matrix4x4 outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	outMatrix[1][1] == cosTheta;
	outMatrix[1][2] == -sinTheta;
	outMatrix[2][1] == sinTheta;
	outMatrix[2][2] == cosTheta;

	//return &matTransl3D;
}

void PointRotateByNormalVector(SRVector vector, float radTheta, Matrix4x4 outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	// todo:看3d游戏引擎设计p14页填充

	//return &matTransl3D;
}

void PointScaleByXYZ(float x, float y, float z, Matrix4x4 outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	outMatrix[0][0] = x;
	outMatrix[1][1] = y;
	outMatrix[2][2] = z;

	//return &matTransl3D;
}

void MatrixMultiMatrix(Matrix4x4 m1, Matrix4x4 m2, Matrix4x4 outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			outMatrix[row][col] =
				m1[row][0] * m2[0][col] +
				m1[row][1] * m2[1][col] +
				m1[row][2] * m2[2][col] +
				m1[row][3] * m2[3][col];
		}
	}

	//return &matTransl3D;
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
