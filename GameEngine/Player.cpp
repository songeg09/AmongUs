#include "pch.h"
#include "Player.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Collider.h"
#include "SceneManager.h"
#include "GameScene.h"

Player::Player()
{
	m_pHurtBoxCollider = nullptr;
	m_pInteractionCollider = nullptr;
	m_pInteractableObject = nullptr;
	m_eState = CHARACTER_STATE::NONE;
}

Player::~Player()
{
}

void Player::Init(Vector2 _vec2Position, std::function<void()> _funcMapKeyCallback)
{
	Character::Init(_vec2Position);

	m_funcMapKeyCallback = _funcMapKeyCallback;

	m_pWallCollider = CreateRectCollider(COLLISION_TAG::WALL_DETECTOR, true, Vector2(64, 32), Vector2(0, 45));
	m_pHurtBoxCollider = CreateRectCollider(COLLISION_TAG::PLAYER_HURTBOX, true, Vector2(60, 95), Vector2(0, 15));
	
	m_pInteractionCollider = CreateCircleCollider(COLLISION_TAG::PLAYER_INTERACTION, true, 110.f, Vector2(0, 15));
	m_pInteractionCollider->SetOnCollisionCallBack(std::bind(&Player::UpdateInteractableObject, this, std::placeholders::_1));
	m_pInteractionCollider->SetEndCollisionCallBack(std::bind(&Player::ClearCurrentInteractable, this, std::placeholders::_1));

	Actor::SetMoveSpeed(300.0f);
}

void Player::Update()
{
	Character::Update();
	Input();
}

void Player::Input()
{
	if (m_eState == CHARACTER_STATE::DEAD)
		return;

	// 지도 눌렀는지 확인
	CheckMapKey();

	// 이동 키 확인
	CheckMoveKeys();

	// 인터랙트 키 확인
	CheckInteractKey();

	// ESC키 확인
	CheckEscapeKey();
		
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

void Player::ClearCurrentInteractable(Collider* _pOther)
{
	if (m_pInteractableObject == dynamic_cast<Interactable*>(_pOther->GetTarget()))
		m_pInteractableObject = nullptr;
}

void Player::InitAnimation()
{
	AnimationData Idle(TEXTURE_TYPE::CHARACTER, Vector2(0, 0), Vector2(128, 128), 0, 1, ANIMATION_TYPE::ONCE, 0.1f, ANCHOR::CENTER);
	AnimationData Run(TEXTURE_TYPE::CHARACTER, Vector2(1, 0), Vector2(128, 128), 0, 8, ANIMATION_TYPE::LOOP, 0.5f, ANCHOR::CENTER);
	AnimationData Dead(TEXTURE_TYPE::CHARACTER, Vector2(9, 0), Vector2(128, 128), 0, 1, ANIMATION_TYPE::ONCE, 0.1f, ANCHOR::CENTER);

	// 애니메이션 설정 == 여기를 나중에 데이터를 받아서 자동으로 하는 방향으로 바꿔야 됨
	Actor::ResizeAnimation(static_cast<int>(ANIMATION::END));
	Actor::InitAnimation(static_cast<int>(ANIMATION::IDLE), Idle);
	Actor::InitAnimation(static_cast<int>(ANIMATION::RUN), Run);
	Actor::InitAnimation(static_cast<int>(ANIMATION::DEAD), Dead);
	Actor::SetAnimation(static_cast<int>(ANIMATION::IDLE));
}

void Player::CheckMapKey()
{
	if (InputManager::GetInstance()->GetKeyState(VK_TAB) != KEY_STATE::DOWN)
		return;

	if (m_funcMapKeyCallback != nullptr)
		m_funcMapKeyCallback();
}

void Player::CheckInteractKey()
{
	if (InputManager::GetInstance()->GetKeyState('E') != KEY_STATE::DOWN || m_pInteractableObject == nullptr)
		return;

	if (m_eState == CHARACTER_STATE::NONE)
		UseInteractableObject();
}

void Player::CheckMoveKeys()
{
	// 이동 키 확인
	Vector2 vec2MoveForce;
	if (InputManager::GetInstance()->GetKeyState('A') == KEY_STATE::PRESS)
		vec2MoveForce.m_fx += -1.0f;
	if (InputManager::GetInstance()->GetKeyState('D') == KEY_STATE::PRESS)
		vec2MoveForce.m_fx += 1.0f;
	if (InputManager::GetInstance()->GetKeyState('W') == KEY_STATE::PRESS)
		vec2MoveForce.m_fy += -1.0f;
	if (InputManager::GetInstance()->GetKeyState('S') == KEY_STATE::PRESS)
		vec2MoveForce.m_fy += 1.0f;

	if (m_eState == CHARACTER_STATE::NONE  && vec2MoveForce.isValid() == true)
	{
		Actor::Move(vec2MoveForce);
		Actor::SetAnimation(static_cast<int>(ANIMATION::RUN));
	}
	else
		Actor::SetAnimation(static_cast<int>(ANIMATION::IDLE));
}

void Player::CheckEscapeKey()
{
	if (InputManager::GetInstance()->GetKeyState(VK_ESCAPE) != KEY_STATE::DOWN)
		return;
}

void Player::Hide()
{
	if (m_eState == CHARACTER_STATE::HIDDEN)
	{
		m_eState = CHARACTER_STATE::NONE;
		m_pHurtBoxCollider->SetEnable(true);
	}
	else
	{
		m_eState = CHARACTER_STATE::HIDDEN;
		m_pHurtBoxCollider->SetEnable(false);
	}
}

void Player::Die()
{
	Actor::SetAnimation(static_cast<int>(ANIMATION::DEAD));
	m_eState = CHARACTER_STATE::DEAD;
	m_pHurtBoxCollider->SetEnable(false);
}

void Player::UseInteractableObject()
{
	if(m_pInteractableObject != nullptr)
		m_pInteractableObject->Interact(this);
}


