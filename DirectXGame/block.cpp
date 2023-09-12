#include "block.h"
#include "ImGuiManager.h"

//メニュー
void Block::MenuInitialize(){
	
	for (int i = 0; i < 50; i++) {
		
		white2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		red2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		blue2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		green2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		yellow2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		
	}
	for (int i = 0; i < 3; i++) {
		sprite[i]->SetPosition({float(320 + 320 * i), 360});
	}
	menu_ = true;
	stage_ = 1;
};
void Block::MenuUpdata(){ 
	
	for (int i = 0; i < 3; i++) {
		sprite[i] = Sprite::Create(
		    texture_[i], {float(320 + 320 * i),360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	}

	if (stage_ == 1 && start_) {
		behaviorRequest_ = Behavior::kStage1;
	} else if (stage_ == 2 && start_) {
		behaviorRequest_ = Behavior::kStage2;
	} else if (stage_ == 3 && start_) {
		behaviorRequest_ = Behavior::kStage3;
	}

	if (stage_ <= 1 ) {
		sprite[0] = Sprite::Create(
		    textureTrue_[0], {320, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	} else if (stage_ <= 2) {
		sprite[1] =
		    Sprite::Create(textureTrue_[1], {320 * 2, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	} else if (stage_ <= 3) {
		sprite[2] =
		    Sprite::Create(textureTrue_[2], {320*3, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	} 

	
	
};

//ステージ
void Block::Stage1Initialize(){ 


	for (int i = 0; i < 15; ++i) {
		velocity[i] = {0, 0};
		hahenPos[i] = {75, 360};
		hahen_[i] = false;
	}
	// レーン１,2,3
	
	int L2[50] = {0, 3, 4, 3, 5, 4, 5, 4, 2, 5, 5, 5, 3, 2, 4, 2, 4, 3, 5, 3, 3, 3, 2, 3, 2};
	
	for (int i = 0; i < 50; i++) {
	
		lane2[i] = L2[i];
		
	}
	pos = 75;
	menu_ = false;
	kSpeed = 65;

	textureBackground1_ = TextureManager::Load("title/title1.png");
	textureBackground2_ = TextureManager::Load("title/title2.png");
	Background1 = Sprite::Create(textureBackground1_, {1280/2,720/2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	Background2 = Sprite::Create(textureBackground2_, {1280/2,720/2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	BackgroundPos1_ = {1280 / 2, 720 / 2};
	BackgroundPos2_ = {1920, 720 / 2};
	
};
void  Block::stage1(){
	Background1->SetPosition(BackgroundPos1_);
	Background2->SetPosition(BackgroundPos2_);
	BackGroundMove();
	blockBreak();
	BreackEffect();
	
	for (int i = 0; i < 50; i++) {

		red2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		blue2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		green2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		yellow2_[i]->SetPosition({pos + (float(i) * 65), (360)});
	}
	
	if (input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kRoot;
	}

	
	
	
};

void Block::Stage2Initialize() { 
	// レーン１,2,3
	
	int L2[50] = {2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 1, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3};
	
	for (int i = 0; i < 50; i++) {
		
		lane2[i] = L2[i];
		
	}
	pos = 75;
	menu_ = false;
	kSpeed = 65;
	textureBackground1_ = TextureManager::Load("title/title1.png");
	textureBackground2_ = TextureManager::Load("title/title2.png");
	Background1 = Sprite::Create(
	    textureBackground1_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	Background2 = Sprite::Create(
	    textureBackground2_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	BackgroundPos1_ = {1280 / 2, 720 / 2};
	BackgroundPos2_ = {1920, 720 / 2};
};
void  Block::stage2(){
	Background1->SetPosition(BackgroundPos1_);
	Background2->SetPosition(BackgroundPos2_);
	blockBreak();

	for (int i = 0; i < 50; i++) {
		
		white2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		red2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		blue2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		green2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		yellow2_[i]->SetPosition({pos + (float(i) * 65), (360)});

	}
	
	if (input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kRoot;
	}
};

void Block::Stage3Initialize() { 
		// レーン１,2,3
	int L1[50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int L2[50] = {0, 5, 5, 0, 1, 0, 2, 0, 3, 3, 0, 0, 2, 2, 0, 0, 0, 0, 0, 1, 0, 3, 1, 0, 0};
	int L3[50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 50; i++) {
		
		lane2[i] = L2[i];
		
	}
	pos = 75;
	menu_ = false;
	kSpeed = 65;
	textureBackground1_ = TextureManager::Load("title/title1.png");
	textureBackground2_ = TextureManager::Load("title/title2.png");
	Background1 = Sprite::Create(
	    textureBackground1_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	Background2 = Sprite::Create(
	    textureBackground2_, {1280 / 2, 720 / 2}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	BackgroundPos1_ = {1280 / 2, 720 / 2};
	BackgroundPos2_ = {1920, 720 / 2};
};
void  Block::stage3(){
	Background1->SetPosition(BackgroundPos1_);
	Background2->SetPosition(BackgroundPos2_);
	blockBreak();

	for (int i = 0; i < 50; i++) {
		
		white2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		red2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		blue2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		green2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		yellow2_[i]->SetPosition({pos + (float(i) * 65), (360)});

		
	}
	
	if (input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kRoot;
	}
};

//ブロックの破壊
void Block::blockBreak() {
	for (int i = 0; i < 50; i++) {
		if (input_->TriggerKey(DIK_2)) {
			
			if (lane2[i - 1] == 0 && lane2[i] == 2) {
				lane2[i] = 0;
				pos -= kSpeed;
				BackgroundPos1_.x -= kSpeed;
				BackgroundPos2_.x -= kSpeed;
				for (int j = 0; j < 15; ++j) {
					if (!hahen_[j]) {
						hahen_[j] = true;
						float numberX = (rand() % 11 - 4) * 3.0f;
						float numberY = (rand() % 11 + 3) * 3.0f;
						velocity[i] = {numberX, numberY};
					}
				}
				break;
			}
		}

		if (input_->TriggerKey(DIK_3)) {
			if (lane2[i - 1] == 0 && lane2[i] == 3) {
				lane2[i] = 0;
				pos -= kSpeed;
				BackgroundPos1_.x -= kSpeed;
				BackgroundPos2_.x -= kSpeed;
				for (int j = 0; j < 15; ++j) {
					if (!hahen_[j]) {
						float numberX = (rand() % 11 - 5) * 3.0f;
						float numberY = (rand() % 11 + 3) * 3.0f;
						velocity[i] = {numberX, numberY};
						hahen_[j] = true;
					}
				}
				break;
			}
		}

		if (input_->TriggerKey(DIK_4)) {
			if (lane2[i - 1] == 0 && lane2[i] == 4) {
				lane2[i] = 0;
				pos -= kSpeed;
				BackgroundPos1_.x -= kSpeed;
				BackgroundPos2_.x -= kSpeed;
				for (int j = 0; j < 15; ++j) {
					if (!hahen_[j]) {
						float numberX = (rand() % 11 - 5) * 3.0f;
						float numberY = (rand() % 11 + 3) * 3.0f;
						velocity[i] = {numberX, numberY};
						hahen_[j] = true;
					}
				}
				break;
			}
		}

		if (input_->TriggerKey(DIK_5)) {
			if (lane2[i - 1] == 0 && lane2[i] == 5) {
				lane2[i] = 0;
				pos -= kSpeed;
				BackgroundPos1_.x -= kSpeed;
				BackgroundPos2_.x -= kSpeed;
				for (int j = 0; j < 15; ++j) {
					if (!hahen_[j]) {
						float numberX = (rand() % 11 - 5) * 3.0f;
						float numberY = (rand() % 11 + 3) * 3.0f;
						velocity[i] = {numberX, numberY};
						hahen_[j] = true;
					}
				}
				break;
			}
		}
	}
}

void Block::BackGroundMove() {
	if (BackgroundPos1_.x <= -640.0f) {
		BackgroundPos1_.x = 1900;
	}
	if (BackgroundPos2_.x <= -640.0f) {
		BackgroundPos2_.x = 1900;
	}
}

void Block::BreackEffect() {

	for (int i = 0; i < 15; ++i) {
		Hahen_[i]->SetPosition(hahenPos[i]);
		if (hahenPos[i].x <= 0 || hahenPos[i].x >= 1280 || hahenPos[i].y <= 0 ||
		    hahenPos[i].y >= 720) {
			hahen_[i] = false;
			hahenPos[i] = {75, 360};
		}
		if (hahen_[i]) {
			velocity[i].y -= 2.0f;
			hahenPos[i].x += velocity[i].x;
			hahenPos[i].y -= velocity[i].y;
		}

		

	}


}

Block::Block() {};

Block::~Block(){};

void Block::Initialize() {
	texture_[0] = TextureManager::Load("title/stage1.png");
	texture_[1] = TextureManager::Load("title/stage2.png");
	texture_[2] = TextureManager::Load("title/stage3.png");
	textureTrue_[0] = TextureManager::Load("title/TrueStage1.png");
	textureTrue_[1] = TextureManager::Load("title/TrueStage2.png");
	textureTrue_[2] = TextureManager::Load("title/TrueStage3.png");
	textureWhite_ = TextureManager::Load("block/white.png");
	textureRed_ = TextureManager::Load("block/red.png");
	textureBlue_ = TextureManager::Load("block/blue.png");
	textureGreen_ = TextureManager::Load("block/green.png");
	textureYellow_ = TextureManager::Load("block/yellow.png");
	textureHahen_ = TextureManager::Load("block/hahen.png");
	
	
	// ブロックの生成
	for (int i = 0; i < 50; i++) {
		
		white2_[i] = Sprite::Create(textureWhite_, {0,0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		red2_[i] = Sprite::Create(textureRed_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		blue2_[i] = Sprite::Create(textureBlue_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		green2_[i] = Sprite::Create(textureGreen_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		yellow2_[i] = Sprite::Create(textureYellow_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		
		
	}
	
	//破片作成
	for (int i = 0; i < 15; i++) {
		Hahen_[i] =
		    Sprite::Create(textureHahen_, {75, 360}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	}

	for (int i = 0; i < 3; i++) {
		sprite[i] = Sprite::Create(
		    texture_[i], {-1280, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
	}

	input_ = Input::GetInstance();
	
	behaviorRequest_ = Behavior::kRoot;

	pos = 720;
	menu_ = true;
}


void Block::Update() {

	if (behaviorRequest_) {
		// 振る舞い変更
		behavior_ = behaviorRequest_.value();
		// 各振る舞いごとの初期化
		switch (behavior_) {
		case Behavior::kRoot:
		default:
			MenuInitialize();
			break;
		case Behavior::kStage1:
			Stage1Initialize();
			break;
		case Behavior::kStage2:
			Stage2Initialize();
			break;
		case Behavior::kStage3:
			Stage3Initialize();
			break;
		}
		// 振る舞いリセット
		behaviorRequest_ = std::nullopt;
	}

	switch (behavior_) {
	case Behavior::kRoot:
	  default:
		MenuUpdata();
		 break;
	   case Behavior::kStage1:
		 stage1();
		 break;
	   case Behavior::kStage2:
		 stage2();
		break;
	  case Behavior::kStage3:
		stage3();
		break;
	 
	}

	ImGui::Begin("Debug1");
	ImGui::Text("RED = 2\nBLUE = 3\nGREEN = 4\nYELLOW = 5\nMunu%d",menu_);
	ImGui::Text("%d", hahen_[13]);
	ImGui::Text("%f", hahenPos[0].x);
	ImGui::End();
}


void Block::Draw() { 
	 
	if (!menu_) {
		Background1->Draw();
		Background2->Draw();
	}

	if (menu_) {
		for (int i = 0; i < 3; i++) {
			sprite[i]->Draw();
		}

	} else {
		

		for (int i = 0; i < 50; i++) {
			
			if (lane2[i] == NORMALBLOCK) {
				white2_[i]->Draw();
			}

			if (lane2[i] == REDBLOCK) {
				red2_[i]->Draw();
			}

			if (lane2[i] == BLUEBLOCK) {
				blue2_[i]->Draw();
			}

			if (lane2[i] == GREENBLOCK) {
				green2_[i]->Draw();
			}

			if (lane2[i] == YELLOWBLOCK) {
				yellow2_[i]->Draw();
			}


		}
	
	}
	
	
	
	for (int i = 0; i < 15; ++i) {
		if (hahen_[i]) {
			Hahen_[i]->Draw();
		}
	}
}