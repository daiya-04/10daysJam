#pragma once
#include "Sprite.h"
#include "BaseObject.h"
#include "Vec2.h"
#include "Input.h"
#include <optional>
#include <memory>
#include "TextureManager.h"
#include "Audio.h"

class Player : public BaseObject {
private:

	/*const float moveLength = 200.0f;
	const float LeftLimit = 640.0f - moveLength;
	const float RightLimit = 640.0f + moveLength;*/

	//行動パターン
	enum class Behavior {
		kRoot,
		kAttack,
	};

	Behavior behavior_ = Behavior::kRoot;
	std::optional<Behavior> behaviorRequest_ = std::nullopt;

	Input* input_ = nullptr;

	std::unique_ptr<Sprite> player_;
	uint32_t playerTexture_ = 0;

	//位置
	Vec2 position_;
	Vec2 playerPos_;
	//サイズ
	Vec2 size_;

	//イージング用
	float num = 1.0f;
	Vec2 easeStartPos{};
	Vec2 easeEndPos{};

	
	Type type_{};

	bool key_ = false;
	bool preKey_ = false;
	int charge = 0;

	Vec2 random{};
	int randomRange = 20;

	Audio* audio_ = nullptr;
	uint32_t chargeSoundData_ = 0;
	uint32_t soundHandle_ = 0;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="sprite">スプライトデータ</param>
	void Initialize(Sprite* sprite)override;
	/// <summary>
	/// 更新
	/// </summary>
	void Update()override;
	/// <summary>
	/// 描画
	/// </summary>
	void Draw()override;
	/// <summary>
	/// 通常行動初期化
	/// </summary>
	void RootInitialize();
	/// <summary>
	/// 通常行動更新
	/// </summary>
	void RootUpdate();
	/// <summary>
	/// 攻撃行動初期化
	/// </summary>
	void AttackInitialize();
	/// <summary>
	/// 攻撃行動更新
	/// </summary>
	void AttackUpdate();


	Vec2 GetPosition() { return position_; }
	Vec2 GetSize() { return size_; }
	Type GetType() { return type_; }

};
