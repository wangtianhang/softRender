#ifndef SROBJ_H
#define SROBJ_H

#include <vector>

#include "SRCommonStruct.h"

class SRObj
{
public:
	void GetObjToWorldMatrix(Matrix4x4 outMatrix);

	SRPoint m_pos;
	std::vector<SRVertex> m_vertexVec; // ����������
};

#endif