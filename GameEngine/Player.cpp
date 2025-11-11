#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Collider.h"

Player::Player()
{
	m_pHurtBoxCollider = nullptr;
	m_pInteractionCollider = nullptr;
	m_pInteractableObject = nullptr;
}

Player::~Player()
{
}

void Player::Init(Vector2 _vec2Position)
{
	Character::Init(_vec2Position);

	// Å° ¼³Á¤
	InputManager::GetInstance()->RegistKey(VK_LEFT);
	InputManager::GetInstance()->RegistKey(VK_RIGHT);
	InputManager::GetInstance()->RegistKey(VK_UP);
	InputManager::GetInstance()->RegistKey(VK_DOWN);
	InputManager::GetInstance()->RegistKey('E');

	m_pHurtBoxCollider = CreateRectCollider(COLLISION_TAG::PLAYER_HURTBOX, true, Vector2(60, 95), Vector2(0, 15));
	m_pInteractionCollider = CreateCircleCollider(COLLISION_TAG::PLAYER_INTERACTION, true, 110.f, Vector2(0, 15));
	m_pInteractionCollider->SetOnCollisionCallBack(std::bind(&Player::UpdateInteractableObject, this, std::placeholders::_1));
}

void Player::Update()
{
	Character::Update();
	Input();
}

void Player::Input()
{
	for (Skill* skill : m_Skills)
		skill->Input();

	if (m_bInput == false)
		return;

	Vector2 vec2MoveForce;
	if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == KEY_STATE::PRESS)
		vec2MoveForce.m_fx += -1.0f;
	if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == KEY_STATE::PRESS)
		vec2MoveForce.m_fx += 1.0f;
	if (InputManager::GetInstance()->GetKeyState(VK_UP) == KEY_STATE::PRESS)
		vec2MoveForce.m_fy += -1.0f;
	if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == KEY_STATE::PRESS)
		vec2MoveForce.m_fy += 1.0f;

	if (InputManager::GetInstance()->GetKeyState('E') == KEY_STATE::PRESS && m_pInteractableObject != nullptr)
		m_pInteractableObject->Interact();

	if (vec2MoveForce.isValid() == true)
	{
		Actor::Move(vec2MoveForce);
		if (m_eState == CHARACTER_STATE::ALIVE)
			Actor::SetAnimation(ANIMATION::RUN);
	}
	else
		if (m_eState == CHARACTER_STATE::ALIVE)
			Actor::SetAnimation(ANIMATION::IDLE);
}

void Player::UpdateInteractableObject(Collider* _pOther)
{
	if (m_pInteractableObject != nullptr)
	{
		Vector2 PlayerPos = GetPosition();
		Vector2 CurrentObjectPos = m_pInteractableObject->GetPosition();
		Vector2 NewObjectPos = _pOther->GetTarget()->GetPosition();

		if (Vector2::Distance(PlayerPos, CurrentObjectPos) > Vector2::Distance(PlayerPos, NewObjectPos))
		{
			m_pInteractableObject = dynamic_cast<Interactable*>(_pOther->GetTarget());
		}
	}
	else
		m_pInteractableObject = dynamic_cast<Interactable*>(_pOther->GetTarget());
}
