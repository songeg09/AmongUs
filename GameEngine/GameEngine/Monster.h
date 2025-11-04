#pragma once
#include"Actor.h"
#include"ResourceManager.h"
class Monster : public Actor
{
	enum ANIMATION
	{
		IDLE,
		END
	};
private:
public:
	Monster();
	~Monster();
	virtual void Init(Vector2 _vec2Position);
	virtual void Update() override;
	virtual void Render(HDC _memDC) override;
	virtual void Attack(Collider* _pOther) override;
};