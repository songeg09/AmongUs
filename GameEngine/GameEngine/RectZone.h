#pragma once
#include"SkillObject.h"
#include "Animation.h"

class Actor;
class RectCollider;
class RectZone : public SkillObject
{
protected:
	std::list<Actor*> m_TargetList;
	RectCollider* m_pCollider;
	Animation m_Animation;
public:
	RectZone();
	~RectZone();
	void Init(int _iIndex, Object* _pTarget = nullptr);
	void Update() override;
	void Render(HDC _memDC) override;
	void SetEnable(bool _bEnabled) override;
	const std::list<Actor*>& GetTargetList() { return m_TargetList; }
};

