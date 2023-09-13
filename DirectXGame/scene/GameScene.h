#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Title.h"
#include "Player.h"
#include "Rock.h"
#include <memory>
#include <list>
#include <vector>
#include "Vec2.h"
#include <sstream>
#include "Score.h"


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

	void CollisionCheck();

    void RockPop(uint32_t texture, Type type);

    void LoadRockPopData(const std::string& fileName);

    void RockPopCommand();

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
	int stage_;

	///タイトル
	std::unique_ptr<Title> title_;
	bool title = false;

	//ゲームスタート
	bool start = false;

	// アルファ値
	float a = 0;
	bool transition_;

	//看板
	uint32_t textureBoard_;
	Sprite* spriteBoard_;


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

	bool scene_ = false;

	const std::string kDirectoryPath = "./Resources/RockPop/";
    int order = 1;
    
    //スコア
    uint32_t numberTexture_ = 0;
    std::unique_ptr<Score> score_;
    const int comboCoolTime = 85;
    int comboCoolTimer = comboCoolTime;

	const int LimitTime = 60 * 30;
	//int timer = LimitTime;
	const int sceneChangeCount = 60 * 2;
	int sceneChangeTimer = sceneChangeCount;
	const int startTime = 60;
	int startCount = startTime;
	uint32_t finishTexture_ = 0;
	std::unique_ptr<Sprite> finishSprite_;
	uint32_t spaceCharTexture_ = 0;
	std::unique_ptr<Sprite> spaceCharSprite_;
    
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

	//タイトルBGM
	uint32_t titleBgmData_ = 0;
	uint32_t titleBGMHandle_ = 0;

	//決定音
	uint32_t decisionSEData_ = 0;
	uint32_t decisionSEHandle_ = 0;
	

};
