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
	m_vec2MoveVec = { 0,0 };
	SetPosition(_vec2Position);
}

Collider* Object::CreateRectCollider(COLLISION_TAG _eTag, bool _eEnabled, Vector2 _vecSize, Vector2 _vecOffset)
{
	RectCollider* collider = new RectCollider;
	collider->SetTarget(this);
	collider->Init(_eEnabled, _vecSize, _vecOffset);
	m_pColliderList.push_back(collider);

	SceneManager::GetInstance()->GetCurScene()->AddCollider(collider, _eTag);
	return collider;
}

Collider* Object::CreateCircleCollider(COLLISION_TAG _eTag, bool _eEnabled, float _fRadius, Vector2 _vecOffset)
{
	CircleCollider* collider = new CircleCollider;
	collider->SetTarget(this);
	collider->Init(_eEnabled, _fRadius, _vecOffset);
	m_pColliderList.push_back(collider);

	SceneManager::GetInstance()->GetCurScene()->AddCollider(collider, _eTag);
	return collider;
}

WallDetector* Object::CreateWallDetector(Vector2 _vec2Offset, float _fRadius)
{
	WallDetector* detector = new WallDetector;
	detector->Init(this, _vec2Offset, _fRadius);
	SceneManager::GetInstance()->GetCurScene()->AddWallDetector(detector);
	return detector;
}

void Object::ColliderRender(HDC _memDC)
{
	for (Collider* collider : m_pColliderList)
		collider->Render(_memDC);
}

