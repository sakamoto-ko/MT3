#include "Move.h"
#include "Draw.h"
#include "Overroad.h"
#include "MT4MyMath.h"
#include "Quaterinion.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	//インスタンス
	// キーの入力情報を取得するInputManager
	InputManager* inputManager_ = InputManager::GetInstance();

	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };

	Quaternion mul1 = Multiply(q1, q2);
	Quaternion mul2 = Multiply(q2, q1);

	Quaternion identiy = IdentityQuaternion();

	Quaternion conj = Conjugate(q1);

	float norm = Norm(q1);

	Quaternion normal = Normalize(q1);

	Quaternion inv = Inverse(q1);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		//入力
		inputManager_->Update();

		QuaternionScreenPrintf(0, 0, mul1, "Multiply(q1, q2)");
		QuaternionScreenPrintf(0, 50, mul2, "Multiply(q2, q1)");
		QuaternionScreenPrintf(0, 100, identiy, "Identity");
		QuaternionScreenPrintf(0, 150, conj, "Conjugate");
		Novice::ScreenPrintf(0, 200, "%s", "Norm");
		Novice::ScreenPrintf(0, 220, "%2.02f", norm);
		QuaternionScreenPrintf(0, 250, normal, "Normalize");
		QuaternionScreenPrintf(0, 300, inv, "Inverse");

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