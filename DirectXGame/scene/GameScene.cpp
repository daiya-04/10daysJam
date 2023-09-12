#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>

void GameScene::CartMove() {

	spriteCart->SetPosition(CartPos_);
	for (int i = 0; i < 2; i++) {
		spriteTire[i]->SetPosition({TirepPos_.x + 120 * i, TirepPos_.y});
		spriteTire[i]->SetRotation(tireRotation);
	}
	cycle = float(rand() % 60 + 30);
	amplitude = float(rand() % 3);

	// 1フレームでのパラメータ加算値
	const float steppe = 3.0f * Pi / cycle;

	// パラメータを1分加算
	floatingParameter_ += steppe;
	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * Pi);

	CartPos_.x += cartSpeed;
	TirepPos_.x += cartSpeed;
	CartPos_.y += std::sin(floatingParameter_) * amplitude;
	TirepPos_.y += std::sin(floatingParameter_) * amplitude;
	tireRotation += 0.3f;

	if (input_->TriggerKey(DIK_SPACE) && !careMove_ && title) {
		cartSpeed = 10.0f;
		Move_ = true;
	}

	if (CartPos_.x > 1480) {
		careMove_ = true;
	}
}

void GameScene::BackGroundMove() {
	BackgroundPos1_.x -= 4.0f;
	BackgroundPos2_.x -= 4.0f;
	if (BackgroundPos1_.x <= -640.0f) {
		BackgroundPos1_.x = 1920;
	}
	if (BackgroundPos2_.x <= -640.0f) {
		BackgroundPos2_.x = 1920;
	}
	Background1->SetPosition(BackgroundPos1_);
	Background2->SetPosition(BackgroundPos2_);
}

void GameScene::StageSelect() {
	

	--lightTime_;
	spriteLight->SetSize(lightSize_);

	// ランプ設定
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
	if (!Move_) {
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

	

	
}

//タイトル初期化
void GameScene::BehaviorTitleInitialize() { 
	BackgroundPos1_ = {1280 / 2, 720 / 2};
	BackgroundPos2_ = {1920, 720 / 2};
	CartPos_ = {200, 580};
	TirepPos_ = {140, 630};
	
}

//メニュー初期化
void GameScene::BehaviorMenuInitialize() {
	a = 0;
	careMove_ = false;
	Move_ = false;
	// 光
	spriteLight =
	    Sprite::Create(textureLight_, {-200, 600}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	for (int i = 0; i < 3; i++) {
		sprite[i]->SetPosition({float(320 + 320 * i), 360});
	}
	textureBackground1_ = TextureManager::Load("block/backGround.png");
	textureBackground2_ = TextureManager::Load("block/backGround.png");
	Background1 = Sprite::Create(
	    textureBackground1_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	Background2 = Sprite::Create(
	    textureBackground2_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
}

// ゲームシーン初期化
void GameScene::BehaviorSceneInitialize() {
	cartSpeed = 0.0f;
	CartPos_ = {200, 580};
	TirepPos_ = {140, 630};
	careMove_ = false;
	Move_ = false;
	textureBackground1_ = TextureManager::Load("title/title1.png");
	textureBackground2_ = TextureManager::Load("title/title2.png");
	Background1 = Sprite::Create(
	    textureBackground1_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	Background2 = Sprite::Create(
	    textureBackground2_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
}

// クリア初期化
void GameScene::BehaviorClearInitialize() {}

// オーバー初期化
void GameScene::BehaviorOverInitialize() {
}

//タイトル
void GameScene::BehaviorTitleUpdata() { 
	title_->Update();
	if (careMove_) {
		transition_ = true;
	}

	if (start) {
		title_->SetGame(start);
		transition_ = false;
		a = 0;
	}
	title = title_->GetTitle();
	
	if (title) {
		behaviorRequest_ = Behavior::kMenuScene;
	}
}

//メニュー
void GameScene::BehaviorMenuUpdata() { 
	title_->Update();
	StageSelect(); 
	if (careMove_) {
		if (a < 1) {
			a += 0.01f;

		} else {
			behaviorRequest_ = Behavior::kGameScene;
			a = 1.0f;
		}
	}
}

//ゲームシーン
void GameScene::BehaviorSceneUpdata() { 
		
	if (input_->TriggerKey(DIK_1)) {
		behaviorRequest_ = Behavior::kMenuScene;
	}
	if (a >= 0) {
		a -= 0.01f;
	} else {
		a = 0;
	}
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

	//トロッコ
	textureCart_ = TextureManager::Load("title/cart.png");
	textureTire_ = TextureManager::Load("title/tire.png");
	
	spriteCart = Sprite::Create(textureCart_, {200, 600}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	
	
	//背景
	textureBackground1_ = TextureManager::Load("block/backGround.png");
	textureBackground2_ = TextureManager::Load("block/backGround.png");
	Background1 = Sprite::Create(
	    textureBackground1_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	Background2 = Sprite::Create(
	    textureBackground2_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	

	title_ = std::make_unique<Title>();
	title_->Initialize();

	
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

	for (int i = 0; i < 2; i++) {
		spriteTire[i] =
		    Sprite::Create(textureTire_, {200, 600}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	}
	
	behaviorRequest_ = Behavior::kTitle;
}

void GameScene::Update() {
	BackGroundMove();
	CartMove();

	spriteTransition_->SetColor({1.0f, 1.0f, 1.0f, a});	

	if (behaviorRequest_) {
		// 振る舞い変更
		behavior_ = behaviorRequest_.value();
		// 各振る舞いごとの初期化
		switch (behavior_) {
		case Behavior::kTitle:
		default:
			BehaviorTitleInitialize();
			break;
		case Behavior::kMenuScene:
			BehaviorMenuInitialize();
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
	case Behavior::kMenuScene:
		BehaviorMenuUpdata();
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

	ImGui::Begin("T");
	ImGui::Text("%d", title);
	ImGui::End();
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
	
	Background1->Draw();
	Background2->Draw();
	spriteCart->Draw();

	for (int i = 0; i < 2; i++) {
		spriteTire[i]->Draw();
	}
	spriteLight->Draw();
	for (int i = 0; i < 3; i++) {
		sprite[i]->Draw();
	}


	title_->Draw();
	


	


	spriteTransition_->Draw();
	
	
	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
