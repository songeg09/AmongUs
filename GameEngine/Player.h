#pragma once
#include "Character.h"

class Interactable;
class Player : public Character
{
public:
	enum CHARACTER_STATE
	{
		NONE,
		WORKING,
		DEAD
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

	int				m_iTasksTotal;
	int				m_iTasksCompleted;

public:
	Player();
	~Player();

	void Init(Vector2 _vec2Position) override;
	virtual void Update() override;
	void Input();
	
	void UpdateInteractableObject(Collider* _pOther);
	void ClearCurrentInteractable(Collider* _pOther);

	void InitAnimation() override;
	void SetCharacterState(CHARACTER_STATE _eState) { m_eState = _eState; }
	CHARACTER_STATE GetCharacterState() { return m_eState; }

	Interactable* GetInteractableObject() {return m_pInteractableObject;}

	void UseInteractableObject();

	

private:
	void CheckMapKey();
	void CheckInteractKey();
	void CheckMoveKeys();
	void CheckEscapeKey();




};

