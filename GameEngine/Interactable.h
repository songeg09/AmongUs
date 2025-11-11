#pragma once

class Interactable abstract
{
public:
	virtual ~Interactable() = default;

	virtual void Interact() = 0;
	virtual Vector2 GetPosition() = 0;
};