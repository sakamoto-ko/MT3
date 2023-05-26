#pragma once
#include "Cross.h"

//直線(-∞~∞)
struct Line {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};

//半直線(0~∞)
struct Ray {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};

//線分(0~1)
struct Segment {
	Vector3 origin;//始点
	Vector3 diff;//終点への差分ベクトル
};

//当たり判定クラス
class Collision
{
public:
	//正射影ベクトル
	Vector3 Project(const Vector3& v1, const Vector3& v2);

	//最近接点
	Vector3 ClosesetPoint(const Vector3& point, const Segment& segment);
};

