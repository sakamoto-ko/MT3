﻿#include "base.h"

class InputManager final {
private:
	// コンストラクタをprivateとして外部からインスタンスを作れないようにする。
	// デストラクタもついでにprivateに
	InputManager();
	~InputManager() = default;

	// コピーコンストラクタの禁止
	InputManager(const InputManager&) = delete;

	// 代入演算子のオーバーロードを禁止
	const InputManager& operator=(const InputManager&) = delete;

	// メンバ変数 メンバ変数は後ろに_をつけて区別する
	char keys_[256] = { 0 };
	char preKeys_[256] = { 0 };

	int num_;

public:
	// 一つしか生成されないインスタンスにはGetInstance()関数経由でアクセスする
	static InputManager* GetInstance();

	// メンバ関数
	// void Init(); // 今回未使用
	void Update();
	// void Draw(); // 今回未使用

	// Getter経由でキーの入力状況を取得aする
	char* GetKeys();
	char* GetPreKeys();
};