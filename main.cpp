#include "Move.h"
#include "Draw.h"
#include "imgui.h"
#include "Collision.h"
#include <algorithm>
#include <functional>

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	//インスタンス
	// キーの入力情報を取得するInputManager
	InputManager* inputManager_ = InputManager::GetInstance();
	Draw* draw = new Draw();
	Collision* collision = new Collision();

	//変数
	Vector3 translate{};
	Vector3 rotate{};
	//カメラ
	Vector3 cameraTranslate{
		0.0f,1.9f,-6.49f
	};
	Vector3 cameraRotate{
		0.26f,0.0f,0.0f
	};
	Vector3 kLocalVertices[3]{
		{1.5f,1.0f,0.0f},
		{0.0f,-1.0f,0.0f},
		{3.0f,-1.0f,0.0f}
	};

	//各種行列の計算
	Matrix4x4 worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
	Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
	Matrix4x4 viewMatrix = Inverse(cameraMatrix);
	Matrix4x4 projectionMatrix = MakePerspecriveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
	//WVPMatrixを作る
	Matrix4x4 worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
	//ViewportMatrixを作る
	Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

	Line line = {
		.origin = { 0.0f,0.0f,1.0f },
		.diff = { 1.0f,1.0f,0.0f }
	};
	Segment segment = { line.origin,line.diff };
	StartEnd lineLength = {};

	Sphere sphere = { Vector3{0.0f,0.0f,0.0f},1.0f };

	Plane plane = { Vector3{0.0f,1.0f,0.0f},1.0f };

	Triangle triangle = {
		triangle.vertices[0] = Vector3{-1.0f,0.0f,1.0f},
		triangle.vertices[1] = Vector3{0.0f,1.0f,1.0f},
		triangle.vertices[2] = Vector3{1.0f,0.0f,1.0f},
	};

	AABB aabb1{
		.min{-0.5f,-0.5f,-0.5f},
		.max{0.0f,0.0f,0.0f},
	};
	AABB aabb2{
		.min{0.2f,0.2f,0.2f},
		.max{1.0f,1.0f,1.0f},
	};

	int color = WHITE;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		//入力
		inputManager_->Update();

		//更新
		//カメラのリセット
		if (inputManager_->GetKeys()[DIK_R] && inputManager_->GetPreKeys()[DIK_R] != 0) {
			cameraTranslate.x = 0.0f;
			cameraTranslate.y = 1.9f;
			cameraTranslate.z = -6.49f;
			cameraRotate.x = 0.26f;
			cameraRotate.y = 0.0f;
			cameraRotate.z = 0.0f;
		}

		//各種行列の計算
		worldMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, rotate, translate);
		cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		viewMatrix = Inverse(cameraMatrix);
		projectionMatrix = MakePerspecriveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		//WVPMatrixを作る
		worldViewProjectionMatrix = Multiply(worldMatrix, Multiply(viewMatrix, projectionMatrix));
		//ViewportMatrixを作る
		viewportMatrix = MakeViewportMatrix(0, 0, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		//lineLength.start = Transform(Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
		//lineLength.end = Transform(Transform(Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewportMatrix);

		//aabbのminとmaxが入れ替わらないようにするやつ
		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);
		aabb2.min.x = (std::min)(aabb2.min.x, aabb2.max.x);
		aabb2.min.y = (std::min)(aabb2.min.y, aabb2.max.y);
		aabb2.min.z = (std::min)(aabb2.min.z, aabb2.max.z);
		aabb2.max.x = (std::max)(aabb2.min.x, aabb2.max.x);
		aabb2.max.y = (std::max)(aabb2.min.y, aabb2.max.y);
		aabb2.max.z = (std::max)(aabb2.min.z, aabb2.max.z);

		if (collision->IsCollision(aabb1, aabb2)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		//描画
		//グリッド
		draw->DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		//線
		//Novice::DrawLine((int)lineLength.start.x, (int)lineLength.start.y, (int)lineLength.end.x, (int)lineLength.end.y, color);
		//三角形
		//draw->DrawTriangle(triangle, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//球
		//draw->DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, color);
		//平面
		//draw->DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//AABB
		draw->DrawAABB(aabb1, worldViewProjectionMatrix, viewportMatrix, color);
		draw->DrawAABB(aabb2, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//imgui
		ImGui::Begin("Window");
		if (ImGui::TreeNode("camera")) {
			ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
			ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("line")) {
			ImGui::DragFloat3("line.origin", &segment.origin.x, 0.01f);
			ImGui::DragFloat3("line.diff", &segment.diff.x, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("triangle")) {
			ImGui::DragFloat3("triangle.vertices1", &triangle.vertices[0].x, 0.01f);
			ImGui::DragFloat3("triangle.vertices2", &triangle.vertices[1].x, 0.01f);
			ImGui::DragFloat3("triangle.vertices3", &triangle.vertices[2].x, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("sphere")) {
			ImGui::DragFloat3("sphere.center", &sphere.center.x, 0.01f);
			ImGui::DragFloat("sphere.radius", &sphere.radius, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("plane")) {
			ImGui::DragFloat3("plane.normal", &plane.normal.x, 0.01f);
			ImGui::DragFloat("plane.distance", &plane.distance, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("aabb")) {
			ImGui::DragFloat3("aabb.min1", &aabb1.min.x, 0.01f);
			ImGui::DragFloat3("aabb.max1", &aabb1.max.x, 0.01f);
			ImGui::DragFloat3("aabb.min2", &aabb2.min.x, 0.01f);
			ImGui::DragFloat3("aabb.max2", &aabb2.max.x, 0.01f);
			ImGui::TreePop();
		}
		ImGui::End();

		//plane.normal = Normalize(plane.normal);

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (inputManager_->GetPreKeys()[DIK_ESCAPE] == 0 &&
			inputManager_->GetKeys()[DIK_ESCAPE] != 0) {
			break;
		}

	}
	//デストラクタ
	//delete inoutManager_ //不要
	delete draw;
	delete collision;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}