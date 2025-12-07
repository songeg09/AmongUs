#include "pch.h"
#include "GameObject.h"
#include "Collider.h"
#include "TimerManager.h"


GameObject::GameObject()
{
	m_pInteractRange = nullptr;
	m_funcInteractCallback = nullptr;
	m_pSoundCollider = nullptr;
	m_fAlarmTime = 0.0f;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
	if (m_pSoundCollider->isEnable() == true)
	{
		m_fAlarmTime += TimerManager::GetInstance()->GetfDeltaTime();

		if (m_fAlarmTime >= ConstValue::fAlarmDuration)
			m_pSoundCollider->SetEnable(false);
	}
}

void GameObject::Init(Vector2 _vec2Position, Vector2 _colliderSize, std::function<void()> _funcInteractCallback)
{
	Object::Init(_vec2Position);
	m_pInteractRange = CreateRectCollider(COLLISION_TAG::OBJECT_INTERACTION_DETECTOR, true, _colliderSize, Vector2(0, 0));
	m_pSoundCollider = CreateCircleCollider(COLLISION_TAG::SOUND, false, 50.0f);
	m_funcInteractCallback = _funcInteractCallback;
}

void GameObject::Interact(Character* _Interactor)
{
	m_funcInteractCallback();
}

Vector2 GameObject::GetPosition()
{
	return Object::GetPosition();
}

void GameObject::OnSuccess()
{
	m_pInteractRange->SetEnable(false);
	m_pSoundCollider->SetEnable(false);
}

void GameObject::OnFail()
{
	m_pSoundCollider->SetEnable(true);
	m_fAlarmTime = 0.0f;
}

