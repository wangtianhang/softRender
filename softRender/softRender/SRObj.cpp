#include "SRObj.h"
#include "SRMatrix.h"

void SRObj::GetObjToWorldMatrix(Matrix4x4 outMatrix)
{
	TranslatePoint(m_pos.x, m_pos.y, m_pos.z, outMatrix);
}

void SRObj::InitToCube()
{
	float cubeVertexPos[] = 
	{
		1.0f, -1.0f, -1.0f, // triangle 1 : begin
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f, -1.0f, // triangle 2 : begin
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f, // triangle 2 : end
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, -1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 1.0f
	};

	m_vertexVec.clear();
	for (int i = 0; i < 36; ++i)
	{
		SRVertex vertex;
		vertex.m_point.x = cubeVertexPos[i];
		vertex.m_point.y = cubeVertexPos[i + 1];
		vertex.m_point.z = cubeVertexPos[i + 2];
		m_vertexVec.push_back(vertex);
	}
}
