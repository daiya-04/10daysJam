#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>

void GameScene::StageSelect() {
	block_->SetStage(stage_);
	block_->SetStart(start);

	--lightTime_;
	spriteLight->SetSize(lightSize_);

	//ランプ設定
	for (int i = 0; i < 3; i++) {
		sprite[i] = Sprite::Create(
		    texture_[i], {float(320 + 320 * i), 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	}

	if (lightTime_ < -50) {
		lightTime_ = 50;
	}
	if (lightTime_ < 0) {
		lightSize_.x -= 1.0f;
		lightSize_.y -= 1.0f;
	} else {
		lightSize_.x += 1.0f;
		lightSize_.y += 1.0f;
	}

	if (stage_ <= 1) {
		sprite[0] =
		    Sprite::Create(textureTrue_[0], {320, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		spriteLight->SetPosition({320, 360});
	} else if (stage_ <= 2) {
		sprite[1] =
		    Sprite::Create(textureTrue_[1], {320 * 2, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		spriteLight->SetPosition({320 * 2, 360});
	} else if (stage_ <= 3) {
		sprite[2] =
		    Sprite::Create(textureTrue_[2], {320 * 3, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		spriteLight->SetPosition({320 * 3, 360});
	}

	//ステージ選択
	if (!title_->GetMove()) {
		if (input_->TriggerKey(DIK_LEFTARROW)) {
			stage_ -= 1.0f;
		} else if (input_->TriggerKey(DIK_RIGHTARROW)) {
			stage_ += 1.0f;
		}
	}

	if (stage_ >= 3) {
		stage_ = 3;
	} else if (stage_ <= 1) {
		stage_ = 1;
	}

	if (title_->GetCart()) {
		transition_ = true;
		
	}

	if (start) {
		start = block_->GetMenu();
		title_->SetGame(start);
		transition_ = false;
		a = 0;
	}

	
}

//タイトル初期化
void GameScene::BehaviorTitleInitialize() { 
	title = false;
}

// ゲームシーン初期化
void GameScene::BehaviorSceneInitialize() {
	a = 0; 
}

// クリア初期化
void GameScene::BehaviorClearInitialize() {}

// オーバー初期化
void GameScene::BehaviorOverInitialize() {}

//タイトル
void GameScene::BehaviorTitleUpdata() {
	
}

//ゲームシーン
void GameScene::BehaviorSceneUpdata() {
	
}

//クリア
void GameScene::BehaviorClearUpdata() {}

// オーバー
void GameScene::BehaviorOverUpdata() {}

GameScene::GameScene() {
	a = 0;
	transition_ = false;
	lightSize_ = {250, 250};
	lightTime_ = 50;
}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	title_ = std::make_unique<Title>();
	title_->Initialize();

	block_ = std::make_unique<Block>();
	// ブロックの初期化
	block_->Initialize();
	
	textureTransition_ = TextureManager::Load("title/black.png");
	spriteTransition_ = Sprite::Create(textureTransition_, {1280/2,720/2}, {1.0f, 1.0f, 1.0f, 0.0f}, {0.5f, 0.5f});
	
	//ランプ
	texture_[0] = TextureManager::Load("title/stage1.png");
	texture_[1] = TextureManager::Load("title/stage2.png");
	texture_[2] = TextureManager::Load("title/stage3.png");
	textureTrue_[0] = TextureManager::Load("title/TrueStage1.png");
	textureTrue_[1] = TextureManager::Load("title/TrueStage2.png");
	textureTrue_[2] = TextureManager::Load("title/TrueStage3.png");
	//光
	textureLight_ = TextureManager::Load("title/Light.png");

	// 光
	spriteLight =
	    Sprite::Create(textureLight_, {-200, 600}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	for (int i = 0; i < 3; i++) {
		sprite[i] = Sprite::Create(texture_[i], {-1280, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	}

	for (int i = 0; i < 3; i++) {
		sprite[i]->SetPosition({float(320 + 320 * i), 360});
	}

	
	behaviorRequest_ = Behavior::kTitle;
}

void GameScene::Update() {
	spriteTransition_->SetColor({1.0f, 1.0f, 1.0f, a});
	title_->Update();
	title = title_->GetTitle();
	if (title) {
		StageSelect();
		block_->Update();
	}
	
	if (a >= 1.0f) {
		behaviorRequest_ = Behavior::kGameScene;

	} else if (transition_ && !start) {
		a += 0.01f;
	}

	
	

	if (behaviorRequest_) {
		// 振る舞い変更
		behavior_ = behaviorRequest_.value();
		// 各振る舞いごとの初期化
		switch (behavior_) {
		case Behavior::kTitle:
		default:
			BehaviorTitleInitialize();
			break;
		case Behavior::kGameScene:
			BehaviorSceneInitialize();
			break;

		case Behavior::kGameClear:
			BehaviorClearInitialize();
			break;
		case Behavior::kGameOver:
			BehaviorOverInitialize();
			break;
		}

		// 振る舞いリセット
		behaviorRequest_ = std::nullopt;
	}

	// BaseCharacter::Update();

	// 各振る舞いごとの初期化
	switch (behavior_) {
	case Behavior::kTitle:
	default:
		BehaviorTitleUpdata();
		break;
	case Behavior::kGameScene:
		BehaviorSceneUpdata();
		break;
	case Behavior::kGameClear:
		BehaviorClearUpdata();
		break;
	case Behavior::kGameOver:
		BehaviorOverUpdata();
		break;
	}

	
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	
	title_->Draw();
	if (title) {
		spriteLight->Draw();
		for (int i = 0; i < 3; i++) {
			sprite[i]->Draw();
		}
	}
	

	block_->Draw();
	spriteTransition_->Draw();
	
	
	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
