#include "pch.h"
#include "GameObject.h"
#include "Collider.h"


GameObject::GameObject()
{
	m_pInteractRange = nullptr;
	m_funcInteractCallback = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{

}

void GameObject::Init(Vector2 _vec2Position, Vector2 _colliderSize, std::function<void()> _funcInteractCallback)
{
	Object::Init(_vec2Position);
	m_pInteractRange = CreateRectCollider(COLLISION_TAG::OBJECT_INTERACTION_DETECTOR, true, _colliderSize, Vector2(0, 0));
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

