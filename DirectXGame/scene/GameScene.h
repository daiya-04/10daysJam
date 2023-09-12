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
};
