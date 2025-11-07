#include "pch.h"
#include "Character.h"
#include "Texture.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Core.h"
#include "Collider.h"
#include "Monster.h"
#include "CircleDamageSkill.h"
#include "SwordBeam.h"

Character::Character()
{
	m_eState = CHARACTER_STATE::ALIVE;
	m_bInput = true;
	m_pWallCollider = nullptr;
	m_pInteractCollider = nullptr;
}

Character::~Character()
{
	for (Skill* skill : m_Skills)
		delete skill;
}

void Character::Init(Vector2 _vec2Position)
{
	// 키 등록
	SetActorType(ACTOR_TYPE::PLAYER);
	InputManager::GetInstance()->RegistKey(VK_LEFT);
	InputManager::GetInstance()->RegistKey(VK_RIGHT);
	InputManager::GetInstance()->RegistKey(VK_UP);
	InputManager::GetInstance()->RegistKey(VK_DOWN);
	InputManager::GetInstance()->RegistKey(VK_SPACE);

	m_pWallCollider = CreateRectCollider(true, Vector2(64, 32), Vector2(0,45));
	m_pInteractCollider = CreateCircleCollider(true, 110.f, Vector2(0,15));

	AnimationData Idle(TEXTURE_TYPE::CHARACTER, Vector2(0, 0), Vector2(128, 128), 0, 1, ANIMATION_TYPE::LOOP, 0.5f, ANCHOR::CENTER);
	AnimationData Run(TEXTURE_TYPE::CHARACTER, Vector2(1, 0), Vector2(128, 128), 0, 8, ANIMATION_TYPE::LOOP, 0.7f, ANCHOR::CENTER);
	AnimationData Ghost(TEXTURE_TYPE::CHARACTER, Vector2(0, 10), Vector2(128, 128), 0, 16, ANIMATION_TYPE::LOOP, 2.0f, ANCHOR::CENTER);


	// 애니메이션 설정
	Actor::SetPosition(_vec2Position);
	Actor::ResizeAnimation(ANIMATION::END);
	Actor::InitAnimation(ANIMATION::IDLE, Idle);
	Actor::InitAnimation(ANIMATION::RUN, Run);
	Actor::InitAnimation(ANIMATION::GHOST, Ghost);
	Actor::SetAnimation(ANIMATION::GHOST);
	m_eState = CHARACTER_STATE::DEAD;
	
	// 속도 설정
	Actor::SetMoveSpeed(200.0f);
}

void Character::Update()
{
  	Actor::Update();
	Input();
}

void Character::Render(HDC _memDC)
{
	Actor::Render(_memDC);
}

void Character::Input()
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


	if (vec2MoveForce.isValid() == true)
	{
		Actor::Move(vec2MoveForce);
		if(m_eState == CHARACTER_STATE::ALIVE)
			Actor::SetAnimation(ANIMATION::RUN);
	}
	else
		if (m_eState == CHARACTER_STATE::ALIVE)
			Actor::SetAnimation(ANIMATION::IDLE);
}
