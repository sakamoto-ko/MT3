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

	Quaternion rotation0 = MakeRotateAxisAngleQuaternion(Vector3{ 0.71f, 0.71f, 0.0f }, 0.3f);
	Quaternion rotation1 = MakeRotateAxisAngleQuaternion(Vector3{ 0.71f, 0.0f, 0.71f }, 3.141592f);

	Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
	Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
	Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
	Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
	Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		//入力
		inputManager_->Update();

		QuaternionScreenPrintf(0, kRowHeight * 0, interpolate0, "interpolate0, Slerp(q0, q1, 0.0f)");
		QuaternionScreenPrintf(0, kRowHeight * 1, interpolate1, "interpolate1, Slerp(q0, q1, 0.3f)");
		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate2, "interpolate2, Slerp(q0, q1, 0.5f)");
		QuaternionScreenPrintf(0, kRowHeight * 3, interpolate3, "interpolate3, Slerp(q0, q1, 0.7f)");
		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate4, "interpolate4, Slerp(q0, q1, 1.0f)");

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