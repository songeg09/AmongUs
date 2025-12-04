#pragma once
#include "Actor.h"
#include "ResourceManager.h"
#include "Skill.h"

class Character abstract : public Actor 
{	
public:
	Character();
	~Character();
	virtual void Init(Vector2 _vec2Position);
	virtual void InitAnimation() = 0;
};