#include "Move.h"
#include "Draw.h"
#include "Overroad.h"
#include "MT4MyMath.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	//インスタンス
	// キーの入力情報を取得するInputManager
	InputManager* inputManager_ = InputManager::GetInstance();

	Vector3 axis = Normalize({ 1.0f,1.0f,1.0f });
	float angle = 0.44f;
	Matrix4x4 rotateMatrix = MakeRotateAxisAngle(axis, angle);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		//入力
		inputManager_->Update();

		MatrixScreenPrintf(0, 0, rotateMatrix, "rotateMatrix");

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (inputManager_->GetPreKeys()[DIK_ESCAPE] == 0 &&
			inputManager_->GetKeys()[DIK_ESCAPE] != 0) {
			break;
		}
	}

	//デストラクタ

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}