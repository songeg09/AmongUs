#pragma once
#include "GameObject.h"

class Vent : public GameObject
{
public:
	Vent();
	~Vent();

	void Init(Vector2 _vec2Position) override;
	void Interact(Character* _Interactor) override;
};

