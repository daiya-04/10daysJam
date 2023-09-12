#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <time.h>
#include <fstream>
#include "Easing.h"

GameScene::GameScene() {}

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

	LoadRockPopData("stage1");

	for (size_t i = 0; i < static_cast<size_t>(rockNum - 1); i++) {
		RockPopCommand();
		for (const auto& rock : rock_) {
			rock->SetPosition(rock->GetPosition() - rock->GetInterval());
		}
	}

	backGround_.reset(Sprite::Create(stage1_bgTexture_, {}));

	score_ = std::make_unique<Score>();
	score_->Initialize(numberTexture_);

}

void GameScene::Update() {

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

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	backGround_->Draw();

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

	
	for (const auto& rock : rock_) {
		rock->Draw();
	}
	player_->Draw();
	score_->Draw();

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