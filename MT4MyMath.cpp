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

Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to)
{
	Vector3 normal = Cross(from, to);
	float cosT = Dot(from, to);
	float sinT = Length(normal);

	float espilon = 1e-6f;

	Vector3 axis;
	if (std::abs(cosT + 1.0f) <= espilon) {
		if (std::abs(from.x) > espilon || std::abs(from.y) > espilon) {
			axis.x = from.y;
			axis.y = -from.x;
			axis.z = 0.0f;
		}
		else if (std::abs(from.x) > espilon || std::abs(from.z) > espilon) {
			axis.x = from.z;
			axis.y = 0.0f;
			axis.z = -from.x;
		}
		else {
			assert(false);
		}
		axis = Normalize(axis);
	}
	else {
		axis = Normalize(normal);
	}

	Matrix4x4 matrix = {};

	matrix.m[0][0] = { axis.x * axis.x * (1 - cosT) + cosT };
	matrix.m[0][1] = { axis.x * axis.y * (1 - cosT) + axis.z * sinT };
	matrix.m[0][2] = { axis.x * axis.z * (1 - cosT) - axis.y * sinT };
	matrix.m[0][3] = { 0.0f };

	matrix.m[1][0] = { axis.x * axis.y * (1 - cosT) - axis.z * sinT };
	matrix.m[1][1] = { axis.y * axis.y * (1 - cosT) + cosT };
	matrix.m[1][2] = { axis.y * axis.z * (1 - cosT) + axis.x * sinT };
	matrix.m[1][3] = { 0.0f };

	matrix.m[2][0] = { axis.x * axis.z * (1 - cosT) + axis.y * sinT };
	matrix.m[2][1] = { axis.y * axis.z * (1 - cosT) - axis.x * sinT };
	matrix.m[2][2] = { axis.z * axis.z * (1 - cosT) + cosT };
	matrix.m[2][3] = { 0.0f };

	matrix.m[3][0] = { 0.0f };
	matrix.m[3][1] = { 0.0f };
	matrix.m[3][2] = { 0.0f };
	matrix.m[3][3] = { 1.0f };

	return matrix;
}
