#pragma once
#include "Cross.h"
#include "InputManager.h"

class Move
{
private:
	//インスタンス
	// キーの入力情報を取得するInputManager
	InputManager* inputManager_ = InputManager::GetInstance();

public:
	void MovePlayer(Vector3 translate, Vector3 rotate, Vector3 cameraPosition, Vector3 kLocalVertices[]);
};

