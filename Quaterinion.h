#pragma once

#include "Matrix.h"
#include "Vector.h"

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