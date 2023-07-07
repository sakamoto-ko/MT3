#include "Draw.h"

void Draw::DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	const uint32_t kSubdivision = 12;//分割数
	const float kLonEvery = 12;//経度分割1つ分の角度
	const float kLatEvery = 12;//緯度分割1つ分の角度
	//緯度の方向に分割-π/2 ~ π/2
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -pi / 2.0f + kLatEvery * latIndex;//現在の緯度
		//経度の方向に分割0 ~ 2π
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;//現在の経度
			Vector3 a, b, c;
			//world座標系でのa,b,cを求める
			a = {
				cosf(lat) * cosf(lon),
				sinf(lat),
				cosf(lat) * sinf(lon)
			};
			b = {
				cosf(lat + kLatEvery) * cosf(lon),
				sinf(lat + kLatEvery),
				cosf(lat + kLatEvery) * sinf(lon)
			};
			c = {
				cosf(lat) * cosf(lon + kLonEvery),
				sinf(lat),
				cosf(lat) * sinf(lon + kLonEvery)
			};
			//a,b,cをScreen座標系まで変換
			Vector3 screenVertices[3]{};
			Vector3 tmp[3]{
				{ a.x, a.y, a.z },
				{ b.x, b.y, b.z },
				{ c.x, c.y, c.z }
			};
			for (uint32_t i = 0; i < 3; ++i) {
				//球の計算
				tmp[i] = Scalar(sphere.radius, tmp[i]);
				tmp[i] = Add(sphere.center, tmp[i]);
				//NDCまで変換。Transformを使うと、同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
				Vector3 ndcVertex = Transform(tmp[i], viewProjectionMatrix);
				//Viewport変換を行ってScreen空間へ
				screenVertices[i] = Transform(ndcVertex, viewportMatrix);
			}
			//ab,bcで線を引く
			Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, color);//ab
			Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[2].x, (int)screenVertices[2].y, color);//ac
		}
	}
}
void Draw::DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix) {
	const float kGridHalfWidth = 2.0f;//Gridの半分の幅
	const uint32_t kSubdivision = 10;//分割数
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);//1つ分の長さ

	//奥から手前への線を順々に引いていく
	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {
		//上の情報を使ってワールド座標上の始点と終点を求める
		float kStartGridX = kGridEvery * (-5);
		float kFinishGridX = kGridEvery * (5);
		float kGridZ = kGridEvery * ((-5) + (float)zIndex);
		Vector3 kGrid[2]{
			{ kStartGridX,0,kGridZ },
			{ kFinishGridX,0,kGridZ }
		};
		//スクリーン座標系まで変換をかける
		Vector3 screenVertices[2]{};
		for (uint32_t i = 0; i < 2; ++i) {
			//NDCまで変換。Transformを使うと、同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
			Vector3 ndcVertex = Transform(kGrid[i], viewProjectionMatrix);
			//Viewport変換を行ってScreen空間へ
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		//色
		int color = 0;
		if (zIndex == 5) {
			color = BLACK;
		}
		else {
			color = 0xAAAAAAFF;
		}
		//変換した座標を使って表示
		Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), color);
	}

	//左から右も同じように順々に引いていく
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		//上の情報を使ってワールド座標上の始点と終点を求める
		float kStartGridZ = kGridEvery * (-5);
		float kFinishGridZ = kGridEvery * (5);
		float kGridX = kGridEvery * ((-5) + (float)xIndex);
		Vector3 kGrid[2]{
			{ kGridX,0,kStartGridZ },
			{ kGridX,0,kFinishGridZ }
		};
		//スクリーン座標系まで変換をかける
		Vector3 screenVertices[2]{};
		for (uint32_t i = 0; i < 2; ++i) {
			//NDCまで変換。Transformを使うと、同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
			Vector3 ndcVertex = Transform(kGrid[i], viewProjectionMatrix);
			//Viewport変換を行ってScreen空間へ
			screenVertices[i] = Transform(ndcVertex, viewportMatrix);
		}
		//色
		int color = 0;
		if (xIndex == 5) {
			color = BLACK;
		}
		else {
			color = 0xAAAAAAFF;
		}
		//変換した座標を使って表示
		Novice::DrawLine(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y), color);
	}
}

Vector3 Draw::Perpendicular(const Vector3& vector) {
	if (vector.x != 0.0f || vector.y != 0.0f) {
		return { -vector.y,vector.x,0.0f };
	}
	return { 0.0f,-vector.z,vector.y };
}

void Draw::DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 screenVertices[3]{};
	for (uint32_t i = 0; i < 3; ++i) {
		Vector3 tmp[3] = {
			{ triangle.vertices[0].x, triangle.vertices[0].y, triangle.vertices[0].z},
			{ triangle.vertices[1].x, triangle.vertices[1].y, triangle.vertices[1].z},
			{ triangle.vertices[2].x, triangle.vertices[2].y, triangle.vertices[2].z},
		};
		//NDCまで変換。Transformを使うと、同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
		Vector3 ndcVertex = Transform(tmp[i], viewProjectionMatrix);
		//Viewport変換を行ってScreen空間へ
		screenVertices[i] = Transform(ndcVertex, viewportMatrix);
	}
	Novice::DrawTriangle((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, (int)screenVertices[2].x, (int)screenVertices[2].y, color, kFillModeWireFrame);
}

void Draw::DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 center = Scalar(plane.distance, plane.normal);
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];
	for (int32_t index = 0; index < 4; ++index) {
		Vector3 extend = Scalar(2.0f, perpendiculars[index]);
		Vector3 point = Add(center, extend);
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[2].x, (int)points[2].y, color);
}

void Draw::DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	Vector3 screenVertices[8]{};
	float width = aabb.max.x - aabb.min.x;
	float height = aabb.max.y - aabb.min.y;
	Vector3 a, b, c, d, e, f, g, h;
	a = aabb.min;
	h = aabb.max;
	b = { aabb.min.x + width,aabb.min.y,aabb.min.z };
	c = { aabb.min.x,aabb.min.y + height,aabb.min.z };
	d = { aabb.min.x + width,aabb.min.y + height,aabb.min.z };
	e = { aabb.max.x - width,aabb.max.y - height,aabb.max.z };
	f = { aabb.max.x,aabb.max.y - height,aabb.max.z };
	g = { aabb.max.x - width,aabb.max.y,aabb.max.z };

	for (uint32_t i = 0; i < 8; ++i) {
		Vector3 tmp[8]{
			{ a.x, a.y, a.z },
			{ b.x, b.y, b.z },
			{ c.x, c.y, c.z },
			{ d.x, d.y, d.z },
			{ e.x, e.y, e.z },
			{ f.x, f.y, f.z },
			{ g.x, g.y, g.z },
			{ h.x, h.y, h.z }
		};
		//NDCまで変換。Transformを使うと、同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
		Vector3 ndcVertex = Transform(tmp[i], viewProjectionMatrix);
		//Viewport変換を行ってScreen空間へ
		screenVertices[i] = Transform(ndcVertex, viewportMatrix);
	}

	Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, color);
	Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[2].x, (int)screenVertices[2].y, color);
	Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[4].x, (int)screenVertices[4].y, color);
	Novice::DrawLine((int)screenVertices[1].x, (int)screenVertices[1].y, (int)screenVertices[3].x, (int)screenVertices[3].y, color);
	Novice::DrawLine((int)screenVertices[1].x, (int)screenVertices[1].y, (int)screenVertices[5].x, (int)screenVertices[5].y, color);
	Novice::DrawLine((int)screenVertices[2].x, (int)screenVertices[2].y, (int)screenVertices[3].x, (int)screenVertices[3].y, color);
	Novice::DrawLine((int)screenVertices[2].x, (int)screenVertices[2].y, (int)screenVertices[6].x, (int)screenVertices[6].y, color);
	Novice::DrawLine((int)screenVertices[3].x, (int)screenVertices[3].y, (int)screenVertices[7].x, (int)screenVertices[7].y, color);
	Novice::DrawLine((int)screenVertices[4].x, (int)screenVertices[4].y, (int)screenVertices[5].x, (int)screenVertices[5].y, color);
	Novice::DrawLine((int)screenVertices[4].x, (int)screenVertices[4].y, (int)screenVertices[6].x, (int)screenVertices[6].y, color);
	Novice::DrawLine((int)screenVertices[5].x, (int)screenVertices[5].y, (int)screenVertices[7].x, (int)screenVertices[7].y, color);
	Novice::DrawLine((int)screenVertices[6].x, (int)screenVertices[6].y, (int)screenVertices[7].x, (int)screenVertices[7].y, color);
}

Vector3 Draw::Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 result;
	result.x = (1.0f - t) * v1.x + t * v2.x;
	result.y = (1.0f - t) * v1.y + t * v2.y;
	result.z = (1.0f - t) * v1.z + t * v2.z;
	return result;
}

Vector3 Draw::Bazier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, float t) {
	//制御点p0, p1の線形補完
	Vector3 p0p1 = Lerp(controlPoint0, controlPoint1, t);
	//制御点p1, p2の線形補完
	Vector3 p1p2 = Lerp(controlPoint1, controlPoint2, t);
	//補完点p0p1, p1p2をさらに線形補完
	return Lerp(p0p1, p1p2, t);
}

void Draw::DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2,
	const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color) {
	constexpr int kNumDevide = 32;
	constexpr float kNumDevideF = float(kNumDevide);

	for (int divideIndex = 0; divideIndex < kNumDevide; ++divideIndex) {
		float t = float(divideIndex) / kNumDevideF;

		Vector3 bezierPoint = Bazier(controlPoint0, controlPoint1, controlPoint2, t);
		Vector3 bezierPointNext = Bazier(controlPoint0, controlPoint1, controlPoint2, t + 1.0f / 32.0f);

		Vector3 screenVertices[2]{};
		Vector3 ndcVertex[2]{};
		Vector3 tmp[2] = {
			{bezierPoint},
			{bezierPointNext},
		};
		//NDCまで変換。Transformを使うと、同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
		ndcVertex[0] = Transform(tmp[0], viewProjectionMatrix);
		ndcVertex[1] = Transform(tmp[1], viewProjectionMatrix);
		//Viewport変換を行ってScreen空間へ
		screenVertices[0] = Transform(ndcVertex[0], viewportMatrix);
		screenVertices[1] = Transform(ndcVertex[1], viewportMatrix);

		Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y,
			(int)screenVertices[1].x, (int)screenVertices[1].y, color);
	}
}