#pragma once
#include "Character.h"

class Interactable;
class Player : public Character
{
public:
	enum CHARACTER_STATE
	{
		NONE,
		DEAD,
		WORKING,
		HIDDEN,
	};

	enum ANIMATION
	{
		IDLE,
		RUN,
		GHOST,
		END,
	};

private:
	Collider*		m_pHurtBoxCollider;
	Collider*		m_pInteractionCollider;
	CHARACTER_STATE m_eState;

	Interactable*	m_pInteractableObject;
public:
	Player();
	~Player();

	void Init(Vector2 _vec2Position) override;
	virtual void Update() override;
	void Input();
	
	void UpdateInteractableObject(Collider* _pOther);
	void ClearCurrentInteractable(Collider* _pOther);

	void InitAnimation() override;
	void SetState(int _iIndex) override { m_eState = static_cast<CHARACTER_STATE>(_iIndex); }
};

