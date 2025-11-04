#include "pch.h"
#include "Actor.h"
#include "TimerManager.h"

Actor::Actor()
{
	m_bMovable = true;
	m_iCurAnimation = -1;
	m_eDirection = DIRECTION::DOWN;
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
	else if (_vec2Force.m_fy < 0.0f)
		SetDirection(DIRECTION::UP);
	else if (_vec2Force.m_fy > 0.0f)
		SetDirection(DIRECTION::DOWN);
}

void Actor::ResizeAnimation(int _iSize)
{
	for (int i = DIRECTION::START; i != DIRECTION::END; ++i)
		m_AnimationList[i].resize(_iSize);
}

void Actor::InitAnimation(int _iIndex, int _iStartTextureIndex, int _iEndTextureIndex,
	float _fPlaySpeed, ANIMATION_TYPE _eAnimationType, ANCHOR _eAnchor)
{
	std::vector<AnimNode> vecAnimationList;
	for (int i = DIRECTION::START; i != DIRECTION::END; ++i)
	{
		assert(_iIndex < m_AnimationList[i].size());
		m_AnimationList[i][_iIndex].Init(static_cast<DIRECTION>(i), _iStartTextureIndex, _iEndTextureIndex, _eAnimationType, _fPlaySpeed, _eAnchor);
	}
}

void Actor::SetAnimationEvent(int _iIndex, int _iTextureIndex, std::function<void()> _pCallBack)
{
	for (int i = DIRECTION::START; i != DIRECTION::END; ++i)
	{
		assert(_iIndex < m_AnimationList[i].size());
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
