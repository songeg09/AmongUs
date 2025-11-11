#pragma once
#include "Actor.h"
#include "ResourceManager.h"
#include "Skill.h"

class Character abstract : public Actor 
{	
public:
	enum CHARACTER_STATE
	{
		ALIVE,
		DEAD,
	};

	enum ANIMATION
	{
		IDLE,
		RUN,
		GHOST,
		END,
	};

protected:
	bool m_bInput;
	CHARACTER_STATE m_eState;
	Collider* m_pWallCollider;
	std::vector<Skill*> m_Skills;
	
public:
	Character();
	virtual ~Character();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	void SetInput(bool _bInput) { m_bInput = _bInput; }
	void InitAnimation();
};