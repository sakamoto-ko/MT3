#pragma once
#include "base.h"

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2);
//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
//スカラー倍
Vector3 Scalar(float scalar, const Vector3& v);
//内積
float Dot(const Vector3& v1, const Vector3& v2);
//長さ
float Length(const Vector3& v);
//正規化
Vector3 Normalize(const Vector3& v);

//文字出力
void VectorScreenPrintf(int x, int y, Vector3& vector, const char* label);

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2);

//ベクトルとフロートの加算
Vector3 Add(const Vector3& v, const float& a);

//ベクトルとフロートの減算
Vector3 Subtract(const Vector3& v, const float& a);

//フロートとベクトルの減算
Vector3 Subtract(const float& a, const Vector3& v);

//ベクトルとベクトルの積
Vector3 Multiply(const Vector3& v1, Vector3& v2);