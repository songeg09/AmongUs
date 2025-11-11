#pragma once
#include "Character.h";

class Crew : public Character
{
private:
	Collider* m_pCrewCollider;

public:
	void Init(Vector2 _vec2Position) override;
};

