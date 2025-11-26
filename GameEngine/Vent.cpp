#include "pch.h"
#include "Vent.h"
#include "Player.h"

Vent::Vent()
{
	m_pInteractRange = nullptr;
}

Vent::~Vent()
{
}

void Vent::Update()
{
}

void Vent::Init(Vector2 _vec2Position)
{
	Object::Init(_vec2Position);
	m_pInteractRange = CreateRectCollider(COLLISION_TAG::OBJECT_INTERACTION_DETECTOR,true, ConstValue::vec2VentSize);
}

void Vent::Interact(Character* _Interactor)
{
	if (Player* player = static_cast<Player*>(_Interactor))
	{
		player->SetPosition(GetPosition());
		player->Hide();
	}
}
