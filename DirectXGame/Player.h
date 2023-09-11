#pragma once
#include "Sprite.h"

class Player {
private:

	Sprite* sprite_;

public:

	void Initialize(Sprite* sprite);

	void Update();

	void Draw();

};
