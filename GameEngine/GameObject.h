#pragma once
#include "Object.h"
#include "Interactable.h"

class GameObject : public Object, public Interactable
{
protected:
	Collider*				m_pInteractRange;
	std::function<void()>	m_funcInteractCallback;

public:
	GameObject();
	~GameObject();

	void Update() override;
	virtual void Init(Vector2 _vec2Position, Vector2 _colliderSize, std::function<void()> _funcInteractCallback);
	virtual void Interact(Character* _Interactor);
	Vector2 GetPosition() override;
	void OnSuccess() override;
};

