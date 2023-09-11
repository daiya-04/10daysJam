#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "Rock.h"
#include <memory>
#include <list>
#include <vector>
#include "Vec2.h"
#include <sstream>

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

	void CollisionCheck();

	void RockPop(uint32_t texture, Type type);

	void LoadRockPopData(const std::string& fileName);

	void RockPopCommand();

	

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	const std::string kDirectoryPath = "./Resources/RockPop/";
	int order = 1;
	

	//プレイヤー
	uint32_t playerTexture_ = 0;
	std::unique_ptr<Player> player_;
	std::unique_ptr<Sprite> playerSprite_;

	//岩
	uint32_t rockSoftTexture_ = 0;
	uint32_t rockHardTexture_ = 0;
	static const int rockNum = 5;
	std::list<std::unique_ptr<Rock>> rock_;
	int num = 0;
	std::stringstream rockPopCommands;

	//背景
	uint32_t stage1_bgTexture_ = 0;
	uint32_t stage2_bgTexture_ = 0;
	std::unique_ptr<Sprite> backGround_;
	Vec2 position_{};
	Vec2 scroll{};
	bool isMove_ = false;
	std::optional<bool> moveRequest_ = std::nullopt;
	float num_ = 0.0f;
	Vec2 easeStartPos{};
	Vec2 easeEndPos{};

	//音
	uint32_t breakSoundData_ = 0;
	uint32_t breakMissSoundData_ = 0;
	uint32_t stage1BgmData_ = 0;

	uint32_t breakMissSoundHandle_ = 0;
	uint32_t breakSoundHandle_ = 0;
	uint32_t stage1Bgmhandle_ = 0;

};
