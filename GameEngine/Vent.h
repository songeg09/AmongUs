#pragma once
#include "Object.h"
#include "IInteractable.h"

class Vent : public Object, public IInteractable
{
private:
	std::shared_ptr<Collider> m_pInteractRange;

public:
	Vent();
	~Vent();

	void Update() override;
	virtual void Init(Vector2 _vec2Position);
	virtual void Interact(Character* _Interactor) override;
	Vector2 GetPosition() override { return Object::GetPosition(); };
};

