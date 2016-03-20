#include "SRMatrix.h"


void Matrix4x4SetIdentity(Matrix4x4 & matIdent4x4)
{
// 	int row, col;
// 	for (row = 0; row < 4; row++)
// 	{
// 		for (col = 0; col < 4; col++)
// 		{
// 			matIdent4x4[row][col] = (row == col);
// 		}
// 	}
	matIdent4x4.m00 = 1;
	matIdent4x4.m11 = 1;
	matIdent4x4.m22 = 1;
	matIdent4x4.m33 = 1;
}

// void Matrix4x4SetZero(Matrix4x4 matIdent4x4)
// {
// 	int row, col;
// 	for (row = 0; row < 4; row++)
// 	{
// 		for (col = 0; col < 4; col++)
// 		{
// 			matIdent4x4[row][col] = 0;
// 		}
// 	}
// }

void TranslatePoint(float tx, float ty, float tz, Matrix4x4 & outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	outMatrix.m03 = tx;
	outMatrix.m13 = ty;
	outMatrix.m23 = tz;

	//return &matTransl3D;
}

void PointRotateByZ(float radTheta, Matrix4x4 & outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	outMatrix.m00 = cosTheta;
	outMatrix.m01 = -sinTheta;
	outMatrix.m10 = sinTheta;
	outMatrix.m11 = cosTheta;

	//return &matTransl3D;
}

void PointRotateByY(float radTheta, Matrix4x4 & outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	outMatrix.m00 = cosTheta;
	outMatrix.m02 = sinTheta;
	outMatrix.m20 = -sinTheta;
	outMatrix.m22 = cosTheta;

	//return &matTransl3D;
}

void PointRotateByX(float radTheta, Matrix4x4 & outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	outMatrix.m11 = cosTheta;
	outMatrix.m12 = -sinTheta;
	outMatrix.m21 = sinTheta;
	outMatrix.m22 = cosTheta;

	//return &matTransl3D;
}

void PointRotateByNormalVector(SRVector vector, float radTheta, Matrix4x4 & outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	float sinTheta = sin(radTheta);
	float cosTheta = cos(radTheta);

	// todo:看3d游戏引擎设计p14页填充

	//return &matTransl3D;
}

void PointScaleByXYZ(float x, float y, float z, Matrix4x4 & outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

	outMatrix.m00 = x;
	outMatrix.m11 = y;
	outMatrix.m22 = z;

	//return &matTransl3D;
}

void MatrixMultiMatrix(Matrix4x4 m1, Matrix4x4 m2, Matrix4x4 & outMatrix)
{
	//Matrix4x4 matTransl3D;
	Matrix4x4SetIdentity(outMatrix);

// 	for (int row = 0; row < 4; row++)
// 	{
// 		for (int col = 0; col < 4; col++)
// 		{
// 			outMatrix[row][col] =
// 				m1[row][0] * m2[0][col] +
// 				m1[row][1] * m2[1][col] +
// 				m1[row][2] * m2[2][col] +
// 				m1[row][3] * m2[3][col];
// 		}
// 	}
	outMatrix.m00 = m1.m00 * m2.m00 + m1.m01 * m2.m10 + m1.m02 * m2.m20 + m1.m03 * m2.m30;
	outMatrix.m01 = m1.m00 * m2.m01 + m1.m01 * m2.m11 + m1.m02 * m2.m21 + m1.m03 * m2.m31;
	outMatrix.m02 = m1.m00 * m2.m02 + m1.m01 * m2.m12 + m1.m02 * m2.m22 + m1.m03 * m2.m32;
	outMatrix.m03 = m1.m00 * m2.m03 + m1.m01 * m2.m13 + m1.m02 * m2.m23 + m1.m03 * m2.m33;

	outMatrix.m10 = m1.m10 * m2.m00 + m1.m11 * m2.m10 + m1.m12 * m2.m20 + m1.m13 * m2.m30;
	outMatrix.m11 = m1.m10 * m2.m01 + m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31;
	outMatrix.m12 = m1.m10 * m2.m02 + m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32;
	outMatrix.m13 = m1.m10 * m2.m03 + m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33;

	outMatrix.m20 = m1.m20 * m2.m00 + m1.m21 * m2.m10 + m1.m22 * m2.m20 + m1.m23 * m2.m30;
	outMatrix.m21 = m1.m20 * m2.m01 + m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31;
	outMatrix.m22 = m1.m20 * m2.m02 + m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32;
	outMatrix.m23 = m1.m20 * m2.m03 + m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33;

	outMatrix.m30 = m1.m30 * m2.m00 + m1.m31 * m2.m10 + m1.m32 * m2.m20 + m1.m33 * m2.m30;
	outMatrix.m31 = m1.m30 * m2.m01 + m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31;
	outMatrix.m32 = m1.m30 * m2.m02 + m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32;
	outMatrix.m33 = m1.m30 * m2.m03 + m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33;

	//return &matTransl3D;
}

SRPoint MatrixMultiPoint(Matrix4x4 m1, SRPoint point)
{
	SRPoint ret;
	ret.x = m1.m00 * point.x + m1.m01 * point.y + m1.m02 * point.z + m1.m03 * point.w;
	ret.y = m1.m10 * point.x + m1.m11 * point.y + m1.m12 * point.z + m1.m13 * point.w;
	ret.z = m1.m20 * point.x + m1.m21 * point.y + m1.m22 * point.z + m1.m23 * point.w;
	ret.w = m1.m30 * point.x + m1.m31 * point.y + m1.m32 * point.z + m1.m33 * point.w;
	return point;
}

SRVector MatrixMultiVector(Matrix4x4 m1, SRVector vector)
{
	SRVector ret;
	ret.x = m1.m00 * vector.x + m1.m01 * vector.y + m1.m02 * vector.z + m1.m03 * vector.w;
	ret.y = m1.m10 * vector.x + m1.m11 * vector.y + m1.m12 * vector.z + m1.m13 * vector.w;
	ret.z = m1.m20 * vector.x + m1.m21 * vector.y + m1.m22 * vector.z + m1.m23 * vector.w;
	ret.w = m1.m30 * vector.x + m1.m31 * vector.y + m1.m32 * vector.z + m1.m33 * vector.w;
	return ret;
}
