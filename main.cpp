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

	int s1color = WHITE;
	Sphere sphere1 = { Vector3{0.0f,0.0f,0.0f},1.0f };
	Sphere sphere2 = { Vector3{1.0f,1.0f,1.0f},1.0f };

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

		if (collision->IsCollision(sphere1, sphere2)) {
			s1color = RED;
		}
		else {
			s1color = WHITE;
		}

		//描画
		//グリッド
		draw->DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		//球
		draw->DrawSphere(sphere1, worldViewProjectionMatrix, viewportMatrix, s1color);
		draw->DrawSphere(sphere2, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//imgui
		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("sphere1C", &sphere1.center.x, 0.01f);
		ImGui::DragFloat("sphere1R", &sphere1.radius, 0.01f);
		ImGui::DragFloat3("sphere2C", &sphere2.center.x, 0.01f);
		ImGui::DragFloat("sphere2R", &sphere2.radius, 0.01f);
		ImGui::End();

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