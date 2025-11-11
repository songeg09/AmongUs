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
}

Character::~Character()
{
	for (Skill* skill : m_Skills)
		delete skill;
}

void Character::Init(Vector2 _vec2Position)
{
	// 키 등록
	m_pWallCollider = CreateRectCollider(COLLISION_TAG::WALL_DETECTOR,true, Vector2(64, 32), Vector2(0,45));

	InitAnimation();
	Actor::SetPosition(_vec2Position);
	//m_eState = CHARACTER_STATE::DEAD;
	
	// 속도 설정
	Actor::SetMoveSpeed(300.0f);
}

void Character::Update()
{
  	Actor::Update();
	
}

void Character::Render(HDC _memDC)
{
	Actor::Render(_memDC);
}

void Character::InitAnimation()
{
	AnimationData Idle(TEXTURE_TYPE::CHARACTER, Vector2(0, 0), Vector2(128, 128), 0, 1, ANIMATION_TYPE::LOOP, 0.5f, ANCHOR::CENTER);
	AnimationData Run(TEXTURE_TYPE::CHARACTER, Vector2(1, 0), Vector2(128, 128), 0, 8, ANIMATION_TYPE::LOOP, 0.7f, ANCHOR::CENTER);
	AnimationData Ghost(TEXTURE_TYPE::CHARACTER, Vector2(0, 10), Vector2(128, 128), 0, 16, ANIMATION_TYPE::LOOP, 2.0f, ANCHOR::CENTER);

	// 애니메이션 설정 == 여기를 나중에 데이터를 받아서 자동으로 하는 방향으로 바꿔야 됨
	
	Actor::ResizeAnimation(ANIMATION::END);
	Actor::InitAnimation(ANIMATION::IDLE, Idle);
	Actor::InitAnimation(ANIMATION::RUN, Run);
	Actor::InitAnimation(ANIMATION::GHOST, Ghost);
	Actor::SetAnimation(ANIMATION::IDLE);
}
