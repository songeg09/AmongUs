#pragma once

class Character;
class Interactable abstract
{
public:
	virtual ~Interactable() = default;

	virtual void Interact(Character* _Interactor) = 0;
	virtual Vector2 GetPosition() = 0;
	virtual void OnSuccess() = 0;
};