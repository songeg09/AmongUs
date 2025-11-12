#include "pch.h"
#include "Vent.h"
#include "Player.h"

Vent::Vent()
{
}

Vent::~Vent()
{
}

void Vent::Init(Vector2 _vec2Position)
{
	Object::Init(_vec2Position);
	m_pInteractRange = CreateRectCollider(COLLISION_TAG::OBJECT_INTERACTION_DETECTOR, true, Vector2(10, 10));
}

void Vent::Interact(Character* _Interactor)
{
	if (Player* player = dynamic_cast<Player*>(_Interactor))
	{
		player->SetState(Player::CHARACTER_STATE::WORKING);
		player->SetAnimation(Player::ANIMATION::IDLE);
		player->SetPosition(GetPosition());
	}
}
