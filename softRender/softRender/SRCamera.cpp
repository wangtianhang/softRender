#include <math.h>

#include "SRCamera.h"

#include "SRMatrix.h"

float ConvertRadToDeg(float rad)
{
	return rad / PI * 180;
}

float ConvertDegToRad(float deg)
{
	return deg / 180 * PI;
}

SRCamera::SRCamera(SRPoint pos, SRVector u, SRVector v, int width, int height)
{
	m_pos = pos;
	m_near = 0.1f;
	m_far = 100;
	m_fovRadTheta = ConvertDegToRad(60);
	//m_fovRadTheta = m_fovRadTheta / ;
	m_aspect = (float)width / height;

	m_u = u.GetNormaliseVector();
	m_v = v.GetNormaliseVector();
	m_n = SRVector::GetCrossVector(m_u, m_v);


}

SRCamera::SRCamera(SRPoint pos, float eulerX, float eulerY, float eulerZ, int width, int height)
{
	m_pos = pos;
	m_near = 0.1f;
	m_far = 100;
	m_fovRadTheta = ConvertDegToRad(60);
	m_aspect = (float)width / height;
	// 一个物体分别绕自己的xyz坐标轴旋转αβγ角度相当于物体绕世界坐标轴的zyx分别旋转γβα角度
	SRVector right = SRVector(1, 0, 0);
	SRVector up = SRVector(0, 1, 0);
	SRVector normal = SRVector(0, 0, 1);

	float radX = ConvertDegToRad(eulerX);
	float radY = ConvertDegToRad(eulerY);
	float radZ = ConvertDegToRad(eulerZ);

	Matrix4x4 rotateByX;
	PointRotateByX(radX, rotateByX);
	Matrix4x4 rotateByY;
	PointRotateByY(radY, rotateByY);
	Matrix4x4 rotateByZ;
	PointRotateByZ(radZ, rotateByZ);

	Matrix4x4 tmpYX;
	MatrixMultiMatrix(rotateByY, rotateByX, tmpYX);
	Matrix4x4 finalZYX;
	MatrixMultiMatrix(rotateByZ, tmpYX, finalZYX);

	m_u = MatrixMultiVector(finalZYX, right);
	m_u = m_u.GetNormaliseVector();
	m_v = MatrixMultiVector(finalZYX, up);
	m_v = m_v.GetNormaliseVector();
	m_n = MatrixMultiVector(finalZYX, normal);
	m_n = m_n.GetNormaliseVector();
}

void SRCamera::GetWorldToViewMatrix(Matrix4x4 & outMatrix)
{
	Matrix4x4 t;
	Matrix4x4SetIdentity(t);
	t.m03 = -m_pos.x;
	t.m13 = -m_pos.y;
	t.m23 = -m_pos.z;

	Matrix4x4 r;
	Matrix4x4SetIdentity(r);
	r.m00 = m_u.x; r.m01 = m_u.y; r.m02 = m_u.z;
	r.m10 = m_v.x; r.m11 = m_v.y; r.m12 = m_v.z;
	r.m20 = m_n.x; r.m21 = m_n.y; r.m22 = m_n.z;

	MatrixMultiMatrix(r, t, outMatrix);
}

void SRCamera::GetPerspectiveMatrix(Matrix4x4 & outMatrix)
{
	// 对称棱台特化矩阵
	//Matrix4x4SetZero(outMatrix);

	float halfTheta = m_fovRadTheta / 2;
	float cotHalfTheta = 1 / tan(halfTheta);

	outMatrix.m00 = cotHalfTheta / m_aspect;
	outMatrix.m11 = cotHalfTheta;
	outMatrix.m22 = (m_near + m_far) / (m_near - m_far);
	outMatrix.m23 = -(2 * m_near * m_far / (m_near - m_far));
	outMatrix.m32 = -1;
}
