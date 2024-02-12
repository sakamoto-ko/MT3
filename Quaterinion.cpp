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
	Vector3 resultV;
	float resultW;

	Vector3 lhsV = Vector3{ lhs.x,lhs.y,lhs.z };
	float lhsW = lhs.w;

	Vector3 rhsV = Vector3{ rhs.x,rhs.y,rhs.z };
	float rhsW = rhs.w;

	resultV = Add(Add(Cross(lhsV, rhsV), Scalar(rhsW, lhsV)), Scalar(lhsW, rhsV));
	resultW = lhsW * rhsW - Dot(lhsV, rhsV);

	Quaternion result = { resultV.x,resultV.y,resultV.z,resultW };

	return result;
}

Quaternion IdentityQuaternion()
{
	Quaternion result;

	result = { 0.0f,0.0f,0.0f,1.0f };

	return result;
}

Quaternion Conjugate(const Quaternion& quaternion)
{
	Quaternion result;

	result = { -quaternion.x,-quaternion.y,-quaternion.z,quaternion.w };

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
	Quaternion result;

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
