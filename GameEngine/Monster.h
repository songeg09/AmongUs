#pragma once
#include "Character.h"

class Monster : public Character
{
private:
	Collider* m_pPlayerDetectCollider;
	Collider* m_pAttackRangeCollider;
public:
	Monster();
	~Monster();

	void Init(Vector2 _vec2Position) override;
	virtual void Update() override;
};

