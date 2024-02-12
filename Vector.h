#pragma once
#include "base.h"

void Vector3ScreenPrintf(int x, int y, const Vector3& v, const char* label);

//加算
Vector3 Add(const Vector3& v1, const Vector3& v2);
//減算
Vector3 Subtract(const Vector3& v1, const Vector3& v2);
//スカラー倍
Vector3 Scalar(float scalar, const Vector3& v);
//スカラー倍
Vector3 Scalar(const Vector3& v, float scalar);
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
Vector3 Multiply(const Vector3& v1, const Vector3& v2);

Vector3 Harf(const Vector3& v, const float& a);

Vector3 Reflect(const Vector3& input, const Vector3& normal);