#include "pch.h"
#include "Character.h"
#include "Texture.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "Core.h"
#include "Collider.h"

Character::Character()
{
}

Character::~Character()
{
}

void Character::Init(Vector2 _vec2Position)
{	
	Actor::Init(_vec2Position);
	InitAnimation();	
}


