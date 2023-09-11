#include "BaseObject.h"
#include <assert.h>

void BaseObject::Initialize(const std::vector<Sprite*>& sprite) {
	
	sprite_ = sprite;

}

void BaseObject::Update() {

}

void BaseObject::Draw() {
	for (int i = 0; i < 50; i++) {
		// モデル描画
		for (Sprite* model : sprite_) {
			model->Draw();
		}
	}
	

}