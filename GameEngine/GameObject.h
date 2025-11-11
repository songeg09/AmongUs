#pragma once
#include "Object.h"
#include "Interactable.h"

class GameObject : public Object, public Interactable
{
private:
	Collider* m_pInteractRange;

public:
	GameObject();
	~GameObject();

	void Update() override;
	void Init(Vector2 _vec2Position) override;
	virtual void Interact() override;
	Vector2 GetPosition() override;
};

