#include "pch.h"
#include "Crew.h"

void Crew::Init(Vector2 _vec2Position)
{
	Character::Init(_vec2Position);
	//m_pCrewCollider = CreateRectCollider(COLLISION_TAG::HURTBOX_CREW, true, Vector2(60,95), Vector2(0,15));
	//m_pInteractionCollider = CreateCircleCollider(COLLISION_TAG::INTERACTION_CREW, true, 110.f, Vector2(0, 15));
}
