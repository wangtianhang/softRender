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

SRCamera::SRCamera(SRPoint pos, SRVector u, SRVector v)
{
	m_pos = pos;
	m_u = u.GetNormaliseVector();
	m_v = v.GetNormaliseVector();
	m_n = SRVector::GetCrossVector(m_u, m_v);

	m_near = 0.1f;
	m_far = 100;
	m_fovRadTheta = ConvertDegToRad(60);
	//m_fovRadTheta = m_fovRadTheta / ;
	m_aspect = (float)m_height / m_width;
}

void SRCamera::GetWorldToViewMatrix(Matrix4x4 outMatrix)
{
	Matrix4x4 t;
	Matrix4x4SetIdentity(t);
	t[0][3] = -m_pos.x;
	t[1][3] = -m_pos.y;
	t[2][3] = -m_pos.z;

	Matrix4x4 r;
	Matrix4x4SetIdentity(r);
	r[0][1] = m_u.x; r[0][1] = m_u.y; r[0][2] = m_u.z;
	r[1][1] = m_v.x; r[1][1] = m_v.y; r[1][2] = m_v.z;
	r[2][1] = m_n.x; r[2][1] = m_n.y; r[2][2] = m_n.z;

	MatrixMultiMatrix(r, t, outMatrix);
}

void SRCamera::GetPerspectiveMatrix(Matrix4x4 outMatrix)
{
	// 对称棱台特化矩阵
	Matrix4x4SetZero(outMatrix);

	float halfTheta = m_fovRadTheta / 2;
	float cotHalfTheta = 1 / tan(halfTheta);

	outMatrix[0][0] = cotHalfTheta / m_aspect;
	outMatrix[1][1] = cotHalfTheta;
	outMatrix[2][2] = (m_near + m_far) / (m_near - m_far);
	outMatrix[2][3] = -(2 * m_near * m_far / (m_near - m_far));
	outMatrix[3][2] = -1;
}
