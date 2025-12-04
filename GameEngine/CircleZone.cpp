#include "pch.h"
#include "CircleZone.h"
#include "ResourceManager.h"
#include "CircleZoneData.h"
#include "Collider.h"
#include "Object.h"

CircleZone::CircleZone()
{
	m_pCollider = nullptr;
}

CircleZone::~CircleZone()
{
}

void CircleZone::Init(COLLISION_TAG _eTag, float _fRadius, Object* _pTarget)
{
	SkillObject::Init(_pTarget);

	//m_pCollider = static_cast<CircleCollider*>(CreateCircleCollider(_eTag, true, _fRadius));
	//m_pCollider->SetBeginCollisionCallBack(
	//	[this](Collider* _pOther)
	//	{
	//		Object* actor = _pOther->GetTarget();
	//		if (actor != nullptr)
	//			m_TargetList.push_back(actor);
	//	}
	//);
	//m_pCollider->SetEndCollisionCallBack(
	//	[this](Collider* _pOther)
	//	{
	//		Object* actor = _pOther->GetTarget();
	//		if (actor != nullptr)
	//			m_TargetList.remove(actor);
	//	}
	//);
	//SetEnable(true);
}

void CircleZone::Update()
{
	if (m_bEnable == false)
		return;
	SkillObject::Update();
}

void CircleZone::Render(HDC _memDC)
{
	if (m_bEnable == false)
		return;
	Object::Render(_memDC);
}

void CircleZone::SetEnable(bool _bEnabled)
{
	m_bEnable = _bEnabled;
	if (m_pCollider != nullptr)
	{
		m_pCollider->SetEnable(m_bEnable);
	}
}

const Object* CircleZone::GetClosestTarget()
{
	Object* Closest = nullptr;
	float closestDist = FLT_MAX;

	std::list<Object*>::iterator it = m_TargetList.begin();
	float dist;

	while (it != m_TargetList.end())
	{
		dist = Vector2::Distance(GetPosition(),(*it)->GetPosition());
		if (dist < closestDist)
		{
			Closest = *it;
			closestDist = dist;
		}
		it++;
	}

	return Closest;
}
