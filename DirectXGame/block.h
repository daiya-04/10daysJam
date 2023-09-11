#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "BaseObject.h"
#include <optional>


/// <summary>
/// ゲームシーン
/// </summary>
class Block{

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	Block();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Block();

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



	void SetStage(const float stage) { 
		stage_ = stage;
	}
	
	//メニュー初期化
	void MenuInitialize();

	void MenuUpdata();

	void Stage1Initialize();

	void Stage2Initialize();

	void Stage3Initialize();

	void Stage4Initialize();

	void stage1();
	void stage2();
	void stage3();
	void stage4();

	void blockBreak();

	void BreackEffect(int lane);

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t textureWhite_;
	uint32_t textureRed_;
	uint32_t textureBlue_;
	uint32_t textureGreen_;
	uint32_t textureYellow_;

	float pos = 720;
	float kSpeed;

	//画像番号
	int white = 0;
	int red = 1;
	int blue = 2;
	int green = 3;
	int yellow = 4;
	
	//レーン
	int lane1[50];
	int lane2[50];
	int lane3[50];

	//ブロックの番号
	enum {
		NONE = 0,    // 0
		NORMALBLOCK, // 1
		REDBLOCK,    // 2
		BLUEBLOCK,   // 3
		GREENBLOCK,  // 4
		YELLOWBLOCK  // 5
	};

	/// ブロック
	//れーん1
	Sprite* white1_[50] = {nullptr};
	Sprite* red1_[50] = {nullptr};
	Sprite* blue1_[50] = {nullptr};
	Sprite* yellow1_[50] = {nullptr};
	Sprite* green1_[50] = {nullptr};
	// れーん2
	Sprite* white2_[50] = {nullptr};
	Sprite* red2_[50] = {nullptr};
	Sprite* blue2_[50] = {nullptr};
	Sprite* yellow2_[50] = {nullptr};
	Sprite* green2_[50] = {nullptr};
	// れーん3
	Sprite* white3_[50] = {nullptr};
	Sprite* red3_[50] = {nullptr};
	Sprite* blue3_[50] = {nullptr};
	Sprite* yellow3_[50] = {nullptr};
	Sprite* green3_[50] = {nullptr};


	// 振る舞い
	enum class Behavior {
		kRoot,         // メニュー
		kStage1,        // ステージ1
		kStage2, // ステージ2
		kStage3, // ステージ3
		kStage4, // ステージ４
	};

	Behavior behavior_ = Behavior::kRoot;
	// 次の振る舞いリクエスト
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	float stage_;
	bool menu_;

	
	bool effect_ = false;
	Vector2 velocity[15];
	Vector2 effectPos[15];
};
