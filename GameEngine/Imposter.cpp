#include "pch.h"
#include "Imposter.h"

void Imposter::Init(Vector2 _vec2Position)
{
	Character::Init(_vec2Position);
	//m_pInteractionCollider = CreateCircleCollider(COLLISION_TAG::INTERACTION_IMPOSTER, true, 110.f, Vector2(0, 15));
}
