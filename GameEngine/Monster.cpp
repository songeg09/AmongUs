#include "pch.h"
#include "Monster.h"

Monster::Monster()
{

}

Monster::~Monster()
{
}

void Monster::Init(Vector2 _vec2Position)
{
	Character::Init(_vec2Position);
	m_pPlayerDetectCollider = CreateCircleCollider(COLLISION_TAG::MONSTER_PLAYER_DETECTOR, true, 150.f, Vector2(0, 15));
	m_pAttackRangeCollider = CreateCircleCollider(COLLISION_TAG::MONSTER_ATTACK_RANGE, true, 110.f, Vector2(0, 15));
}

void Monster::Update()
{
}
