#ifndef SROBJ_H
#define SROBJ_H

#include <vector>

#include "SRCommonStruct.h"

class SRObj
{
public:
	void GetObjToWorldMatrix(Matrix4x4 outMatrix);
	void InitToCube();

	SRPoint m_pos;
	std::vector<SRVertex> m_vertexVec; // 三角形条带
};

#endif