#include "pch.h"
#include "CircleZone.h"
#include "ResourceManager.h"
#include "CircleZoneData.h"
#include "Collider.h"
#include "Actor.h"

CircleZone::CircleZone()
{
	m_pCollider = nullptr;
}

CircleZone::~CircleZone()
{
}

void CircleZone::Init(int _iIndex, Object* _pTarget)
{
	SkillObject::Init(_pTarget);

	CircleZoneData* data = static_cast<CircleZoneData*>(ResourceManager::GetInstance()->GetData(L"CircleZone.txt", _iIndex));

	if (m_pCollider == nullptr)
	{
		m_pCollider = static_cast<CircleCollider*>(CreateCircleCollider(true, data->GetRadius()));
		m_pCollider->SetBeginCollisionCallBack(
			[this](Collider* _pOther)
			{
				Actor* actor = dynamic_cast<Actor*>(_pOther->GetTarget());
				if (actor != nullptr)
					m_TargetList.push_back(actor);
			}
		);
		m_pCollider->SetEndCollisionCallBack(
			[this](Collider* _pOther)
			{
				Actor* actor = dynamic_cast<Actor*>(_pOther->GetTarget());
				if (actor != nullptr)
					m_TargetList.remove(actor);
			}
		);
		m_Animation.Init(data->GetAnimationStart(), data->GetAnimationEnd(), ANIMATION_TYPE::LOOP, 0.3f, ANCHOR::CENTER);
	}
	else
	{
		m_pCollider->SetEnable(true);
		m_pCollider->SetSize(data->GetRadius());
		m_Animation.Reset();
	}
	SetEnable(true);
}

void CircleZone::Update()
{
	if (m_bEnable == false)
		return;
	SkillObject::Update();
	m_Animation.Update();
}

void CircleZone::Render(HDC _memDC)
{
	if (m_bEnable == false)
		return;
	Object::Render(_memDC);
	m_Animation.Render(_memDC, Object::GetPosition());
}

void CircleZone::SetEnable(bool _bEnabled)
{
	m_bEnable = _bEnabled;
	if (m_pCollider != nullptr)
	{
		m_pCollider->SetEnable(m_bEnable);
	}
}
