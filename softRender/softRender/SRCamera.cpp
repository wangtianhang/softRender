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
	m_u = u.GetNormaliseVector();
	m_v = v.GetNormaliseVector();
	m_n = SRVector::GetCrossVector(m_u, m_v);

	m_near = 0.1f;
	m_far = 100;
	m_fovRadTheta = ConvertDegToRad(60);
	//m_fovRadTheta = m_fovRadTheta / ;
	m_aspect = (float)width / height;
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
