#pragma once
#include "Object.h"
#include "Interactable.h"

class GameObject : public Object, public Interactable
{
protected:
	Collider* m_pInteractRange;

public:
	GameObject();
	~GameObject();

	void Update() override;
	void Init(Vector2 _vec2Position) = 0;
	virtual void Interact(Character* _Interactor) = 0;
	Vector2 GetPosition() override;
};

