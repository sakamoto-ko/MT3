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
