#pragma once
#include "pch.h"

class Character;
class IInteractable abstract
{
public:
	virtual ~IInteractable() = default;

	virtual void Interact(Character* _Interactor) = 0;
	virtual Vector2 GetPosition() = 0;
};