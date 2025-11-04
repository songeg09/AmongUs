#pragma once
#include"SkillObject.h"
#include "Animation.h"

class Actor;
class CircleCollider;
class CircleZone : public SkillObject
{
private:
	std::list<Actor*> m_TargetList;
	CircleCollider* m_pCollider;
	Animation m_Animation;
public:
	CircleZone();
	~CircleZone();
	void Init(int _iIndex, Object* _pTarget = nullptr);
	void Update() override;
	void Render(HDC _memDC) override;
	void SetEnable(bool _bEnabled) override;
	const std::list<Actor*>& GetTargetList() { return m_TargetList; }
};

