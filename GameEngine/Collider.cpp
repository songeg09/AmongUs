#include "pch.h"
#include "Collider.h"
#include "GDIManager.h"
#include "Actor.h"
#include "SceneManager.h"
#include "CollisionManager.h"

unsigned int Collider::s_uID = 0;

Collider::Collider(COLLISION_TAG _eTag)
	: m_uID(++s_uID), m_eTag(_eTag)
{
	m_vecOffset = {};
	m_vecPosition = {};
	m_iCollisionCount = 0;
	m_bEnabled = false;
	m_OnCollisioncallBack = nullptr;
	m_BeginCollisioncallBack = nullptr;
	m_EndCollisioncallBack = nullptr;
	m_eColliderType = COLLIDER_TYPE::RECTANGLE;

	CollisionManager::GetInstance()->RegistCollider(this);
}

Collider::~Collider()
{
	CollisionManager::GetInstance()->UnregistCollider(this);
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
	Vector2 vecObjectPosition = m_pTarget.lock()->GetPosition();
	m_vecPosition = vecObjectPosition + m_vecOffset;
}

RectCollider::RectCollider(COLLISION_TAG _eTag)
	:Collider(_eTag)
{
}

RectCollider::~RectCollider()
{
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

	Vector2 BackBufferTopLeftInScene = SceneManager::GetInstance()->GetCurScene()->GetBackBufferTopLeftInScene();
	Rectangle(_memDC,
		GetPosition().m_fx - BackBufferTopLeftInScene.m_fx - GetSize().m_fx / 2.0f,
		GetPosition().m_fy - BackBufferTopLeftInScene.m_fy - GetSize().m_fy / 2.0f,
		GetPosition().m_fx - BackBufferTopLeftInScene.m_fx + GetSize().m_fx / 2.0f,
		GetPosition().m_fy - BackBufferTopLeftInScene.m_fy + GetSize().m_fy / 2.0f
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

CircleCollider::CircleCollider(COLLISION_TAG _eTag)
	: Collider(_eTag)
{
}

CircleCollider::~CircleCollider()
{
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

	Vector2 BackBufferTopLeftInScene = SceneManager::GetInstance()->GetCurScene()->GetBackBufferTopLeftInScene();
	Ellipse(_memDC,
		GetPosition().m_fx - BackBufferTopLeftInScene.m_fx - GetSize(),
		GetPosition().m_fy - BackBufferTopLeftInScene.m_fy - GetSize(),
		GetPosition().m_fx - BackBufferTopLeftInScene.m_fx + GetSize(),
		GetPosition().m_fy - BackBufferTopLeftInScene.m_fy + GetSize());

	GDIManager::GetInstance()->ResetBrush(_memDC);
	GDIManager::GetInstance()->ResetPen(_memDC);
}
