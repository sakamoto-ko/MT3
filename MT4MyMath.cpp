#include "MT4MyMath.h"

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle)
{
	Matrix4x4 matrix = {};

	matrix.m[0][0] = { axis.x * axis.x * (1 - cosf(angle)) + cosf(angle) };
	matrix.m[0][1] = { axis.x * axis.y * (1 - cosf(angle)) + axis.z * sinf(angle) };
	matrix.m[0][2] = { axis.x * axis.z * (1 - cosf(angle)) - axis.y * sinf(angle) };
	matrix.m[0][3] = { 0.0f };

	matrix.m[1][0] = { axis.x * axis.y * (1 - cosf(angle)) - axis.z * sinf(angle) };
	matrix.m[1][1] = { axis.y * axis.y * (1 - cosf(angle)) + cosf(angle) };
	matrix.m[1][2] = { axis.y * axis.z * (1 - cosf(angle)) + axis.x * sinf(angle) };
	matrix.m[1][3] = { 0.0f };

	matrix.m[2][0] = { axis.x * axis.z * (1 - cosf(angle)) + axis.y * sinf(angle) };
	matrix.m[2][1] = { axis.y * axis.z * (1 - cosf(angle)) - axis.x * sinf(angle) };
	matrix.m[2][2] = { axis.z * axis.z * (1 - cosf(angle)) + cosf(angle) };
	matrix.m[2][3] = { 0.0f };

	matrix.m[3][0] = { 0.0f };
	matrix.m[3][1] = { 0.0f };
	matrix.m[3][2] = { 0.0f };
	matrix.m[3][3] = { 1.0f };

	return matrix;
}
