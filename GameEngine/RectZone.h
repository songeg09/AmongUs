#pragma once
#include"SkillObject.h"
#include "Animation.h"

class Object;
class RectCollider;
class RectZone : public SkillObject
{
protected:
	std::list<Object*> m_TargetList;
	RectCollider* m_pCollider;

public:
	RectZone();
	~RectZone();
	void Init(COLLISION_TAG _eTag, Vector2 _Size, Object* _pTarget = nullptr);
	void Update() override;
	void Render(HDC _memDC) override;
	void SetEnable(bool _bEnabled) override;
	const std::list<Object*>& GetTargetList() { return m_TargetList; }
	const Object* GetClosestTarget();

	bool HasAny() { return m_TargetList.size() > 0; }
};

