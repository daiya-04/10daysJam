#pragma once
#include "Sprite.h"
#include "BaseObject.h"
#include "Vec2.h"
#include <optional>
#include <memory>
#include "TextureManager.h"



class Rock {
private:

	
	//テクスチャ
	uint32_t texture_ = 0u;

	std::unique_ptr<Sprite> sprite_;

	Type type_{};

	//間隔
	Vec2 posInterval_ = {250.0f, 0.0f};
	//位置
	Vec2 position_;
	//サイズ
	Vec2 size_;
	//壊されたか
	bool isDead_ = false;

	bool isMove_ = false;
	float num_ = 0.0f;
	Vec2 easeStartPos{};
	Vec2 easeEndPos{};
	std::optional<bool> moveRequest_ = std::nullopt;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="texture">テクスチャ</param>
	/// <param name="position">生成位置</param>
	/// <param name="type">岩の種類</param>
	void Initialize(uint32_t texture,const Vec2& position,Type type);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 壊された
	/// </summary>
	void Break();
	
	void SetRequest(bool request = true) { moveRequest_ = request; }
	void SetPosition(Vec2 position) { position_ = position; }

	bool isDead() { return isDead_; }
	Type GetType() { return type_; }
	Vec2 GetPosition() { return position_; }
	Vec2 GetSize() { return size_; }
	Vec2 GetInterval() { return posInterval_; }

};
