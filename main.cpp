#include "Move.h"
#include "Draw.h"
#include "imgui.h"
#include "Collision.h"

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
		{1.5f,1.0f,1.0f},
		{0.0f,-1.0f,1.0f},
		{3.0f,-1.0f,1.0f}
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
		{ 0.0f,0.0f,0.0f },
		{ 1.0f,1.0f,1.0f }
	};
	Segment segment = { line.origin,line.diff };
	StartEnd lineLength = {};

	//Sphere sphere = { Vector3{0.0f,0.0f,0.0f},1.0f };

	Plane plane = { Vector3{0.0f,1.0f,0.0f},1.0f };

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

		lineLength.start = Transform(Transform(segment.origin, worldViewProjectionMatrix), viewportMatrix);
		lineLength.end = Transform(Transform(Add(segment.origin, segment.diff), worldViewProjectionMatrix), viewportMatrix);
		
		if (collision->IsCollision(plane, segment)) {
			color = RED;
		}
		else {
			color = WHITE;
		}

		//描画
		//グリッド
		draw->DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		//線
		Novice::DrawLine((int)lineLength.start.x, (int)lineLength.start.y, (int)lineLength.end.x, (int)lineLength.end.y, color);
		//球
		//draw->DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, color);
		//平面
		draw->DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//imgui
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("lineO", &segment.origin.x, 0.01f);
		ImGui::DragFloat3("lineD", &segment.diff.x, 0.01f);
		//ImGui::DragFloat3("sphereC", &sphere.center.x, 0.01f);
		//ImGui::DragFloat("sphereR", &sphere.radius, 0.01f);
		ImGui::DragFloat3("planeN", &plane.normal.x, 0.01f);
		ImGui::DragFloat("planeD", &plane.distance, 0.01f);
		ImGui::End();

		plane.normal = Normalize(plane.normal);

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