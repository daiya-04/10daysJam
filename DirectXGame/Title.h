#pragma once
#include <Sprite.h>
#include <Input.h> 
#include <optional>

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

	void TitleMove();

	void MenuMove();

	

	void Effect();
	bool GetTitle() { return title; };

	

	void TitleInitialize();

	void MenuInitialize();

	void GameSceneInitialize();
	void GameSceneUpdata();

	void SetGame(const bool game) { 
		game_ = game;
	}

private:
	Input* input_ = nullptr;

	Sprite* sprite[4] = {nullptr};
	Sprite* Background1;
	Sprite* Background2;
	Sprite* spriteTitle;
	

	
	
	uint32_t texture_[3];
	uint32_t textureBackground1_;
	uint32_t textureBackground2_;
	uint32_t textureTitle_;
	

	Vector2 pos;
	Vector2 BackgroundPos1_;
	Vector2 BackgroundPos2_;
	Vector2 MenuPos_;

	Vector2 velo = {0, 0};
	bool effect = false;
	bool title = false;
	float time;


	//全体の動き
	bool move_;


	// 振る舞い
	enum class Behavior {
		kTitle,  // タイトル
		kMenu,   // メニュー
		kGameScene, //ゲームシーン 
	};

	Behavior behavior_ = Behavior::kTitle;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	bool game_ = false;
};