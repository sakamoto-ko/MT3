#pragma once

#include "Vector.h"
#include "Matrix.h"

	//二項演算子
	Vector3 operator+ (const Vector3& v1, const Vector3& v2) { return Add(v1, v2); }
	Vector3 operator- (const Vector3& v1, const Vector3& v2) { return Subtract(v1, v2); }
	Vector3 operator* (float s, const Vector3& v) { return Scalar(s, v); }
	Vector3 operator* (const Vector3& v, float s) { return s * v; }
	Vector3 operator/ (const Vector3& v, float s) { return Scalar(1.0f / s, v); }

	Matrix4x4 operator+ (const Matrix4x4& m1, const Matrix4x4& m2) { return Add(m1, m2); }
	Matrix4x4 operator- (const Matrix4x4& m1, const Matrix4x4& m2) { return Subtract(m1, m2); }
	Matrix4x4 operator* (const Matrix4x4& m1, const Matrix4x4& m2) { return Multiply(m1, m2); }

	//単項演算子
	Vector3 operator- (const Vector3& v) { return Vector3(-v.x, -v.y, -v.z); }
	Vector3 operator+ (const Vector3& v) { return v; }

class Overroad {
private:
	float x;
	float y;
	float z;
public:
	//複合代入演算子
	/*const Vector3& operator*=(float s) { x *= s; y *= s; z *= s; return Vector3{ x,y,z }; }
	const Vector3& operator-=(const Vector3& v) { x -= v.x; y -= v.y; z -= v.z; return Vector3{ x,y,z }; }
	const Vector3& operator+=(const Vector3& v) { x += v.x; y += v.y; z += v.z; return Vector3{ x,y,z }; }
	const Vector3& operator/=(float s) { x /= s; y /= s; z /= s; return Vector3{ x,y,z }; }*/
};