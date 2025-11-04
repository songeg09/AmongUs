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

void RectZone::Init(int _iIndex, Object* _pTarget)
{
	SkillObject::Init(_pTarget);

	RectZoneData* data = static_cast<RectZoneData*>(ResourceManager::GetInstance()->GetData(L"RectZone.txt", _iIndex));
	assert(data != nullptr);
	if (m_pCollider == nullptr)
	{
		m_pCollider = static_cast<RectCollider*>(CreateRectCollider(true, data->GetSize()));
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
		m_pCollider->SetSize(data->GetSize());
		m_Animation.Reset();
	}
	SetEnable(true);
}

void RectZone::Update()
{
	if (m_bEnable == false)
		return;
	SkillObject::Update();
	m_Animation.Update();
}

void RectZone::Render(HDC _memDC)
{
	if (m_bEnable == false)
		return;
	Object::Render(_memDC);
	m_Animation.Render(_memDC, Object::GetPosition());
}

void RectZone::SetEnable(bool _bEnabled)
{
	m_bEnable = _bEnabled;
	if (m_pCollider != nullptr)
	{
		m_pCollider->SetEnable(m_bEnable);
	}
}
