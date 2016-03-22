#ifndef SRCAMERA_H
#define SRCAMERA_H

#include "SRCommonStruct.h"

class SRCamera
{
public:
	SRCamera(SRPoint pos, SRVector u, SRVector v, int width, int height);
	SRCamera(SRPoint pos, float eulerX, float eulerY, float eulerZ, int width, int height);

	void GetWorldToViewMatrix(Matrix4x4 & outMatrix);
	void GetPerspectiveMatrix(Matrix4x4 & outMatrix);

	SRPoint m_pos;
	SRVector m_u; // 相机右方向
	SRVector m_v; // 相机上方向 
	SRVector m_n; // 相机正方向 n = u X v

	float m_near;
	float m_far;
	float m_fovRadTheta;
	float m_aspect;
};

#endif