#include "Move.h"

void Move::MovePlayer(Vector3 translate, Vector3 rotate, Vector3 cameraPosition, Vector3 playerPosition[]) {
	inputManager_->Update(); // 入力処理

	//WSキーで前後に、ADキーで左右に三角形を動かす処理、Y軸回転をさせる処理
	//前後
	if (inputManager_->GetKeys()[DIK_W]) {
		translate.z += 0.1f;
	}
	else if (inputManager_->GetKeys()[DIK_S]) {
		translate.z += -0.1f;
	}
	else {}
	//左右
	if (inputManager_->GetKeys()[DIK_D]) {
		translate.x += 0.1f;
	}
	else if (inputManager_->GetKeys()[DIK_A]) {
		translate.x += -0.1f;
	}
	else {}

	//Y軸回転
	rotate.y += 0.03f;

	//各種行列の計算
	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, cameraPosition);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspecriveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	//WVPMatrixを作る
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	//ViewportMatrixを作る
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);
	//Screen空間へと頂点を変換する
	Vector3 screenVertices[3]{};
	for (uint32_t i = 0; i < 3; ++i) {
		//NDCまで変換。Transformを使うと、同次座標系->デカルト座標系の処理が行われ、結果的にZDivideが行われることになる
		Vector3 ndcVertex = Transform(playerPosition[i], worldViewProjectionMatrix);
		//Viewport変換を行ってScreen空間へ
		screenVertices[i] = Transform(ndcVertex, viewportMatrix);
	}
}