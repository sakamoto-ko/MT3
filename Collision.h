#pragma once
#include "Vector.h"
#include "Matrix.h"
#include "Draw.h"

//当たり判定クラス
class Collision
{
private:
	Draw* draw = new Draw();
public:
	//正射影ベクトル
	Vector3 Project(const Vector3& v1, const Vector3& v2);

	//最近接点
	Vector3 ClosesetPoint(const Vector3& point, const Segment& segment);

	//球と球の衝突
	bool IsCollision(const Sphere& s1, const Sphere& s2);

	//球と平面の衝突
	bool IsCollision(const Sphere& sphere, const Plane plane);

	//線と平面の衝突
	bool IsCollision(const Plane plane, const Segment segment);

	//三角形と線の衝突
	bool IsCollision(const Triangle& triangle, const Segment& segment);

	//AABBとAABBの衝突
	bool IsCollision(const AABB& aabb1, const AABB& aabb2);

	//AABBと球の衝突
	bool IsCollision(const AABB& aabb, const Sphere& sphere);

	//AABBと線の衝突
	bool IsCollision(const AABB& aabb, const Segment& segment);
};

