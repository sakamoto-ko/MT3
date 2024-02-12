#include "Vector.h"

//文字出力
void Vector3ScreenPrintf(int x, int y, const Vector3& v, const char* label) {
	Novice::ScreenPrintf(x, y + 20, "%2.02f", v.x);
	Novice::ScreenPrintf(x + 80, y + 20, "%2.02f", v.y);
	Novice::ScreenPrintf(x + 160, y + 20, "%2.02f", v.z);
	Novice::ScreenPrintf(x, y, "%s", label);
}

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
Vector3 Scalar(float scalar, const Vector3& v) {
	Vector3 result = { 0 };
	result.x = scalar * v.x;
	result.y = scalar * v.y;
	result.z = scalar * v.z;
	return result;
}

Vector3 Scalar(const Vector3& v, float scalar)
{
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

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};

	result = {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};

	return result;
}

//ベクトルとフロートの加算
Vector3 Add(const Vector3& v, const float& a) {
	Vector3 result;

	result = {
		v.x + a,
		v.y + a,
		v.z + a
	};

	return result;
}

//ベクトルとフロートの減算
Vector3 Subtract(const Vector3& v, const float& a) {
	Vector3 result;

	result = {
		v.x - a,
		v.y - a,
		v.z - a
	};

	return result;
}

//フロートとベクトルの減算
Vector3 Subtract(const float& a, const Vector3& v) {
	Vector3 result;

	result = {
		a - v.x,
		a - v.y,
		a - v.z
	};

	return result;
}

//ベクトルとベクトルの積
//Vector3 Multiply(const Vector3& v1, Vector3& v2) {
//	Vector3 result;
//
//	result = {
//		v1.x * v2.x,
//		v1.y * v2.y,
//		v1.z * v2.z,
//	};
//
//	return result;
//}

Vector3 Harf(const Vector3& v, const float& a) {
	return Vector3{ v.x / a, v.y / a, v.z / a };
}

//反射関数
Vector3 Reflect(const Vector3& input, const Vector3& normal) {
	Vector3 r = {};

	r.x = input.x - 2 * Dot(input, normal) * normal.x;
	r.y = input.y - 2 * Dot(input, normal) * normal.y;
	r.z = input.z - 2 * Dot(input, normal) * normal.z;

	return r;
}