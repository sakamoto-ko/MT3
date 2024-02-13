#include "Quaterinion.h"

//文字出力
void QuaternionScreenPrintf(int x, int y, const Quaternion& quaternion, const char* label) {
	Novice::ScreenPrintf(x, y + 20, "%2.02f", quaternion.x);
	Novice::ScreenPrintf(x + 80, y + 20, "%2.02f", quaternion.y);
	Novice::ScreenPrintf(x + 160, y + 20, "%2.02f", quaternion.z);
	Novice::ScreenPrintf(x + 240, y + 20, "%2.02f", quaternion.w);
	Novice::ScreenPrintf(x, y, "%s", label);
}

Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs)
{
	Vector3 lhsV = Vector3{ lhs.x,lhs.y,lhs.z };
	float lhsW = lhs.w;

	Vector3 rhsV = Vector3{ rhs.x,rhs.y,rhs.z };
	float rhsW = rhs.w;

	Vector3 resultV = Add(Add(Cross(lhsV, rhsV), Scalar(rhsW, lhsV)), Scalar(lhsW, rhsV));
	float resultW = lhsW * rhsW - Dot(lhsV, rhsV);

	Quaternion result = { resultV.x,resultV.y,resultV.z,resultW };

	return result;
}

Quaternion IdentityQuaternion()
{
	Quaternion result = { 0.0f,0.0f,0.0f,1.0f };

	return result;
}

Quaternion Conjugate(const Quaternion& quaternion)
{
	Quaternion result = { -quaternion.x,-quaternion.y,-quaternion.z,quaternion.w };

	return result;
}

float Norm(const Quaternion& quaternion)
{
	float x2 = quaternion.x * quaternion.x;
	float y2 = quaternion.y * quaternion.y;
	float z2 = quaternion.z * quaternion.z;
	float w2 = quaternion.w * quaternion.w;

	float result = std::sqrtf(w2 + x2 + y2 + z2);

	return result;
}

Quaternion Normalize(const Quaternion& quaternion)
{
	Quaternion result{};

	float x2 = quaternion.x * quaternion.x;
	float y2 = quaternion.y * quaternion.y;
	float z2 = quaternion.z * quaternion.z;
	float w2 = quaternion.w * quaternion.w;

	float a = std::sqrtf(w2 + x2 + y2 + z2);
	if (a != 0) {
		result.x = quaternion.x / a;
		result.y = quaternion.y / a;
		result.z = quaternion.z / a;
		result.w = quaternion.w / a;
	}

	return result;
}

Quaternion Inverse(const Quaternion& quaternion)
{
	Quaternion result = Scalar(Conjugate(quaternion), 1.0f / (Norm(quaternion) * Norm(quaternion)));

	return result;
}

Quaternion Scalar(float scalar, const Quaternion& q)
{
	Quaternion result{};

	result.x = scalar * q.x;
	result.y = scalar * q.y;
	result.z = scalar * q.z;
	result.w = scalar * q.w;

	return result;
}

Quaternion Scalar(const Quaternion& q, float scalar)
{
	Quaternion result{};

	result.x = scalar * q.x;
	result.y = scalar * q.y;
	result.z = scalar * q.z;
	result.w = scalar * q.w;

	return result;
}

Quaternion MakeRotateAxisAngleQuaternion(const Vector3& axis, float angle)
{
	Vector3 qV = Scalar(axis, sinf(angle / 2.0f));
	float qW = cosf(angle / 2.0f);

	Quaternion result = { qV.x,qV.y,qV.z,qW };

	return result;
}

Vector3 RotateVector(const Vector3& v, const Quaternion& q)
{
	Quaternion vq = { v.x,v.y,v.z,0.0f };
	Quaternion conj = { Conjugate(q) };
	Quaternion resultQ = { Multiply(Multiply(q,vq),conj) };
	Vector3 result = { resultQ.x,resultQ.y,resultQ.z };

	return result;
}

Matrix4x4 MakeRotateMatrixQuaternion(const Quaternion& q)
{
	Matrix4x4 m{};

	m.m[0][0] = { q.w * q.w + q.x * q.x - q.y * q.y - q.z * q.z };
	m.m[0][1] = { 2.0f * (q.x * q.y + q.w * q.z) };
	m.m[0][2] = { 2.0f * (q.x * q.z - q.w * q.y) };
	m.m[0][3] = { 0.0f };

	m.m[1][0] = { 2.0f * (q.x * q.y - q.w * q.z) };
	m.m[1][1] = { q.w * q.w - q.x * q.x + q.y * q.y - q.z * q.z };
	m.m[1][2] = { 2.0f * (q.y * q.z + q.w * q.x) };
	m.m[1][3] = { 0.0f };

	m.m[2][0] = { 2.0f * (q.x * q.z + q.w * q.y) };
	m.m[2][1] = { 2.0f * (q.y * q.z - q.w * q.x) };
	m.m[2][2] = { q.w * q.w - q.x * q.x - q.y * q.y + q.z * q.z };
	m.m[2][3] = { 0.0f };

	m.m[3][0] = { 0.0f };
	m.m[3][1] = { 0.0f };
	m.m[3][2] = { 0.0f };
	m.m[3][3] = { 1.0f };

	return m;
}

Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t)
{
	float dot = Dot(Vector3{ q0.x,q0.y,q0.z }, Vector3{ q1.x,q1.y,q1.z });

	Quaternion tmp0 = q0;

	if (dot < 0) {
		tmp0 = Scalar(-1.0f, tmp0);
		dot = -dot;
	}

	Quaternion q0q1 = Lerp(tmp0, q1, t);

	float theta = std::acos(dot);
	float sinTheta = sinf(theta);

	float scale0 = sinf((1 - t) * theta) / sinTheta;
	float scale1 = sin(t * theta) / sinTheta;

	Quaternion result = {
		{ scale0 * tmp0.x + scale1 * q1.x },
		{ scale0 * tmp0.y + scale1 * q1.y },
		{ scale0 * tmp0.z + scale1 * q1.z },
		{ scale0 * tmp0.w + scale1 * q1.w } };

	return result;
}

Quaternion Lerp(const Quaternion& q0, const Quaternion& q1, float t) {
	Quaternion result = {
		(1.0f - t) * q0.x + t * q1.x,
		(1.0f - t) * q0.y + t * q1.y,
		(1.0f - t) * q0.z + t * q1.z,
		(1.0f - t) * q0.w + t * q1.w, };

	return result;
}

Quaternion Add(const Quaternion& q1, const Quaternion& q2)
{
	Quaternion result = {
		q1.x + q2.x,
		q1.y + q2.y,
		q1.z + q2.z,
		q1.w + q2.w };

	return result;
}
