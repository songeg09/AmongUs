#include "pch.h"
#include "Character.h"
#include "Texture.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Core.h"
#include "Collider.h"
#include "CircleDamageSkill.h"
#include "SwordBeam.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Init(Vector2 _vec2Position)
{	
	InitAnimation();
	Actor::SetPosition(_vec2Position);
}

void Character::Update()
{
  	Actor::Update();
	
}

void Character::Render(HDC _memDC)
{
	Actor::Render(_memDC);
}


