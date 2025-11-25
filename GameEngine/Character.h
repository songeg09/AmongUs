#pragma once
#include "Actor.h"
#include "ResourceManager.h"
#include "Skill.h"

class Character abstract : public Actor 
{	
public:
	Character();
	virtual ~Character();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	virtual void InitAnimation() = 0;
};