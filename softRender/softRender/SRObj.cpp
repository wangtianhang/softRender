#include "SRObj.h"
#include "SRMatrix.h"

void SRObj::GetObjToWorldMatrix(Matrix4x4 outMatrix)
{
	TranslatePoint(m_pos.x, m_pos.y, m_pos.z, outMatrix);
}
