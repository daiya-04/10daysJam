#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>
#include <time.h>
#include <fstream>
#include "Easing.h"

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

	// ステージ選択
	if (!Move_) {
		if (input_->TriggerKey(DIK_LEFTARROW)) {
			stage_ -= 1;
		} else if (input_->TriggerKey(DIK_RIGHTARROW)) {
			stage_ += 1;
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
	scene_ = false;
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

	if (!audio_->IsPlaying(stage1BgmData_)) {
	    stage1Bgmhandle_ = audio_->PlayWave(stage1BgmData_, true, 0.1f);

    }

    rock_.remove_if([](const std::unique_ptr<Rock>& rock) {
	    if (rock->isDead()) {
		    return true;
	    }
	    return false;
    });

    CollisionCheck();

    if (input_->TriggerKey(DIK_1)) {
	    backGround_->SetTextureHandle(stage1_bgTexture_);
    }
    if (input_->TriggerKey(DIK_2)) {
	    backGround_->SetTextureHandle(stage2_bgTexture_);
    }

    for (const auto& rocks : rock_) {
	    if (rocks->isDead()) {
		    for (const auto& rock : rock_) {
			    rock->SetRequest();
	    	}
	    }
    }

    player_->Update();
    for (const auto& rock : rock_) {
	    rock->Update();
    }
    score_->Update();

    if (moveRequest_) {
	    Vec2 interval = {1280.0f / 8.0f, 0.0f};
	    easeStartPos = scroll;
	    easeEndPos = scroll - interval;
	    isMove_ = true;
	    moveRequest_ = std::nullopt;
    }

    if (isMove_) { 

	    num_ += 0.1f;
	    num_ = min(num_, 1.0f);
	    float T = Easing::easeInSine(num_);
	    scroll = Lerp(T, easeStartPos, easeEndPos);
	    if (num_ == 1.0f) {
		    isMove_ = false;
	    }

    } else {
	    num_ = 0.0f;
    }

    if (scroll.x <= -1280.0f) {
		scroll.x = 0.0f;
    }
    if (--comboCoolTimer <= 0) {
	    score_->ComboReset();
    }

    backGround_->SetPosition({position_.x + scroll.x, position_.y + scroll.y});

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

	//テクスチャデータの読み込み
    playerTexture_ = TextureManager::Load("white1x1.png");
    rockSoftTexture_ = TextureManager::Load("softRock.png");
    rockHardTexture_ = TextureManager::Load("hardRock.png");
    stage1_bgTexture_ = TextureManager::Load("1s.png");
    stage2_bgTexture_ = TextureManager::Load("2s.png");
    numberTexture_ = TextureManager::Load("number.png");

	//サウンドデータの読み込み
    breakSoundData_ = audio_->LoadWave("breakRock.mp3");
    breakMissSoundData_ = audio_->LoadWave("breakMiss.mp3");
    stage1BgmData_ = audio_->LoadWave("stage1_BGM.mp3");

	playerSprite_.reset(Sprite::Create(playerTexture_, {}));

    player_ = std::make_unique<Player>();
    player_->Initialize(playerSprite_.get());

	backGround_.reset(Sprite::Create(stage1_bgTexture_, {}));

    score_ = std::make_unique<Score>();
    score_->Initialize(numberTexture_);

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

	switch (stage_) {
	case 1:
		sprite[0] =
		    Sprite::Create(textureTrue_[0], {320, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		spriteLight->SetPosition({320, 360});

		// ステージ読み込み
		if (Move_) {
			LoadRockPopData("stage1");

			for (size_t i = 0; i < static_cast<size_t>(rockNum - 1); i++) {
				RockPopCommand();
				for (const auto& rock : rock_) {
					rock->SetPosition(rock->GetPosition() - rock->GetInterval());
				}
			}
		}
		break; // switch ブロックを終了
	case 2:
		sprite[1] =
		    Sprite::Create(textureTrue_[1], {320 * 2, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		spriteLight->SetPosition({320 * 2, 360});

		// ステージ読み込み
		if (Move_) {
		}
		break; // switch ブロックを終了
	case 3:
		sprite[2] =
		    Sprite::Create(textureTrue_[2], {320 * 3, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		spriteLight->SetPosition({320 * 3, 360});

		// ステージ読み込み
		if (Move_) {
		}
		break; // switch ブロックを終了
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

	for (const auto& rock : rock_) {
	    rock->Draw();
    }
    player_->Draw();
    score_->Draw();


	title_->Draw();
	

	spriteTransition_->Draw();
	
	
	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::CollisionCheck() {

	for (const auto& rocks : rock_) {
		float radius = rocks->GetSize().x / 2.0f;

		if (player_->GetPosition().x <= rocks->GetPosition().x + radius&&
		    player_->GetPosition().x >= rocks->GetPosition().x -radius&&
			player_->GetPosition().y<=rocks->GetPosition().y + radius&&
		    player_->GetPosition().y >= rocks->GetPosition().y - radius) {

			if (!(player_->GetType() == Type::Soft && rocks->GetType() == Type::Hard)) {
				rocks->Break();
				RockPopCommand();
				moveRequest_ = true;
				breakSoundHandle_ = audio_->PlayWave(breakSoundData_, false, 0.5f);
				score_->AddCombo();
				score_->AddScore();
			} else if (player_->GetType() == Type::Soft && rocks->GetType() == Type::Hard) {
				if (!audio_->IsPlaying(breakMissSoundHandle_)) {
					breakMissSoundHandle_ = audio_->PlayWave(breakMissSoundData_, false, 0.5f);
				}
				score_->ComboReset();
			}
			comboCoolTimer = comboCoolTime;
		}
		
	}
}

void GameScene::RockPop(uint32_t texture, Type type) {

	Rock* rock = new Rock();
	rock->Initialize(
	    texture, {400.0f + rock->GetInterval().x * (float)(rockNum - 1), 600.0f - (rock->GetSize().y / 2.0f)},
	    type);
	rock_.push_back(std::unique_ptr<Rock>(rock));

}

void GameScene::LoadRockPopData(const std::string& fileName) {

	std::ifstream file;
	std::string filePath = kDirectoryPath + fileName + ".csv";
	file.open(filePath);
	assert(file.is_open());

	rockPopCommands << file.rdbuf();

	file.close();
}

void GameScene::RockPopCommand() {

	std::string line;

	while (getline(rockPopCommands, line)) {

		std::istringstream line_stream(line);

		std::string word;
		getline(line_stream, word, ',');

		if (word.find("//") == 0) {
			continue;
		}

		if (order == (int)std::atof(word.c_str())) {
			getline(line_stream, word, ',');
			if (word.find("Soft") == 0) {
				RockPop(rockSoftTexture_,Type::Soft);
			} else if (word.find("Hard") == 0) {
				RockPop(rockHardTexture_,Type::Hard);
			}
			order++;
			break;
		}
	}
}