#include "pch.h"
#include "Actor.h"
#include "TimerManager.h"

Actor::Actor()
{
	m_bMovable = true;
	m_iCurAnimation = -1;
	m_eDirection = DIRECTION::RIGHT;
	m_fMoveSpeed = 100.0f;
}

Actor::~Actor()
{
}

void Actor::Move(Vector2 _vec2Force)
{
	if (m_bMovable == false)
		return;
	if (_vec2Force.isValid() == false)
		return;

	_vec2Force.Normalize();
	_vec2Force *= (m_fMoveSpeed * TimerManager::GetInstance()->GetfDeltaTime());
	Object::AddPosition(_vec2Force);
	if (_vec2Force.m_fx < 0.0f)
		SetDirection(DIRECTION::LEFT);
	else if (_vec2Force.m_fx > 0.0f)
		SetDirection(DIRECTION::RIGHT);
}

void Actor::ResizeAnimation(int _iSize)
{
	for(int i=0; i<2; ++i)
		m_AnimationList[i].resize(_iSize);
}

void Actor::InitAnimation(int _iIndex, AnimationData _data)
{
	m_AnimationList[DIRECTION::RIGHT][_iIndex].Init(_data.GetTextureType(), _data.GetPosition(), _data.GetSize(), 
		_data.GetMargin(), _data.GetLength(), false, _data.GetAnimationType(), _data.GetDuration(), _data.GetAnchor());

	m_AnimationList[DIRECTION::LEFT][_iIndex].Init(_data.GetTextureType(), _data.GetPosition(), _data.GetSize(),
		_data.GetMargin(), _data.GetLength(), true, _data.GetAnimationType(), _data.GetDuration(), _data.GetAnchor());
}

void Actor::SetAnimationEvent(int _iIndex, int _iTextureIndex, std::function<void()> _pCallBack)
{
	for (int i = 0; i < 2; ++i)
	{
		m_AnimationList[i][_iIndex].SetEvent(_iTextureIndex, _pCallBack);
	}
}

void Actor::Update()
{
	assert(m_iCurAnimation != -1);
	m_AnimationList[m_eDirection][m_iCurAnimation].Update();

	if (m_vec2Force.isValid())
	{
		Vector2 vec2Friction = (m_vec2Force * ConstValue::fFrictionCoefficient) * TimerManager::GetInstance()->GetfDeltaTime();
		m_vec2Force -= vec2Friction;
		m_vec2Force.ZeroSet();
		Object::AddPosition(m_vec2Force * TimerManager::GetInstance()->GetfDeltaTime());
	}
}

void Actor::Render(HDC _memDC)
{
	Object::Render(_memDC);
	m_AnimationList[m_eDirection][m_iCurAnimation].Render(_memDC, Object::GetPosition());
}

void Actor::Init(Vector2 _vec2Position)
{
	Object::Init(_vec2Position);
}

void Actor::SetAnimation(int _iIndex)
{
	if (m_iCurAnimation == _iIndex)
		return;
	m_iCurAnimation = _iIndex;
	m_AnimationList[m_eDirection][m_iCurAnimation].Reset();
}
