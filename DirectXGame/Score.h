#pragma once
#include "Sprite.h"
#include "Vec2.h"
#include <vector>
#include <memory>
#include "TextureManager.h"

class Score {
private:
	//スコアの桁数
	static const int kScoreDigits = 8;
	//コンボの桁数
	static const int kComboDigits = 3;
	//時間の桁数
	static const int kTimeDigits = 2;
	const int fixedScore = 100;

	uint32_t texture_ = 0;
	uint32_t comboTexture_ = 0;

	std::vector<std::unique_ptr<Sprite>> scoreSprite_{kScoreDigits};
	std::vector<std::unique_ptr<Sprite>> comboSprite_{kComboDigits};
	std::vector<std::unique_ptr<Sprite>> resultScore_{kScoreDigits};
	std::vector<std::unique_ptr<Sprite>> timerSprite_{kTimeDigits};
	std::unique_ptr<Sprite> comboCharSprite_;

	int combo_ = 0;
	int score_ = 0;
	int resultScore = 0;
	int timer_ = 0;
	
	int eachScoreNumber[kScoreDigits]{};
	int eachComboNumber[kComboDigits]{};
	int eachResultScoreNum[kScoreDigits]{};
	int eachTimerNumber[kTimeDigits]{};

	Vec2 texSize{};

	Vec2 scoreSize{};
	Vec2 comboSize{};
	Vec2 resultScoreSize{};
	Vec2 timerSize{};


public:

	void Initialize(uint32_t texture);

	void Update();

	void Draw();

	void ResultScoreDraw();

	void AddCombo();

	void AddScore();

	void ComboReset();

	void SetScore(int score) { score_ = score; }
	void SetCombo(int combo) { combo_ = combo; }
	void SetTimer(int timer);
	void SetResultScore();

	int GetScore() { return score_; }
	int GetTimer() { return timer_; }
};
