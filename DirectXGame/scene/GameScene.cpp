#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include <ImGuiManager.h>

void GameScene::StageSelect() {
	block_->SetStage(stage_);
	block_->SetStart(start);
	if (input_->TriggerKey(DIK_LEFTARROW)) {
		stage_ -= 1.0f;
	} else if (input_->TriggerKey(DIK_RIGHTARROW)) {
		stage_ += 1.0f;
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
	}

	
}

GameScene::GameScene() {
	a = 0;
	transition_ = false;
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
		start = true;
	}else if (transition_ && !start) {
		a += 0.01f;
	}

	/*
	ImGui::Begin("Debug1");
	ImGui::Text("%f", a);
	ImGui::Text("%d", start);
	ImGui::End();*/
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
	block_->Draw();
	if (!start) {
		spriteTransition_->Draw();
	}
	
	

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
