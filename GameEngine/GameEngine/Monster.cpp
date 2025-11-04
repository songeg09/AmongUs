#include "pch.h"
#include "Monster.h"
#include "Collider.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Init(Vector2 _vec2Position)
{
	Actor::SetPosition(_vec2Position);

	// 애니메이션 설정
	Actor::ResizeAnimation(ANIMATION::END);
	Actor::InitAnimation(ANIMATION::IDLE, TEXTURE_TYPE::MONSTER_IDLE_START, TEXTURE_TYPE::MONSTER_IDLE_END, 0.5f);
	Actor::SetAnimation(ANIMATION::IDLE);

	Actor::SetMoveSpeed(200.0f);
	CreateRectCollider(true, Vector2{ 40.0f, 40.0f }, Vector2{ 0.0f,30.0f });
}

void Monster::Update()
{
	Actor::Update();
}

void Monster::Render(HDC _memDC)
{
	Actor::Render(_memDC);
}

void Monster::Attack(Collider* _pOther)
{
}
