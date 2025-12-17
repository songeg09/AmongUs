#pragma once
#include "Object.h"
#include "IAttemptable.h"

class GameObject : public Object, public IAttemptable
{
protected:
	std::shared_ptr<Collider>		m_pInteractRange;
	std::shared_ptr<Collider>		m_pSoundCollider;
	std::function<void()>			m_funcInteractCallback;
	float							m_fAlarmTime;

public:
	GameObject();
	~GameObject();

	void Update() override;
	virtual void Init(Vector2 _vec2Position, Vector2 _colliderSize, std::function<void()> _funcInteractCallback);
	virtual void Interact(Character* _Interactor) override;
	Vector2 GetPosition() override;
	void OnSuccess() override;
	void OnFail() override;
};

