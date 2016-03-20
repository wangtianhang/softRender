#ifndef SRMATRIX_H
#define SRMATRIX_H

#include <math.h>

// 坐标系选择右手坐标系
// 法向量从模型空间转到世界空间，乘以转换矩阵的逆矩阵的转置矩阵
// 法向量从世界空间转到相机空间，不发生空间扭曲，直接乘以转换矩阵就好

#include "SRCommonStruct.h"
//typedef float * PMatrix4x4;

void Matrix4x4SetIdentity(Matrix4x4 & matIdent4x4);

//void Matrix4x4SetZero(Matrix4x4 matIdent4x4);

void TranslatePoint(float tx, float ty, float tz, Matrix4x4 & outMatrix);

void PointRotateByZ(float radTheta, Matrix4x4 & outMatrix);

void PointRotateByY(float radTheta, Matrix4x4 & outMatrix);

void PointRotateByX(float radTheta, Matrix4x4 & outMatrix);

void PointRotateByNormalVector(SRVector vector, float radTheta, Matrix4x4 & outMatrix);

void PointScaleByXYZ(float x, float y, float z, Matrix4x4 & outMatrix);

void MatrixMultiMatrix(Matrix4x4 m1, Matrix4x4 m2, Matrix4x4 & outMatrix);

SRPoint MatrixMultiPoint(Matrix4x4 m1, SRPoint point);

SRVector MatrixMultiVector(Matrix4x4 m1, SRVector vector);

#endif