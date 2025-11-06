#pragma once
#include "Actor.h"
#include "ResourceManager.h"
#include "Skill.h"

class Character abstract : public Actor 
{	
private:
	bool m_bInput;
	Collider* m_pWallCollider;
	Collider* m_pInteractCollider;
	std::vector<Skill*> m_Skills;
	
public:
	enum ANIMATION
	{
		IDLE,
		RUN,
		//DEAD,
		END,
	};

	Character();
	~Character();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	void Input();
	void SetInput(bool _bInput) { m_bInput = _bInput; }
};