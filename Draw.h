#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Collision.h"

class Draw
{
public:
	void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
	void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	Vector3 Perpendicular(const Vector3& vector);
	void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
	Vector3 Bazier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, float t);
	void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	Vector3 CatmullRom(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3, float t);
	void DrawCatmullRom(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Vector3& controlPoint3,
		const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color);
	void DrawArm(Vector3 translates[3], Vector3 rotates[3], Vector3 scales[3], const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
	void DrawSpring(Ball ball, Spring spring, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix);
};

