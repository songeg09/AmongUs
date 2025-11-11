#include "pch.h"
#include "GameObject.h"
#include "Collider.h"

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Init(Vector2 _vec2Position)
{
	Object::Init(_vec2Position);
	m_pInteractRange = CreateRectCollider(COLLISION_TAG::OBJECT_INTERACTION_DETECTOR, true, Vector2(10, 10));
}

void GameObject::Interact()
{
	//m_pInteractRange->SetEnable(false);
}

Vector2 GameObject::GetPosition()
{
	return Object::GetPosition();
}

