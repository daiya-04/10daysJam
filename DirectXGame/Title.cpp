#include "Title.h"
#include <TextureManager.h>
#include <ImGuiManager.h>

void Title::BackGroundMove() {
	BackgroundPos1_.x -= 4.0f;
	BackgroundPos2_.x -= 4.0f;
	if (BackgroundPos1_.x <= -640.0f) {
		BackgroundPos1_.x = 1920;
	}
	if (BackgroundPos2_.x <= -640.0f) {
		BackgroundPos2_.x = 1920;
	}
	Background1->SetPosition(BackgroundPos1_);
	Background2->SetPosition(BackgroundPos2_);
}

void Title::TitleInitialize() { 
	MenuPos_ = {1920, 720 / 2};
	TirepPos_ = {140, 600};
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
	if (effect ) {
		MenuPos_.x -= 4;
	}
	if (MenuPos_.x <= 320) {
		MenuPos_.x = 320;
		title = true;
		behaviorRequest_ = Behavior::kMenu;
	}
	CartMove();
}

void Title::MenuInitialize(){
	CartPos_ = {200, 580};
	TirepPos_ = {140, 630};
	careMove_ = false;
	Move_ = false;
};

void Title::CartMove() { 
	
	spriteCart->SetPosition(CartPos_);
	for (int i = 0; i < 2; i++) {
		spriteTire[i]->SetPosition({TirepPos_.x + 120 * i, TirepPos_.y});
		spriteTire[i]->SetRotation(tireRotation);
	}
	cycle = float(rand() % 60 + 30);
	amplitude = float(rand() % 3);

	// 1フレームでのパラメータ加算値
	const float steppe = 3.0f * Pi / cycle;

	// パラメータを1分加算
	floatingParameter_ += steppe;
	// 2πを超えたら0に戻す
	floatingParameter_ = std::fmod(floatingParameter_, 2.0f * Pi);

	CartPos_.x += cartSpeed;
	TirepPos_.x += cartSpeed;
	CartPos_.y += std::sin(floatingParameter_) * amplitude;
	TirepPos_.y += std::sin(floatingParameter_) * amplitude;
	tireRotation += 0.3f;
	

	if (input_->TriggerKey(DIK_SPACE) && !careMove_ && title) {
		cartSpeed = 10.0f;
		Move_ = true;
	}

	if (CartPos_.x > 1480) {
		behaviorRequest_ = Behavior::kGameScene;
		careMove_ = true;
		
	}
	
	


}

void Title::GameSceneInitialize() { 	
	CartPos_ = {200, 550};
	TirepPos_ = {140, 600};
	careMove_ = false;
	game_ = true;
	Move_ = false;
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
	texture_[0] = TextureManager::Load("title/stage1.png");
	texture_[1] = TextureManager::Load("title/stage2.png");
	texture_[2] = TextureManager::Load("title/stage3.png");
	textureBackground1_ = TextureManager::Load("block/backGround.png");
	textureBackground2_ = TextureManager::Load("block/backGround.png");
	textureTitle_ = TextureManager::Load("title/title.png");
	textureCart_ = TextureManager::Load("title/cart.png");
	textureTire_ = TextureManager::Load("title/tire.png");
	
	

	for (int i = 0; i < 3; i++) {
		sprite[i] =
		    Sprite::Create(texture_[i], {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		
	}
	for (int i = 0; i < 2; i++) {
		spriteTire[i] = Sprite::Create(textureTire_, {200, 600}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	}
	Background1 = Sprite::Create(textureBackground1_, {1280/2,720/2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	Background2 = Sprite::Create(textureBackground2_, {1280/2,720/2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	spriteTitle = Sprite::Create(textureTitle_, {1300 , 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	spriteCart = Sprite::Create(textureCart_, {200, 600}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	
	input_ = Input::GetInstance();

	time = 20;
	pos = {1540 , 720 / 2};
	BackgroundPos1_ = {1280 / 2, 720 / 2};
	BackgroundPos2_ = {1920 , 720 / 2};
	
	

	behaviorRequest_ = Behavior::kTitle;
}

void Title::Update() {
	
	BackGroundMove();
	

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
		CartMove();
		break;
	case Behavior::kGameScene:
		GameSceneInitialize();
		break;
	}

	
	ImGui::Begin("Title");
	ImGui::Text("%f", CartPos_.x);
	ImGui::Text("%f", CartPos_.y);
	ImGui::Text("careMove_%d", careMove_);
	ImGui::Text("%d", title);
	ImGui::End();

}

void Title::Draw() { 
	Background1->Draw();
	Background2->Draw();
	if (!title) {
		
		spriteTitle->Draw();
		for (int i = 0; i < 3; i++) {
			sprite[i]->Draw();
		}
	
		
	}

	spriteCart->Draw();
	for (int i = 0; i < 2; i++) {
		spriteTire[i]->Draw();
	}
	
}