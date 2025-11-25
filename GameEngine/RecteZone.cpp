#include "pch.h"
#include "RectZone.h"
#include "ResourceManager.h"
#include "Collider.h"
#include "Actor.h"
#include "RectZoneData.h"

RectZone::RectZone()
{
	m_pCollider = nullptr;
}

RectZone::~RectZone()
{
}

void RectZone::Init(COLLISION_TAG _eTag, Vector2 _Size, Object* _pTarget)
{
	SkillObject::Init(_pTarget);

	m_pCollider = static_cast<RectCollider*>(CreateRectCollider(_eTag, true, _Size));
	m_pCollider->SetBeginCollisionCallBack(
		[this](Collider* _pOther)
		{
			Object* actor = _pOther->GetTarget();
			if (actor != nullptr)
				m_TargetList.push_back(actor);
		}
	);
	m_pCollider->SetEndCollisionCallBack(
		[this](Collider* _pOther)
		{
			Object* actor = _pOther->GetTarget();
			if (actor != nullptr)
				m_TargetList.remove(actor);
		}
	);
	SetEnable(true);

}

void RectZone::Update()
{
	if (m_bEnable == false)
		return;
	SkillObject::Update();
}

void RectZone::Render(HDC _memDC)
{
	if (m_bEnable == false)
		return;
	Object::Render(_memDC);
}

void RectZone::SetEnable(bool _bEnabled)
{
	m_bEnable = _bEnabled;
	if (m_pCollider != nullptr)
	{
		m_pCollider->SetEnable(m_bEnable);
	}
}

const Object* RectZone::GetClosestTarget()
{
	Object* Closest = nullptr;
	float closestDist = FLT_MAX;

	std::list<Object*>::iterator it = m_TargetList.begin();
	float dist;

	while (it != m_TargetList.end())
	{
		dist = Vector2::Distance(GetPosition(), (*it)->GetPosition());
		if (dist < closestDist)
		{
			Closest = *it;
			closestDist = dist;
		}
		it++;
	}

	return Closest;
}
