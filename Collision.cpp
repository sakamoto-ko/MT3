#include "Collision.h"

//正射影ベクトル
Vector3 Collision::Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};

	//c = (a ・ 単位ベクトルb) × 単位ベクトルb
	result = Scalar(Dot(v1, Normalize(v2)), Normalize(v2));

	return result;
}

//最近接点
Vector3 Collision::ClosesetPoint(const Vector3& point, const Segment& segment) {
	Vector3 result = {};

	//cp = o(始点) + 正射影ベクトルb
	result = Add(segment.origin, Project(point, segment.diff));

	return result;
}

//球と球の衝突
bool Collision::IsCollision(const Sphere& s1, const Sphere& s2) {
	//2つの球の中心間の距離を求める	
	float distance = Length(Subtract(s2.center, s1.center));

	//半径の合計よりも短ければ衝突
	if (distance <= s1.radius + s2.radius) {
		//衝突処理
		return true;
	}

	return false;
}

//球と平面の衝突
bool Collision::IsCollision(const Sphere& sphere, const Plane plane) {
	//平面と球の中心点との距離を求める
	float k = Dot(sphere.center, plane.normal) - plane.distance;
	k = sqrt(k * k);

	//半径よりも短ければ衝突
	if (k <= sphere.radius) {
		//衝突処理
		return true;
	}

	return false;
}

//線と平面の衝突
bool Collision::IsCollision(const Plane plane, const Segment segment) {
	//法線と線の内積
	float dot = Dot(segment.diff, plane.normal);

	//垂直=平行なので、衝突していないため早期リターン
	if (dot == 0.0f) {
		return false;
	}

	//tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	//tの値と種類によって衝突しているかを判断する
	if (t <= 1.0f && t >= 0.0f) {
		//衝突処理
		return true;
	}

	return false;
}

//三角形と線の衝突
bool Collision::IsCollision(const Triangle& triangle, const Segment& segment) {
	Plane plane{};
	Vector3 point{};
	Vector3 normal[3]{};
	float NormalDot[3]{};
	Triangle newTriangle[3]{};

	Vector3 a = triangle.vertices[0];
	Vector3 b = triangle.vertices[1];
	Vector3 c = triangle.vertices[2];
	Vector3 v1 = Subtract(b, a);
	Vector3 v2 = Subtract(c, b);
	plane.normal = Cross(v1, v2);
	plane.normal = Normalize(plane.normal);
	plane.distance = Dot(a, plane.normal);

	//法線と線の内積
	float dot = Dot(segment.diff, plane.normal);
	//媒介変数tを求める
	float t = (plane.distance - Dot(segment.origin, plane.normal)) / dot;

	//三角形の内外の判定
	if (t <= 1.0f && t >= 0.0f) {
		//衝突点を求める
		point = Add(segment.origin, (t * plane.distance));
		//衝突点と新しい三角形を作る
		newTriangle[0] = {
			newTriangle[0].vertices[0] = {triangle.vertices[0].x,triangle.vertices[0].y,triangle.vertices[0].z},
			newTriangle[0].vertices[1] = {triangle.vertices[1].x,triangle.vertices[1].y,triangle.vertices[1].z},
			newTriangle[0].vertices[2] = {point.x,point.y,point.z}
		};
		newTriangle[1] = {
			newTriangle[1].vertices[0] = {triangle.vertices[1].x,triangle.vertices[1].y,triangle.vertices[1].z},
			newTriangle[1].vertices[1] = {triangle.vertices[2].x,triangle.vertices[2].y,triangle.vertices[2].z},
			newTriangle[1].vertices[2] = {point.x,point.y,point.z}
		};
		newTriangle[2] = {
			newTriangle[2].vertices[0] = {triangle.vertices[2].x,triangle.vertices[2].y,triangle.vertices[2].z},
			newTriangle[2].vertices[1] = {triangle.vertices[0].x,triangle.vertices[0].y,triangle.vertices[0].z},
			newTriangle[2].vertices[2] = {point.x,point.y,point.z}
		};
		//法線
		normal[0] = Cross(Subtract(newTriangle[1].vertices[0], newTriangle[0].vertices[0]), Subtract(newTriangle[2].vertices[0], newTriangle[1].vertices[0]));
		normal[1] = Cross(Subtract(newTriangle[1].vertices[1], newTriangle[0].vertices[1]), Subtract(newTriangle[2].vertices[1], newTriangle[1].vertices[1]));
		normal[2] = Cross(Subtract(newTriangle[1].vertices[2], newTriangle[0].vertices[2]), Subtract(newTriangle[2].vertices[2], newTriangle[1].vertices[2]));
		for (uint32_t i = 0; i < 3; ++i) {
			normal[i] = Normalize(normal[i]);
			//内積
			NormalDot[i] = Dot(normal[i], point);
		}
		//全部プラス
		if (dot >= 0) {
			if (NormalDot[0] >= 0 &&
				NormalDot[1] >= 0 &&
				NormalDot[2] >= 0) {
				return true;
			}
		}
		//全部マイナス
		else if (dot <= 0) {
			if (NormalDot[0] <= 0 &&
				NormalDot[1] <= 0 &&
				NormalDot[2] <= 0) {
				return true;
			}
		}
	}
	return false;
}

//AABBとAABBの衝突
bool Collision::IsCollision(const AABB& aabb1, const AABB& aabb2) {
	if ((aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x) &&
		(aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y) &&
		(aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z)) {
		return true;
	}
	return false;
}

//AABBと球の衝突
bool Collision::IsCollision(const AABB& aabb, const Sphere& sphere) {
	//最近接点を求める
	Vector3 closetPoint{
		std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
		std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
		std::clamp(sphere.center.z,aabb.min.z,aabb.max.z),
	};
	//最近接点と球の中心との距離を求める
	float distance = Length(Subtract(closetPoint, sphere.center));
	//距離が半径よりも小さければ衝突
	if (distance <= sphere.radius) {
		return true;
	}
	return false;
}

//AABBと線の衝突
bool Collision::IsCollision(const AABB& aabb, const Segment& segment) {
	//平面
	//X
	Plane XPlaneMin{
		.normal = { 1, 0, 0 },
		.distance = aabb.min.x,
	};
	Plane XPlaneMax{
		.normal = { 1, 0, 0 },
		.distance = aabb.max.x,
	};
	//Y
	Plane YPlaneMin{
		.normal = { 0, 1, 0 },
		.distance = aabb.min.y,
	};
	Plane YPlaneMax{
		.normal = { 0, 1, 0 },
		.distance = aabb.max.y,
	};
	//Z
	Plane ZPlaneMin{
		.normal = { 0, 0, 1 },
		.distance = aabb.min.z,
	};
	Plane ZPlaneMax{
		.normal = { 0, 0, 1 },
		.distance = aabb.max.z,
	};

	//媒介変数t
	float tXmin = (XPlaneMin.distance - segment.origin.x) / segment.diff.x;
	float tXmax = (XPlaneMax.distance - segment.origin.x) / segment.diff.x;
	float tYmin = (YPlaneMin.distance - segment.origin.y) / segment.diff.y;
	float tYmax = (YPlaneMax.distance - segment.origin.y) / segment.diff.y;
	float tZmin = (ZPlaneMin.distance - segment.origin.z) / segment.diff.z;
	float tZmax = (ZPlaneMax.distance - segment.origin.z) / segment.diff.z;

	//近い点
	Vector3 tNear{
		.x = min(tXmin, tXmax),
		.y = min(tYmin, tYmax),
		.z = min(tZmin, tZmax),
	};
	//遠い点
	Vector3 tFar{
		.x = max(tXmin,tXmax),
		.y = max(tYmin,tYmax),
		.z = max(tZmin,tZmax),
	};

	//衝突点(貫通点)
	//小さい方
	float tMin = max(max(tNear.x, tNear.y), tNear.z);
	//大きい方
	float tMax = min(min(tFar.x, tFar.y), tFar.z);

	//特殊ケース
	/*if (1) {
		return false;
	}*/

	if (tMin <= tMax) {
		return true;
	}
	return false;
}
