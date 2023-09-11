#include "Title.h"
#include <TextureManager.h>

void Title::Effect() {
	
	if (effect) {
		pos.x += velo.x;
		pos.y += velo.y;
		--time;
		velo.y = 0;
		if (time >= 0) {
			velo.y = 5.0f;
		} else if (time < -10) {
			velo.y -= 100.0f;
			title = true;
		}
	}


}

void Title::Initialize() { 
	texture_ = TextureManager::Load("title/black.png");
	textureTitle_ = TextureManager::Load("block/red.png");
	
	
	sprite = Sprite::Create(texture_, {1280/2,720/2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	spriteTitle = Sprite::Create(textureTitle_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	
	input_ = Input::GetInstance();
	time = 20;
	pos = {1280 / 2, 720 / 2};
}

void Title::Update() {
	sprite->SetPosition(pos); 
	spriteTitle->SetPosition(pos); 
	if (!effect) {
		if (input_->TriggerKey(DIK_SPACE)) {
			effect = true;
		}
	}
	

	Effect();



}

void Title::Draw() { 
	if (!effect) {
		
	}
	
	sprite->Draw();
	spriteTitle->Draw();
}