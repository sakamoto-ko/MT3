#include "Move.h"
#include "Draw.h"
#include "Overroad.h"

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

	AABB aabb{
		.min{-0.5f,-0.5f,-0.5f},
		.max{0.0f,0.0f,0.0f},
	};

	Vector3 controlPoints[4] = {
		{ -0.8f, 0.58f ,1.0f },
		{ 1.76f, 1.0f ,-0.3f },
		{ 0.94f, -0.7f ,2.3f },
		{ -0.53f, -0.26f, -0.15f },
	};

	Vector3 translates[3] = {
		{0.2f,1.0f,0.0f},
		{0.4f,0.0f,0.0f},
		{0.3f,0.0f,0.0f},
	};
	Vector3 rotates[3] = {
		{0.0f,0.0f,-6.8f},
		{0.0f,0.0f,-1.4f},
		{0.0f,0.0f,0.0f},
	};
	Vector3 scales[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	//int color = WHITE;

	Vector3 a{ 0.2f,1.0f,0.0f };
	Vector3 b{ 2.4f,3.1f,1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 rotateTest{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateMatrix = MakeRotateMatrix(rotateTest);

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

		//aabbのminとmaxが入れ替わらないようにするやつ
		aabb.min.x = (std::min)(aabb.min.x, aabb.max.x);
		aabb.min.y = (std::min)(aabb.min.y, aabb.max.y);
		aabb.min.z = (std::min)(aabb.min.z, aabb.max.z);
		aabb.max.x = (std::max)(aabb.min.x, aabb.max.x);
		aabb.max.y = (std::max)(aabb.min.y, aabb.max.y);
		aabb.max.z = (std::max)(aabb.min.z, aabb.max.z);

		/*if (collision->IsCollision(aabb, segment)) {
			color = RED;
		}
		else {
			color = WHITE;
		}*/

		//imgui
		ImGui::Begin("Window");
		if (ImGui::TreeNode("camera")) {
			ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
			ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
			ImGui::TreePop();
		}
		/*if (ImGui::TreeNode("line")) {
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
			ImGui::DragFloat3("aabb.min", &aabb.min.x, 0.01f);
			ImGui::DragFloat3("aabb.max", &aabb.max.x, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("bezier")) {
			ImGui::DragFloat3("controlPoints0", &controlPoints[0].x, 0.01f);
			ImGui::DragFloat3("controlPoints1", &controlPoints[1].x, 0.01f);
			ImGui::DragFloat3("controlPoints2", &controlPoints[2].x, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("catmullRom")) {
			ImGui::DragFloat3("controlPoints0", &controlPoints[0].x, 0.01f);
			ImGui::DragFloat3("controlPoints1", &controlPoints[1].x, 0.01f);
			ImGui::DragFloat3("controlPoints2", &controlPoints[2].x, 0.01f);
			ImGui::DragFloat3("controlPoints3", &controlPoints[3].x, 0.01f);
			ImGui::TreePop();
		}*/
		/*if (ImGui::TreeNode("shoulder")) {
			ImGui::DragFloat3("translation", &translates[0].x, 0.01f);
			ImGui::DragFloat3("rotation", &rotates[0].x, 0.01f);
			ImGui::DragFloat3("scale", &scales[0].x, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("elbow")) {
			ImGui::DragFloat3("translation", &translates[1].x, 0.01f);
			ImGui::DragFloat3("rotation", &rotates[1].x, 0.01f);
			ImGui::DragFloat3("scale", &scales[1].x, 0.01f);
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("arm")) {
			ImGui::DragFloat3("translation", &translates[2].x, 0.01f);
			ImGui::DragFloat3("rotation", &rotates[2].x, 0.01f);
			ImGui::DragFloat3("scale", &scales[2].x, 0.01f);
			ImGui::TreePop();
		}*/
		if (ImGui::TreeNode("Test")) {
			ImGui::Text("c: %f, %f, %f", c.x, c.y, c.z);
			ImGui::Text("d: %f, %f, %f", d.x, d.y, d.z);
			ImGui::Text("e: %f, %f, %f", e.x, e.y, e.z);
			ImGui::Text(
				"matrix:\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n%f, %f, %f, %f\n",
				rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2],
				rotateMatrix.m[0][3], rotateMatrix.m[1][0], rotateMatrix.m[1][1],
				rotateMatrix.m[1][2], rotateMatrix.m[1][3], rotateMatrix.m[2][0],
				rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3],
				rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2],
				rotateMatrix.m[3][3]);
			ImGui::TreePop();
		}
		ImGui::End();

		//移動した後に正規化を忘れずに
		plane.normal = Normalize(plane.normal);

		//描画
		//グリッド
		draw->DrawGrid(worldViewProjectionMatrix, viewportMatrix);
		//線
		//Novice::DrawLine((int)lineLength.start.x, (int)lineLength.start.y, (int)lineLength.end.x, (int)lineLength.end.y, WHITE);
		//三角形
		//draw->DrawTriangle(triangle, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//球
		//draw->DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//平面
		//draw->DrawPlane(plane, worldViewProjectionMatrix, viewportMatrix, WHITE);
		//AABB
		//draw->DrawAABB(aabb, worldViewProjectionMatrix, viewportMatrix, color);

		//ベジエ曲線
		/*draw->DrawBezier(controlPoints[0], controlPoints[1], controlPoints[2],
			worldViewProjectionMatrix, viewportMatrix, color);*/
		//キャトムルロム曲線
		/*draw->DrawCatmullRom(controlPoints[3], controlPoints[0], controlPoints[1], controlPoints[2],
			worldViewProjectionMatrix, viewportMatrix, color);
		draw->DrawCatmullRom(controlPoints[0], controlPoints[1], controlPoints[2], controlPoints[3],
			worldViewProjectionMatrix, viewportMatrix, color);
		draw->DrawCatmullRom(controlPoints[1], controlPoints[2], controlPoints[3], controlPoints[0],
			worldViewProjectionMatrix, viewportMatrix, color);
		for (int i = 0; i < 4; i++) {
			draw->DrawSphere(Sphere(controlPoints[i], 0.01f), worldViewProjectionMatrix, viewportMatrix, BLACK);
		}*/

		//腕
		//draw->DrawArm(translates, rotates, scales, worldViewProjectionMatrix, viewportMatrix);

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