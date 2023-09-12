#include "Score.h"
#include <cmath>

void Score::Initialize(uint32_t texture) {

	texture_ = texture;

	scoreSize = {64.0f, 64.0f};
	comboSize = {96.0f, 96.0f};
	texSize = {32.0f, 32.0f};

	for (size_t i = 0; i < kScoreDigits; i++) {
		scoreSprite_[i].reset(Sprite::Create(texture_, {}));
		scoreSprite_[i]->SetSize({scoreSize.x, scoreSize.y});
		//scoreSprite_[i]->SetAnchorPoint({0.5f, 0.5f});
		scoreSprite_[i]->SetTextureRect({}, {texSize.x, texSize.y});
		scoreSprite_[i]->SetPosition({20.0f + (scoreSize.x * (3.0f / 4.0f)) * (float)i, 20.0f});
	}
	for (size_t i = 0; i < kComboDigits; i++) {
		comboSprite_[i].reset(Sprite::Create(texture_, {}));
		comboSprite_[i]->SetSize({comboSize.x, scoreSize.y});
		//comboSprite_[i]->SetAnchorPoint({0.5f, 0.5f});
		comboSprite_[i]->SetTextureRect({}, {texSize.x, texSize.y});
		comboSprite_[i]->SetPosition({250.0f + (comboSize.x * (2.0f / 3.0f)) * (float)i, 270.0f});
	}

	

}

void Score::Update() {

	int scoreNum = score_;
	int comboNum = combo_;

	for (size_t i = 0; i < kScoreDigits; i++) {
		eachScoreNumber[i] = scoreNum / (int)std::powf(10.0f, (float)kScoreDigits - (1.0f + (float)i));
		scoreSprite_[i]->SetTextureRect({texSize.x * (float)eachScoreNumber[i], 0.0f}, {texSize.x, texSize.y});
		scoreNum %= (int)std::powf(10.0f, (float)kScoreDigits - (1.0f + (float)i));
	}

	for (size_t i = 0; i < kComboDigits; i++) {
		eachComboNumber[i] = comboNum / (int)std::powf(10.0f, (float)kComboDigits - (1.0f + (float)i));
		comboSprite_[i]->SetTextureRect({texSize.x * (float)eachComboNumber[i], 0.0f}, {texSize.x, texSize.y});
		comboNum %= (int)std::powf(10.0f, (float)kComboDigits - (1.0f + (float)i));
	}
	

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
	}

	for (size_t i = 0; i < kScoreDigits; i++) {
		scoreSprite_[i]->Draw();
	}
}

void Score::AddCombo() { combo_++; }

void Score::AddScore() { score_ += fixedScore * combo_; }

void Score::ComboReset() { combo_ = 0; }