﻿#include "Vector.h"

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2) {
	Vector3 result = { 0 };
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2) {
	Vector3 result = { 0 };
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

//スカラー倍
Vector3 Multiply(float scalar, const Vector3& v) {
	Vector3 result = { 0 };
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

//内積
float Dot(const Vector3& v1, const Vector3& v2) {
	float result = { 0 };
	result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return result;
}

//長さ
float Length(const Vector3& v) {
	float result = { 0 };
	result = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	return result;
}

//正規化
Vector3 Normalize(const Vector3& v) {
	Vector3 result = { 0 };
	float a = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
	if (a != 0) {
		result.x = v.x / a;
		result.y = v.y / a;
		result.z = v.z / a;
	}
	return result;
}

//文字出力
void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}