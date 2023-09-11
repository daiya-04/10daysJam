#include "Rock.h"
#include "Easing.h"

void Rock::Initialize(uint32_t texture, const Vec2& position, Type type) {

	type_ = type;
	texture_ = texture;
	
	sprite_.reset(Sprite::Create(texture_, {}));

	position_ = position;
	size_ = {130.0f, 190.0f};
	position_.y = 600.0f - (size_.y / 2.0f);
	sprite_->SetSize({size_.x, size_.y});
	sprite_->SetAnchorPoint({0.5f, 0.5f});
	

}

void Rock::Update() {

	if (moveRequest_) {
		easeStartPos = position_;
		easeEndPos = position_ - posInterval_;
		isMove_ = true;
		moveRequest_ = std::nullopt;
	}

	if (isMove_) {

		num_ += 0.1f;
		num_ = min(num_, 1.0f);
		float T = Easing::easeInSine(num_);
		position_ = Lerp(T, easeStartPos, easeEndPos);
		if (num_ == 1.0f) { isMove_ = false; }

	} else {
		num_ = 0.0f;
	}

	

	sprite_->SetPosition({position_.x,position_.y});
}

void Rock::Draw() {
	sprite_->Draw();
}

void Rock::Break() { isDead_ = true; }