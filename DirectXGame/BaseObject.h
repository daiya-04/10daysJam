#pragma once
#include "Sprite.h"

class BaseObject {
protected:

	Sprite* sprite_;

public:

	virtual void Initialize(Sprite* sprite);

	virtual void Update();

	virtual void Draw();

};
