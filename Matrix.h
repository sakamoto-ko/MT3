#pragma once
#include"base.h"

//加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
//減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
//積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
//逆行列
Matrix4x4 Inverse(const Matrix4x4& m);
//転置行列
Matrix4x4 Transpose(const Matrix4x4& m);
//単位行列
Matrix4x4 MakeIdenttity4x4();

//文字出力
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label);

// 平行移動行列
Matrix4x4 MakeTranslateMatrix(const Vector3& translate);

// X軸回転
Matrix4x4 MakeRotateXMatrix(float radian);
// Y軸回転
Matrix4x4 MakeRotateYMatrix(float radian);
// Z軸回転
Matrix4x4 MakeRotateZMatrix(float radian);
// 回転行列
Matrix4x4 MakeRotateMatrix(const Vector3& radian);

// 拡大縮小行列
Matrix4x4 MakeScaleMatrix(const Vector3& scale);

//アフィン変換行列
Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rot, const Vector3& translate);

//座標返還
Vector3 Transform(const Vector3& v, const Matrix4x4& m);

//透視投影行列
Matrix4x4 MakePerspecriveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);

//正射影行列
Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);

//ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float MaxDepth);
