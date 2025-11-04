#include "pch.h"
#include "Player.h"
#include "Texture.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Core.h"
#include "Collider.h"
#include "Monster.h"
#include "CircleDamageSkill.h"
#include "SwordBeam.h"

Player::Player()
{
	m_bInput = true;
	m_pAttackCollider = nullptr;
}

Player::~Player()
{
	for (Skill* skill : m_Skills)
		delete skill;
}

void Player::Init(Vector2 _vec2Position)
{
	// 키 등록
	SetActorType(ACTOR_TYPE::PLAYER);
	InputManager::GetInstance()->RegistKey(VK_LEFT);
	InputManager::GetInstance()->RegistKey(VK_RIGHT);
	InputManager::GetInstance()->RegistKey(VK_UP);
	InputManager::GetInstance()->RegistKey(VK_DOWN);
	InputManager::GetInstance()->RegistKey(VK_SPACE);

	CreateCircleCollider(true, 40.f);\
	m_pAttackCollider = CreateRectCollider(false, Vector2{ 40.f, 40.f }, Vector2(0.0f, 20.f));
	m_pAttackCollider->SetBeginCollisionCallBack(
		std::bind([this](Collider* _pOther)
			{
				Monster* TargetMonster = dynamic_cast<Monster*>(_pOther->GetTarget());
				if (TargetMonster == nullptr)
					return;
				Vector2 ForceDirection = _pOther->GetPosition() - GetPosition();
				ForceDirection.Normalize();
				TargetMonster->AddForce(ForceDirection * 300.0f);
			}, std::placeholders::_1));

	// 애니메이션 설정
	Actor::SetPosition(_vec2Position);
	Actor::ResizeAnimation(ANIMATION::END);
	Actor::InitAnimation(ANIMATION::IDLE, TEXTURE_TYPE::PLAYER_IDLE_START, TEXTURE_TYPE::PLAYER_IDLE_END);
	Actor::InitAnimation(ANIMATION::RUN, TEXTURE_TYPE::PLAYER_RUN_START, TEXTURE_TYPE::PLAYER_RUN_END);
	Actor::InitAnimation(ANIMATION::ATTACK, TEXTURE_TYPE::PLAYER_ATTACK_START, TEXTURE_TYPE::PLAYER_ATTACK_END, 0.5f, ANIMATION_TYPE::ONCE);
	Actor::SetAnimationEvent(ANIMATION::ATTACK, 1,
		[this]() {
			m_pAttackCollider->SetEnable(true);
		}
	);
	Actor::SetAnimationEvent(ANIMATION::ATTACK, 2,
		[this]() {
			m_pAttackCollider->SetEnable(false);
		}
	);
	Actor::SetAnimationEvent(ANIMATION::ATTACK, 3,
		[this]() {
			m_bInput = true;
			Actor::SetAnimation(ANIMATION::IDLE);
		}
	);
	Actor::SetAnimation(ANIMATION::IDLE);
	
	// 속도 설정
	Actor::SetMoveSpeed(200.0f);

	Skill* Skill = new CircleDamageSkill(1, this, 'Q');
	m_Skills.push_back(Skill);

	Skill = new SwordBeam(0, this, 'W');
	m_Skills.push_back(Skill);
}

void Player::Update()
{
  	Actor::Update();
	Input();
}

void Player::Render(HDC _memDC)
{
	Actor::Render(_memDC);
}

void Player::Attack(Collider* _pOther)
{
}

void Player::Input()
{
	for (Skill* skill : m_Skills)
		skill->Input();

	if (m_bInput == false)
		return;

	if (InputManager::GetInstance()->GetKeyState(VK_SPACE) == KEY_STATE::DOWN)
	{
		m_bInput = false;
		Actor::SetAnimation(ANIMATION::ATTACK);
	}
	else
	{
		Vector2 vec2MoveForce;
		if (InputManager::GetInstance()->GetKeyState(VK_LEFT) == KEY_STATE::PRESS)
			vec2MoveForce.m_fx += -1.0f;
		if (InputManager::GetInstance()->GetKeyState(VK_RIGHT) == KEY_STATE::PRESS)
			vec2MoveForce.m_fx += 1.0f;
		if (InputManager::GetInstance()->GetKeyState(VK_UP) == KEY_STATE::PRESS)
			vec2MoveForce.m_fy += -1.0f;
		if (InputManager::GetInstance()->GetKeyState(VK_DOWN) == KEY_STATE::PRESS)
			vec2MoveForce.m_fy += 1.0f;

		if (vec2MoveForce.isValid() == true)
		{
			Actor::Move(vec2MoveForce);
			Actor::SetAnimation(ANIMATION::RUN);
		}
		else
			Actor::SetAnimation(ANIMATION::IDLE);
	}
}
