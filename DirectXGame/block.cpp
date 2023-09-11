#include "block.h"
#include "ImGuiManager.h"

//メニュー
void Block::MenuInitialize(){
	
	for (int i = 0; i < 50; i++) {
		white1_[i]->SetPosition({720 + (float(i) * 50), (180)});
		red1_[i]->SetPosition({720 + (float(i) * 50), (180)});
		blue1_[i]->SetPosition({720 + (float(i) * 50), (180)});
		green1_[i]->SetPosition({720 + (float(i) * 50), (180)});
		yellow1_[i]->SetPosition({720 + (float(i) * 50), (180)});

		white2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		red2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		blue2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		green2_[i]->SetPosition({720 + (float(i) * 50), (360)});
		yellow2_[i]->SetPosition({720 + (float(i) * 50), (360)});

		white3_[i]->SetPosition({720 + (float(i) * 50), (540)});
		red3_[i]->SetPosition({720 + (float(i) * 50), (540)});
		blue3_[i]->SetPosition({720 + (float(i) * 50), (540)});
		green3_[i]->SetPosition({720 + (float(i) * 50), (540)});
		yellow3_[i]->SetPosition({720 + (float(i) * 50), (540)});
	}
	red1_[0]->SetPosition({256, 360});
	white1_[0]->SetPosition({256, 360});
	white1_[1]->SetPosition({256 * 2, 360});
	white1_[2]->SetPosition({256 * 3, 360});
	white1_[3]->SetPosition({256 * 4, 360});
	menu_ = true;
	stage_ = 1;
};
void Block::MenuUpdata(){ 


	if (stage_ == 1 && input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kStage1;
	} else if (stage_ == 2 && input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kStage2;
	} else if (stage_ == 3 && input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kStage3;
	} else if (stage_ == 4 && input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kStage4;
	} 

	if (stage_ <= 1 ) {
		red1_[0]->SetPosition({256, 360});
	} else if (stage_ <= 2) {
		red1_[0]->SetPosition({256*2, 360});
	} else if (stage_ <= 3) {
		red1_[0]->SetPosition({256*3, 360});
	} else if (stage_ <= 4) {
		red1_[0]->SetPosition({256*4, 360});
	}

	if (input_->TriggerKey(DIK_2)) {
		BreackEffect(2);
	}

	ImGui::Begin("Debug1");
	ImGui::Text("%f", stage_);
	ImGui::End();
};

//ステージ
void Block::Stage1Initialize(){ 
	// レーン１,2,3
	int L1[50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int L2[50] = {2, 3, 4, 3, 5, 4, 5, 4, 2, 5, 5, 5, 3, 2, 4, 2, 4, 3, 5, 3, 3, 3, 2, 3, 2};
	int L3[50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 50; i++) {
		lane1[i] = L1[i];
		lane2[i] = L2[i];
		lane3[i] = L3[i];
	}
	pos = 75;
	menu_ = false;
	kSpeed = 65;
};
void  Block::stage1(){
	
	blockBreak();

	
	for (int i = 0; i < 50; i++) {
		white1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		red1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		blue1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		green1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		yellow1_[i]->SetPosition({pos + (float(i) * 50), (180)});

		white2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		red2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		blue2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		green2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		yellow2_[i]->SetPosition({pos + (float(i) * 65), (360)});

		white3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		red3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		blue3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		green3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		yellow3_[i]->SetPosition({pos + (float(i) * 50), (540)});
	}
	
	if (input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kRoot;
	}


	
};

void Block::Stage2Initialize() { 
	// レーン１,2,3
	int L1[50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int L2[50] = {2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 1, 3, 3, 3, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3};
	int L3[50] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	for (int i = 0; i < 50; i++) {
		lane1[i] = L1[i];
		lane2[i] = L2[i];
		lane3[i] = L3[i];
	}
	pos = 75;
	menu_ = false;
	kSpeed = 65;
};
void  Block::stage2(){
	
	blockBreak();

	for (int i = 0; i < 50; i++) {
		white1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		red1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		blue1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		green1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		yellow1_[i]->SetPosition({pos + (float(i) * 50), (180)});

		white2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		red2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		blue2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		green2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		yellow2_[i]->SetPosition({pos + (float(i) * 65), (360)});

		white3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		red3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		blue3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		green3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		yellow3_[i]->SetPosition({pos + (float(i) * 50), (540)});
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
		lane1[i] = L1[i];
		lane2[i] = L2[i];
		lane3[i] = L3[i];
	}
	pos = 75;
	menu_ = false;
	kSpeed = 65;
};
void  Block::stage3(){

	blockBreak();

	for (int i = 0; i < 50; i++) {
		white1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		red1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		blue1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		green1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		yellow1_[i]->SetPosition({pos + (float(i) * 50), (180)});

		white2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		red2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		blue2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		green2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		yellow2_[i]->SetPosition({pos + (float(i) * 65), (360)});

		white3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		red3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		blue3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		green3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		yellow3_[i]->SetPosition({pos + (float(i) * 50), (540)});
	}
	
	if (input_->TriggerKey(DIK_SPACE)) {
		behaviorRequest_ = Behavior::kRoot;
	}
};

void Block::Stage4Initialize() { 
	// レーン１,2,3
	int L1[50] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1};
	int L2[50] = {5, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 3, 0, 0, 0, 0, 1, 0, 3, 1, 0, 0};
	int L3[50] = {5, 1, 1, 1, 0, 0, 5, 0, 5, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 2, 0};
	for (int i = 0; i < 50; i++) {
		lane1[i] = L1[i];
		lane2[i] = L2[i];
		lane3[i] = L3[i];
	}
	pos = 75;
	menu_ = false;
	kSpeed = 65;
};
void  Block::stage4(){
	
	blockBreak();
	
	for (int i = 0; i < 50; i++) {
		white1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		red1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		blue1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		green1_[i]->SetPosition({pos + (float(i) * 50), (180)});
		yellow1_[i]->SetPosition({pos + (float(i) * 50), (180)});

		white2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		red2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		blue2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		green2_[i]->SetPosition({pos + (float(i) * 65), (360)});
		yellow2_[i]->SetPosition({pos + (float(i) * 65), (360)});

		white3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		red3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		blue3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		green3_[i]->SetPosition({pos + (float(i) * 50), (540)});
		yellow3_[i]->SetPosition({pos + (float(i) * 50), (540)});
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
				
				break;
			}
		}

		if (input_->TriggerKey(DIK_3)) {
			if (lane2[i - 1] == 0 && lane2[i] == 3) {
				lane2[i] = 0;
				pos -= kSpeed;
				BreackEffect(lane2[i]);
				break;
			}
		}

		if (input_->TriggerKey(DIK_4)) {
			if (lane2[i - 1] == 0 && lane2[i] == 4) {
				lane2[i] = 0;
				pos -= kSpeed;
				BreackEffect(lane2[i]);
				break;
			}
		}

		if (input_->TriggerKey(DIK_5)) {
			if (lane2[i - 1] == 0 && lane2[i] == 5) {
				lane2[i] = 0;
				pos -= kSpeed;
				BreackEffect(lane2[i]);
				break;
			}
		}
	}
}

void Block::BreackEffect(int lane) {
	effect_ = true;
	lane;
	
	for (int i = 0; i < 15; ++i) {
	
		float numberX = (rand() % 11 - 5) / 5.0f;
		float numberY = (rand() % 11 - 5) / 5.0f;
		velocity[i] = {numberX, numberY};
		
	}
	
	for (int i = 0; i < 15; ++i) {
		blue1_[i]->SetPosition(effectPos[i]);
		effectPos[i].x += velocity[i].x;
		effectPos[i].y += velocity[i].y;
		
	}
}

Block::Block() {};

Block::~Block(){};

void Block::Initialize() {
	textureWhite_ = TextureManager::Load("block/white.png");
	textureRed_ = TextureManager::Load("block/red.png");
	textureBlue_ = TextureManager::Load("block/blue.png");
	textureGreen_ = TextureManager::Load("block/green.png");
	textureYellow_ = TextureManager::Load("block/yellow.png");
	
	// ブロックの生成
	for (int i = 0; i < 50; i++) {
		white1_[i] = Sprite::Create(textureWhite_, {0,0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		red1_[i] = Sprite::Create(textureRed_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		blue1_[i] = Sprite::Create(textureBlue_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		green1_[i] = Sprite::Create(textureGreen_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		yellow1_[i] = Sprite::Create(textureYellow_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		white2_[i] = Sprite::Create(textureWhite_, {0,0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		red2_[i] = Sprite::Create(textureRed_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		blue2_[i] = Sprite::Create(textureBlue_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		green2_[i] = Sprite::Create(textureGreen_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		yellow2_[i] = Sprite::Create(textureYellow_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		white3_[i] = Sprite::Create(textureWhite_, {0,0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		red3_[i] = Sprite::Create(textureRed_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		blue3_[i] = Sprite::Create(textureBlue_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		green3_[i] = Sprite::Create(textureGreen_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});
		yellow3_[i] = Sprite::Create(textureYellow_, {0, 0}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

		
	}
	
	input_ = Input::GetInstance();
	
	behaviorRequest_ = Behavior::kRoot;

	pos = 720;
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
		case Behavior::kStage4:
			Stage4Initialize();
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
	  case Behavior::kStage4:
		stage4();
		break;
	}

	ImGui::Begin("Debug1");
	ImGui::Text("RED = 2\nBLUE = 3\nGREEN = 4\nYELLOW = 5");
	ImGui::End();
}


void Block::Draw() { 
	 
	
	if (menu_) {
		white1_[0]->Draw();
		white1_[1]->Draw();
		white1_[2]->Draw();
		white1_[3]->Draw();
		red1_[0]->Draw();
	} else {
		for (int i = 0; i < 50; i++) {
			if (lane1[i] == NORMALBLOCK) {
				white1_[i]->Draw();
			}

			if (lane1[i] == REDBLOCK) {
				red1_[i]->Draw();
			}

			if (lane1[i] == BLUEBLOCK) {
				blue1_[i]->Draw();
			}

			if (lane1[i] == GREENBLOCK) {
				green1_[i]->Draw();
			}

			if (lane1[i] == YELLOWBLOCK) {
				yellow1_[i]->Draw();
			}

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

			if (lane3[i] == NORMALBLOCK) {
				white3_[i]->Draw();
			}

			if (lane3[i] == REDBLOCK) {
				red3_[i]->Draw();
			}

			if (lane3[i] == BLUEBLOCK) {
				blue3_[i]->Draw();
			}

			if (lane3[i] == GREENBLOCK) {
				green3_[i]->Draw();
			}

			if (lane3[i] == YELLOWBLOCK) {
				yellow3_[i]->Draw();
			}
		}
	
	}
	
	/*if (effect_) {
		for (int i = 0; i < 15; ++i) {
			blue1_[i]->Draw();
		}
	}*/
}