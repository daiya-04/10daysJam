#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "block.h"
#include "Title.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

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

	//トロッコ
	void CartMove();

	void StageSelect();

	void BackGroundMove();

	// タイトル初期化
	void BehaviorTitleInitialize();

	//メニュー初期化
	void BehaviorMenuInitialize();

	// シーン初期化
	void BehaviorSceneInitialize();

	// クリア初期化
	void BehaviorClearInitialize();

	// オーバー初期化
	void BehaviorOverInitialize();

	// タイトル
	void BehaviorTitleUpdata();

	//メニュー
	void BehaviorMenuUpdata();

	// シーン
	void BehaviorSceneUpdata();

	// クリア
	void BehaviorClearUpdata();

	// オーバー
	void BehaviorOverUpdata();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	Sprite* spriteTransition_ = nullptr; 

	uint32_t textureTransition_;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	//トロッコ
	uint32_t textureCart_;
	uint32_t textureTire_;
	Sprite* spriteCart;
	Sprite* spriteTire[2];

	Vector2 CartPos_;
	Vector2 TirepPos_;

	// トロッコの動き
	float floatingParameter_ = 0.0f;

	// 浮遊移動サイクル
	float cycle = 60;
	float Pi = 3.1415f;
	// 浮遊の振幅
	float amplitude = 1.0f;

	// トロッコの動き
	bool Move_ = false;
	bool careMove_ = false;

	float cartSpeed = 0.0f;
	float tireRotation;

	/// ブロック
	float stage_;

	///タイトル
	std::unique_ptr<Title> title_;
	bool title = false;

	//ゲームスタート
	bool start = false;

	// アルファ値
	float a = 0;
	bool transition_;


	//ランプ
	uint32_t texture_[3];
	uint32_t textureTrue_[3];
	uint32_t textureLight_;

	// ステージ
	Sprite* sprite[3] = {nullptr};
	Sprite* spriteLight;
	Vector2 lightSize_;
	int lightTime_;

	enum class Behavior {
		kTitle,     // タイトル
		kMenuScene, // メニュー
		kGameScene, // ゲームシーン
		kGameClear, // 　ゲームクリア
		kGameOver,  // ゲームオーバー
	};

	Behavior behavior_ = Behavior::kTitle;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	//背景
	Sprite* Background1;
	Sprite* Background2;
	uint32_t textureBackground1_;
	uint32_t textureBackground2_;
	Vector2 BackgroundPos1_;
	Vector2 BackgroundPos2_;
};
