#include "Collision.h"

//正射影ベクトル
Vector3 Collision::Project(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {};

	//c = (a ・ 単位ベクトルb) × 単位ベクトルb
	result = Multiply(Dot(v1, Normalize(v2)), Normalize(v2));

	return result;
}

//最近接点
Vector3 Collision::ClosesetPoint(const Vector3& point, const Segment& segment) {
	Vector3 result = {};

	//cp = o(始点) + 正射影ベクトルb
	result = Add(segment.origin,Project(point, segment.diff));

	return result;
}