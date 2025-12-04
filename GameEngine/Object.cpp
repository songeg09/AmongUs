#include "pch.h"
#include "Object.h"
#include "Texture.h"
#include "Collider.h"
#include "SceneManager.h"
#include "Scene.h"
#include "WallDetector.h"

Object::Object()
{
	m_vec2Position = {};
	m_vec2Scale = {};
}

Object::~Object()
{
	//for (Collider* collider : m_pColliderList)
	//	delete collider;
	//m_pColliderList.clear();
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
	m_vec2MoveVec = { 0,0 };
	SetPosition(_vec2Position);
}

std::unique_ptr<Collider>Object::CreateRectCollider(COLLISION_TAG _eTag, bool _eEnabled, Vector2 _vecSize, Vector2 _vecOffset)
{
	std::unique_ptr<RectCollider> collider = std::make_unique<RectCollider>(_eTag);
	collider->SetTarget(this);
	collider->Init(_eEnabled, _vecSize, _vecOffset);
	m_pColliderList.push_back(collider.get());

	return collider;
}

std::unique_ptr<Collider> Object::CreateCircleCollider(COLLISION_TAG _eTag, bool _eEnabled, float _fRadius, Vector2 _vecOffset)
{
	std::unique_ptr<CircleCollider> collider = std::make_unique<CircleCollider>(_eTag);
	collider->SetTarget(this);
	collider->Init(_eEnabled, _fRadius, _vecOffset);
	m_pColliderList.push_back(collider.get());

	return collider;
}

std::unique_ptr<WallDetector> Object::CreateWallDetector(Object* _Owner, Vector2 _vec2Offset, float _fRadius)
{
	std::unique_ptr<WallDetector> wallDetector = std::make_unique<WallDetector>();
	wallDetector->Init(_Owner, Vector2(0, 40), 20.0f);
	return wallDetector;
}


void Object::ColliderRender(HDC _memDC)
{
	for (Collider* collider : m_pColliderList)
		collider->Render(_memDC);
}

