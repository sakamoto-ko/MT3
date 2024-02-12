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

	Quaternion rotation = MakeRotateAxisAngleQuaternion(Normalize(Vector3{ 1.0f,0.4f,-0.2f }), 0.45f);

	Vector3 pointY = { 2.1f,-0.9f,1.3f };

	Vector3 rotateByQuaternion = RotateVector(pointY, rotation);

	Matrix4x4 rotateMatrix = MakeRotateMatrixQuaternion(rotation);

	Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		//入力
		inputManager_->Update();

		QuaternionScreenPrintf(0, 0, rotation, "Rotation");

		Vector3ScreenPrintf(0, 50, rotateByQuaternion, "rotateByQuaternion");

		MatrixScreenPrintf(0, 100, rotateMatrix, "rotateMatrix");

		Vector3ScreenPrintf(0, 200, rotateByMatrix, "rotateByMatrix");

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