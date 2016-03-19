#include "SRCamera.h"

#include "SRMatrix.h"

SRCamera::SRCamera(SRPoint pos, SRVector u, SRVector v)
{
	m_pos = pos;
	m_u = u.GetNormaliseVector();
	m_v = v.GetNormaliseVector();
	m_n = SRVector::GetCrossVector(m_u, m_v);
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

}
