#include "pch.h"
#include "Collider.h"
#include "GDIManager.h"
#include "Actor.h"

unsigned int Collider::s_uID = 0;

Collider::Collider() 
	: m_uID(++s_uID)
{
	m_vecOffset = {};
	m_vecPosition = {};
	m_pTarget = nullptr;
	m_iCollisionCount = 0;
	m_bEnabled = false;
	m_OnCollisioncallBack = nullptr;
	m_BeginCollisioncallBack = nullptr;
	m_EndCollisioncallBack = nullptr;
}

Collider::~Collider()
{
}

void Collider::Init(bool _bEnabled, Vector2 _vecOffset)
{
	m_vecOffset = _vecOffset;
	m_bEnabled = _bEnabled;
}

void Collider::OnCollision(Collider* _pOther)
{
	if (m_OnCollisioncallBack != nullptr)
		m_OnCollisioncallBack(_pOther);
}

void Collider::BeginCollision(Collider* _pOther)
{
	m_iCollisionCount += 1;
	if (m_BeginCollisioncallBack != nullptr)
		m_BeginCollisioncallBack(_pOther);
}

void Collider::EndCollision(Collider* _pOther)
{
	m_iCollisionCount -= 1;
	assert(m_iCollisionCount >= 0);
	if (m_EndCollisioncallBack != nullptr)
		m_EndCollisioncallBack(_pOther);
}

void Collider::FinalUpdate()
{
	Vector2 vecObjectPosition = m_pTarget->GetPosition();
	Actor* Owner = dynamic_cast<Actor*>(m_pTarget);
	if (Owner == nullptr)
	{
		m_vecPosition = vecObjectPosition + m_vecOffset;
	}
	else
	{
		switch (Owner->GetDirection())
		{
		case DIRECTION::LEFT:
			m_vecPosition.m_fx = vecObjectPosition.m_fx - m_vecOffset.m_fy;
			m_vecPosition.m_fy = vecObjectPosition.m_fy + m_vecOffset.m_fx;
			break;
		case DIRECTION::RIGHT:
			m_vecPosition.m_fx = vecObjectPosition.m_fx + m_vecOffset.m_fy;
			m_vecPosition.m_fy = vecObjectPosition.m_fy - m_vecOffset.m_fx;
			break;
		case DIRECTION::UP:
			m_vecPosition.m_fx = vecObjectPosition.m_fx - m_vecOffset.m_fx;
			m_vecPosition.m_fy = vecObjectPosition.m_fy - m_vecOffset.m_fy;
			break;
		case DIRECTION::DOWN:
			m_vecPosition.m_fx = vecObjectPosition.m_fx + m_vecOffset.m_fx;
			m_vecPosition.m_fy = vecObjectPosition.m_fy + m_vecOffset.m_fy;
			break;
		}
	}
}

void RectCollider::Init(bool _bEnabled, Vector2 _vecSize, Vector2 _vecOffset)
{
	Collider::Init(_bEnabled, _vecOffset);
	Collider::SetType(COLLIDER_TYPE::RECTANGLE);
	SetSize(_vecSize);
}

void RectCollider::Render(HDC _memDC)
{
	if (isEnable() == false)
		return;
	GDIManager::GetInstance()->SetBrush(_memDC, BRUSH_TYPE::HOLLOW);
	if (GetCollisionCount() > 0)
		GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::RED);
	else
		GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::BLUE);

	Rectangle(_memDC,
		GetPosition().m_fx - GetSize().m_fx / 2.0f,
		GetPosition().m_fy - GetSize().m_fy / 2.0f,
		GetPosition().m_fx + GetSize().m_fx / 2.0f,
		GetPosition().m_fy + GetSize().m_fy / 2.0f
	);

	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}

Rect RectCollider::GetRect()
{
	return Rect{ GetPosition().m_fx - GetSize().m_fx / 2.0f,
		GetPosition().m_fy - GetSize().m_fy / 2.0f,
		GetPosition().m_fx + GetSize().m_fx / 2.0f,
		GetPosition().m_fy + GetSize().m_fy / 2.0f };
}

void CircleCollider::Init(bool _bEnabled, float _fRadius, Vector2 _vecOffset)
{
	Collider::Init(_bEnabled, _vecOffset);
	Collider::SetType(COLLIDER_TYPE::CIRCLE);
	SetSize(_fRadius);
}

void CircleCollider::Render(HDC _memDC)
{
	if (isEnable() == false)
		return;
	GDIManager::GetInstance()->SetBrush(_memDC, BRUSH_TYPE::HOLLOW);
	if (GetCollisionCount() > 0)
		GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::RED);
	else
	{
		GDIManager::GetInstance()->SetPen(_memDC, PEN_TYPE::BLUE);
	}
	Ellipse(_memDC,
		GetPosition().m_fx - GetSize(),
		GetPosition().m_fy - GetSize(),
		GetPosition().m_fx + GetSize(),
		GetPosition().m_fy + GetSize());

	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}
