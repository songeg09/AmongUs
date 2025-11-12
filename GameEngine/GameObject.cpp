#include "pch.h"
#include "GameObject.h"
#include "Collider.h"


GameObject::GameObject()
{
	m_pInteractRange = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}


Vector2 GameObject::GetPosition()
{
	return Object::GetPosition();
}

