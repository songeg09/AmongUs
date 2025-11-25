#pragma once
#include "Character.h"
#include "Interactable.h"

class Player : public Character, public Interactable
{
public:
	enum class CHARACTER_STATE
	{
		NONE,
		WORKING,
		HIDDEN,
		DEAD
	};

	enum class ANIMATION
	{
		IDLE,
		RUN,
		HIDE,
		REVEAL,
		DEAD,
		END,
	};

private:
	Collider*		m_pWallCollider;
	Collider*		m_pHurtBoxCollider;
	Collider*		m_pInteractionCollider;
	CHARACTER_STATE m_eState;

	Interactable*	m_pInteractableObject;

	std::function<void()> m_funcMapKeyCallback;

public:
	Player();
	~Player();

	void Init(Vector2 _vec2Position, std::function<void()> _funcMapKeyCallback = nullptr);
	void Update() override;
	void Input();
	
	void UpdateInteractableObject(Collider* _pOther);
	void ClearCurrentInteractable(Collider* _pOther);

	void InitAnimation() override;
	void SetCharacterState(CHARACTER_STATE _eState) { m_eState = _eState; }
	CHARACTER_STATE GetCharacterState() { return m_eState; }

	Interactable* GetInteractableObject() {return m_pInteractableObject;}

	void UseInteractableObject();

	void Interact(Character* _Interactor) override { Die(); }
	Vector2 GetPosition() override { return Actor::GetPosition(); }
	void OnSuccess() override {}

	void Hide();

private:
	void CheckMapKey();
	void CheckInteractKey();
	void CheckMoveKeys();
	void CheckEscapeKey();

	void Die();



};

