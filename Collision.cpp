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
	result = Add(segment.origin,Project(point, segment.diff));

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
bool Collision::IsCollision(const Plane plane, const Line line) {
	//法線と線の内積
	float dot = Dot(plane.normal, line.diff);

	//衝突していないため早期リターン
	if (dot == 0.0f) {
		return false;
	}

	//tを求める
	//float t = (plane.distance - Dot(line.origin, plane.normal)) / dot;

	//tの値と種類によって衝突しているかを判断する
	//直線
	return true;

	//線分
	//return true;

	//return false;
}