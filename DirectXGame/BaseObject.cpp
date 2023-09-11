#include "BaseObject.h"
#include <assert.h>

void BaseObject::Initialize(Sprite* sprite) {
	assert(sprite);

	sprite_ = sprite;
	sprite_->Initialize();

}

void BaseObject::Update() {



}

void BaseObject::Draw() {

	sprite_->Draw();

}