#include "Score.h"
#include <cmath>

void Score::Initialize(uint32_t texture) {

	texture_ = texture;
	comboTexture_ = TextureManager::Load("combo.png");

	scoreSize = {64.0f, 64.0f};
	comboSize = {96.0f, 96.0f};
	resultScoreSize = {96.0f, 96.0f};
	timerSize = {128.0f, 128.0f};
	texSize = {32.0f, 32.0f};
	//スコア
	for (size_t i = 0; i < kScoreDigits; i++) {
		scoreSprite_[i].reset(Sprite::Create(texture_, {}));
		scoreSprite_[i]->SetSize({scoreSize.x, scoreSize.y});
		//scoreSprite_[i]->SetAnchorPoint({0.5f, 0.5f});
		scoreSprite_[i]->SetTextureRect({}, {texSize.x, texSize.y});
		scoreSprite_[i]->SetPosition({20.0f + scoreSize.x * (float)i, 20.0f});
	}
	//コンボ
	for (size_t i = 0; i < kComboDigits; i++) {
		comboSprite_[i].reset(Sprite::Create(texture_, {}));
		comboSprite_[i]->SetSize({comboSize.x, comboSize.y});
		//comboSprite_[i]->SetAnchorPoint({0.5f, 0.5f});
		comboSprite_[i]->SetTextureRect({}, {texSize.x, texSize.y});
		comboSprite_[i]->SetPosition({250.0f + comboSize.x * (float)i, 270.0f});
	}
	//リザルトスコア
	for (size_t i = 0; i < kScoreDigits; i++) {
		resultScore_[i].reset(Sprite::Create(texture_, {}));
		resultScore_[i]->SetSize({resultScoreSize.x, resultScoreSize.y});
		resultScore_[i]->SetTextureRect({}, {texSize.x, texSize.y});
		resultScore_[i]->SetPosition({250.0f + resultScoreSize.x * (float)i, 270.0f});
	}
	//タイマー
	for (size_t i = 0; i < kTimeDigits; i++) {
		timerSprite_[i].reset(Sprite::Create(texture_, {}));
		timerSprite_[i]->SetSize({timerSize.x, timerSize.y});
		timerSprite_[i]->SetTextureRect({}, {texSize.x, texSize.y});
		timerSprite_[i]->SetPosition({900.0f + timerSize.x * (float)i, 20.0f});
	}
	
	Vec2 comboCharPos = {
	    comboSprite_[(kComboDigits - 1)]->GetPosition().x + comboSprite_[(kComboDigits - 1)]->GetSize().x,
	    comboSprite_[(kComboDigits - 1)]->GetPosition().y + (comboSprite_[(kComboDigits - 1)]->GetSize().y / 2.0f)
	};
	comboCharSprite_.reset(Sprite::Create(comboTexture_, {comboCharPos.x, comboCharPos.y}));

}

void Score::Update() {

	int scoreNum = score_;
	int comboNum = combo_;
	int time = timer_ / 60;
	//スコア
	for (size_t i = 0; i < kScoreDigits; i++) {
		eachScoreNumber[i] = scoreNum / (int)std::powf(10.0f, (float)kScoreDigits - (1.0f + (float)i));
		scoreSprite_[i]->SetTextureRect({texSize.x * (float)eachScoreNumber[i], 0.0f}, {texSize.x, texSize.y});
		scoreNum %= (int)std::powf(10.0f, (float)kScoreDigits - (1.0f + (float)i));
	}
	//コンボ
	for (size_t i = 0; i < kComboDigits; i++) {
		eachComboNumber[i] = comboNum / (int)std::powf(10.0f, (float)kComboDigits - (1.0f + (float)i));
		comboSprite_[i]->SetTextureRect({texSize.x * (float)eachComboNumber[i], 0.0f}, {texSize.x, texSize.y});
		comboNum %= (int)std::powf(10.0f, (float)kComboDigits - (1.0f + (float)i));
	}
	//タイマー
	for (size_t i = 0; i < kTimeDigits; i++) {
		eachTimerNumber[i] = time / (int)std::powf(10.0f, (float)kTimeDigits - (1.0f + (float)i));
		timerSprite_[i]->SetTextureRect({texSize.x * (float)eachTimerNumber[i], 0.0f}, {texSize.x, texSize.y});
		time %= (int)std::powf(10.0f, (float)kTimeDigits - (1.0f + (float)i));
	}

	timer_--;
}

void Score::Draw() {

	if (combo_ >= 100) {
		comboSprite_[0]->Draw();
	}
	if (combo_ >= 10) {
		comboSprite_[1]->Draw();
	}
	if (combo_ > 0) {
		comboSprite_[2]->Draw();
		comboCharSprite_->Draw();
	}

	for (size_t i = 0; i < kScoreDigits; i++) {
		scoreSprite_[i]->Draw();
	}

	if (timer_ >= (60 * 10)) {
		timerSprite_[0]->Draw();
	}
	timerSprite_[1]->Draw();
}

void Score::AddCombo() { combo_++; }

void Score::AddScore() { score_ += fixedScore * combo_; }

void Score::ComboReset() { combo_ = 0; }

void Score::SetResultScore() {

	resultScore = score_;
	for (size_t i = 0; i < kScoreDigits; i++) {
		eachResultScoreNum[i] = resultScore / (int)std::powf(10.0f, (float)kScoreDigits - (1.0f + (float)i));
		resultScore_[i]->SetTextureRect({texSize.x * (float)eachResultScoreNum[i], 0.0f}, {texSize.x, texSize.y});
		resultScore %= (int)std::powf(10.0f, (float)kScoreDigits - (1.0f + (float)i));
	}
}

void Score::SetTimer(int timer) {

	timer_ = timer;
	int time = timer / 60;
	// タイマー
	for (size_t i = 0; i < kTimeDigits; i++) {
		eachTimerNumber[i] = time / (int)std::powf(10.0f, (float)kTimeDigits - (1.0f + (float)i));
		timerSprite_[i]->SetTextureRect(
		    {texSize.x * (float)eachTimerNumber[i], 0.0f}, {texSize.x, texSize.y});
		time %= (int)std::powf(10.0f, (float)kTimeDigits - (1.0f + (float)i));
	}

}

void Score::ResultScoreDraw() {
	for (size_t i = 0; i < kScoreDigits; i++) {
		resultScore_[i]->Draw();
	}
}