#pragma once
#include "Sprite.h"

enum Type {
	Soft,
	Hard,
};

class BaseObject {
protected:

	Sprite* sprite_;

public:

	virtual void Initialize(Sprite* sprite);

	virtual void Update();

	virtual void Draw();

};