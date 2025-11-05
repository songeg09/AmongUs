#include "pch.h"
#include "Object.h"
#include "Texture.h"
#include "Collider.h"

Object::Object()
{
	m_vec2Position = {};
	m_vec2Scale = {};
}

Object::~Object()
{
	for (Collider* collider : m_pColliderList)
		delete collider;
	m_pColliderList.clear();
}

void Object::LateUpdate()
{
	for (Collider* collider : m_pColliderList)
		collider->FinalUpdate();
}

void Object::Render(HDC _memDC)
{
	ColliderRender(_memDC);
}

void Object::Init(Vector2 _vec2Position)
{
	SetPosition(_vec2Position);
}

Collider* Object::CreateRectCollider(bool _eEnabled, Vector2 _vecSize, Vector2 _vecOffset)
{
	RectCollider* collider = new RectCollider;
	collider->SetTarget(this);
	collider->Init(_eEnabled, _vecSize, _vecOffset);
	m_pColliderList.push_back(collider);
	return collider;
}

Collider* Object::CreateCircleCollider(bool _eEnabled, float _fRadius, Vector2 _vecOffset)
{
	CircleCollider* collider = new CircleCollider;
	collider->SetTarget(this);
	collider->Init(_eEnabled, _fRadius, _vecOffset);
	m_pColliderList.push_back(collider);
	return collider;
}

void Object::ColliderRender(HDC _memDC)
{
	for (Collider* collider : m_pColliderList)
		collider->Render(_memDC);
}

