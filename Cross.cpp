#include "Cross.h"

//クロス積
Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	Vector3 result{};

	result = {
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	};

	return result;
}

//bool CrossFrontOrRear(Vector3 cameraPosition, Vector3& v1, Vector3& v2) {
//	if (Multiply(Dot(v1, v2), cameraPosition) <= 0) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}