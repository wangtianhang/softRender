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
		-1.0f, -1.0f, -1.0f, // triangle 1 : begin
		 - 1.0f, -1.0f, 1.0f,
		 - 1.0f, 1.0f, 1.0f, // triangle 1 : end
		     1.0f, 1.0f, -1.0f, // triangle 2 : begin
		 - 1.0f, -1.0f, -1.0f,
		 - 1.0f, 1.0f, -1.0f, // triangle 2 : end
		     1.0f, -1.0f, 1.0f,
		 - 1.0f, -1.0f, -1.0f,
		     1.0f, -1.0f, -1.0f,
		     1.0f, 1.0f, -1.0f,
		     1.0f, -1.0f, -1.0f,
		 - 1.0f, -1.0f, -1.0f,
		 - 1.0f, -1.0f, -1.0f,
		 - 1.0f, 1.0f, 1.0f,
		 - 1.0f, 1.0f, -1.0f,
		     1.0f, -1.0f, 1.0f,
		 - 1.0f, -1.0f, 1.0f,
		 - 1.0f, -1.0f, -1.0f,
		 - 1.0f, 1.0f, 1.0f,
		 - 1.0f, -1.0f, 1.0f,
		     1.0f, -1.0f, 1.0f,
		     1.0f, 1.0f, 1.0f,
		     1.0f, -1.0f, -1.0f,
		     1.0f, 1.0f, -1.0f,
		     1.0f, -1.0f, -1.0f,
		     1.0f, 1.0f, 1.0f,
		     1.0f, -1.0f, 1.0f,
		     1.0f, 1.0f, 1.0f,
		     1.0f, 1.0f, -1.0f,
		 - 1.0f, 1.0f, -1.0f,
		     1.0f, 1.0f, 1.0f,
		 - 1.0f, 1.0f, -1.0f,
		 - 1.0f, 1.0f, 1.0f,
		     1.0f, 1.0f, 1.0f,
		 - 1.0f, 1.0f, 1.0f,
		     1.0f, -1.0f, 1.0f
	};

	m_vertexVec.clear();
	for (int i = 0; i < 36; ++i)
	{
		SRVertex vertex;
		vertex.m_pos.x = cubeVertexPos[i * 3];
		vertex.m_pos.y = cubeVertexPos[i * 3 + 1];
		vertex.m_pos.z = cubeVertexPos[i * 3 + 2];
		m_vertexVec.push_back(vertex);
	}
}
