#pragma once
#include "Character.h"

class Interactable;
class Player : public Character
{
private:
	Collider*	m_pHurtBoxCollider;
	Collider*	m_pInteractionCollider;

	Interactable* m_pInteractableObject;
public:
	Player();
	~Player();

	void Init(Vector2 _vec2Position) override;
	virtual void Update() override;
	void Input();
	void UpdateInteractableObject(Collider* _pOther);
};

