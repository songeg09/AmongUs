#include "pch.h"
#include "SwordBeamObject.h"
#include "TimerManager.h"
#include "Collider.h"
#include "Actor.h"

void SwordBeamObject::Init(int _iIndex, DIRECTION _eDirection, Vector2 _vec2InitialPos, float _fRange, float _fSpeed)
{
	//RectZone::Init(_iIndex);
	SkillObject::Init(nullptr);
	m_eDirection = _eDirection;
	m_vec2InitialPos = _vec2InitialPos + GetDirectionVector(m_eDirection) * 20.f;
	m_fRange = _fRange;
	m_fSpeed = _fSpeed;
	m_vec2DestPos = m_vec2InitialPos + GetDirectionVector(m_eDirection) * _fRange;

	if (m_pCollider == nullptr)
	{
		m_pCollider = static_cast<RectCollider*>(CreateRectCollider(true, Vector2(64,64)));
		m_pCollider->SetBeginCollisionCallBack(
			[this](Collider* _pOther)
			{
				Actor* actor = dynamic_cast<Actor*>(_pOther->GetTarget());
				if (actor != nullptr)
				{
					Vector2 ForceDirection = _pOther->GetPosition() - GetPosition();
					ForceDirection.Normalize();
					actor->AddForce(ForceDirection * 300.0f);
				}
			}
		);
		m_Animation.Init(TEXTURE_TYPE::EFFECT, 0, 0,7,64, ANIMATION_TYPE::LOOP, 0.3f, ANCHOR::CENTER);
	}
	else
	{
		m_pCollider->SetEnable(true);
		m_pCollider->SetSize(Vector2(64, 64));
		m_Animation.Reset();
	}
	SetEnable(true);
}

void SwordBeamObject::Update()
{
	if (m_bEnable == false)
		return;
	
	float TargetDist = (m_vec2DestPos - m_vec2InitialPos).Length();
	float ActualDist = (GetPosition() - m_vec2InitialPos).Length();
	if (ActualDist >= TargetDist)
	{
		RectZone::SetEnable(false);
	}
	else
	{
		Vector2 MoveDirection = GetDirectionVector(m_eDirection);
		MoveDirection *= m_fSpeed * TimerManager::GetInstance()->GetfDeltaTime();
		SetPosition(GetPosition() + MoveDirection);
	}

	SkillObject::Update();
	RectZone::Update();
}

Vector2 SwordBeamObject::GetDirectionVector(DIRECTION _direction)
{
	switch (_direction)
	{
	case DIRECTION::DOWN:
		return Vector2(0, 1);
	case DIRECTION::UP:
		return Vector2(0, -1);
	case DIRECTION::LEFT:
		return Vector2(-1, 0);
	case DIRECTION::RIGHT:
		return Vector2(1, 0);
	default:
		return Vector2(0, 0);
	}
}
