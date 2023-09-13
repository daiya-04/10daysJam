#include "Player.h"
#include <assert.h>
#include <cmath>
#include "Easing.h"

void Player::Initialize(Sprite* sprite) {
	BaseObject::Initialize(sprite);
	

	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	
	size_ = {200.0f, 280.0f};
	position_ = {200.0f, 600.0f - (size_.y / 2.0f)};
	sprite_->SetSize({size_.x, size_.y});
	sprite_->SetAnchorPoint({0.5f, 0.5f});

	playerTexture_ = TextureManager::Load("player.png");
	player_.reset(Sprite::Create(playerTexture_, {}));
	player_->SetSize({player_->GetSize().x / 3.0f, player_->GetSize().y});
	playerPos_ = {240.0f, 600.0f - (player_->GetSize().y / 2.0f)};
	player_->SetTextureRect({}, player_->GetSize());
	player_->SetAnchorPoint({0.5f, 0.5f});

	chargeSoundData_ = audio_->LoadWave("charge.mp3");
	chargeMaxSoundData_ = audio_->LoadWave("chargeMax.mp3");

}

void Player::Update() {

	random = {};

	if (playerBehaviorRequest_) {
		behavior_ = playerBehaviorRequest_.value();
		switch (behavior_) {
			case Behavior::kRoot:
		    default:
			    RootInitialize();
				break;
		    case Behavior::kAttack:
			    AttackInitialize();
				break;
		}
		playerBehaviorRequest_ = std::nullopt;
	}

	switch (behavior_) {
		case Behavior::kRoot:
	    default:
		    RootUpdate();
			break;
	    case Behavior::kAttack:
		    AttackUpdate();
			break;
	}

	

	

	sprite_->SetPosition({position_.x, position_.y});
	player_->SetPosition({playerPos_.x + random.x, playerPos_.y + random.y});
}

void Player::Draw() {

	//sprite_->Draw();
	player_->Draw();

}

void Player::RootInitialize() {

	num = 0.0f;
	easeStartPos = easeEndPos;
	easeEndPos = {200.0f, 600.0f - (size_.y / 2.0f)};
	player_->SetTextureRect({}, player_->GetSize());

}

void Player::RootUpdate() {

	preKey_ = key_;
	
	if (input_->PushKey(DIK_SPACE)) {
		key_ = true;
		player_->SetTextureRect({player_->GetSize().x, 0.0f}, player_->GetSize());
		
		if (num == 1.0f) {
			charge++;
			if (charge > 10) {
				if (!audio_->IsPlaying(soundHandle_)) {
					soundHandle_ = audio_->PlayWave(chargeSoundData_, false, 0.5f);
				}
			}
			if (charge == 45) {
				chargeMaxSoundHandle_ = audio_->PlayWave(chargeMaxSoundData_, false, 0.5f);
				/*if (!audio_->IsPlaying(chargeMaxSoundHandle_)) {
					
				}*/
			}
			if (charge > 45) {
				random.x = static_cast<float>(std::rand() % randomRange + 1);
				random.y = static_cast<float>(std::rand() % randomRange + 1);
			}
		}
	} else {
		key_ = false;
	}
	
	if (preKey_ && !key_) {
		if (num == 1.0f) {
     		playerBehaviorRequest_ = Behavior::kAttack;
			if (charge <= 30) {
				type_ = Type::Soft;
			} else {
				type_ = Type::Hard;
			}
			charge = 0;
		}
		audio_->StopWave(soundHandle_);
	}
	

	if (num != 1.0f) {
		num += 0.2f;
		num = min(num, 1.0f);
		float T = Easing::easeInSine(num);
		position_ = Lerp(T, easeStartPos, easeEndPos);
		
	}

}

void Player::AttackInitialize() {

	Vec2 interval = {200.0f, 0.0f};
	num = 0.0f;
	easeStartPos = position_;
	easeEndPos = easeStartPos + interval;
	player_->SetTextureRect({player_->GetSize().x * 2.0f, 0.0f}, player_->GetSize());
}

void Player::AttackUpdate() {

	if (num == 1.0f) {
		playerBehaviorRequest_ = Behavior::kRoot;
		return;
	}

	num += 1.0f / 5.0f;
	num = min(num, 1.0f);
	float T = Easing::easeInSine(num);
	position_ = Lerp(T, easeStartPos, easeEndPos);
	
}

void Player::SceneInitialize() {

	position_ = {200.0f, 600.0f - (size_.y / 2.0f)};
	sprite_->SetPosition({position_.x, position_.y});
	player_->SetPosition({playerPos_.x, playerPos_.y});
	playerBehaviorRequest_ = Behavior::kRoot;
	RootInitialize();
	key_ = false;
	preKey_ = false;
	charge = 0;

}