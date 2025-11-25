#pragma once
#include"SkillObject.h"
#include "Animation.h"

class Object;
class CircleCollider;
class CircleZone : public SkillObject
{
private:
	std::list<Object*> m_TargetList;
	CircleCollider* m_pCollider;
public:
	CircleZone();
	~CircleZone();
	void Init(COLLISION_TAG _eTag, float _fRadius, Object* _pTarget = nullptr);
	void Update() override;
	void Render(HDC _memDC) override;
	void SetEnable(bool _bEnabled) override;
	const std::list<Object*>& GetTargetList() { return m_TargetList; }
	const Object* GetClosestTarget();

	bool HasAny() { return m_TargetList.size() > 0; }
};

