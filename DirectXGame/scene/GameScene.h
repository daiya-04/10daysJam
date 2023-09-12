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

	void StageSelect();


		// タイトル初期化
	void BehaviorTitleInitialize();

	// シーン初期化
	void BehaviorSceneInitialize();

	// クリア初期化
	void BehaviorClearInitialize();

	// オーバー初期化
	void BehaviorOverInitialize();

	// タイトル
	void BehaviorTitleUpdata();

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
	
	/// ブロック
	std::unique_ptr<Block> block_;
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
		kGameScene, // ゲームシーン
		kGameClear, // 　ゲームクリア
		kGameOver,  // ゲームオーバー
	};

	Behavior behavior_ = Behavior::kTitle;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

};
