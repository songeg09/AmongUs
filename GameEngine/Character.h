#pragma once
#include "Actor.h"
#include "ResourceManager.h"
#include "Skill.h"

class Character abstract : public Actor 
{	
protected:
	Collider* m_pWallCollider;
	std::vector<Skill*> m_Skills;
	
public:
	Character();
	virtual ~Character();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	virtual void InitAnimation() = 0;
	virtual void SetState(int _iIndex) = 0;
};