#include "Title.h"
#include <TextureManager.h>
#include <ImGuiManager.h>



void Title::TitleInitialize() { 
	MenuPos_ = {1920, 720 / 2};
	
	move_ = true;
	
}

void Title::TitleMove() { 
	
	if (!effect) {
		pos.x -= 4.0f;
	} else {
		pos.x -= 4.0f;
	}
	
	


	if (pos.x <= 640 && !effect) {
		pos.x = 640.0f;
		move_ = false;
	}

	spriteTitle->SetPosition(pos); 
}

void Title::MenuMove() {
	for (int i = 0; i < 3; i++) {
		sprite[i]->SetPosition({MenuPos_.x + 320*i, MenuPos_.y});
	}
	spriteBoard_->SetPosition({MenuPos_.x + 320 , 100});
	if (effect ) {
		MenuPos_.x -= 4;
	}
	if (MenuPos_.x < 320) {
		MenuPos_.x = 320;
		title = true;
		behaviorRequest_ = Behavior::kMenu;
	}
	
}

void Title::MenuInitialize(){
	
};



void Title::GameSceneInitialize() { 	
	
	game_ = true;
	
}
void Title::GameSceneUpdata() {
	if (!game_) {
		behaviorRequest_ = Behavior::kMenu;
	}
}

void Title::Effect() {
	
	if (effect) {
		
		pos.y += velo.y;
		--time;
		velo.y = 0;
		if (time >= 0) {
			velo.y = 5.0f;
		} else if (time < -10) {
			velo.y -= 100.0f;
			
		}
	} else {
		pos.x += velo.x;
	}


}

void Title::Initialize() { 
	audio_ = Audio::GetInstance();

	texture_[0] = TextureManager::Load("title/stage1.png");
	texture_[1] = TextureManager::Load("title/stage2.png");
	texture_[2] = TextureManager::Load("title/stage3.png");
	textureTitle_ = TextureManager::Load("title/title.png");
	
	// 看板
	textureBoard_ = TextureManager::Load("signboard.png");
	spriteBoard_ =
	    Sprite::Create(textureBoard_, {640, 100}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	

	spriteTitle = Sprite::Create(textureTitle_, {1300, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	for (int i = 0; i < 3; i++) {
		sprite[i] =
		    Sprite::Create(texture_[i], {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		
	}
	
	decisionSEData_ = audio_->LoadWave("decision.mp3");
	
	input_ = Input::GetInstance();

	time = 20;
	pos = {1540 , 720 / 2};
	
	spaceCharTexture_ = TextureManager::Load("space.png");
	spaceCharSprite_ = Sprite::Create(spaceCharTexture_, {440, 500});

	behaviorRequest_ = Behavior::kTitle;
}

void Title::Update() {
	
	
	

	/*if (move_) {
		TitleMove();
		BackGroundMove();
		MenuMove();
		CartMove();
	}*/
	
	if (!effect && pos.x <= 640) {
		if (input_->TriggerKey(DIK_SPACE)) {
			move_ = true;
			effect = true;
			decisionSEHandle_ = audio_->PlayWave(decisionSEData_, false, 0.1f);
		}
	}
	

	if (behaviorRequest_) {
		// 振る舞い変更
		behavior_ = behaviorRequest_.value();
		// 各振る舞いごとの初期化
		switch (behavior_) {
		case Behavior::kTitle:
		default:
			TitleInitialize();
			MenuInitialize();
			break;
		case Behavior::kMenu:
			//MenuInitialize();
			break;
		case Behavior::kGameScene:
			GameSceneUpdata();
			break;
		
		}

		// 振る舞いリセット
		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_) {
	case Behavior::kTitle:
	default:
		TitleMove();
		MenuMove();
		break;
	case Behavior::kMenu:
		
		break;
	case Behavior::kGameScene:
		GameSceneInitialize();
		break;
	}

#ifdef _DEBUG
	ImGui::Begin("Title");

	ImGui::Text("%f", MenuPos_.x);
	ImGui::End();
#endif // DEBUG

	

}

void Title::Draw() { 
	
	if (!title) {
		
		spriteTitle->Draw();
		for (int i = 0; i < 3; i++) {
			sprite[i]->Draw();
		}
	
		
	}
	
	if (pos.x == 640) {
		spaceCharSprite_->Draw();
	}

	spriteBoard_->Draw();
	
}