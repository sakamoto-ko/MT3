#pragma once

#include "MT4MyMath.h"

struct Quaternion {
	float x;
	float y;
	float z;
	float w;
};

//文字出力
void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label);
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
Quaternion IdentityQuaternion();
Quaternion Conjugate(const Quaternion& quaternion);
float Norm(const Quaternion& quaternion);
Quaternion Normalize(const Quaternion& quaternion);
Quaternion Inverse(const Quaternion& quaternion);
Quaternion Scalar(float scalar, const Quaternion& q);
Quaternion Scalar(const Quaternion& q, float scalar);
Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle);
Vector3 RotateVector(const Vector3& v, const Quaternion& q);
Matrix4x4 MakeRotateMatrixQuaternion(const Quaternion& q);
Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);
Quaternion Add(const Quaternion& q1, const Quaternion& q2);
Quaternion Lerp(const Quaternion& q0, const Quaternion& q1, float t);
