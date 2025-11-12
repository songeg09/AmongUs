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


