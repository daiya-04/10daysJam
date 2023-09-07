#pragma once
#include <Sprite.h>
#include <Input.h> 

class Title {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void Effect();
	bool GetTitle() { return title; };

private:
	Input* input_ = nullptr;

	Sprite* sprite;
	Sprite* spriteTitle;
	uint32_t texture_;
	uint32_t textureTitle_;

	Vector2 pos;
	Vector2 velo = {0, 0};
	bool effect = false;
	bool title = false;
	float time;
};