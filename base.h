#pragma once
#include <Novice.h>
#define _USE_MATH_DEFIENS
#include <math.h>
#include <cmath>
#include <assert.h>
#include <iostream>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"

#define kWindowWidth 1280
#define kWindowHeight 720
#define pi 3.14f

const char kWindowTitle[] = "LE2B_06_サカモトコウスケ_MT3";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

struct Sphere {
	Vector3 center;//!<中心点
	float radius;//!<半径
};

struct Triangle {
	Vector3 vertices[3];//頂点
};

//線の始点と終点
struct StartEnd {
	Vector3 start;//始点
	Vector3 end;//終点
};

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

struct Plane {
	Vector3 normal;//法線
	float distance;//距離
};

struct AABB {
	Vector3 min;//最小点
	Vector3 max;//最大点
};

int GetColor(unsigned int red, unsigned int  green, unsigned int  blue, int  alpha);

float Cot(float a);