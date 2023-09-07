#pragma once
#include "Sprite.h"
#include <vector>

class BaseObject {
protected:

	std::vector<Sprite*> sprite_;

public:

	virtual void Initialize(const std::vector<Sprite*>& sprite);

	virtual void Update();

	virtual void Draw();

};
