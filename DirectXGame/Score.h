#pragma once
#include "Sprite.h"
#include "Vec2.h"
#include <vector>
#include <memory>

class Score {
private:
	//スコアの桁数
	static const int kScoreDigits = 8;
	//コンボの桁数
	static const int kComboDigits = 3;
	const int fixedScore = 100;

	uint32_t texture_ = 0;

	std::vector<std::unique_ptr<Sprite>> scoreSprite_{kScoreDigits};
	std::vector<std::unique_ptr<Sprite>> comboSprite_{kComboDigits};

	int combo_ = 0;
	int score_ = 0;
	
	int eachScoreNumber[kScoreDigits]{};
	int eachComboNumber[kComboDigits]{};

	Vec2 texSize{};

	Vec2 scoreSize{};
	Vec2 comboSize{};


public:

	void Initialize(uint32_t texture);

	void Update();

	void Draw();

	void AddCombo();

	void AddScore();

	void ComboReset();

};
